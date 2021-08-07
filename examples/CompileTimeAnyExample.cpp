#include <iostream>
#include "EasyDelegate.hpp"

using namespace EasyDelegate;

//    An important note. You cannot use TDelegateAny and TDelegateAnyCT at the 
//    same time due to some technical problems. The same is the case with the 
//    enumerator. When the problem is resolved, this will be indicated in the update.

enum class EEnumerator
{
    EIntDelegate,
    EBoolDelegate
};

//This declarations should be in cpp file
DeclareDelegateFuncCompileTime(EEnumerator, EEnumerator::EIntDelegate, int(int, int, bool))
DeclareDelegateFuncCompileTime(EEnumerator, EEnumerator::EBoolDelegate, bool(bool, bool))

        int foo(int x, int y, bool ts)
{
    return ts ? x : y;
}

class Foo
{
public:
    bool foo(bool ts, bool fs)
    {
        return ts && fs;
    }
};

int main()
{
    //Attaching function to abstract global delegate container
    TDelegateAnyCT<EEnumerator>::attach<EEnumerator::EIntDelegate>(&foo);
    //Calling function
    auto iresult = TDelegateAnyCT<EEnumerator>::eval<EEnumerator::EIntDelegate>(50, -50, false); 
    TDelegateAnyCT<EEnumerator>::detach<EEnumerator::EIntDelegate>();

    //Class example
    Foo boo;
    //Attach class method to delegate container
    TDelegateAnyCT<EEnumerator>::attach<EEnumerator::EBoolDelegate>(&boo, &Foo::foo);
    auto bresult = TDelegateAnyCT<EEnumerator>::eval<EEnumerator::EBoolDelegate>(true, true);
    TDelegateAnyCT<EEnumerator>::detach<EEnumerator::EBoolDelegate>();

    //And with lambda function
    TDelegateAnyCT<EEnumerator>::attach<EEnumerator::EBoolDelegate>([&](bool b, bool n)
    { 
        return boo.foo(b, n) || b; 
    });

    auto lresult = TDelegateAnyCT<EEnumerator>::eval<EEnumerator::EBoolDelegate>(true, false);
    TDelegateAnyCT<EEnumerator>::detach<EEnumerator::EBoolDelegate>();

    std::cout << lresult << std::endl;

    return 0;
}
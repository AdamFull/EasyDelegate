#include <iostream>
#include "EasyDelegate.hpp"

using namespace EasyDelegate;

//    An important note. You cannot use TDelegateAny and TDelegateAnyCT at the 
//    same time due to some technical problems. The same is the case with the 
//    enumerator. When the problem is resolved, this will be indicated in the update.

//Your enumerator type
enum class EEnumerator
{
    EIntDelegate,
    EBoolDelegate,
    EAnother
};

//This declarations should be in cpp file
DeclareDelegateFuncRuntime(EEnumerator, EEnumerator::EIntDelegate, int(int, int, bool))
DeclareDelegateFuncRuntime(EEnumerator, EEnumerator::EBoolDelegate, bool(bool, bool))
DeclareDelegateFuncRuntime(EEnumerator, EEnumerator::EAnother, void(int, int))

int foo(int x, int y, bool ts)
{
    return ts ? x : y;
}

void boob(int x, int y)
{
    std::cout << x + y << std::endl;
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
    //Declare any delegate object
    TDelegateAny<EEnumerator> _delegates;
    //Attach to static function 
    _delegates.attach<EEnumerator::EIntDelegate>(&foo);
    //Call function
    auto iresult = _delegates.eval<EEnumerator::EIntDelegate>(50, -50, false);

    //Now with class object (also you can use 'this', if your delegate inside a class)
    Foo boo;
    //Attach class method to delegate container
    _delegates.attach<EEnumerator::EBoolDelegate>(&boo, &Foo::foo); //Same with classes
    auto bresult = _delegates.eval<EEnumerator::EBoolDelegate>(true, true);
    _delegates.detach<EEnumerator::EBoolDelegate>();

    //Attaching existing delegate
    TDelegate<void(int, int)> AnotherDelegate;
    AnotherDelegate.attach(&boob);

    _delegates.attach<EEnumerator::EAnother>(std::move(AnotherDelegate));

    _delegates.execute<EEnumerator::EAnother>(1, 2);
    _delegates.execute<EEnumerator::EAnother>(2, 1);

    //And lambda functions
    _delegates.attach<EEnumerator::EBoolDelegate>([&](bool b, bool n)
    { 
        return boo.foo(b, n) || b;
    });

    auto lresult = _delegates.eval<EEnumerator::EBoolDelegate>(true, false);
    _delegates.detach<EEnumerator::EBoolDelegate>();

    std::cout << lresult << std::endl;

    return 0;
}

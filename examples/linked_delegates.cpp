#include <iostream>
#include "examples.h"
#include "EasyDelegate.hpp"

using namespace EasyDelegate;

//It's temporary method, will be changed soon
enum class EEnumerator
{
    EIntDelegate,
    EBoolDelegate
};

//DeclareDelegateFunc(EEnumerator, EEnumerator::EIntDelegate, int(int, int, bool))
//DeclareDelegateFunc(EEnumerator, EEnumerator::EBoolDelegate, bool(bool, bool))

namespace shared_delegates
{
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

    void linked_delegates_fun()
    {
        /*EasyDelegateAnyCT<EEnumerator> _delegates;                                          //Linker structure

        _delegates.CreateLink<EEnumerator::EIntDelegate>(&foo);              //Creating link to structure
        auto iresult = _delegates.Call<EEnumerator::EIntDelegate>(50, -50, false);       //Calling function
        _delegates.BreakLink<EEnumerator::EIntDelegate>();

        Foo boo;
        _delegates.CreateLink<EEnumerator::EBoolDelegate>(&boo, &Foo::foo);        //Same with classes
        auto bresult = _delegates.Call<EEnumerator::EBoolDelegate>(true, true);
        _delegates.BreakLink<EEnumerator::EBoolDelegate>();

        _delegates.CreateLink<EEnumerator::EBoolDelegate>([&](bool b, bool n)
        {
            return boo.foo(b, n) || b;
        });

        auto lresult = _delegates.Call<EEnumerator::EBoolDelegate>(true, false);
        _delegates.BreakLink<EEnumerator::EBoolDelegate>();

        std::cout << lresult << std::endl;*/
    }
}
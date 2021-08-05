#include <iostream>
#include "examples.h"
#include "EasyDelegate.hpp"

/** @example linked_delegates.cpp
 * How to use linked delegates. 
 * Examples */

//It's temporary method, will be changed soon
AddDelegateKeyword(intDelegate, 0)
AddDelegateKeyword(boolDelegate, 1)

DeclareDelegateFunc(intDelegate, int(int, int, bool))
DeclareDelegateFunc(boolDelegate, bool(bool, bool))

namespace linked_delegates
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
        FDelegates _delegates;                                          //Linker structure

        DelegateCreateLink<intDelegate>(_delegates, &foo);              //Creating link to structure
        auto iresult = DelegateCall<intDelegate>(_delegates, 50, -50, false);       //Calling function
        DelegateBreakLink<intDelegate>(_delegates);

        Foo boo;
        DelegateCreateLink<boolDelegate>(_delegates, &boo, &Foo::foo);        //Same with classes
        auto bresult = DelegateCall<boolDelegate>(_delegates, true, true);
        DelegateBreakLink<boolDelegate>(_delegates);

        DelegateCreateLink<boolDelegate>(_delegates, [&](bool b, bool n)
        {
            return boo.foo(b, n) || b;
        });

        auto lresult = DelegateCall<boolDelegate>(_delegates, true, false);
        DelegateBreakLink<boolDelegate>(_delegates);

        std::cout << lresult << std::endl;
    }
}
#include <iostream>
#include "examples.h"
#include "EasyDelegate.hpp"

/** @example manual_using.cpp
 * How to use EasyDelegate manuallity.
 * Examples */
namespace manual_using
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

    void manual_using_fun()
    {
        EasyDelegate<int(int, int, bool)> fooDelegate;          //Creating delegate object with specified signature
        fooDelegate.attach(&foo);                               //Attaching static function to delegate
        auto iresult = fooDelegate(5, 10, true);                               //Calling delegate function
        fooDelegate.detach();                                   //Removing function from delegate. After detach, you can attach another function.

        Foo fuf;
        EasyDelegate<bool(bool, bool)> fooClassDelegate;
        fooClassDelegate.attach(&fuf, &Foo::foo);
        auto bresult = fooClassDelegate(true, false);

        EasyDelegate<int(int, bool)> fooLambdaDelegate;         //Also you can attach lambda
        fooLambdaDelegate.attach([&](int i, bool b)              
        {
            return fuf.foo(b, i > 0) ? i*i : i * 2;
        });
        auto lresult = fooLambdaDelegate(iresult, bresult);
        std::cout << lresult << std::endl;
    }
}
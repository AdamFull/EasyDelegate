#include <iostream>
#include "examples/examples.h"
#include "EasyDelegateMultiImpl.hpp"

enum class EEnumerator
{
    EFirst,
    ESecond,
    EThird,
    EFourth
};

void foo(int x, int y)
{
    std::cout << x-y << std::endl;
}

void boo(int x, int y)
{
    std::cout << x+y << std::endl;
}

int ifoo(int x, int y)
{
    return x-y;
}

int iboo(int x, int y)
{
    return x+y;
}

class Foo
{
public:
    void foo(int x, int y)
    {
        std::cout << "Class foo: " << x/y << std::endl;
    }

    int boo(int x, int y)
    {
        return x * (x % y)*(x - y);
    }
};

int main()
{
    manual_using::manual_using_fun();
    linked_delegates::linked_delegates_fun();

    Foo cfoo;

    EasyDelegateMulti<EEnumerator, void(int, int)> MultDelegate;
    MultDelegate.attach<EEnumerator::EFirst>(&foo);
    MultDelegate.attach<EEnumerator::ESecond>(&boo);
    MultDelegate.attach<EEnumerator::EThird>(&cfoo, &Foo::foo);

    //MultDelegate<EEnumerator::EFirst>(5, 6);
    //MultDelegate<EEnumerator::ESecond>(5, 6);

    MultDelegate.execute(5, 6);

    EasyDelegateMulti<EEnumerator, int(int, int)> MultDelegateE;
    MultDelegateE.attach<EEnumerator::EFirst>(&ifoo);
    MultDelegateE.attach<EEnumerator::ESecond>(&iboo);
    MultDelegateE.attach<EEnumerator::EThird>([&](int x, int y)
    {
        return x*x - cfoo.boo(x*y, x%y) + y*y;
    });
    MultDelegateE.attach<EEnumerator::EFourth>(&cfoo, &Foo::boo);

    auto results = MultDelegateE.eval(5, 9);
    for(auto& [_key, _value] : results)
    {
        std::cout << _value << std::endl;
    }

    return 0;
}
#include "EasyDelegate.hpp"
#include <iostream>

using namespace EasyDelegate;

enum class EEnumerator
{
    EFirst,
    ESecond,
    EThird,
    EFourth,
    EAnother
};

void foo(int x, int y)
{
    std::cout << x - y << std::endl;
}

void boo(int x, int y)
{
    std::cout << x + y << std::endl;
}

int ifoo(int x, int y)
{
    return x - y;
}

int iboo(int x, int y)
{
    return x + y;
}

class Foo
{
public:
    void foo(int x, int y)
    {
        std::cout << "Class foo: " << x / y << std::endl;
    }

    int boo(int x, int y)
    {
        return x * (x % y) * (x - y);
    }
};

int main()
{
    Foo cfoo;

    //Declare multi delegate container
    TDelegateMulti<EEnumerator, void(int, int)> MultDelegate;
    //Attaching delegates
    MultDelegate.attach<EEnumerator::EFirst>(&foo);
    MultDelegate.attach<EEnumerator::ESecond>(&boo);
    MultDelegate.attach<EEnumerator::EThird>(&cfoo, &Foo::foo);

    //Attaching existing delegate
    TDelegate<void(int, int)> AnotherDelegate;
    AnotherDelegate.attach(&foo);

    MultDelegate.attach<EEnumerator::EAnother>(std::move(AnotherDelegate));

    //Executing all delegates
    MultDelegate.execute(5, 6);

    //Declare multi delegate container with another signature
    TDelegateMulti<EEnumerator, int(int, int)> MultDelegateE;
    MultDelegateE.attach<EEnumerator::EFirst>(&ifoo);
    MultDelegateE.attach<EEnumerator::ESecond>(&iboo);
    MultDelegateE.attach<EEnumerator::EThird>([&](int x, int y)
    { 
        return x * x - cfoo.boo(x * y, x % y) + y * y; 
    });
    MultDelegateE.attach<EEnumerator::EFourth>(&cfoo, &Foo::boo);

    //Evaluating all delegates
    auto results = MultDelegateE.eval(5, 9);
    for (auto &[_key, _value] : results)
    {
        std::cout << _value << std::endl;
    }

    return 0;
}
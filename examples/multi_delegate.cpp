#include "examples.h"
#include "EasyDelegateMultiImpl.hpp"
#include <iostream>

using namespace EasyDelegate;

namespace multi_delegate
{
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

    void multi_delegate_fun()
    {
        Foo cfoo;

        TDelegateMulti<EEnumerator, void(int, int)> MultDelegate;
        MultDelegate.attach<EEnumerator::EFirst>(&foo);
        MultDelegate.attach<EEnumerator::ESecond>(&boo);
        MultDelegate.attach<EEnumerator::EThird>(&cfoo, &Foo::foo);

        //MultDelegate<EEnumerator::EFirst>(5, 6);
        //MultDelegate<EEnumerator::ESecond>(5, 6);

        MultDelegate.execute(5, 6);

        TDelegateMulti<EEnumerator, int(int, int)> MultDelegateE;
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
    }
}
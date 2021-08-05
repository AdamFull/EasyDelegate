#include <iostream>
#include "EasyDelegate.hpp"

AddDelegateKeyword(fooCall, 0)
AddDelegateKeyword(fooClassCall, 1)
AddDelegateKeyword(pupaCall, 2)
AddDelegateKeyword(popopeCall, 3)

DeclareDelegateFunc(fooCall, void(int, int))
DeclareDelegateFunc(pupaCall, void())
DeclareDelegateFunc(popopeCall, bool(int, int))

void foo(int x, int y)
{
    std::cout << x + y << std::endl;
}

void pupa()
{
    std::cout << "pupa" << std::endl;
}

bool isXgreaterY(int x, int y)
{
    return x > y;
}

class foof
{
public:
    void foo(int x, int y)
    {
        std::cout << x + y << std::endl;
    }

    bool isX(int x, int y)
    {
        return static_cast<bool>(x) && !static_cast<bool>(y);
    }
};

int main()
{
    FDelegates _delegates;

    std::cout << "Static function with arguments" << std::endl;
    DelegateCreateLink<fooCall>(_delegates, &foo);
    DelegateCall<fooCall>(_delegates, 5, 5);
    DelegateBreakLink<fooCall>(_delegates);

    std::cout << "With class example" << std::endl;
    foof fooof;
    DelegateCreateLink<fooCall>(_delegates, &fooof, &foof::foo);
    DelegateCall<fooCall>(_delegates, 28, 22);
    DelegateBreakLink<fooCall>(_delegates);

    std::cout << "Void function with no args" << std::endl;
    DelegateCreateLink<pupaCall>(_delegates, &pupa);
    DelegateCall<pupaCall>(_delegates);
    DelegateBreakLink<pupaCall>(_delegates);

    std::cout << "Function with return value" << std::endl;
    DelegateCreateLink<popopeCall>(_delegates, &isXgreaterY);
    std::cout << DelegateCall<popopeCall>(_delegates, 6, 5) << std::endl;
    DelegateBreakLink<popopeCall>(_delegates);

    std::cout << "Class method with return value" << std::endl;
    DelegateCreateLink<popopeCall>(_delegates, &fooof, &foof::isX);
    std::cout << DelegateCall<popopeCall>(_delegates, 0, 5) << std::endl;
    DelegateBreakLink<popopeCall>(_delegates);

    return 0;
}
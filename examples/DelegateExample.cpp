#include <iostream>
#include "EasyDelegate.hpp"

using namespace EasyDelegate;

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
    //Creating delegate object with specified signature
    TDelegate<int(int, int, bool)> fooDelegate; 
    //Attaching static function to delegate
    fooDelegate.attach(&foo);         
    //Calling delegate function          
    auto iresult = fooDelegate(5, 10, true);    
    //Removing function from delegate. After detach, you can attach another function.
    fooDelegate.detach();             

    //Attaching in constructor
    TDelegate<int(int, int, bool)> fooConstructable(&foo);      
    iresult += fooConstructable(10, 5, false);   

    //Using delegate with class member
    Foo fuf;
    //Declare delegate with another signature
    TDelegate<bool(bool, bool)> fooClassDelegate;
    //Attaching reference to class and class method. Class method should be public, or static
    fooClassDelegate.attach(&fuf, &Foo::foo);
    //Executing delegate and getting result
    auto bresult = fooClassDelegate(true, false);

    //Attaching class method in constructor
    TDelegate<bool(bool, bool)> fooClassConstructable(&fuf, &Foo::foo);
    bresult = bresult && fooClassConstructable(false, true);

    //We can attach another function after detach
    fooClassDelegate.detach();
    //Also you can attach lambda
    fooClassDelegate.attach([&](bool f, bool s)
    {
        return fuf.foo(f, f || s);
    });

    //And another lambda
    TDelegate<int(int, bool)> fooLambdaDelegate;
    fooLambdaDelegate.attach([&](int i, bool b)
    { 
        auto subres = fooClassDelegate(i, b);
        return fuf.foo(b, i > 0) && subres ? i * i : i * 2; 
    });
    auto lresult = fooLambdaDelegate(iresult, bresult);
    std::cout << lresult << std::endl;

    return 0;
}

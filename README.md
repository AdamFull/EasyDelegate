# EasyDelegate
[![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2FAdamFull%2FEasyDelegate.svg?type=shield)](https://app.fossa.com/projects/git%2Bgithub.com%2FAdamFull%2FEasyDelegate?ref=badge_shield)

 
## Simple delegate system implementation using std::function.


### Examples

Example of use with a static function
```c++
    AddDelegateKeyword(fooCall, 0)
    DeclareDelegateFunc(fooCall, void(int, int))
    
    void foo(int x, int y)
    {
        std::cout << x + y << std::endl;
    }
    
    int main()
    {
        FDelegates _delegates;

        std::cout << "Static function with arguments" << std::endl;
        DelegateCreateLink<fooCall>(_delegates, &foo);
        DelegateCall<fooCall>(_delegates, 5, 5);
        DelegateBreakLink<fooCall>(_delegates);
    }
```

Example of use with a class method with args
```c++
    AddDelegateKeyword(fooCall, 0)
    DeclareDelegateFunc(fooCall, void(int, int))
    
    class foof
    {
    public:
        void foo(int x, int y)
        {
            std::cout << x + y << std::endl;
        }
    };
    
    int main()
    {
        FDelegates _delegates;

        std::cout << "With class example" << std::endl;
        foof fooof;
        DelegateCreateLink<fooCall>(_delegates, &fooof, &foof::foo);
        DelegateCall<fooCall>(_delegates, 28, 22);
        DelegateBreakLink<fooCall>(_delegates);
    }
```

Example with return type
```c++
    AddDelegateKeyword(fooCall, 0)
    DeclareDelegateFunc(popopeCall, bool(int, int))
    
    class foof
    {
    public:
        bool isX(int x, int y)
        {
            return static_cast<bool>(x) && !static_cast<bool>(y);
        }
    };
    
    int main()
    {
        FDelegates _delegates;

        std::cout << "With class example" << std::endl;
        foof fooof;
        DelegateCreateLink<fooCall>(_delegates, &fooof, &foof::foo);
        DelegateCall<fooCall>(_delegates, 28, 22);
        DelegateBreakLink<fooCall>(_delegates);
    }
```

Use manuality
```c++
    void foo(int x, int y)
    {
        std::cout << "foo:" << x+y << std::endl;
    }
    int main()
    {
        EasyDelegate<void(int, int)> fooDelegate;
        fooDelegate.attach(&foo);
        if(fooDelegate)
        {
            fooDelegate(5+5);
            fooDelegate.detach();
        }
    }
```

## License

MIT


[![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2FAdamFull%2FEasyDelegate.svg?type=large)](https://app.fossa.com/projects/git%2Bgithub.com%2FAdamFull%2FEasyDelegate?ref=badge_large)
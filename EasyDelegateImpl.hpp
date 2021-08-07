/**
 * MIT License
 * 
 * @copyright Copyright (c) 2021 AdamFull && range36rus
 *
 *Permission is hereby granted, free of charge, to any person obtaining a copy
 *of this software and associated documentation files (the "Software"), to deal
 *in the Software without restriction, including without limitation the rights
 *to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *copies of the Software, and to permit persons to whom the Software is
 *furnished to do so, subject to the following conditions:
 *
 *The above copyright notice and this permission notice shall be included in all
 *copies or substantial portions of the Software.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *SOFTWARE.
 */

#pragma once
#include <functional>
#include "EasyDelegateGlobalTemplates.hpp"

namespace EasyDelegate
{
    /**
     * @brief Implementation of a simple delegate based on the std::function functionality from 
     * the c++ standard library. Allows you to implement a functional object of a class 
     * method or a static function for further invocation. 
     * 
     * @tparam _Signature signature of the delegate function
     */
    template<class _Signature>
    class __Delegate
    {
    public:
        /**
         * @brief The method is intended for binding a lambda function to a delegate.
         * 
         * @tparam LabbdaFunction lambda function type transited with template parameter.
         * @param lfunc 
         */
        template<class _LabbdaFunction>
        void attach(_LabbdaFunction&& lfunc)
        {
            mDelegate = std::function(std::forward<_LabbdaFunction>(lfunc));
        }

        /**
         * @brief The method is intended for binding a static function to a delegate. 
         * A reference to the required function is passed as arguments.
         * 
         * @param args static function reference...
         * @return void
         */
        template<class ...Args>
        void attach(Args&&... args)
        {
            mDelegate = make_delegate(std::forward<Args>(args)...);
        }

        /**
         * @brief For class or const class method. Receiving class pointer and class method reference.
         * 
         * @param c Class pointer
         * @param m Method reference
         * 
         */
        template <class _Class, class _ReturnType, class ...Args>
        void attach(_Class* c, _ReturnType (_Class::*m)(Args...))
        {
            mDelegate = make_delegate(c, m);
        }

        /**
         * @brief Detaching function delegate
         * 
         */
        void detach()
        {
            mDelegate = nullptr;
        }

        /**
         * @brief Redefining the parenthesis operator for convenient delegate invocation
         * 
         * @tparam Args Templated std::tuple arguments 
         * @param args Delegate arguments 
         * @return auto 
         */
        template<class ...Args>
        auto operator()(Args&&... args)
        {
            return mDelegate(std::forward<Args>(args)...);
        }

        operator bool()
        {
            return static_cast<bool>(mDelegate);
        }

    private:
        std::function<_Signature> mDelegate;

    private:
        /**
         * @brief 
         * 
         * Implementation of creating a delegate for a static method.
         * 
         * @tparam ReturnType (set automatically in c++17) class type
         * @tparam Args (set automatically in c++17) another arguments
         * @param m reference to function
         * @return std::function<ReturnType(Args...)> 
         */
        template <class _ReturnType, class ...Args>
        std::function<_ReturnType(Args...)> make_delegate(_ReturnType (*m)(Args...))
        {
            return [=](Args&&... args) { return (*m)(std::forward<Args>(args)...); };
        }

        /**
         * @brief
         * 
         * Implementation of creating a delegate for a class.
         * 
         * @tparam Class (set automatically in c++17) class type
         * @tparam ReturnType (set automatically in c++17)
         * @tparam Args (set automatically in c++17)
         * @param c pointer to class
         * @param m reference to class method
         * @return std::function<ReturnType(Args...)> 
         */
        template <class _Class, class _ReturnType, class ...Args>
        std::function<_ReturnType(Args...)> make_delegate(_Class* c, _ReturnType (_Class::*m)(Args...))
        {
            return [=](Args&&... args) { return (c->*m)(std::forward<Args>(args)...); };
        }

        /**
         * @brief 
         * 
         * Implementation of creating a delegate for a constant class.
         * 
         * @tparam Class (set automatically in c++17)
         * @tparam ReturnType (set automatically in c++17)
         * @tparam Args (set automatically in c++17)
         * @param c const pointer to class
         * @param m reference to class method
         * @return std::function<ReturnType(Args...)> 
         */
        template <class _Class, class _ReturnType, class ... Args>
        std::function<_ReturnType(Args...)> make_delegate(const _Class* c, _ReturnType (_Class::*m)(Args...) const)
        {
            return [=](Args&&... args) { return (c->*m)(std::forward<Args>(args)...); };
        }
    };

    template<class _Signature>
    using TDelegate = __Delegate<_Signature>;
}

/**
 * @example DelegateExample
 * 
 * @code
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

    //Using delegate with class member
    Foo fuf;
    //Declare delegate with another signature
    TDelegate<bool(bool, bool)> fooClassDelegate;
    //Attaching reference to class and class method. Class method should be public, or static
    fooClassDelegate.attach(&fuf, &Foo::foo);
    //Executing delegate and getting result
    auto bresult = fooClassDelegate(true, false);

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
 *   @endcode
 * 
 */
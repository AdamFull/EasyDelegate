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
#include <map>
#include "EasyDelegateImpl.hpp"

namespace EasyDelegate
{
    /**
     * @brief Implementation of the ability to store multiple delegates with the same signature inside a single structure with a user-friendly interface
     * 
     * @tparam _Enumerator The enumerator class used for binding to a functional object
     * @tparam _Signature Signature of the function accepted by the delegate
     * @tparam _Comp Comparator for the enumerator
     */
    template<class _Enumerator, class _Signature, class _Comp>
    class __DelegateMulti
    {
    public:
        /**
         * @brief Attaching existing delegate if signature is same
         * 
         * @tparam eBase User defined enumeration key
         * @param _delegate existing delegate as r-value
         */
        template<_Enumerator eBase>
        inline void attach(__Delegate<_Signature>&& _delegate)
        {
            static_assert(std::is_same<
            std::remove_reference<decltype(_delegate)>::type, __Delegate<_Signature>>::value,
            "Attached delegate has diferent signatures." );
            m_Delegates.try_emplace(eBase, std::move(_delegate));
        }

        /**
         * @brief Attaches the passed method to the User defined enumeration key
         * 
         * @tparam eBase User defined enumeration key
         * @tparam LabbdaFunction Lambda object
         * @param lfunc 
         */
        template<_Enumerator eBase, class _LabbdaFunction>
        inline void attach(_LabbdaFunction&& lfunc)
        {
            __Delegate<_Signature> _delegate;
            _delegate.attach(std::forward<_LabbdaFunction>(lfunc));
            m_Delegates.emplace(eBase, std::move(_delegate));
        }

        /**
         * @brief Attaches the passed method to the User defined enumeration key
         * 
         * @tparam eBase User defined enumeration key
         * @tparam Args Templated std::tuple arguments 
         * @param args Delegate arguments
         */
        template<_Enumerator eBase, class ...Args>
        inline void attach(Args&&... args)
        {
            __Delegate<_Signature> _delegate;
            _delegate.attach(std::forward<Args>(args)...);
            m_Delegates.emplace(eBase, std::move(_delegate));
        }

        /**
         * @brief Detaching delegate from included std::map container
         * 
         * @tparam eBase User defined enumeration key
         */
        template<_Enumerator eBase>
        inline void detach()
        {
            m_Delegates.erase(eBase);
        }

        /**
         * @brief Executes the delegate for the specified enumerator
         * 
         * @tparam eBase User defined enumeration key
         * @tparam Args Templated std::tuple arguments 
         * @param args Delegate arguments
         */
        template<_Enumerator eBase, class ...Args>
        inline void execute(Args&&... args)
        {
            using return_type = typename __SignatureDesc<_Signature>::return_type;
            //Checking for the correctness of the type used
            static_assert(std::is_same<return_type, void>::value, "Trying to execute delegates with return type 'non-void'. For 'non-void' you should use 'eval' method.");

            m_Delegates[eBase](std::forward<Args>(args)...);
        }

        /**
         * @brief Executes all the delegates that were attached to the object
         * 
         * @tparam Args Templated std::tuple arguments 
         * @param args Delegate arguments
         */
        template<class ...Args>
        inline void execute(Args&&... args)
        {
            using return_type = typename __SignatureDesc<_Signature>::return_type;
            //Checking for the correctness of the type used 
            static_assert(std::is_same<return_type, void>::value, "Trying to execute delegates with return type 'non-void'. For 'non-void' you should use 'eval' method.");

            for (auto &[_key, _delegate] : m_Delegates)
            {
                if (_delegate)
                {
                    _delegate(std::forward<Args>(args)...);
                }
            }
        }

        /**
         * @brief Evaluates the delegate on the specified enumerator and returns the value
         * 
         * @tparam eBase User defined enumeration key
         * @tparam Args Templated std::tuple arguments 
         * @param args Delegate arguments
         * @return SignatureDesc<_Signature>::return_type auto eval(Args&&... args) 
         */
        template<_Enumerator eBase, class ...Args> 
        inline auto eval(Args&&... args) -> typename __SignatureDesc<_Signature>::return_type
        {
            using return_type = typename __SignatureDesc<_Signature>::return_type;
            static_assert(!std::is_same<return_type, void>::value, "Trying to evaluate delegates with return type 'void'. For 'void' you should use 'execute' method.");

            return m_Delegates[eBase](std::forward<Args>(args)...);
        }
        
        /**
         * @brief Executes all the delegates attached to the object and returns the std::map object containing the calculation results. You can also refer to the result by the numerator.
         * 
         * @tparam Args Templated std::tuple arguments 
         * @param args Delegate arguments
         * @return std::map<_Enumerator, return_type> 
         */
        template<class ...Args>
        inline auto eval(Args&&... args) -> typename std::map<_Enumerator, 
        typename __SignatureDesc<_Signature>::return_type>
        {
            using return_type = typename __SignatureDesc<_Signature>::return_type;
            static_assert(!std::is_same<return_type, void>::value, "Trying to evaluate delegates with return type 'void'. For 'void' you should use 'execute' method.");
            std::map<_Enumerator, return_type> _results;

            for (auto &[_key, _delegate] : m_Delegates)
            {
                if (_delegate)
                {
                    _results.emplace(_key, _delegate(std::forward<Args>(args)...));
                }
            }

            return std::forward<decltype(_results)>(_results);
        }

        /**
         * @brief Illegal in any c++ standart
         * 
         * @tparam eBase 
         * @tparam Args 
         * @param args 
         * @return SignatureDesc<_Signature>::return_type 
         */
        template<_Enumerator eBase, class ...Args>
        inline auto operator()(Args&&... args) -> typename __SignatureDesc<_Signature>::return_type
        {
            return m_Delegates[eBase](std::forward<Args>(args)...);
        }
    private:
        std::map<_Enumerator, __Delegate<_Signature>, _Comp> m_Delegates;
    };

    template<class _Enumerator, class _Signature, class _Comp = __EnumeratorComp<_Enumerator>>
    using TDelegateMulti = __DelegateMulti<_Enumerator, _Signature, _Comp>;
}

/**
 * @example Example of using TDelegateMulti
 * 
 * @code
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
 * @endcode
 * 
 */
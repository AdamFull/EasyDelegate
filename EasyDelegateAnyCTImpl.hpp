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
#include "EasyDelegateImpl.hpp"

namespace EasyDelegate
{
    /**
     * @brief Architectural layer for creating global delega
     * 
     */
    template<class _Enumerator>
    struct __FDelegates
    {
        template<_Enumerator>
        struct __DelegateType;

        template<_Enumerator>
        struct __DelegateMap;

        /**
         * @brief Compile-time implementation of the global delegate subscription mechanism
         * 
         * @tparam eBase User defined enumeration key
         * @tparam Args Templated std::tuple arguments 
         * @param args arguments
         */
        template<_Enumerator eBase, class ...Args>
        constexpr void SubscribeTo(Args&&... args)
        {
            using _delegate_t = typename DelegateType<eBase>::Type;
            _delegate_t& _delegate = GetDelegate<eBase>();
            _delegate.attach(std::forward<Args>(args)...);
        }

        /**
         * @brief Mechanism for unsubscribing from a global delegate
         * 
         * @tparam eBase User defined enumeration key
         */
        template<_Enumerator eBase>
        constexpr void UnsubscribeFrom()
        {
            using _delegate_t = typename DelegateType<eBase>::Type;
            _delegate_t& _delegate = GetDelegate<eBase>();
            _delegate.detach();
        }

        /**
         * @brief Getting a global delegate by enumerator
         * 
         * @tparam eBase user defined enumeration key
         * @return constexpr auto& 
         */
        template<_Enumerator eBase>
        constexpr auto& GetDelegate()
        {
            return DelegateMap<eBase>::Value;
        }
    };

    template<class _Enumerator>
    using FDelegates = __FDelegates<_Enumerator>;

    /**
     * @brief Implementation of global compile-time delegates. Not working for now
     * 
     * @tparam _Enumerator Enumerator class
     */
    template <class _Enumerator>
    struct __DelegateAnyCT
    {
        /**
     * @brief Creates a connection with the method and the enumerator
     * 
     * @tparam eType User defined enumeration key
     * @tparam Args Templated std::tuple arguments 
     * @param args 
     */
        template <_Enumerator eType, class... Args>
        static void CreateLink(Args &&...args)
        {
            delegates.SubscribeTo<eType>(std::forward<Args>(args)...);
        }

        /**
     * @brief Breaks a connection between the method and the enumerator
     * 
     * @tparam eType User defined enumeration key
     * 
     */
        template <_Enumerator eType>
        static void BreakLink()
        {
            delegates.UnsubscribeFrom<eType>();
        }

        /**
     * @brief 
     * 
     * Helps to call a delegate by its ID.
     * 
     * @tparam eType User defined enumeration key
     * @tparam Args Args Templated std::tuple arguments 
     * @param args arguments unpacked
     * @return auto 
     */
        template <_Enumerator eType, class... Args>
        static auto Call(Args &&...args)
        {
            auto &_delegate = delegates.GetDelegate<eType>();
            return _delegate(std::forward<Args>(args)...);
        }

    private:
        static FDelegates<_Enumerator> delegates;
    };

    template <class _Enumerator>
    using TDelegateAnyCT = __DelegateAnyCT<_Enumerator>;
}

/**
 * @example AnyCTExample
 * 
 * @code
   
    #include "EasyDelegate.hpp"

    using namespace EasyDelegate;
  
    enum class EEnumerator
    {
        EIntDelegate,
        EBoolDelegate
    };

    DeclareDelegateFuncCompileTime(EEnumerator, EEnumerator::EIntDelegate, int(int, int, bool))
    DeclareDelegateFuncCompileTime(EEnumerator, EEnumerator::EBoolDelegate, bool(bool, bool))

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
        TDelegateAnyCT<EEnumerator> _delegates;                                          //Linker structure

        _delegates.CreateLink<EEnumerator::EIntDelegate>(&foo);              //Creating link to structure
        auto iresult = _delegates.Call<EEnumerator::EIntDelegate>(50, -50, false);       //Calling function
        _delegates.BreakLink<EEnumerator::EIntDelegate>();

        Foo boo;
        _delegates.CreateLink<EEnumerator::EBoolDelegate>(&boo, &Foo::foo);        //Same with classes
        auto bresult = _delegates.Call<EEnumerator::EBoolDelegate>(true, true);
        _delegates.BreakLink<EEnumerator::EBoolDelegate>();

        _delegates.CreateLink<EEnumerator::EBoolDelegate>([&](bool b, bool n)
        {
            return boo.foo(b, n) || b;
        });

        auto lresult = _delegates.Call<EEnumerator::EBoolDelegate>(true, false);
        _delegates.BreakLink<EEnumerator::EBoolDelegate>();

        std::cout << lresult << std::endl;

        return 0;
    }
    @endcode
 * 
 */
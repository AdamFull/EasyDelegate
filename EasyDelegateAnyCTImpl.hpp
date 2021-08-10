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
     * @brief Implementation of global compile-time delegates. Not working for now
     * 
     * @tparam _Enumerator Enumerator class
     */
    template <class _Enumerator>
    struct __DelegateAnyCT
    {
        /**
         * @brief Attaches the passed method to the User defined enumeration key
         * 
         * @tparam eEnum User defined enumeration key
         * @tparam _LabbdaFunction Lambda object
         * @param lfunc  
         */
        template<_Enumerator eBase, class _LabbdaFunction>
		static inline void attach(_LabbdaFunction&& lfunc) noexcept
        {
            using _delegate_t = typename __DelegateTypeStore<TakeStoreKey<_Enumerator, eBase>()>::type;
            _delegate_t& _delegate = __DelegateObjectStore<TakeStoreKey<_Enumerator, eBase>()>::value;
            _delegate.attach(std::forward<_LabbdaFunction>(lfunc));
        }

        /**
         * @brief Creates a connection with the method and the enumerator
         * 
         * @tparam eBase User defined enumeration key
         * @tparam Args Templated std::tuple arguments 
         * @param args 
         */
        template <_Enumerator eBase, class... Args>
        static inline void attach(Args &&...args) noexcept
        {
            using _delegate_t = typename __DelegateTypeStore<TakeStoreKey<_Enumerator, eBase>()>::type;
            _delegate_t& _delegate = __DelegateObjectStore<TakeStoreKey<_Enumerator, eBase>()>::value;
            _delegate.attach(std::forward<Args>(args)...);
        }

        /**
         * @brief Breaks a connection between the method and the enumerator
         * 
         * @tparam eBase User defined enumeration key
         * 
         */
        template <_Enumerator eBase>
        static inline void detach() noexcept
        {
            using _delegate_t = typename __DelegateTypeStore<TakeStoreKey<_Enumerator, eBase>()>::type;
            _delegate_t& _delegate = __DelegateObjectStore<TakeStoreKey<_Enumerator, eBase>()>::value;
            _delegate.detach();
        }

        /**
         * @brief Executes the delegate for the specified enumerator
         * 
         * @tparam eEnum User defined enumeration key
         * @tparam Args Templated std::tuple arguments 
         * @param args Delegate arguments
         */
        template<class ...Args>
        static inline void execute(Args&&... args)
        {
            using _sign_t = typename __DelegateTypeStore<TakeStoreKey<_Enumerator, eBase>()>::signature;
            using return_type = typename __SignatureDesc<_sign_t>::return_type;
            //Checking for the correctness of the type used 
            static_assert(std::is_same<return_type, void>::value, "Trying to execute delegates with return type 'non-void'. For 'non-void' you should use 'eval' method.");

            auto &_delegate = __DelegateObjectStore<TakeStoreKey<_Enumerator, eBase>()>::value;
            _delegate(std::forward<Args>(args)...);
        }

        /**
         * @brief Evaluates the delegate on the specified enumerator and returns the value
         * 
         * @tparam eEnum User defined enumeration key
         * @tparam Args Templated std::tuple arguments 
         * @param args Delegate arguments
         * @return SignatureDesc<_Signature>::return_type auto eval(Args&&... args) 
         */
        template <_Enumerator eBase, class... Args>
        static inline auto eval(Args &&...args)
        {
            using _sign_t = typename __DelegateTypeStore<TakeStoreKey<_Enumerator, eBase>()>::signature;
            using return_type = typename __SignatureDesc<_sign_t>::return_type;
            static_assert(!std::is_same<return_type, void>::value, "Trying to evaluate delegate with return type 'void'. For 'void' you should use 'execute' method."); 

            auto &_delegate = __DelegateObjectStore<TakeStoreKey<_Enumerator, eBase>()>::value;
            return _delegate(std::forward<Args>(args)...);
        }
    };

    template <class _Enumerator>
    using TDelegateAnyCT = __DelegateAnyCT<_Enumerator>;
}

/**
 * @example AnyCTExample
 * 
 * @code
#include <iostream>
#include "EasyDelegate.hpp"

using namespace EasyDelegate;

//    An important note. You cannot use TDelegateAny and TDelegateAnyCT at the 
//    same time due to some technical problems. The same is the case with the 
//    enumerator. When the problem is resolved, this will be indicated in the update.

// If you want use multiple enums, start new enum with higher index
enum class EEnumerator
{
    EIntDelegate = 100,
    EBoolDelegate
};

//This declarations should be in cpp file
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
    //Attaching function to abstract global delegate container
    TDelegateAnyCT<EEnumerator>::attach<EEnumerator::EIntDelegate>(&foo);
    //Calling function
    auto iresult = TDelegateAnyCT<EEnumerator>::eval<EEnumerator::EIntDelegate>(50, -50, false); 
    TDelegateAnyCT<EEnumerator>::detach<EEnumerator::EIntDelegate>();

    //Class example
    Foo boo;
    //Attach class method to delegate container
    TDelegateAnyCT<EEnumerator>::attach<EEnumerator::EBoolDelegate>(&boo, &Foo::foo);
    auto bresult = TDelegateAnyCT<EEnumerator>::eval<EEnumerator::EBoolDelegate>(true, true);
    TDelegateAnyCT<EEnumerator>::detach<EEnumerator::EBoolDelegate>();

    //And with lambda function
    TDelegateAnyCT<EEnumerator>::attach<EEnumerator::EBoolDelegate>([&](bool b, bool n)
    { 
        return boo.foo(b, n) || b; 
    });

    auto lresult = TDelegateAnyCT<EEnumerator>::eval<EEnumerator::EBoolDelegate>(true, false);
    TDelegateAnyCT<EEnumerator>::detach<EEnumerator::EBoolDelegate>();

    std::cout << lresult << std::endl;

    return 0;
}
    @endcode
 * 
 */
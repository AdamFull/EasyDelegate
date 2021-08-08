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
#include <any>
#include <cassert>

namespace EasyDelegate
{
	/**
	 * @brief A container for creating delegates at the program execution stage. Allows you to add delegates with any signature, 
	 * and make their further call. At the moment, it cannot be used together with TDelegateAnyCT and vice versa.
	 * 
	 * @tparam _Enumerator 
	 * @tparam _Signature 
	 */
	template<class _Enumerator, class _Comp>
	struct __DelegateAny
	{
		/**
         * @brief Attaching existing delegate if signature is same
         * 
         * @tparam eBase User defined enumeration key
         * @param _delegate existing delegate as r-value
         */
        template<_Enumerator eBase>
        inline void attach(__Delegate<typename __DelegateTypeStore<TakeStoreKey<_Enumerator>(eBase)>::signature>&& _delegate)
        {
			using _sign_t = typename __DelegateTypeStore<TakeStoreKey<_Enumerator>(eBase)>::signature;
            static_assert(std::is_same<
            std::remove_reference<decltype(_delegate)>::type, __Delegate<_sign_t>>::value,
            "Attached delegate has diferent signatures." );
            m_Delegates.emplace(eBase, std::move(_delegate));
        }

		/**
		 * @brief Attaches the passed method to the user defined enumeration key
		 * 
		 * @tparam eBase User defined enumeration key
		 * @tparam LabbdaFunction Lambda function signature
		 * @param lfunc Universal ling to LambdaFunction signature
		 */
		template<_Enumerator eBase, class _LabbdaFunction>
		inline void attach(_LabbdaFunction&& lfunc)
		{
			using _delegate_t = typename __DelegateTypeStore<TakeStoreKey<_Enumerator>(eBase)>::type;
			_delegate_t _delegate;
			_delegate.attach(std::forward<_LabbdaFunction>(lfunc));
			m_Delegates.emplace(eBase, std::move(_delegate));
		}

		/**
		 * @brief Attaches the passed method to the user defined enumeration key
		 * 
		 * @tparam eBase User defined enumeration key
		 * @tparam Args 
		 * @param args 
		 */
		template<_Enumerator eBase, class ...Args>
		inline void attach(Args&&... args)
		{
			using _delegate_t = typename __DelegateTypeStore<TakeStoreKey<_Enumerator>(eBase)>::type;
			_delegate_t _delegate;
			_delegate.attach(std::forward<Args>(args)...);
			m_Delegates.emplace(eBase, std::move(_delegate) /*rvalue*/);
		}

		/** 
		 * @brief Detaching delegate
		 * 
		 * @tparam eBase User defined enumeration key
		 */
		template<_Enumerator eBase>
		inline void detach()
		{
			using _delegate_t = typename __DelegateTypeStore<TakeStoreKey<_Enumerator>(eBase)>::type;
			_delegate_t _delegate;
			if (!GetDelegate<_delegate_t>(eBase, &_delegate))
			{
				// TODO: error
			}
			_delegate.detach();
		}

		/**
         * @brief Executes the delegate for the specified enumerator
         * 
         * @tparam eEnum User defined enumeration key
         * @tparam Args Templated std::tuple arguments 
         * @param args Delegate arguments
         */
        template<_Enumerator eBase, class ...Args>
        inline void execute(Args&&... args)
        {
            using _sign_t = typename __DelegateTypeStore<TakeStoreKey<_Enumerator>(eBase)>::signature;
            using return_type = typename __SignatureDesc<_sign_t>::return_type;
            //Checking for the correctness of the type used 
            static_assert(std::is_same<return_type, void>::value, "Trying to execute delegates with return type 'non-void'. For 'non-void' you should use 'eval' method.");

            auto &_delegate = _GetDelegateF<eBase>();
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
        inline auto eval(Args &&...args)
        {
            using _sign_t = typename __DelegateTypeStore<TakeStoreKey<_Enumerator>(eBase)>::signature;
            using return_type = typename __SignatureDesc<_sign_t>::return_type;
            static_assert(!std::is_same<return_type, void>::value, "Trying to evaluate delegate with return type 'void'. For 'void' you should use 'execute' method."); 

            auto &_delegate = _GetDelegateF<eBase>();
            return _delegate(std::forward<Args>(args)...);
        }

		private:
		/**
		 * @brief Commits a cast from std::any to the required delegate and returns a reference to it
		 * 
		 * @tparam eEnum User defined enumeration key
		 * @return DelegateType<eEnum>::Type 
		 */
		template<_Enumerator eBase>
		inline auto _GetDelegateF() -> typename __DelegateTypeStore<TakeStoreKey<_Enumerator>(eBase)>::type
		{
			using _delegate_t = typename __DelegateTypeStore<TakeStoreKey<_Enumerator>(eBase)>::type;
			_delegate_t _delegate;
			if (!GetDelegate<_delegate_t>(eBase, &_delegate))
			{
				// TODO: error
			}
			return _delegate;
		}

		/**
		 * @brief Tries to cast std::any to the required delegate
		 * 
		 * @tparam CastType Type to be reduced to
		 * @tparam T Output object type
		 * @param eEnum 
		 * @param out 
		 */
		template<class _CastType, class _T>
		inline bool GetDelegate(const _Enumerator& eEnum, _T* out)
		{
			try
			{
				*out = std::any_cast<_CastType>(m_Delegates[eEnum]);
				return true;
			}
			catch (const std::bad_any_cast& e)
			{
				assert(false && e.what());
			}
			out = nullptr;
			return false;
		}

		std::map<_Enumerator, std::any, _Comp> m_Delegates;
	};

	template<class _Enumerator, class _Comp = __EnumeratorComp<_Enumerator>>
	using TDelegateAny = __DelegateAny<_Enumerator, _Comp>;
}

/**
 * @example AnyExample
 * 
 * @code
#include <iostream>
#include "EasyDelegate.hpp"

using namespace EasyDelegate;

//    An important note. You cannot use TDelegateAny and TDelegateAnyCT at the 
//    same time due to some technical problems. The same is the case with the 
//    enumerator. When the problem is resolved, this will be indicated in the update.

//Your enumerator type
enum class EEnumerator
{
    EIntDelegate,
    EBoolDelegate,
    EAnother
};

//This declarations should be in cpp file
DeclareDelegateFuncRuntime(EEnumerator, EEnumerator::EIntDelegate, int(int, int, bool))
DeclareDelegateFuncRuntime(EEnumerator, EEnumerator::EBoolDelegate, bool(bool, bool))
DeclareDelegateFuncRuntime(EEnumerator, EEnumerator::EAnother, void(int, int))

int foo(int x, int y, bool ts)
{
    return ts ? x : y;
}

void boob(int x, int y)
{
    std::cout << x + y << std::endl;
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
    //Declare any delegate object
    TDelegateAny<EEnumerator> _delegates;
    //Attach to static function 
    _delegates.attach<EEnumerator::EIntDelegate>(&foo);
    //Call function
    auto iresult = _delegates.eval<EEnumerator::EIntDelegate>(50, -50, false);

    //Now with class object (also you can use 'this', if your delegate inside a class)
    Foo boo;
    //Attach class method to delegate container
    _delegates.attach<EEnumerator::EBoolDelegate>(&boo, &Foo::foo); //Same with classes
    auto bresult = _delegates.eval<EEnumerator::EBoolDelegate>(true, true);
    _delegates.detach<EEnumerator::EBoolDelegate>();

    //Attaching existing delegate
    TDelegate<void(int, int)> AnotherDelegate;
    AnotherDelegate.attach(&boob);

    _delegates.attach<EEnumerator::EAnother>(std::move(AnotherDelegate));

    _delegates.execute<EEnumerator::EAnother>(1, 2);
    _delegates.execute<EEnumerator::EAnother>(2, 1);

    //And lambda functions
    _delegates.attach<EEnumerator::EBoolDelegate>([&](bool b, bool n)
    { 
        return boo.foo(b, n) || b;
    });

    auto lresult = _delegates.eval<EEnumerator::EBoolDelegate>(true, false);
    _delegates.detach<EEnumerator::EBoolDelegate>();

    std::cout << lresult << std::endl;

    return 0;
}
    @endcode
 * 
 */
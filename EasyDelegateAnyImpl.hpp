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

namespace EasyDelegate
{
	/**
	 * @brief 
	 * 
	 * @tparam _Enumerator 
	 * @tparam _Signature 
	 */
	template<class _Enumerator, class _Signature, class _Comp>
	struct __DelegateAny
	{
		template<_Enumerator>
		struct __DelegateType;

		/**
		 * @brief Attaches the passed method to the user defined enumeration key
		 * 
		 * @tparam eEnum User defined enumeration key
		 * @tparam LabbdaFunction Lambda function signature
		 * @param lfunc Universal ling to LambdaFunction signature
		 */
		template<_Enumerator eEnum, class _LabbdaFunction>
		void attach(_LabbdaFunction&& lfunc)
		{
			using _delegate_t = typename __DelegateType<eEnum>::Type;
			_delegate_t _delegate;
			if (!GetDelegate<_delegate_t>(eEnum, &_delegate))
			{
				// TODO: error
			}
			_delegate.attach(std::forward<_LabbdaFunction>(lfunc));
			m_Delegates.emplace(eEnum, std::forward<decltype(_delegate)>(_delegate));
		}

		/**
		 * @brief Attaches the passed method to the user defined enumeration key
		 * 
		 * @tparam eEnum User defined enumeration key
		 * @tparam Args 
		 * @param args 
		 */
		template<_Enumerator eEnum, class ...Args>
		constexpr void attach(Args&&... args)
		{
			using _delegate_t = typename __DelegateType<eEnum>::Type;
			_delegate_t _delegate;
			if (!GetDelegate<_delegate_t>(eEnum, &_delegate))
			{
				// TODO: error
			}
			_delegate.attach(std::forward<Args>(args)...);
			m_Delegates.emplace(eEnum, std::forward<decltype(_delegate)>(_delegate));
		}

		/** 
		 * @brief Detaching delegate
		 * 
		 * @tparam eEnum User defined enumeration key
		 */
		template<_Enumerator eEnum>
		constexpr void detach()
		{
			using _delegate_t = typename __DelegateType<eEnum>::Type;
			_delegate_t _delegate;
			if (!GetDelegate<_delegate_t>(eEnum, &_delegate))
			{
				// TODO: error
			}
			_delegate.detach();
		}

		/**
		 * @brief Commits a cast from std::any to the required delegate and returns a reference to it
		 * 
		 * @tparam eEnum User defined enumeration key
		 * @return DelegateType<eEnum>::Type 
		 */
		template<_Enumerator eEnum>
		auto _GetDelegateF() -> typename __DelegateType<eEnum>::Type
		{
			using _delegate_t = typename __DelegateType<eEnum>::Type;
			_delegate_t _delegate;
			if (!GetDelegate<_delegate_t>(eEnum, &_delegate))
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
		bool GetDelegate(const _Enumerator& eEnum, _T* out)
		{
			try
			{
				*out = std::any_cast<_CastType>(m_Delegates[eEnum]);
				return true;
			}
			catch (const std::bad_any_cast& e)
			{

			}
			out = nullptr;
			return false;
		}

	private:
		std::map<_Enumerator, std::any, _Comp> m_Delegates;
	};

	template<class _Enumerator, class _Signature, class _Comp = __EnumeratorComp<_Enumerator>>
	using TDelegateAny = __DelegateAny<_Enumerator, _Signature, _Comp>;
}

/**
 * @example AnyExample
 * 
 * @code
 * 
 *  
    #include "EasyDelegate.hpp"

	using namespace EasyDelegate;

	enum class EEnumerator
    {
        EIntDelegate,
        EBoolDelegate
    };

    DeclareDelegateFuncRuntime(EEnumerator, EEnumerator::EIntDelegate, int(int, int, bool))
    DeclareDelegateFuncRuntime(EEnumerator, EEnumerator::EBoolDelegate, bool(bool, bool))

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
        TDelegateAny<EEnumerator> _delegates;                                          //Linker structure

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
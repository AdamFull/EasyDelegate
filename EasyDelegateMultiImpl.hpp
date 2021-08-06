#pragma once
#include <map>
#include <tuple>
#include <type_traits>
#include "EasyDelegateImpl.hpp"

template<class _Signature>
struct SignatureDesc;

template<class _ReturnType, class ...Args>
struct SignatureDesc<_ReturnType(Args...)>
{
    using return_type = _ReturnType;
    using argument_type = std::tuple<Args...>;
};

template<class _Enumerator, class _Signature>
class EasyDelegateMulti
{
public:
    template<_Enumerator eEnum, class LabbdaFunction>
	void attach(LabbdaFunction&& lfunc)
    {
        EasyDelegate<_Signature> _delegate;
        _delegate.attach(std::forward<LabbdaFunction>(lfunc));
        mDelegates.emplace(eEnum, _delegate);
    }

    template<_Enumerator eEnum, class ...Args>
    void attach(Args&&... args)
    {
        EasyDelegate<_Signature> _delegate;
        _delegate.attach(std::forward<Args>(args)...);
        mDelegates.emplace(eEnum, _delegate);
    }

    template<_Enumerator eEnum>
    void detach()
    {
        mDelegates.erase(eEnum);
    }

    template<class ...Args>
	void execute(Args&&... args)
	{
        for(auto& [_key, _delegate] : mDelegates)
        {
            if(_delegate)
            {
                _delegate(std::forward<Args>(args)...);
            }
        }
    }

    template<class ...Args>
	auto eval(Args&&... args)
	{
        using return_type = typename SignatureDesc<_Signature>::return_type;
        std::map<_Enumerator, return_type> _results;

        for(auto& [_key, _delegate] : mDelegates)
        {
            if(_delegate)
            {
                _results.emplace(_key, _delegate(std::forward<Args>(args)...));
            }
        }

		return std::move(_results);
	}

    template<_Enumerator eEnum, class ...Args>
	auto operator()(Args&&... args)
	{
		return mDelegates[eEnum](std::forward<Args>(args)...);
	}
private:
    std::map<_Enumerator, EasyDelegate<_Signature>> mDelegates;
};
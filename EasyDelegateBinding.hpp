/**
 * @file EasyDelegateBinding.hpp
 * @author AdamFull (https://github.com/adamfull)
 * @brief 
 * @version 0.1
 * @date 2021-08-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#include "ConstexprStructsImpl.hpp"
#include "EasyDelegateImpl.hpp"

/**
 * @brief 
 * A structure to simplify working with delegates. Allows you to link functional objects.
 */
struct FDelegates
{
    /**
     * @brief Subscribe to delegate eBase with Args...
     * 
     * @tparam eBase delegate id
     * @tparam Args delegate signature
     * @param args arguments
     */
	template<EDelegateBase eBase, class ...Args>
	constexpr void SubscribeTo(Args&&... args)
	{
		using _delegate_t = typename DelegateType<eBase>::Type;
		_delegate_t& _delegate = GetDelegate<eBase>();
		_delegate.attach(std::forward<Args>(args)...);
	}

    /**
     * @brief Unsubscribe from eBase delegate.
     * 
     * @tparam eBase delegate id
     */
	template<EDelegateBase eBase>
	constexpr void UnsubscribeFrom()
	{
		using _delegate_t = typename DelegateType<eBase>::Type;
		_delegate_t& _delegate = GetDelegate<eBase>();
		_delegate.detach();
	}

    /**
     * @brief Get the Delegate object
     * 
     * @tparam eBase delegate id
     * @return constexpr auto& 
     */
    template<EDelegateBase eBase>
    constexpr auto& GetDelegate()
    {
        return DelegateMap<eBase>::Value;
    }
};
/**
 * @file EasyDelegate.hpp
 * @author AdamFull (https://github.com/adamfull)
 * @brief 
 * @version 0.1
 * @date 2021-08-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#include "EasyDelegateBinding.hpp"

/**
 * @brief 
 * Returns the delegate object from the storage by its ID.
 */
#define GetDelegateF(fDelegates, eType) fDelegates.GetDelegate<eType>()

/**
 * @brief 
 * Registers a keyword for a delegate by id/
 */
#define AddDelegateKeyword(eTypeName, eValue) \
static constexpr EDelegateBase eTypeName = eValue;

/**
 * @brief 
 * Declares a new delegate for the delegate store.
 */
#define DeclareDelegateFunc(eType, fSignature) \
template<> struct DelegateType<eType> { using Type = EasyDelegate<fSignature>; }; \
template<> struct DelegateMap<eType> { static EasyDelegate<fSignature> Value; }; \
EasyDelegate<fSignature> DelegateMap<eType>::Value;

//template<EDelegateBase eType, class _Signature>
//DeclareDelegateFunc()

/**
 * @brief 
 * 
 * Helps to connect a functional object to a delegate.
 * 
 * @tparam eType delegate id
 * @tparam Args arguments pack
 * @param delegates delegates storage
 * @param args 
 */
template<EDelegateBase eType, class ...Args>
void DelegateCreateLink(FDelegates& delegates, Args&&... args)
{
    delegates.SubscribeTo<eType>(std::forward<Args>(args)...);
}

/**
 * @brief 
 * 
 * Helps to detach a function object with a delegate
 * 
 * @tparam eType delegate id
 * @param delegates delegates storage
 */
template<EDelegateBase eType>
void DelegateBreakLink(FDelegates& delegates)
{
    delegates.UnsubscribeFrom<eType>();
}

/**
 * @brief 
 * 
 * Helps to call a delegate by its ID.
 * 
 * @tparam eType delegate id
 * @tparam Args arguments pack
 * @param delegates delegates storage
 * @param args arguments unpacked
 * @return auto 
 */
template<EDelegateBase eType,class ...Args>
auto DelegateCall(FDelegates& delegates, Args&&... args)
{
    return GetDelegateF(delegates, eType)(std::forward<Args>(args)...);
}
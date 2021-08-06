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
#include "EasyDelegateAnyCTImpl.hpp"
#include "EasyDelegateMultiImpl.hpp"
#include "EasyDelegateAnyImpl.hpp"

/**
 * @brief Mechanism for creating a global delegate of the compilation-time
 * 
 */
#define DeclareDelegateFuncCompileTime(eEnumeraror, eType, fSignature) \
template<> struct EasyDelegate::__FDelegates<eEnumeraror>::__DelegateType<eType> { using Type = __Delegate<fSignature>; }; \
template<> struct EasyDelegate::__FDelegates<eEnumeraror>::__DelegateMap<eType> { static __Delegate<fSignature> Value; }; \
EasyDelegate<fSignature> EasyDelegate::__FDelegates<eEnumeraror>::__DelegateMap<eType>::Value;

/**
 * @brief Mechanism for creating a delegate for runtime __DelegateAny
 * 
 */
#define DeclareDelegateFuncRuntime(eEnumeraror, eType, fSignature) \
template<> struct EasyDelegate::__DelegateAny<eEnumeraror>::__DelegateType<eType> { using Type = __Delegate<fSignature>; };
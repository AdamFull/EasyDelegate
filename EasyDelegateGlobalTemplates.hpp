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
#include <tuple>
#include <type_traits>

namespace EasyDelegate
{
    /**
     * @brief The method translates the value of the numerator to the key for the template specialization.
     * 
     * @tparam _Enumerator Enumeration class
     * @param eBase Enumerator value
     * @return constexpr uint32_t 
     */
    template<class _Enumerator, _Enumerator eBase>
    [[nodiscard]] constexpr inline uint32_t TakeStoreKey() noexcept
    {
        return static_cast<uint32_t>(eBase);
    }

    template<uint32_t>
    struct __DelegateTypeStore;

    template<uint32_t>
    struct __DelegateObjectStore;

    /**
     * @brief A helper template for dividing a signature into a return type and a list of argument types
     * 
     * @tparam _Signature 
     */
    template<class _Signature>
    struct __SignatureDesc;

    /**
     * @brief Specialization of the helper template for separating the method signature into a return type and an argument type sheet
     * 
     * @tparam _ReturnType 
     * @tparam Args 
     */
    template<class _ReturnType, class ...Args>
    struct __SignatureDesc<_ReturnType(Args...)>
    {
        using return_type = _ReturnType;
        using argument_type = std::tuple<Args...>;
    };

    /**
     * @brief Default comparator for the installed numerator
     * 
     * @tparam _Enumerator Enumerator class
     */
    template<class _Enumerator>
    struct __EnumeratorComp
    {
        static_assert(std::is_enum<_Enumerator>::value);
        inline bool operator()(const _Enumerator& l, const _Enumerator& r) const
        {
            return static_cast<int>(l) < static_cast<int>(r);
        }
    };
}
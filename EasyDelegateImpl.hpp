/**
 * @file EasyDelegateImpl.hpp
 * @author AdamFull (https://github.com/adamfull)
 * @brief 
 * @version 0.1
 * @date 2021-08-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#include <functional>

/**
 * @brief 
 * 
 * Implementation of a simple delegate based on the std::function functionality from @n
 * the c++standard library. Allows you to implement a functional object of a class @n
 * method or a static function for further invocation. @n
 * 
 * @tparam _Signature signature of the delegate function
 */
template<class _Signature>
class EasyDelegate
{
public:
    /**
     * @brief 
     * The method is intended for binding a static function to a delegate.
     * A reference to the required function is passed as arguments.
     * 
     * @param args static function reference...
     * @return void
     */
	template<class ...Args>
	void attach(Args&&... args)
	{
		mDelegate = make_delegate(std::forward<Args>(args)...);
	}

    /**
     * @brief 
     * 
     * @param c 
     * @param m 
     * @return template <class Class, class ReturnType, class ...Args> 
     */
    //For class or const class method. Receiving class pointer and class method reference.
    template <class Class, class ReturnType, class ...Args>
    void attach(Class* c, ReturnType (Class::*m)(Args...))
    {
        mDelegate = make_delegate(c, m);
    }

    /**
     * @brief 
     * Detaching function delegate
     */
	void detach()
	{
		mDelegate = nullptr;
	}

	template<class ...Args>
	auto operator()(Args&&... args)
	{
		return mDelegate(std::forward<Args>(args)...);
	}

	operator bool()
	{
		return static_cast<bool>(mDelegate);
	}

private:
	std::function<_Signature> mDelegate;

private:
    /**
     * @brief 
     * 
     * Implementation of creating a delegate for a static method.
     * 
     * @tparam ReturnType (set automatically in c++17) class type
     * @tparam Args (set automatically in c++17) another arguments
     * @param m reference to function
     * @return std::function<ReturnType(Args...)> 
     */
    template <class ReturnType, class ...Args>
    std::function<ReturnType(Args...)> make_delegate(ReturnType (*m)(Args...))
    {
        return [=](Args&&... args) { return (*m)(std::forward<Args>(args)...); };
    }

    /**
     * @brief
     * 
     * Implementation of creating a delegate for a class.
     * 
     * @tparam Class (set automatically in c++17) class type
     * @tparam ReturnType (set automatically in c++17)
     * @tparam Args (set automatically in c++17)
     * @param c pointer to class
     * @param m reference to class method
     * @return std::function<ReturnType(Args...)> 
     */
    template <class Class, class ReturnType, class ...Args>
    std::function<ReturnType(Args...)> make_delegate(Class* c, ReturnType (Class::*m)(Args...))
    {
        return [=](Args&&... args) { return (c->*m)(std::forward<Args>(args)...); };
    }

    /**
     * @brief 
     * 
     * Implementation of creating a delegate for a constant class.
     * 
     * @tparam Class (set automatically in c++17)
     * @tparam ReturnType (set automatically in c++17)
     * @tparam Args (set automatically in c++17)
     * @param c const pointer to class
     * @param m reference to class method
     * @return std::function<ReturnType(Args...)> 
     */
    template <class Class, class ReturnType, class ... Args>
    std::function<ReturnType(Args...)> make_delegate(const Class* c, ReturnType (Class::*m)(Args...) const)
    {
        return [=](Args&&... args) { return (c->*m)(std::forward<Args>(args)...); };
    }
};
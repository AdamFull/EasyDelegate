# EasyDelegate library for c++17 and higher

[![forthebadge](https://forthebadge.com/images/badges/made-with-c-plus-plus.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/built-with-love.svg)](https://forthebadge.com)

[![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2FAdamFull%2FEasyDelegate.svg?type=shield)](https://app.fossa.com/projects/git%2Bgithub.com%2FAdamFull%2FEasyDelegate?ref=badge_shield)
[![GitHub Issues](https://img.shields.io/github/issues/AdamFull/EasyDelegate.svg)](https://github.com/AdamFull/EasyDelegate/issues)
[![License](https://img.shields.io/badge/license-Mozila-blue.svg)](https://opensource.org/licenses/MPL-2.0)

## Problem

-----------------------------------

The standard language library provides a mechanism for storing functional objects in std::function<> and binding by the std tool::bind migrated from boost. This mechanism has some disadvantages, especially with passing std:: placeholder as parameters of std:: bind.

## Why is it necessary

----------------------------------

This library makes working with delegates much easier. It allows you to create functional objects in the same way as std::function, but changes the mechanism for binding a function to a functional object.
The delegate is based on std::function, it performs all the main work. EasyDelegate is an abstraction over std::function and implements a different function binding mechanism.

## Features (more information on the [wiki](https://github.com/AdamFull/EasyDelegate/wiki))

---------------------------------

### TDelegate ([class implementation](https://github.com/AdamFull/EasyDelegate/wiki/Class-__Delegate))

Implementation of a delegate based on std::function. At the moment, the entire basic algorithm of work is implemented. 
A "scheduled call" will be added soon.The class allows you to perform simple binding with both class methods and static functions.

### TDelegateMulti ([class implementation](https://github.com/AdamFull/EasyDelegate/wiki/Class-__DelegateMulti))

Allows you to create a delegate store with the same signature. Based on std:: map. Requires creating an object. Read more in the wiki.

### TDelegateAnyCT ([class implementation](https://github.com/AdamFull/EasyDelegate/wiki/Struct-__DelegateAnyCT))

A global container for creating delegates at the compilation stage. It can be used for a simple event system. At the moment, 
it cannot be used together with TDelegateAny and vice versa.

### TDelegateAny ([class implementation](https://github.com/AdamFull/EasyDelegate/wiki/Struct-__DelegateAny))

A container for creating delegates at the program execution stage. Allows you to add delegates with any signature, and make their further call. At the moment, it cannot be used together with TDelegateAnyCT and vice versa.

## License

-------

MIT © [AdamFull](https://github.com/AdamFull) && [range36rus](https://github.com/range36rus).

# EasyDelegate library for c++17 and higher

[![forthebadge](https://forthebadge.com/images/badges/made-with-c-plus-plus.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/built-with-love.svg)](https://forthebadge.com)

[![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2FAdamFull%2FEasyDelegate.svg?type=shield)](https://app.fossa.com/projects/git%2Bgithub.com%2FAdamFull%2FEasyDelegate?ref=badge_shield)
[![GitHub Issues](https://img.shields.io/github/issues/AdamFull/IoT_Screen_Emulator.svg)](https://github.com/AdamFull/EasyDelegate/issues)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT)

## Problem

-----------------------------------

The standard language library provides a mechanism for storing functional objects in std::function<> and binding by the std tool::bind migrated from boost. This mechanism has some disadvantages, especially with passing std:: placeholder as parameters of std:: bind.

## Why is it necessary

----------------------------------

This library makes working with delegates much easier. It allows you to create functional objects in the same way as std::function, but changes the mechanism for binding a function to a functional object.
The delegate is based on std::function, it performs all the main work. EasyDelegate is an abstraction over std::function and implements a different function binding mechanism.

## Features (more information on the wiki)

---------------------------------

* Creating simple and convenient delegates using [TDelegate](https://github.com/AdamFull/EasyDelegate/wiki/Class-__Delegate).
* Creating a delegate container with the same function signature using [TDelegateMulti](https://github.com/AdamFull/EasyDelegate/wiki/Class-__DelegateMulti). It can also be used for a simple event system.
* Creating a container of compile-time delegates using [TDelegateAnyCT](https://github.com/AdamFull/EasyDelegate/wiki/Struct-__DelegateAnyCT). (There are problems at the moment.)
* Creating a container of runtime delegates using [TDelegateAny](https://github.com/AdamFull/EasyDelegate/wiki/Struct-__DelegateAny) tools. (Development is underway)

## License

-------

MIT © [AdamFull](https://github.com/AdamFull) && [range36rus](https://github.com/range36rus).
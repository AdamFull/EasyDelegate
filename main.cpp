#include <iostream>
#include "examples/examples.h"
#include "EasyDelegateMultiImpl.hpp"

int main()
{
    manual_using::manual_using_fun();
    shared_delegates::linked_delegates_fun();
    multi_delegate::multi_delegate_fun();

    return 0;
}
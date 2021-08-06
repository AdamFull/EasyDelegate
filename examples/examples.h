#pragma once

namespace manual_using
{
    void manual_using_fun();
    int foo(int x, int y, bool ts);
}

namespace shared_delegates
{
    void linked_delegates_fun();
    int foo(int x, int y, bool ts);
}

namespace multi_delegate
{
    void foo(int x, int y);
    void boo(int x, int y);
    int ifoo(int x, int y);
    int iboo(int x, int y);
    void multi_delegate_fun();
}
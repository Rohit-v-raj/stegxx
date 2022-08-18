#pragma once

#include <iostream>

namespace steg
{
    template <typename __baseTp>
    class __base_type
    {
    protected:
        struct data
        {
            using basetype = __baseTp;
        };
        __baseTp _data;
    };
} // namespace steg

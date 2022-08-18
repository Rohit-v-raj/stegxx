#pragma once

#include "base_type.hpp"

#include <string>

namespace steg
{
    class message;
    typedef class message message_t;

    class message : public __base_type<std::string>
    {
    public:
        struct data : __base_type<std::string>::data
        {
            using enctype = std::string;
        };

        message(const data::basetype &msg = data::basetype());
        message(const char *msg);

        data::basetype ascii() const { return _data; }
        data::enctype binary() const;

        bool operator==(const message_t &other) const;

        static message from_binary(data::enctype bstr);
    };

} // namespace steg

#pragma once

#include "base_type.hpp"

namespace steg
{
    class byte_t : public __base_type<uint8_t>
    {
    public:
        byte_t(data::basetype b = 0);

        void setLSB(int pos, bool bit);
        bool getLSB(int pos) const;

        template <typename Tp>
        Tp as() const { return static_cast<Tp>(_data); }

        friend std::ostream &operator<<(std::ostream &out, const byte_t &b);
        friend std::istream &operator>>(std::istream &in, byte_t &b);

        bool operator==(const byte_t &other) const;
    };
} // namespace steg

#include <limits>

#define BYTE_MAX (int)std::numeric_limits<steg::byte_t::data::basetype>::max()
#define BYTE_MIN (int)std::numeric_limits<steg::byte_t::data::basetype>::min()

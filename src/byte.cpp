#include "types/byte.hpp"
#include "macrologger.hpp"

namespace steg
{
    byte_t::byte_t(byte_t::data::basetype b)
    {
        _data = b;
    }

    void byte_t::setLSB(int pos, bool bit)
    {
        if (pos < 0)
        {
            LOG_WARN("Got invalid value for position, proceeding with 0");
            pos = 0;
        }
        if (pos > 7)
        {
            LOG_WARN("Got invalid value for position, skipped");
            return;
        }

        // Create a mask that has set bit only at given position using bitwise shift
        int mask = 1 << pos;
        int ib = bit ? 1 : 0;

        // using value & ~mask, unset bit at position
        // Then change it to be by doing or of above with (b << p) & mask
        _data = (_data & ~mask) | ((ib << pos) & mask);
    }

    bool byte_t::getLSB(int pos) const
    {
        if (pos < 0)
        {
            LOG_WARN("Got invalid value for position, proceeding with 0");
            pos = 0;
        }

        if (pos > 7)
        {
            LOG_WARN("Got invalid value for position, returning 0");
            return false;
        }

        return _data & (1 << pos);
    }

    std::ostream &operator<<(std::ostream &out, const byte_t &b)
    {
        out << +b._data;
        return out;
    }

    std::istream &operator>>(std::istream &in, byte_t &b)
    {
        int tmp;
        in >> tmp;

        if (tmp > BYTE_MAX || tmp < BYTE_MIN)
        {
            LOG_ERROR("Overflow for type `byte`");
            return in;
        }

        b._data = static_cast<byte_t::data::basetype>(tmp);
        return in;
    }

    bool byte_t::operator==(const byte_t &other) const
    {
        return _data == other._data;
    }

} // namespace steg
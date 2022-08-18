#include "types/message.hpp"
#include "macrologger.hpp"

#include <algorithm>
#include <climits>

namespace steg
{
    message::message(const message::data::basetype &msg)
    {
        _data = msg;
    }

    message::message(const char *msg)
    {
        _data = data::basetype(msg);
    }

    bool message::operator==(const message_t &other) const
    {
        return _data == other._data;
    }

    message::data::enctype message::binary() const
    {
        message::data::enctype bstr;
        bstr.reserve(_data.length() * CHAR_BIT);

        for (const char &ch : _data)
        {
            for (int id = CHAR_BIT - 1; id >= 0; id--)
            {
                bstr += ch & (1 << id) ? '1' : '0';
            }
        }

        return bstr;
    }

    message message::from_binary(data::enctype bstr)
    {
        LOG_DEBUG("Decoding binary string of len: %ld", bstr.length());

        uint64_t extra = bstr.length() % CHAR_BIT;

        if (extra != 0)
        {
            uint64_t to_add = CHAR_BIT - extra;

            bstr.reserve(bstr.length() + to_add);
            bstr.insert(bstr.begin(), to_add, '0');
        }

        data::basetype astr;
        astr.reserve(bstr.length() / CHAR_BIT);

        int ich = 0, count = 0;

        for (const char &ch : bstr)
        {
            ich |= (ch == '1' ? 1 : 0) << (CHAR_BIT - 1 - count);
            count++;

            if (count == CHAR_BIT)
            {
                count = 0;
                astr += char(ich);
                ich = 0;
            }
        }

        // remove everything from null character onwards
        astr.erase(std::find(astr.begin(), astr.end(), '\0'), astr.end());

        LOG_DEBUG("Decoded form: %s", astr.c_str());
        return message(astr);
    }

} // namespace steg
#pragma once

#include "base_type.hpp"
#include "message.hpp"
#include "byte.hpp"
#include <vector>
#include <string>

namespace steg
{
    struct Pixel
    {
        byte_t red, green, blue;

        Pixel(byte_t r = 0, byte_t g = 0, byte_t b = 0)
            : red(r), green(g), blue(b)
        {
        }

        bool operator==(const Pixel &other) const
        {
            return red == other.red &&
                   green == other.green &&
                   blue == other.blue;
        }

        friend std::ostream &operator<<(std::ostream &out, const Pixel &p);
    };

    class PPMImage_t : public __base_type<std::vector<std::vector<Pixel>>>
    {
    public:
        const std::string &fmt() const { return _fmt; }
        const std::vector<std::string> &comments() const { return _comments; }
        const data::basetype &pixels() const { return _data; }

        size_t width() const { return _width; }
        size_t height() const { return _height; }
        uint16_t max_color_value() const { return _max_color_value; }

        friend std::ostream &operator<<(std::ostream &out, const PPMImage_t &ppm);
        friend std::istream &operator>>(std::istream &in, PPMImage_t &ppm);
        friend bool encode(PPMImage_t &ppm, const message_t &msg);

    private:
        std::string _fmt;
        std::vector<std::string> _comments;
        size_t _width, _height;
        uint16_t _max_color_value;

        data::basetype _data;
    };
} // namespace steg

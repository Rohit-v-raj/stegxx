#include "types/PPM.hpp"
#include "macrologger.hpp"

#include <sstream>

static void verify_color_component(steg::byte_t c, steg::byte_t ub)
{
    if (c.as<uint8_t>() > ub.as<uint8_t>())
    {
        LOG_ERROR("Invalid color component");
    }
}

namespace steg
{
    static const char *PPM_MAGIC_NUMBER = "P3";

    std::ostream &operator<<(std::ostream &out, const Pixel &p)
    {
        out << p.red << ' ' << p.green << ' ' << p.blue;
        return out;
    }

    std::ostream &operator<<(std::ostream &out, const PPMImage_t &ppm)
    {
        out << ppm.fmt() << '\n';
        for (const auto &cmt : ppm.comments())
        {
            out << cmt << '\n';
        }

        out << ppm.width() << ' ' << ppm.height() << '\n';
        out << ppm.max_color_value() << '\n';

        for (const auto &row : ppm.pixels())
            for (const auto &pix : row)
                out << pix << '\t';

        return out;
    }

    std::istream &operator>>(std::istream &in, PPMImage_t &ppm)
    {
        std::string line;
        std::getline(in, line);

        if (line != PPM_MAGIC_NUMBER)
        {
            LOG_ERROR("Invalid PPM file");
            throw std::runtime_error("Bad PPM file");
        }

        ppm._fmt = line;

        std::getline(in, line);

        while (line[0] == '#')
        {
            ppm._comments.push_back(line);
            std::getline(in, line);
        }

        std::stringstream ss(line);
        ss >> ppm._width >> ppm._height;
        LOG_DEBUG("Image dimension - %lu x %lu", ppm.width(), ppm.height());

        in >> ppm._max_color_value;

        ppm._data.reserve(ppm.height());

        std::vector<Pixel> tmp_vec;
        tmp_vec.reserve(ppm.width());

        byte_t r, g, b;
        const byte_t max_value(ppm.max_color_value());
        uint16_t pixels_read = 0;
        const uint16_t pixels_total = ppm.width() * ppm.height();

        for (size_t i = 0; i < ppm.height(); i++)
        {
            for (size_t j = 0; j < ppm.width(); j++)
            {
                if (in.eof())
                    break;
    
                in >> r >> g >> b;

                verify_color_component(r, max_value);
                verify_color_component(g, max_value);
                verify_color_component(b, max_value);

                tmp_vec.emplace_back(r, g, b);
                pixels_read++;
            }
            ppm._data.push_back(tmp_vec);
            tmp_vec.clear();
        }

        LOG_DEBUG("Read pixels: %d/%d", pixels_read, pixels_total);
        if (pixels_read != pixels_total)
        {
            LOG_ERROR("Error reading pixels. Expected: %d    Read: %d", pixels_total, pixels_read);
            throw std::runtime_error("Bad PPM file");
        }

        return in;
    }
} // namespace steg
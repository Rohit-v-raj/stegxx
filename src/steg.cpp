#include "steg.hpp"

#include <fstream>
#include <climits>
#include "macrologger.hpp"

namespace steg::PPM
{
    bool load_from_file(const char *file, PPMImage_t &ppm)
    {
        try
        {
            std::ifstream infile(file);
            infile >> ppm;
            infile.close();
            return true;
        }
        catch (std::exception &e)
        {
            LOG_ERROR("Error loading from: %s", file);
            LOG_ERROR("%s", e.what());
            return false;
        }
        LOG_DEBUG("Loaded image from: %s", file);
    }

    bool dump_to_file(const char *file, const PPMImage_t &ppm)
    {
        try
        {
            std::ofstream outfile(file);
            outfile << ppm;
            outfile.close();
            return true;
        }
        catch (std::exception &e)
        {
            LOG_ERROR("Error dumping to: %s", file);
            LOG_ERROR("%s", e.what());
            return false;
        }
        LOG_DEBUG("Saving image as: %s", file);
    }
} // namespace steg::PPM

namespace steg
{
    static const size_t USABLE_LSB = 4;

    bool encode(PPMImage_t &ppm, const message_t &msg)
    {
        std::string bstr = msg.binary();
        std::string::iterator it = bstr.begin();

        const size_t space_available = ppm.height() * ppm.width() * USABLE_LSB;
        const size_t space_required = bstr.length() + CHAR_BIT;

        if (space_required > space_available)
        {
            LOG_ERROR("Image insufficient to encode data");
            LOG_ERROR("Available   : %ld bits", space_available);
            LOG_ERROR("Required    : %ld bits", space_required);
            LOG_ERROR("LSB density : %ld", USABLE_LSB);
            return false;
        }

        LOG_DEBUG("Encoded form: %s", msg.ascii().c_str());
        LOG_DEBUG("Encoding binary string of len: %ld", bstr.length());

        for (size_t i = 0; i < ppm.height(); i++)
        {
            for (size_t j = 0; j < ppm.width(); j++)
            {
                if (it == bstr.end())
                {
                    int k = CHAR_BIT;
                    while (k)
                    {
                        if (j == ppm.width())
                        {
                            j = 0;
                            i++;
                        }

                        for (auto ii = 0; ii < (int)USABLE_LSB; ii++)
                        {
                            ppm._data[i][j].red.setLSB(ii, 0);
                            k--;
                        }
                        j++;
                    }
                    return true;
                }
                for (int ii = 0; ii < (int)USABLE_LSB; ii++)
                {
                    ppm._data[i][j].red.setLSB(ii, *it == '1');
                    it++;
                }
            }
        }
        return true;
    }

    bool decode(const PPMImage_t &ppm, message_t &msg)
    {
        std::string bstr = "";

        int null_count = 0, bits_read = 0;

        for (const auto &row : ppm.pixels())
        {
            for (const auto &pixel : row)
            {
                for (size_t i = 0; i < USABLE_LSB; i++)
                {
                    bool bit = pixel.red.getLSB(i);
                    bstr += (bit ? '1' : '0');
                    bits_read++;

                    if (!bit)
                        null_count++;
                    
                    if (null_count == CHAR_BIT)
                    {
                        msg = message::from_binary(bstr);
                        return true;
                    }

                    if (bit || bits_read % (CHAR_BIT) == 0)
                        null_count = 0;
                }
            }
        }

        LOG_WARN("Undesired state : end of image file");
        msg = message::from_binary(bstr);
        return true;
    }

} // namespace steg
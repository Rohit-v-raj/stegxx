#pragma once

#include "types/PPM.hpp"
#include "types/message.hpp"
#include "types/byte.hpp"

namespace steg
{
    namespace PPM
    {
        bool load_from_file(const char *file, PPMImage_t &ppm);
        bool dump_to_file(const char *file, const PPMImage_t &ppm);
    } // namespace PPM

    bool encode(PPMImage_t &ppm, const message_t &msg);
    bool decode(const PPMImage_t &ppm, message_t &msg);

} // namespace steg

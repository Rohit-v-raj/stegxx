#include "steg.hpp"
#include "macrologger.hpp"

#include <cstring>

static void show_help()
{
    const char *help =
        "Usage: steg++ [-e|-d] file\n"
        "\n"
        "Example:\n"
        "  [ ENCODING ] steg++ -e sample-image.ppm > output-image.ppm\n"
        "  [ DECODING ] steg++ -d output-image.ppm\n";

    std::cerr << help << std::endl;
}

static void FAIL_ON_ERROR(bool res)
{
    if (!res)
        exit(EXIT_FAILURE);
}

static void encode(const char *file)
{
    steg::PPMImage_t ppm;
    FAIL_ON_ERROR(steg::PPM::load_from_file(file, ppm));

    std::cerr << "? Enter message to encode: ";

    std::string message;
    std::getline(std::cin, message);

    FAIL_ON_ERROR(steg::encode(ppm, message));

    std::cout << ppm;

    LOG_INFO("Encoding successful!");
}

static void decode(const char *file)
{
    steg::PPMImage_t ppm;
    FAIL_ON_ERROR(steg::PPM::load_from_file(file, ppm));

    steg::message_t dmsg;

    FAIL_ON_ERROR(steg::decode(ppm, dmsg));
    LOG_INFO("Decoding successful!");

    std::cerr << "Decoded message: ";
    std::cout << dmsg.ascii() << std::endl;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        LOG_ERROR("Incorrect usage");
        show_help();
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-e") == 0)
    {
        encode(argv[2]);
    }
    else if (strcmp(argv[1], "-d") == 0)
    {
        decode(argv[2]);
    }
    else
    {
        return EXIT_FAILURE;
    }
}
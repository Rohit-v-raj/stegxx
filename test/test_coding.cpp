#include "steg.hpp"

#include <gtest/gtest.h>
#include <random>

#define MAX_STR_LEN 4999

static std::string randstr()
{
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    static const size_t lb = 0;
    static const size_t ub = sizeof(alphanum) - 2;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(lb, ub);
    std::string s;

    int n = MAX_STR_LEN;
    while (n--)
        s += alphanum[dist(rng)];

    return s;
}

#define TEST_AGAINST_FILE(_TEST_NAME_, __TEST_PPM_FILE__)                    \
    TEST(EncryptionDecryptionTest, _TEST_NAME_)                              \
    {                                                                        \
        int n = 2;                                                           \
        while (n--)                                                          \
        {                                                                    \
            steg::message_t emsg(randstr()), dmsg;                           \
            steg::PPMImage_t eimg, dimg;                                     \
                                                                             \
            EXPECT_TRUE(steg::PPM::load_from_file(__TEST_PPM_FILE__, eimg)); \
            EXPECT_TRUE(steg::encode(eimg, emsg));                           \
            EXPECT_TRUE(steg::PPM::dump_to_file("/tmp/temp.ppm", eimg));     \
                                                                             \
            EXPECT_TRUE(steg::PPM::load_from_file("/tmp/temp.ppm", dimg));   \
            EXPECT_TRUE(steg::decode(dimg, dmsg));                           \
                                                                             \
            EXPECT_EQ(emsg, dmsg);                                           \
        }                                                                    \
    }

TEST_AGAINST_FILE(FILE1, "../resources/PPM/1.ppm")
// TEST_AGAINST_FILE(FILE2, "../resources/PPM/2.ppm")
// TEST_AGAINST_FILE(FILE3, "../resources/PPM/3.ppm")
// TEST_AGAINST_FILE(FILE4, "../resources/PPM/4.ppm")
// TEST_AGAINST_FILE(FILE5, "../resources/PPM/5.ppm")
// TEST_AGAINST_FILE(FILE6, "../resources/PPM/6.ppm")
// TEST_AGAINST_FILE(FILE7, "../resources/PPM/7.ppm")
// TEST_AGAINST_FILE(FILE8, "../resources/PPM/8.ppm")
// TEST_AGAINST_FILE(FILE9, "../resources/PPM/9.ppm")
// TEST_AGAINST_FILE(FILE10, "../resources/PPM/10.ppm")
// TEST_AGAINST_FILE(FILE11, "resources/PPM/11.ppm")
// TEST_AGAINST_FILE(FILE12, "../resources/PPM/12.ppm")
// TEST_AGAINST_FILE(FILE13, "../resources/PPM/13.ppm")
// TEST_AGAINST_FILE(FILE14, "../resources/PPM/14.ppm")
// TEST_AGAINST_FILE(FILE15, "../resources/PPM/15.ppm")
// TEST_AGAINST_FILE(FILE16, "../resources/PPM/16.ppm")
// TEST_AGAINST_FILE(FILE17, "../resources/PPM/17.ppm")
// TEST_AGAINST_FILE(FILE18, "../resources/PPM/18.ppm")
// TEST_AGAINST_FILE(FILE19, "../resources/PPM/19.ppm")
// TEST_AGAINST_FILE(FILE20, "../resources/PPM/20.ppm")
// TEST_AGAINST_FILE(FILE21, "../resources/PPM/21.ppm")

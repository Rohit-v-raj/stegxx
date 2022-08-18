#include "types/byte.hpp"
#include "types/message.hpp"
#include "types/PPM.hpp"

#include <gtest/gtest.h>
#include <sstream>

TEST(ByteTest, IO)
{
    steg::byte_t b;

    std::stringstream ss("123 255 0");

    ss >> b;
    EXPECT_EQ(b, 123);

    ss >> b;
    EXPECT_EQ(b, 255);

    ss >> b;
    EXPECT_EQ(b, 0);
}

TEST(ByteTest, setLSB)
{
    using namespace steg;

    byte_t b;

    b = byte_t(0);
    b.setLSB(0, 1);
    EXPECT_EQ(b, byte_t(1));

    b = byte_t(0);
    b.setLSB(1, 1);
    EXPECT_EQ(b, byte_t(2));

    b = byte_t(0);
    b.setLSB(2, 1);
    EXPECT_EQ(b, byte_t(4));

    b = byte_t(0);
    b.setLSB(3, 1);
    EXPECT_EQ(b, byte_t(8));

    b = byte_t(0);
    b.setLSB(4, 1);
    EXPECT_EQ(b, byte_t(16));

    b = byte_t(0);
    b.setLSB(5, 1);
    EXPECT_EQ(b, byte_t(32));

    b = byte_t(0);
    b.setLSB(6, 1);
    EXPECT_EQ(b, byte_t(64));

    b = byte_t(0);
    b.setLSB(7, 1);
    EXPECT_EQ(b, byte_t(128));
}

TEST(ByteTest, getLSB)
{
    using namespace steg;

    EXPECT_FALSE(byte_t(0).getLSB(0));
    EXPECT_TRUE(byte_t(2).getLSB(1));
    EXPECT_TRUE(byte_t(4).getLSB(2));
    EXPECT_TRUE(byte_t(8).getLSB(3));
    EXPECT_TRUE(byte_t(16).getLSB(4));
    EXPECT_TRUE(byte_t(32).getLSB(5));
    EXPECT_TRUE(byte_t(64).getLSB(6));
    EXPECT_TRUE(byte_t(128).getLSB(7));

}

TEST(MessageTest, Ascii2Binary)
{
    steg::message_t msg("text");
    std::string bin = "01110100011001010111100001110100";

    EXPECT_EQ(msg.binary(), bin);
}

TEST(MessageTest, Binary2Ascii)
{
    steg::message_t msg("text");
    std::string bin = "01110100011001010111100001110100";

    EXPECT_EQ(msg, steg::message::from_binary(bin));
}

TEST(PPMImageTest, ReadPPM)
{
    const char *PPM =
        "P3\n"
        "# feep.ppma\n"
        "4 4\n"
        "15\n"
        " 0  0  0  0  0  0    0  0  0   15  0 15\n"
        " 0  0  0  0 15  7    0  0  0    0  0  0\n"
        " 0  0  0  0  0  0    0 15  7    0  0  0\n"
        "15  0 15  0  0  0    0  0  0    0  0  0\n";

    std::stringstream ss(PPM);

    steg::PPMImage_t ppm;
    ss >> ppm;

    EXPECT_EQ(ppm.fmt(), "P3");
    EXPECT_EQ(ppm.comments().size(), 1);
    EXPECT_EQ(ppm.comments()[0], "# feep.ppma");
    EXPECT_EQ(ppm.width(), 4);
    EXPECT_EQ(ppm.height(), 4);
    EXPECT_EQ(ppm.max_color_value(), 15);

    EXPECT_EQ(ppm.pixels()[0][0], steg::Pixel(0, 0, 0));
    EXPECT_EQ(ppm.pixels()[0][1], steg::Pixel(0, 0, 0));
    EXPECT_EQ(ppm.pixels()[0][2], steg::Pixel(0, 0, 0));
    EXPECT_EQ(ppm.pixels()[0][3], steg::Pixel(15, 0, 15));

    EXPECT_EQ(ppm.pixels()[1][0], steg::Pixel(0, 0, 0));
    EXPECT_EQ(ppm.pixels()[1][1], steg::Pixel(0, 15, 7));
    EXPECT_EQ(ppm.pixels()[1][2], steg::Pixel(0, 0, 0));
    EXPECT_EQ(ppm.pixels()[1][3], steg::Pixel(0, 0, 0));

    EXPECT_EQ(ppm.pixels()[2][0], steg::Pixel(0, 0, 0));
    EXPECT_EQ(ppm.pixels()[2][1], steg::Pixel(0, 0, 0));
    EXPECT_EQ(ppm.pixels()[2][2], steg::Pixel(0, 15, 7));
    EXPECT_EQ(ppm.pixels()[2][3], steg::Pixel(0, 0, 0));

    EXPECT_EQ(ppm.pixels()[3][0], steg::Pixel(15, 0, 15));
    EXPECT_EQ(ppm.pixels()[3][1], steg::Pixel(0, 0, 0));
    EXPECT_EQ(ppm.pixels()[3][2], steg::Pixel(0, 0, 0));
    EXPECT_EQ(ppm.pixels()[3][3], steg::Pixel(0, 0, 0));
}
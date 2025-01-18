#include <gtest/gtest.h>
#include "util/www/media.h"


TEST(TestMime, TestInvalidMime) {

    EXPECT_THROW({
        util::www::Mime m(std::string(""));
    }, std::invalid_argument);

    EXPECT_THROW({
        util::www::Mime m(std::string("video"));
    }, std::invalid_argument);

    EXPECT_THROW({
        util::www::Mime m(std::string("video/"));
    }, std::invalid_argument);

    EXPECT_THROW({
        util::www::Mime m(std::string("abcde/jpeg"));
    }, std::invalid_argument);

    EXPECT_THROW({
        util::www::Mime m(std::string("IMAGE/jpeg"));
    }, std::invalid_argument);
}

TEST(TestMime, TestOk) {

    auto m1 = util::www::Mime("image/jpeg");
    EXPECT_EQ(m1.get(),  "image/jpeg");
    EXPECT_EQ(m1.get_category(), mailio::mime::media_type_t::IMAGE);
    EXPECT_EQ(m1.get_type(),  "jpeg");

    auto m2 = util::www::Mime("video/mp4");
    EXPECT_EQ(m2.get(),  "video/mp4");
    EXPECT_EQ(m2.get_category(), mailio::mime::media_type_t::VIDEO);
    EXPECT_EQ(m2.get_type(),  "mp4");

    auto m3 = util::www::Mime("audio/mp3");
    EXPECT_EQ(m3.get(),  "audio/mp3");
    EXPECT_EQ(m3.get_category(), mailio::mime::media_type_t::AUDIO);
    EXPECT_EQ(m3.get_type(),  "mp3");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

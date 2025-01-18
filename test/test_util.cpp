#include <gtest/gtest.h>
#include "util/www/media.h"


TEST(TestMime, TestEmptyString) {

    EXPECT_THROW({
        util::www::Mime m(std::string(""));
    }, std::invalid_argument);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

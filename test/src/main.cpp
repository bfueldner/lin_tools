#include <gtest/gtest.h>

#include <lin/test/main.hpp>

namespace lin::test {

std::filesystem::path binary_path;

}

int main(int argc, char **argv)
{
    lin::test::binary_path = std::filesystem::absolute(argv[0]);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

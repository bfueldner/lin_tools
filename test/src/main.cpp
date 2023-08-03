#include <gtest/gtest.h>

#include <lin/test/main.hpp>

namespace lin::test {

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
std::filesystem::path binary_path;

}    // namespace lin::test

int main(int argc, char **argv)
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    lin::test::binary_path = std::filesystem::absolute(argv[0]);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#include <gtest/gtest.h>

#include <lin/common/validate/logger.hpp>

TEST(test_lin_common_logger_validate, ok)
{
    using namespace lin::common::validate;

    logger_t logger{ false, false };

    testing::internal::CaptureStdout();
    logger.log(logger_t::result_t::ok, "name", "message", "value", "help");
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST(test_lin_common_logger_validate, warning)
{
    using namespace lin::common::validate;

    logger_t logger{ false, false };

    testing::internal::CaptureStdout();
    logger.log(logger_t::result_t::warning, "name", "message", "value", "help");
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "name: message 'value' (help)\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST(test_lin_common_logger_validate, error)
{
    using namespace lin::common::validate;

    logger_t logger{ false, false };

    testing::internal::CaptureStdout();
    logger.log(logger_t::result_t::error, "name", "message", "value", "help");
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "name: message 'value' (help)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST(test_lin_common_logger_validate, ok_section)
{
    using namespace lin::common::validate;

    logger_t logger{ false, true };

    testing::internal::CaptureStdout();
    logger.push_section("section");
    logger.log(logger_t::result_t::ok, "name", "message", "value", "help");
    logger.pop_section();
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "section.name: message 'value' (help)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST(test_lin_common_logger_validate, ok_section_name)
{
    using namespace lin::common::validate;

    logger_t logger{ false, true };

    testing::internal::CaptureStdout();
    logger.push_section("section", "name");
    logger.log(logger_t::result_t::ok, "name", "message", "value", "help");
    logger.pop_section();
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(), "section[name].name: message 'value' (help)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST(test_lin_common_logger_validate, ok_verbose)
{
    using namespace lin::common::validate;

    logger_t logger{ false, true };

    testing::internal::CaptureStdout();
    logger.log(logger_t::result_t::ok, "name", "message", "value", "help");
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "name: message 'value' (help)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST(test_lin_common_logger_validate, warning_verbose)
{
    using namespace lin::common::validate;

    logger_t logger{ false, true };

    testing::internal::CaptureStdout();
    logger.log(logger_t::result_t::warning, "name", "message", "value", "help");
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "name: message 'value' (help)\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST(test_lin_common_logger_validate, error_verbose)
{
    using namespace lin::common::validate;

    logger_t logger{ false, true };

    testing::internal::CaptureStdout();
    logger.log(logger_t::result_t::error, "name", "message", "value", "help");
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "name: message 'value' (help)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST(test_lin_common_logger_validate, ok_symbol_verbose)
{
    using namespace lin::common::validate;

    logger_t logger{ true, true };

    testing::internal::CaptureStdout();
    logger.log(logger_t::result_t::ok, "name", "message", "value", "help");
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "\u2705 name: message 'value' (help)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST(test_lin_common_logger_validate, warning_symbol_verbose)
{
    using namespace lin::common::validate;

    logger_t logger{ true, true };

    testing::internal::CaptureStdout();
    logger.log(logger_t::result_t::warning, "name", "message", "value", "help");
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "\u2757 name: message 'value' (help)\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST(test_lin_common_logger_validate, error_symbol_verbose)
{
    using namespace lin::common::validate;

    logger_t logger{ true, true };

    testing::internal::CaptureStdout();
    logger.log(logger_t::result_t::error, "name", "message", "value", "help");
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "\u274C name: message 'value' (help)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

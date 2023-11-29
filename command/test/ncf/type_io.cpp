#include <sstream>

#include <gtest/gtest.h>

#include <lin/ncf/command/type.hpp>
#include <lin/ncf/command/type_io.hpp>

TEST(test_lin_ncf_command_type_io, in_type_export)
{
    using namespace lin::ncf::command;

    type_t type{};

    std::stringstream stream{ "export" };
    stream >> type;
    EXPECT_EQ(type, type_t::export_);
}

TEST(test_lin_ncf_command_type_io, in_type_prettify)
{
    using namespace lin::ncf::command;

    type_t type{};

    std::stringstream stream{ "prettify" };
    stream >> type;
    EXPECT_EQ(type, type_t::prettify);
}

TEST(test_lin_ncf_command_type_io, in_type_validate)
{
    using namespace lin::ncf::command;

    type_t type{};

    std::stringstream stream{ "validate" };
    stream >> type;
    EXPECT_EQ(type, type_t::validate);
}

TEST(test_lin_ncf_command_type_io, in_type_unknown)
{
    using namespace lin::ncf::command;

    type_t type{};

    std::stringstream stream{ "unknown" };
    EXPECT_TRUE(stream.good());
    EXPECT_FALSE(stream.fail());
    stream >> type;
    EXPECT_FALSE(stream.good());
    EXPECT_TRUE(stream.fail());
}

TEST(test_lin_ncf_command_type_io, in_export_type_frame)
{
    using namespace lin::ncf::command;

    export_type_t type{};

    std::stringstream stream{ "frame" };
    stream >> type;
    EXPECT_EQ(type, export_type_t::frame);
}

TEST(test_lin_ncf_command_type_io, in_export_type_signal)
{
    using namespace lin::ncf::command;

    export_type_t type{};

    std::stringstream stream{ "signal" };
    stream >> type;
    EXPECT_EQ(type, export_type_t::signal);
}

TEST(test_lin_ncf_command_type_io, in_export_type_unknown)
{
    using namespace lin::ncf::command;

    export_type_t type{};

    std::stringstream stream{ "unknown" };
    EXPECT_TRUE(stream.good());
    EXPECT_FALSE(stream.fail());
    stream >> type;
    EXPECT_FALSE(stream.good());
    EXPECT_TRUE(stream.fail());
}

TEST(test_lin_ncf_command_type_io, out_type_export)
{
    using namespace lin::ncf::command;

    auto const type{ type_t::export_ };

    std::stringstream stream{};
    stream << type;
    EXPECT_EQ(stream.str(), "export");
}

TEST(test_lin_ncf_command_type_io, out_type_prettify)
{
    using namespace lin::ncf::command;

    auto const type{ type_t::prettify };

    std::stringstream stream{};
    stream << type;
    EXPECT_EQ(stream.str(), "prettify");
}

TEST(test_lin_ncf_command_type_io, out_type_validate)
{
    using namespace lin::ncf::command;

    auto const type{ type_t::validate };

    std::stringstream stream{};
    stream << type;
    EXPECT_EQ(stream.str(), "validate");
}

TEST(test_lin_ncf_command_type_io, out_type_unknown)
{
    using namespace lin::ncf::command;

    auto const type{ static_cast< type_t >(15) };

    std::stringstream stream{};
    stream << type;
    EXPECT_EQ(stream.str(), "<unknown>");
}

TEST(test_lin_ncf_command_type_io, out_export_type_frame)
{
    using namespace lin::ncf::command;

    auto const type{ export_type_t::frame };

    std::stringstream stream{};
    stream << type;
    EXPECT_EQ(stream.str(), "frame");
}

TEST(test_lin_ncf_command_type_io, out_export_type_signal)
{
    using namespace lin::ncf::command;

    auto const type{ export_type_t::signal };

    std::stringstream stream{};
    stream << type;
    EXPECT_EQ(stream.str(), "signal");
}

TEST(test_lin_ncf_command_type_io, out_export_type_unknown)
{
    using namespace lin::ncf::command;

    auto const type{ static_cast< export_type_t >(15) };

    std::stringstream stream{};
    stream << type;
    EXPECT_EQ(stream.str(), "<unknown>");
}

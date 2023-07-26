#include <gtest/gtest.h>

#include <lin/lexical/ncf/node.hpp>

TEST(test_lin_lexical_ncf_node, node)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ncf;

    std::string text{
        "node step_motor {"
        "    free_text { \"step_motor signal values outside 0 - 199 are ignored\" }"
        "    status_management {"
        "        fault_state_signals = fault_state;"
        "        response_error = error_bit;"
        "    }"
        "    encoding {"
        "        position {physical_value, 0, 199, 1.8, 0, \"deg\";}"
        "        fault_enc {logical_value, 0, \"no result\";"
        "                   logical_value, 1, \"failed\";"
        "                   logical_value, 2, \"passed\";}"
        "    }"
        "    frames {"
        "        publish node_status {"
        "            length = 4; min_period = 10 ms; max_period = 100 ms;"
        "            signals {"
        "                state {size = 8; init_value = 0; offset = 0;}"
        "                fault_state {size = 2; init_value = 0; offset = 9; fault_enc;}"
        "                error_bit {size = 1; init_value = 0; offset = 8;}"
        "                angle {size = 16; init_value = {0x22, 0x11}; offset = 16;}"
        "            }"
        "        }"
        "        subscribe control {"
        "            length = 1; max_period = 100 ms;"
        "            signals {"
        "                command {size = 8; init_value = 0; offset = 0; position;}"
        "            }"
        "        }"
        "    }"
        "    diagnostic {"
        "        NAD = 1 to 3;"
        "        diagnostic_class = 2;"
        "        P2_min = 100 ms; ST_min = 40 ms;"
        "        support_sid { 0xB0, 0xB2, 0xB7 };"
        "    }"
        "    general {"
        "        LIN_protocol_version = \"2.2\";"
        "        supplier = 0x0005; function = 0x0020; variant = 1;"
        "        bitrate = automatic min 10 kbps max 20 kbps;"
        "        sends_wake_up_signal = \"yes\";"
        "    }"
        "}"
    };
    node_t node{};

    try
    {
        auto position = text.begin();
        auto result =
            phrase_parse(position, text.end(), parser::node_definition, x3::ascii::space, node);
        ASSERT_TRUE(result);
        ASSERT_EQ(position, text.end());
    }
    catch (const boost::spirit::x3::expectation_failure< std::string::iterator > &exp)
    {
        std::cout << exp.where().base() << std::endl;
        std::cout << exp.which() << std::endl;
        std::cout << exp.what() << std::endl;
    }

    EXPECT_STREQ(node.node_name.c_str(), "step_motor");
    ASSERT_EQ(node.diagnostic.diagnostic_class, 2);
    ASSERT_EQ(node.diagnostic.p2_min, 100.0);
    ASSERT_EQ(node.diagnostic.st_min, 40.0);
    ASSERT_EQ(node.frames.size(), 2);
    ASSERT_EQ(node.encodings.size(), 2);
    EXPECT_STREQ(node.status.response_error.c_str(), "error_bit");
    EXPECT_STREQ(node.status.fault_state_signals.front().c_str(), "fault_state");
    EXPECT_STREQ(node.free_text.c_str(), "step_motor signal values outside 0 - 199 are ignored");
}

#include <string>

#include <gtest/gtest.h>

#include <lin/ldf/frame_diagnostic.hpp>
#include <lin/ldf/parser/frame_diagnostic.hpp>

/* 9.2.4.4 Diagnostic frames */

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST(test_lin_ldf_frame_diagnostic_parser, diagnostic_frame)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{
        "MasterReq: 60 {"
        "    MasterReqB0, 0;"
        "    MasterReqB1, 8;"
        "    MasterReqB2, 16;"
        "    MasterReqB3, 24;"
        "    MasterReqB4, 32;"
        "    MasterReqB5, 40;"
        "    MasterReqB6, 48;"
        "    MasterReqB7, 56;"
        "}"
    };
    frame::diagnostic_t frame{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::diagnostic_frame, x3::ascii::space, frame);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    EXPECT_STREQ(frame.name.c_str(), "MasterReq");
    EXPECT_EQ(frame.id, 60);
    EXPECT_EQ(frame.signals.size(), 8);

    int index = 0;
    for (auto const &signal : frame.signals)
    {
        std::string const name = "MasterReqB" + std::to_string(index);

        EXPECT_STREQ(signal.name.c_str(), name.c_str());
        EXPECT_EQ(signal.offset, index * 8);
        index++;
    }
}
// NOLINTEND(readability-function-cognitive-complexity)

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST(test_lin_ldf_frame_diagnostic_parser, diagnostic_frames)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{
        "Diagnostic_frames {"
        "    MasterReq: 60 {"
        "        MasterReqB0, 0;"
        "        MasterReqB1, 8;"
        "        MasterReqB2, 16;"
        "        MasterReqB3, 24;"
        "        MasterReqB4, 32;"
        "        MasterReqB5, 40;"
        "        MasterReqB6, 48;"
        "        MasterReqB7, 56;"
        "    }"
        "    SlaveResp: 61 {"
        "         SlaveRespB0, 0;"
        "         SlaveRespB1, 8;"
        "         SlaveRespB2, 16;"
        "         SlaveRespB3, 24;"
        "         SlaveRespB4, 32;"
        "         SlaveRespB5, 40;"
        "         SlaveRespB6, 48;"
        "         SlaveRespB7, 56;"
        "    }"
        "}"
    };
    frame::diagnostics_t frames{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::diagnostic_frames, x3::ascii::space, frames);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    EXPECT_EQ(frames.size(), 2);

    EXPECT_STREQ(frames[0].name.c_str(), "MasterReq");
    EXPECT_EQ(frames[0].id, 60);
    EXPECT_EQ(frames[0].signals.size(), 8);

    int index = 0;
    for (auto const &signal : frames[0].signals)
    {
        std::string const name = "MasterReqB" + std::to_string(index);

        EXPECT_STREQ(signal.name.c_str(), name.c_str());
        EXPECT_EQ(signal.offset, index * 8);
        index++;
    }

    EXPECT_STREQ(frames[1].name.c_str(), "SlaveResp");
    EXPECT_EQ(frames[1].id, 61);
    EXPECT_EQ(frames[1].signals.size(), 8);

    index = 0;
    for (auto const &signal : frames[1].signals)
    {
        std::string const name = "SlaveRespB" + std::to_string(index);

        EXPECT_STREQ(signal.name.c_str(), name.c_str());
        EXPECT_EQ(signal.offset, index * 8);
        index++;
    }
}
// NOLINTEND(readability-function-cognitive-complexity)

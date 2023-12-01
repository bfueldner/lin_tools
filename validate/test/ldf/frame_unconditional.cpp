#include <gtest/gtest.h>

#include <lin/common/validate/logger.hpp>
#include <lin/ldf/frame_unconditional.hpp>
#include <lin/ldf/nodes.hpp>
#include <lin/ldf/signal_standard.hpp>
#include <lin/ldf/validate/frame_unconditional.hpp>

/* 9.2.4.1 Unconditional frames */

class test_lin_ldf_frame_unconditional_validate: public testing::Test
{
  public:
    lin::common::validate::logger_t logger{ false, true };
};

TEST_F(test_lin_ldf_frame_unconditional_validate, id)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standards_t const signals{};
    frame::unconditional_t const frame{ .id = 0x10 };

    validate::frame::unconditional::id_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signals, frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "id\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_frame_unconditional_validate, id_error_too_low)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standards_t const signals{};
    frame::unconditional_t const frame{ .id = -1 };

    validate::frame::unconditional::id_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signals, frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "id: Value too low '-1' (0..59)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_frame_unconditional_validate, id_error_too_high)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standards_t const signals{};
    frame::unconditional_t const frame{ .id = 60 };

    validate::frame::unconditional::id_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signals, frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "id: Value too high '60' (0..59)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_frame_unconditional_validate, published_by_master)
{
    using namespace lin::ldf;

    nodes_t const nodes{ .master = { .name = "CEM" }, .slaves = { "LSM", "RSM" } };
    signal::standards_t const signals{};
    frame::unconditional_t const frame{ .published_by = "CEM" };

    validate::frame::unconditional::published_by_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signals, frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "published_by\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_frame_unconditional_validate, published_by_slave)
{
    using namespace lin::ldf;

    nodes_t const nodes{ .master = { .name = "CEM" }, .slaves = { "LSM", "RSM" } };
    signal::standards_t const signals{};
    frame::unconditional_t const frame{ .published_by = "LSM" };

    validate::frame::unconditional::published_by_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signals, frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "published_by\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_frame_unconditional_validate, published_by_error_not_defined_master)
{
    using namespace lin::ldf;

    nodes_t const nodes{ .slaves = { "LSM", "RSM" } };
    signal::standards_t const signals{};
    frame::unconditional_t const frame{ .published_by = "CEM" };

    validate::frame::unconditional::published_by_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signals, frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "published_by: Not defined 'CEM'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_frame_unconditional_validate, published_by_error_not_defined_slave)
{
    using namespace lin::ldf;

    nodes_t const nodes{ .master = { .name = "CEM" }, .slaves = { "RSM" } };
    signal::standards_t const signals{};
    frame::unconditional_t const frame{ .published_by = "LSM" };

    validate::frame::unconditional::published_by_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signals, frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "published_by: Not defined 'LSM'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_frame_unconditional_validate, size)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standards_t const signals{};
    frame::unconditional_t const frame{ .size = 1 };

    validate::frame::unconditional::size_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signals, frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "size\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_frame_unconditional_validate, size_error_too_low)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standards_t const signals{};
    frame::unconditional_t const frame{ .id = 0 };

    validate::frame::unconditional::size_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signals, frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "size: Value too low '0' (1..64)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_frame_unconditional_validate, size_error_too_high)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standards_t const signals{};
    frame::unconditional_t const frame{ .size = 65 };

    validate::frame::unconditional::size_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signals, frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "size: Value too high '65' (1..64)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_frame_unconditional_validate, signal_published_by)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standards_t const signals{
        signal::standard_t{ .name = "LSMerror", .published_by = "LSM" },
        signal::standard_t{ .name = "RSMerror", .published_by = "RSM" },
        signal::standard_t{ .name = "IntError", .published_by = "LSM" }
    };
    frame::unconditional_t const frame{
        .published_by = "LSM",
        .signals      = { frame::unconditional::signal_t{ .name = "LSMerror" },
                          frame::unconditional::signal_t{ .name = "IntError" } }
    };

    validate::frame::unconditional::signal_published_by_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signals, frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signal_published_by\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_frame_unconditional_validate, signal_published_by_error_wrong_node)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standards_t const signals{
        signal::standard_t{ .name = "LSMerror", .published_by = "LSM" },
        signal::standard_t{ .name = "RSMerror", .published_by = "RSM" },
        signal::standard_t{ .name = "IntError", .published_by = "LSM" }
    };
    frame::unconditional_t const frame{
        .published_by = "RSM",
        .signals      = { frame::unconditional::signal_t{ .name = "RSMerror" },
                          frame::unconditional::signal_t{ .name = "LSMerror" } }
    };

    validate::frame::unconditional::signal_published_by_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signals, frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signal_published_by: Wrong node 'LSM'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_frame_unconditional_validate, signal_sizes)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standards_t const signals{ signal::standard_t{ .name = "SignalA", .size = 2 },
                                       signal::standard_t{ .name = "SignalB", .size = 4 },
                                       signal::standard_t{ .name = "SignalC", .size = 2 } };
    frame::unconditional_t const frame{
        .size    = 1,
        .signals = { frame::unconditional::signal_t{ .name = "SignalA", .offset = 0 },
                     frame::unconditional::signal_t{ .name = "SignalC", .offset = 6 },
                     frame::unconditional::signal_t{ .name = "SignalB", .offset = 2 } }
    };

    validate::frame::unconditional::signal_sizes_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signals, frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signal_sizes\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_frame_unconditional_validate, signal_sizes_empty)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standards_t const signals{};
    frame::unconditional_t const frame{};

    validate::frame::unconditional::signal_sizes_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signals, frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_frame_unconditional_validate, signal_sizes_warning_space)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standards_t const signals{ signal::standard_t{ .name = "SignalA", .size = 2 },
                                       signal::standard_t{ .name = "SignalB", .size = 4 },
                                       signal::standard_t{ .name = "SignalC", .size = 2 } };
    frame::unconditional_t const frame{
        .size    = 2,
        .signals = { frame::unconditional::signal_t{ .name = "SignalC", .offset = 6 },
                     frame::unconditional::signal_t{ .name = "SignalB", .offset = 2 },
                     frame::unconditional::signal_t{ .name = "SignalA", .offset = 0 }

        }
    };

    validate::frame::unconditional::signal_sizes_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signals, frame);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "signal_sizes: Signals with unused space '8 bit' (16 bit)\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_frame_unconditional_validate, signal_sizes_error_size)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standards_t const signals{ signal::standard_t{ .name = "SignalA", .size = 2 },
                                       signal::standard_t{ .name = "SignalB", .size = 4 },
                                       signal::standard_t{ .name = "SignalC", .size = 3 } };
    frame::unconditional_t const frame{
        .size    = 1,
        .signals = { frame::unconditional::signal_t{ .name = "SignalA", .offset = 0 },
                     frame::unconditional::signal_t{ .name = "SignalB", .offset = 2 },
                     frame::unconditional::signal_t{ .name = "SignalC", .offset = 6 } }
    };

    validate::frame::unconditional::signal_sizes_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signals, frame);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "signal_sizes: Signals greater than frame '1 bit' (8 bit)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_frame_unconditional_validate, signal_offsets)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standards_t const signals{ signal::standard_t{ .name = "SignalA", .size = 2 },
                                       signal::standard_t{ .name = "SignalB", .size = 4 },
                                       signal::standard_t{ .name = "SignalC", .size = 2 } };
    frame::unconditional_t const frame{
        .size    = 1,
        .signals = { frame::unconditional::signal_t{ .name = "SignalA", .offset = 0 },
                     frame::unconditional::signal_t{ .name = "SignalC", .offset = 6 },
                     frame::unconditional::signal_t{ .name = "SignalB", .offset = 2 } }
    };

    validate::frame::unconditional::signal_offsets_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signals, frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signal_offsets\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_frame_unconditional_validate, signal_offsets_empty)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standards_t const signals{};
    frame::unconditional_t const frame{};

    validate::frame::unconditional::signal_offsets_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signals, frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_frame_unconditional_validate, signal_offsets_error_overlap)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standards_t const signals{ signal::standard_t{ .name = "SignalA", .size = 2 },
                                       signal::standard_t{ .name = "SignalB", .size = 5 },
                                       signal::standard_t{ .name = "SignalC", .size = 2 },
                                       signal::standard_t{ .name = "SignalD", .size = 1 } };
    frame::unconditional_t const frame{
        .size    = 1,
        .signals = { frame::unconditional::signal_t{ .name = "SignalD", .offset = 7 },
                     frame::unconditional::signal_t{ .name = "SignalA", .offset = 0 },
                     frame::unconditional::signal_t{ .name = "SignalC", .offset = 6 },
                     frame::unconditional::signal_t{ .name = "SignalB", .offset = 2 } }
    };

    validate::frame::unconditional::signal_offsets_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signals, frame);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "signal_offsets: Signal overlap 'SignalC, SignalD'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_frame_unconditional_validate, signals)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standards_t const signals{};
    frame::unconditional_t const frame{ .signals = {
                                            frame::unconditional::signal_t{ .offset = 0 },
                                            frame::unconditional::signal_t{ .offset = 1 } } };

    validate::frame::unconditional::signals_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signals, frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signals\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_frame_unconditional_validate, signals_warning_empty)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standards_t const signals{};
    frame::unconditional_t const frame{ .signals = {} };

    validate::frame::unconditional::signals_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signals, frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signals: Empty\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_frame_unconditional_validate, signals_warning_not_sorted)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standards_t const signals{};
    frame::unconditional_t const frame{ .signals = {
                                            frame::unconditional::signal_t{ .offset = 1 },
                                            frame::unconditional::signal_t{ .offset = 0 } } };

    validate::frame::unconditional::signals_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signals, frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signals: Not sorted\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_frame_unconditional_validate, signal_name)
{
    using namespace lin::ldf;

    signal::standards_t const signals{ signal::standard_t{ .name = "LSMerror" },
                                       signal::standard_t{ .name = "RSMerror" } };
    frame::unconditional::signal_t const signal{ .name = "LSMerror" };

    validate::frame::unconditional::signal::name_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "name\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_frame_unconditional_validate, signal_name_error_not_defined)
{
    using namespace lin::ldf;

    signal::standards_t const signals{ signal::standard_t{ .name = "RSMerror" } };
    frame::unconditional::signal_t const signal{ .name = "LSMerror" };

    validate::frame::unconditional::signal::name_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "name: Not defined 'LSMerror'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_frame_unconditional_validate, signal_offset)
{
    using namespace lin::ldf;

    signal::standards_t const signals{};
    frame::unconditional::signal_t const signal{ .offset = 0 };

    validate::frame::unconditional::signal::offset_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "offset\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_frame_unconditional_validate, signal_offset_error_too_low)
{
    using namespace lin::ldf;

    signal::standards_t const signals{};
    frame::unconditional::signal_t const signal{ .offset = -1 };

    validate::frame::unconditional::signal::offset_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "offset: Value too low '-1' (0..63)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_frame_unconditional_validate, signal_offset_error_too_high)
{
    using namespace lin::ldf;

    signal::standards_t const signals{};
    frame::unconditional::signal_t const signal{ .offset = 64 };

    validate::frame::unconditional::signal::offset_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "offset: Value too high '64' (0..63)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

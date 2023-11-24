#include <cstdint>

#include <gtest/gtest.h>
#include <type_traits>

template < typename T, std::underlying_type_t< T > min_, std::underlying_type_t< T > max_ >
requires std::is_enum_v< T >
class signal_t
{
  public:
    using enum_t = T;
    using base_t = std::underlying_type_t< T >;

    explicit signal_t(base_t init):
        _value{ init }
    {
    }

    operator enum_t() const    // NOLINT(hicpp-explicit-conversions)
    {
        return static_cast< enum_t >(_value);
    }
    operator base_t() const { return _value; }    // NOLINT(hicpp-explicit-conversions)

    signal_t &operator=(enum_t value)
    {
        _value = static_cast< base_t >(value);
        return *this;
    }
    signal_t &operator=(base_t value)
    {
        if ((value >= min_) && (value <= max_))
        {
            _value = value;
        }
        return *this;
    }

  private:
    base_t _value;
};

enum class logic_t : std::uint8_t
{
    min   = 0,
    max   = 251,
    reset = 255,
};

using logic_signal_t = signal_t< logic_t, 1, 250 >;

//NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
TEST(test_lin_common_signal_command, usage)
{
    logic_signal_t signal{ 0xFF };

    EXPECT_EQ(signal, logic_t::reset);
    EXPECT_EQ(signal, 0xFF);
    EXPECT_EQ(*reinterpret_cast< std::uint8_t * >(&signal), 0xFF);

    signal = logic_t::min;
    EXPECT_EQ(signal, logic_t::min);
    EXPECT_EQ(signal, 0x00);
    EXPECT_EQ(*reinterpret_cast< std::uint8_t * >(&signal), 0x00);

    signal = logic_t::max;
    EXPECT_EQ(signal, logic_t::max);
    EXPECT_EQ(signal, 0xFB);
    EXPECT_EQ(*reinterpret_cast< std::uint8_t * >(&signal), 0xFB);

    /* Ignore assignment and keep old value */
    signal = 0;
    EXPECT_EQ(signal, logic_t::max);
    EXPECT_EQ(signal, 0xFB);
    EXPECT_EQ(*reinterpret_cast< std::uint8_t * >(&signal), 0xFB);

    /* Allow assignment within range */
    signal = 1;
    EXPECT_NE(signal, logic_t::min);
    EXPECT_NE(signal, logic_t::max);
    EXPECT_EQ(signal, 1);
    EXPECT_EQ(*reinterpret_cast< std::uint8_t * >(&signal), 1);

    signal = 250;
    EXPECT_NE(signal, logic_t::min);
    EXPECT_NE(signal, logic_t::max);
    EXPECT_EQ(signal, 250);
    EXPECT_EQ(*reinterpret_cast< std::uint8_t * >(&signal), 250);
}
//NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)

//NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast, cppcoreguidelines-pro-type-const-cast)
TEST(test_lin_common_signal_command, const_usage)
{
    logic_signal_t const signal{ 0xFF };

    /* Assignments not possible due to const type */
    //signal = logic_t::reset;
    //signal = 0;

    *reinterpret_cast< std::uint8_t * >(const_cast< logic_signal_t * >(&signal)) = 0;
    EXPECT_EQ(signal, logic_t::min);
    EXPECT_EQ(signal, 0);

    *reinterpret_cast< std::uint8_t * >(const_cast< logic_signal_t * >(&signal)) = 251;
    EXPECT_EQ(signal, logic_t::max);
    EXPECT_EQ(signal, 251);

    *reinterpret_cast< std::uint8_t * >(const_cast< logic_signal_t * >(&signal)) = 1;
    EXPECT_NE(signal, logic_t::min);
    EXPECT_NE(signal, logic_t::max);
    EXPECT_EQ(signal, 1);
}
//NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast, cppcoreguidelines-pro-type-const-cast)

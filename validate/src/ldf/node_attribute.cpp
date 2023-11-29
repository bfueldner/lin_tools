#include <string>
#include <vector>

#include <lin/common/validate/version.hpp>
#include <lin/ldf/node_attribute.hpp>
#include <lin/ldf/signal_standard.hpp>
#include <lin/ldf/validate/node_attribute.hpp>

namespace lin::ldf::validate::node::attribute {

void product_id_t::run(
    const signal::standards_t & /*unused*/,
    const ldf::node::attribute_t &attribute) const
{
    if (attribute.product_id.has_value())
    {
        auto product_id = attribute.product_id.value();

        auto const supplier_range =
            std::string{ _to_string(supplier_min) + ".." + _to_string(supplier_max) };

        if (product_id.supplier < supplier_min)
        {
            _log_error("Supplier value too low", _to_string(product_id.supplier), supplier_range);
            return;
        }

        if (product_id.supplier > supplier_max)
        {
            _log_error("Supplier value too high", _to_string(product_id.supplier), supplier_range);
            return;
        }

        auto const function_range =
            std::string{ _to_string(function_min) + ".." + _to_string(function_max) };

        if (product_id.function < function_min)
        {
            _log_error("Function value too low", _to_string(product_id.function), function_range);
            return;
        }

        if (product_id.function > function_max)
        {
            _log_error("Function value too high", _to_string(product_id.function), function_range);
            return;
        }

        if (product_id.variant.has_value())
        {
            auto const variant_range =
                std::string{ _to_string(variant_min) + ".." + _to_string(variant_max) };

            if (product_id.variant < variant_min)
            {
                _log_error(
                    "Variant value too low", _to_string(product_id.variant.value()), variant_range);
                return;
            }

            if (product_id.variant > variant_max)
            {
                _log_error(
                    "Variant value too high",
                    _to_string(product_id.variant.value()),
                    variant_range);
                return;
            }
        }

        _log_ok();
    }
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
void attributes_t::run(
    const signal::standards_t & /*unused*/,
    const ldf::node::attribute_t &attribute) const
{
    auto version = common::validate::version::from_string(attribute.protocol_version);

    if (version.high == 1)
    {
        std::vector< std::string > attributes{};

        if (attribute.product_id.has_value())
        {
            attributes.emplace_back("product_id");
        }

        if (attribute.response_error.has_value())
        {
            attributes.emplace_back("response_error");
        }

        if (!attribute.fault_state_signals.empty())
        {
            attributes.emplace_back("fault_state_signals");
        }

        if (attribute.p2_min.has_value())
        {
            attributes.emplace_back("p2_min");
        }

        if (attribute.st_min.has_value())
        {
            attributes.emplace_back("st_min");
        }

        if (attribute.n_as_timeout.has_value())
        {
            attributes.emplace_back("n_as_timeout");
        }

        if (attribute.n_cr_timeout.has_value())
        {
            attributes.emplace_back("n_cr_timeout");
        }

        if (!attribute.configurable_frames.empty())
        {
            attributes.emplace_back("configurable_frames");
        }

        if (!attributes.empty())
        {
            _log_error("LIN 1.x node has LIN 2.x attributes", _to_string(attributes));
            return;
        }
    }

    if (version.high == 2)
    {
        std::vector< std::string > missing{};

        if (!attribute.product_id.has_value())
        {
            missing.emplace_back("product_id");
        }

        if (!attribute.response_error.has_value())
        {
            missing.emplace_back("response_error");
        }

        if (!missing.empty())
        {
            _log_error(
                "LIN 2.x attributes missing", _to_string(missing), "product_id, response_error");
            return;
        }
    }

    _log_ok();
}
// NOLINTEND(readability-function-cognitive-complexity)

void configurable_frames_t::run(
    const signal::standards_t & /*unused*/,
    const ldf::node::attribute_t &attribute) const
{
    auto version = common::validate::version::from_string(attribute.protocol_version);

    if ((version.high == 2) && !attribute.configurable_frames.empty())
    {
        std::vector< std::string > frames{};

        for (auto const &configurable_frame : attribute.configurable_frames)
        {
            if (((version.low == 0) ^ !configurable_frame.id.has_value()) == 0)
            {
                frames.emplace_back(configurable_frame.name);
            }
        }

        if (!frames.empty())
        {
            /* LIN 2.0 */
            if (version.low == 0)
            {
                _log_error("LIN 2.0 configurable frame without message_id", _to_string(frames));
                return;
            }

            /* LIN 2.1+ */
            _log_error("LIN 2.1 configurable frame with message_id", _to_string(frames));
            return;
        }

        for (auto const &configurable_frame : attribute.configurable_frames)
        {
            if ((version.low == 0) && configurable_frame.id.has_value() &&
                ((configurable_frame.id.value() < 0) || (configurable_frame.id.value() > 255)))
            {
                frames.emplace_back(configurable_frame.name);
            }
        }

        if (!frames.empty())
        {
            _log_error(
                "LIN 2.0 configurable frame message_id out of range", _to_string(frames), "0..255");
            return;
        }

        _log_ok();
    }
}

}    // namespace lin::ldf::validate::node::attribute

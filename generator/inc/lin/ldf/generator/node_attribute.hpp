#pragma once

#include <iostream>

#include <lin/ldf/node_attribute.hpp>

/* 9.2.2 Node definition */

namespace lin::ldf::node {

/* 9.2.2.2 Node attributes */

namespace attribute {

std::ostream &operator<<(std::ostream &out, product_id_t const &product_id);
std::ostream &operator<<(std::ostream &out, configurable_frame_t const &configurable_frame);
std::ostream &operator<<(std::ostream &out, configurable_frames_t const &configurable_frames);

}    // namespace attribute

std::ostream &operator<<(std::ostream &out, attribute_t const &attribute);
std::ostream &operator<<(std::ostream &out, attributes_t const &attributes);

}    // namespace lin::ldf::node

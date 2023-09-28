#pragma once

#include <iostream>

#include <lin/ldf/node.hpp>

/* 9.2.2 Node definition */

namespace lin::ldf::node {

/* 9.2.2.1 Participating nodes */

namespace participating_nodes {

std::ostream &operator<<(std::ostream &out, master_t const &master);
std::ostream &operator<<(std::ostream &out, slaves_t const &slaves);

}    // namespace participating_nodes

std::ostream &operator<<(std::ostream &out, participating_nodes_t const &participating_nodes);

/* 9.2.2.2 Node attributes */

namespace node_attribute {

std::ostream &operator<<(std::ostream &out, product_id_t const &product_id);
std::ostream &operator<<(std::ostream &out, configurable_frame_t const &configurable_frame);
std::ostream &operator<<(std::ostream &out, configurable_frames_t const &configurable_frames);

}    // namespace node_attribute

std::ostream &operator<<(std::ostream &out, node_attribute_t const &node_attribute);
std::ostream &operator<<(std::ostream &out, node_attributes_t const &node_attributes);

/* 9.2.2.3 Node composition definition */

namespace node_composition {

std::ostream &operator<<(std::ostream &out, composition_t const &composition);
std::ostream &operator<<(std::ostream &out, configuration_t const &configuration);

}    // namespace node_composition

std::ostream &operator<<(std::ostream &out, node_composition_t const &node_composition);

}    // namespace lin::ldf::node

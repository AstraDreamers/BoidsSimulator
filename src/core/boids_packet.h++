#pragma once
#include "../config/simulation_config.h++"

/// @brief Boids Packet that contains gain variables and vision range, mainly for communicating between modules.
struct boids_packet {
    float gain_separation{simulation_config::initialization_gain_separation};
    float gain_alignment{simulation_config::initialization_gain_alignment};
    float gain_cohesion{simulation_config::initialization_gain_cohesion};
    float vision_range{simulation_config::initialization_vision_range};
};
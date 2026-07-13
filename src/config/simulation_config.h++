#pragma once

namespace simulation_config {
    constexpr inline float minimum_distance_square{0.01F};
    constexpr inline float initialization_gain_separation{1.F};
    constexpr inline float initialization_gain_alignment{1.F};
    constexpr inline float initialization_gain_cohesion{1.F};
    constexpr inline float initialization_vision_range{100.F};
} // namespace simulation_config
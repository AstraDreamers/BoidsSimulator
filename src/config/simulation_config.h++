#pragma once

namespace simulation_config {
    constexpr inline float minimum_distance_square{0.01F};

    constexpr inline float initialization_gain_separation{1.F};
    constexpr inline float initialization_gain_alignment{1.F};
    constexpr inline float initialization_gain_cohesion{1.F};
    constexpr inline float initialization_vision_range{100.F};

    constexpr inline float random_initialization_velocity_range{200.F};

    constexpr inline uint32_t boids_count{500U};
    constexpr inline uint32_t boids_point_count{5U};
    constexpr inline float    boids_radius{10.F};
} // namespace simulation_config
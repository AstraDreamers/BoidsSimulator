#pragma once

namespace simulation_config {

    /// **************************************************
    /// ***** Safety Parameters **************************
    /// **************************************************

    /// @brief Minimum squared length between 2 objects to ensure safety.
    /// @note This value should NOT become equal to ZERO (0.F), or the program will crash due to division of 0.
    constexpr inline float min_length_square{0.01F};

    /// **************************************************
    /// ***** Main Parameters Initialization *************
    /// **************************************************

    /// @brief Initialization of separation gain in objects' behavior.
    constexpr inline float init_gain_separation{1.F};

    /// @brief Initialization of alignment gain in objects' behavior.
    constexpr inline float init_gain_alignment{1.F};

    /// @brief Initialization of cohesion gain in objects' behavior.
    constexpr inline float init_gain_cohesion{1.F};

    /// @brief Initialization of vision range in objects' behavior.
    constexpr inline float init_vision_range{100.F};

    /// @brief Initialization of velocity for objects.
    /// @details For example, if the value is 200.F, the velocity for each axis will be randomized from -200.F to 200.F.
    constexpr inline float init_velocity_range{200.F};

    /// @brief Object count in the simulation
    /// @details The object count is constant because the backend uses array, and array requires constant number at
    /// compile time evaluation. We use array to squeeze out performance, as this simulation uses a lot of resources.
    constexpr inline uint32_t init_object_count{1000U};

    /// **************************************************
    /// ***** Render Configurations **********************
    /// **************************************************

    /// @brief Point count in the object's shape.
    constexpr inline uint32_t object_render_point_count{5U};

    /// @brief Object radius in rendering.
    constexpr inline float object_render_radius{10.F};

    /// @brief Objects' rotation rate.
    constexpr inline float object_rotation_per_second{10.F};
} // namespace simulation_config
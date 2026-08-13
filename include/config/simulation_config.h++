/*

BoidsSimulator - A simple flocking simulation.
Copyright (C) 2026  AstraDreamers

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

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
    constexpr inline float init_gain_separation{0.F};

    /// @brief Initialization of alignment gain in objects' behavior.
    constexpr inline float init_gain_alignment{0.F};

    /// @brief Initialization of cohesion gain in objects' behavior.
    constexpr inline float init_gain_cohesion{0.F};

    /// @brief Initialization of vision range in objects' behavior.
    constexpr inline float init_vision_range{100.F};

    /// @brief Initialization of velocity for objects.
    /// @details For example, if the value is 200.F, the velocity for each axis will be randomized from -200.F to 200.F.
    constexpr inline float init_velocity_range{200.F};

    /// @brief Object count in the simulation
    /// @details The object count is constant because the backend uses array, and array requires constant number at
    /// compile time evaluation. We use array to squeeze out performance, as this simulation uses a lot of resources.
    constexpr inline uint32_t init_object_count{200U};

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
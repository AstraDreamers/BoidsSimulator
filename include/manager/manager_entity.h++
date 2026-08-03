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

#include "../config/simulation_config.h++"
#include "../core/simulation_parameters.h++"

/// @brief Managing the entities in the simulation.
class manager_entity {
  public:
    /// @brief Construct a new manager_entity object.
    /// @param window_size The size of the window.
    /// @param boids_packet The variable packets for boids.
    manager_entity(sf::Vector2u window_size, simulation_parameters &simulation_parameters);
    ~manager_entity();

    manager_entity(const manager_entity &)                         = delete;
    auto operator=(const manager_entity &) -> manager_entity &     = delete;
    manager_entity(manager_entity &&) noexcept                     = delete;
    auto operator=(manager_entity &&) noexcept -> manager_entity & = delete;

    /// @brief Update the simulation.
    /// @param time_dt The delta time since the last update.
    auto update(float time_dt) -> void;

    /// @brief Render the simulation.
    /// @param window The window to render to.
    auto render(sf::RenderWindow &window) -> void;

  private:
    [[nodiscard]] static auto wrap_position(const float position, const float max_bounds) noexcept -> float {
        return position - (max_bounds * std::floor(position / max_bounds));
    }

    sf::Vector2u           window_size_{0U, 0U};
    sf::Vector2f           window_size_float_{0.F, 0.F};
    simulation_parameters *simulation_parameters_{nullptr};

    sf::CircleShape render_object_;

    std::array<float, simulation_config::init_object_count> array_position_x_{};
    std::array<float, simulation_config::init_object_count> array_position_y_{};
    std::array<float, simulation_config::init_object_count> array_velocity_x_{};
    std::array<float, simulation_config::init_object_count> array_velocity_y_{};
    std::array<float, simulation_config::init_object_count> array_acceleration_x_{};
    std::array<float, simulation_config::init_object_count> array_acceleration_y_{};
};
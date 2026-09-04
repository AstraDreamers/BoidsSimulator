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
#include "../manager/manager_entity.h++"
#include "../manager/manager_ui.h++"
#include "simulation_parameters.h++"

/// @brief Entry point of the whole program.
class core {
  public:
    core();
    ~core();

    core(const core &)                         = delete;
    auto operator=(const core &) -> core &     = delete;
    core(core &&) noexcept                     = default;
    auto operator=(core &&) noexcept -> core & = delete;

    /// @brief Start the program
    auto run() -> void;

  private:
    auto handle_events() -> void;
    auto update() -> void;
    auto render() -> void;

    sf::RenderWindow window_;
    sf::Vector2u     window_size_{0U, 0U};

    std::unique_ptr<manager_entity> manager_entity_{nullptr};
    std::unique_ptr<manager_ui>     manager_ui_{nullptr};

    sf::Clock clock_;
    sf::Time  dt_;

    sf::VertexArray clear_window_shape_{sf::PrimitiveType::TriangleFan, 4U};

    simulation_parameters simulation_parameters_{
        .gain_separation = simulation_config::init_gain_separation,
        .gain_alignment  = simulation_config::init_gain_alignment,
        .gain_cohesion   = simulation_config::init_gain_cohesion,
        .vision_range    = simulation_config::init_vision_range,
    };
};
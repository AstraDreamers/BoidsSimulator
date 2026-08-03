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

#include "../core/simulation_parameters.h++"
#include "ui/slider.h++"

/// @brief Managing the user interface of the simulation.
class manager_ui {
  public:
    /// @brief Construct a new manager_ui object.
    /// @param window_size The size of the window.
    /// @param simulation_parameters The simulation parameters.
    manager_ui(sf::Vector2u window_size, simulation_parameters &simulation_parameters);
    ~manager_ui();

    manager_ui(const manager_ui &)                         = delete;
    auto operator=(const manager_ui &) -> manager_ui &     = delete;
    manager_ui(manager_ui &&) noexcept                     = default;
    auto operator=(manager_ui &&) noexcept -> manager_ui & = delete;

    /// @brief Update the simulation.
    auto update() const -> void;

    /// @brief Render the simulation.
    /// @param window The window to render to.
    auto render(sf::RenderWindow &window) const -> void;

  private:
    sf::Vector2u           window_size_{0, 0};
    simulation_parameters *simulation_parameters_{nullptr};

    sf::Font font_;

    std::unique_ptr<sf::Text>                text_title_{nullptr};
    std::array<std::unique_ptr<sf::Text>, 4> text_slider_name_{nullptr};
    std::array<std::unique_ptr<sf::Text>, 4> text_slider_value_{nullptr};
    std::array<std::unique_ptr<slider>, 4>   slider_{nullptr};

    static constexpr std::array<std::string, 4> slider_names = {"Separation", "Alignment", "Cohesion", "Vision"};
};
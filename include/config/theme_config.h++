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

namespace theme_config {

    /// *******************************
    /// ***** Main Stuffs *************
    /// *******************************

    /// @brief Background color of the simulator window.
    constexpr inline sf::Color background{10U, 10U, 15U};

    /// @brief Body color of entities.
    constexpr inline sf::Color boids{0U, 255U, 204U};

    /// *******************************
    /// ***** Text ********************
    /// *******************************

    /// @brief The color of the title on the top of the simulator window.
    constexpr inline sf::Color text_title{255U, 0U, 128U};

    /// @brief The color of the name beyond the slider.
    constexpr inline sf::Color text_slider_name{150U, 160U, 175U};

    /// @brief the color of the value beyond the slider.
    constexpr inline sf::Color text_slider_value{0U, 255U, 204U};

    /// *******************************
    /// ***** Sliders *****************
    /// *******************************

    /// @brief The color of the slider's track.
    constexpr inline sf::Color slider_background{30U, 30U, 45U};

    /// @brief The color of the slider's fillU, when active.
    /// @details When hovering on or clicking this sliderU, it will fade from the inactive color to this color.
    /// @see color_palette::slider_inactive
    constexpr inline sf::Color slider_active{255U, 0U, 128U};

    /// @brief The color of the slider's fillU, when inactive.
    /// @details When not hovering on the sliderU, it will return to this color.
    /// @see color_palette::slider_active
    constexpr inline sf::Color slider_inactive{80U, 80U, 100U};
} // namespace theme_config
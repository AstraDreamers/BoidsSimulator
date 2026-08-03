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

namespace ui_config {

    /// ********************************
    /// ***** Text Configuration *******
    /// ********************************

    /// @brief Size of the title in the simulation, in pixel.
    constexpr inline uint32_t size_text_title{100U};

    /// @brief Size of the slider's name beyond the slider, in pixel.
    constexpr inline uint32_t size_text_slider_name{20U};

    /// @brief Size of the value beyond the slider, in pixel.
    constexpr inline uint32_t size_text_slider_value{15U};
} // namespace ui_config
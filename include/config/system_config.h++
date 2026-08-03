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

namespace system_config {

    /// @brief Window's anti-aliasing level.
    /// @details The higher it gets, the better the anti-aliasing is, but with the cost of significantly more GPU usage.
    /// @note Minimum is 0U, maximum is 8U, according to SFML API.
    constexpr inline uint32_t antialiasing_level{8U};

    /// @brief Window's framerate limit (FPS).
    constexpr inline uint32_t framerate_limit{60U};

    /// @brief Pixel's size in OpenGL backend. Default is 32 bits per pixel (RGBA, 8 bits or 1 byte per pixel, 8x4=32).
    constexpr inline uint32_t bits_per_pixel{32U};

    /// @brief Window's title.
    constexpr inline std::string window_title{"BoidsSimulator"};
} // namespace system_config
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

inline constexpr uint8_t simulation_parameters_size{16U};

/// @brief Simulation parameters mainly for communicating between modules.
struct alignas(simulation_parameters_size) simulation_parameters {
    float gain_separation{0.F};
    float gain_alignment{0.F};
    float gain_cohesion{0.F};
    float vision_range{0.F};
};

static_assert(sizeof(simulation_parameters) == simulation_parameters_size, "simulation_parameters layout broken.");
static_assert(std::is_trivially_copyable_v<simulation_parameters>, "simulation_parameters must be trivially copyable.");
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

#include "cli.h++"
#include "core/core.h++"

/// @brief An actual entry point.
auto main(const int32_t cli_argument_count, char *cli_argument_vector[]) -> int32_t {
    if (!cli_handle({const_cast<const char **>(cli_argument_vector), static_cast<std::size_t>(cli_argument_count)})) {
        try {
            core::core core_engine;
            core_engine.run();
        } catch (const std::exception &exception) {
            std::println(stderr, "Exception: {}", exception.what());
        }
    }

    return 0;
}
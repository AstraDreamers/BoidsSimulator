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

#include "core/core.h++"
#include "license.h++"

/// @brief An actual entry point.
auto main(int32_t cli_argument_count, char *cli_argument_vector[]) -> int32_t {
    if (cli_license_handle(cli_argument_count, cli_argument_vector)) {
        return 0;
    }

    core core_engine;
    core_engine.run();
    return 0;
}
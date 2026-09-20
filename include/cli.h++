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

#include "version.h++"

/// @brief Handle CLI section
/// @param cli_arguments args
[[nodiscard]] inline auto cli_handle(std::span<const char *> cli_arguments) -> bool {
    // Check if any arguments were provided after the executable path
    if (cli_arguments.size() > 1) {
        std::string_view subcommand{cli_arguments[1]};

        if (subcommand == "version") {
            std::print("\nBoidsSimulator version {}.{} {}\n\n", PROGRAM_VERSION_MAJOR, PROGRAM_VERSION_MINOR,
                       PROGRAM_VERSION_SPECS);
            return true;
        }

        if (subcommand == "about") {
            // Check for a secondary sub-command (e.g., "about warranty")
            if (cli_arguments.size() > 2) {
                std::string_view detail{cli_arguments[2]};

                if (detail == "warranty") {
                    std::print("\n\033[1m15. Disclaimer of Warranty.\033[0m\n"
                               "\n"
                               "THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY\n"
                               "APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT\n"
                               "HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM \"AS IS\" WITHOUT WARRANTY\n"
                               "OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,\n"
                               "THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR\n"
                               "PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM\n"
                               "IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF\n"
                               "ALL NECESSARY SERVICING, REPAIR OR CORRECTION.\n"
                               "\n"
                               "\033[1m16. Limitation of Liability.\033[0m\n"
                               "\n"
                               "IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING\n"
                               "WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS\n"
                               "THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY\n"
                               "GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE\n"
                               "USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF\n"
                               "DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD\n"
                               "PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS),\n"
                               "EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF\n"
                               "SUCH DAMAGES.\n"
                               "\n"
                               "\033[1m17. Interpretation of Sections 15 and 16.\033[0m\n"
                               "\n"
                               "If the disclaimer of warranty and limitation of liability provided\n"
                               "above cannot be given local legal effect according to their terms,\n"
                               "reviewing courts shall apply local law that most closely approximates\n"
                               "an absolute waiver of all civil liability in connection with the\n"
                               "Program, unless a warranty or assumption of liability accompanies a\n"
                               "copy of the Program in return for a fee.\n\n");
                    return true;
                }

                if (detail == "copyright") {
                    std::print(
                        "\n\033[1mBoidsSimulator - A simple flocking simulation.\033[0m\n"
                        "\033[1mCopyright (C) 2026  AstraDreamers\033[0m\n"
                        "\n"
                        "This program is free software: you can redistribute it and/or modify\n"
                        "it under the terms of the GNU General Public License as published by\n"
                        "the Free Software Foundation, either version 3 of the License, or\n"
                        "(at your option) any later version.\n"
                        "\n"
                        "This program is distributed in the hope that it will be useful,\n"
                        "but \033[1;31mWITHOUT ANY WARRANTY\033[0m; without even the implied warranty of\n"
                        "\033[1;31mMERCHANTABILITY\033[0m or \033[1;31mFITNESS FOR A PARTICULAR PURPOSE\033[0m. "
                        " See the\n"
                        "GNU General Public License for more details.\n"
                        "\n"
                        "You should have received a copy of the GNU General Public License\n"
                        "along with this program.  If not, see \033[1m<https://www.gnu.org/licenses/>\033[0m.\n\n");
                    return true;
                }
            }

            std::print("\n\033[1mBoidsSimulator  Copyright (C) 2026  AstraDreamers\033[0m\n"
                       "This program comes with \033[1;31mABSOLUTELY NO WARRANTY\033[0m;\n"
                       "for details type \033[1m'./BoidsSimulator about warranty'\033[0m.\n"
                       "This is free software, and you are welcome to redistribute it\n"
                       "under certain conditions; type \033[1m'./BoidsSimulator about copyright'\033[0m\n"
                       "for details.\n\n");
            return true;
        }
    }

    return false;
}

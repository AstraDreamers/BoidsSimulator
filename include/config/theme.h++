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

namespace config::theme {

    namespace palette {
        constexpr inline sf::Color rosewater{245U, 224U, 220U};
        constexpr inline sf::Color flamingo{242U, 205U, 205U};
        constexpr inline sf::Color pink{245U, 194U, 231U};
        constexpr inline sf::Color mauve{203U, 166U, 247U};
        constexpr inline sf::Color red{243U, 139U, 168U};
        constexpr inline sf::Color maroon{235U, 160U, 172U};
        constexpr inline sf::Color peach{250U, 179U, 135U};
        constexpr inline sf::Color yellow{249U, 226U, 175U};
        constexpr inline sf::Color green{166U, 227U, 161U};
        constexpr inline sf::Color teal{148U, 226U, 213U};
        constexpr inline sf::Color sky{137U, 220U, 235U};
        constexpr inline sf::Color sapphire{116U, 199U, 236U};
        constexpr inline sf::Color blue{137U, 180U, 250U};
        constexpr inline sf::Color lavender{180U, 190U, 254U};

        constexpr inline sf::Color text{205U, 214U, 244U};
        constexpr inline sf::Color subtext1{186U, 194U, 222U};
        constexpr inline sf::Color subtext0{166U, 173U, 200U};

        constexpr inline sf::Color overlay2{147U, 153U, 178U};
        constexpr inline sf::Color overlay1{127U, 132U, 156U};
        constexpr inline sf::Color overlay0{108U, 112U, 134U};

        constexpr inline sf::Color surface2{88U, 91U, 112U};
        constexpr inline sf::Color surface1{69U, 71U, 90U};
        constexpr inline sf::Color surface0{49U, 50U, 68U};

        constexpr inline sf::Color base{30U, 30U, 46U};
        constexpr inline sf::Color mantle{24U, 24U, 37U};
        constexpr inline sf::Color crust{17U, 17U, 27U};
    } // namespace palette

    /// *******************************
    /// ***** Main Stuffs *************
    /// *******************************

    /// @brief Background color of the simulator window.
    constexpr inline sf::Color background{palette::crust};

    /// @brief Background refresh alpha (0 - 255)
    constexpr inline uint8_t background_refresh_alpha{100U};

    /// @brief Body color of entities (Boids).
    constexpr inline sf::Color boids{palette::teal};

    /// *******************************
    /// ***** Text ********************
    /// *******************************

    /// @brief The color of the title on the top of the simulator window.
    constexpr inline sf::Color text_title{palette::yellow};

    /// @brief The color of the name beyond the slider.
    constexpr inline sf::Color text_slider_name{palette::mauve};

    /// @brief The color of the value beyond the slider.
    constexpr inline sf::Color text_slider_value{palette::subtext0};

    /// *******************************
    /// ***** Sliders *****************
    /// *******************************

    /// @brief The color of the slider's track.
    constexpr inline sf::Color slider_background{palette::surface0};

    /// @brief The color of the slider's fill, when active.
    constexpr inline sf::Color slider_active{palette::sky};

    /// @brief The color of the slider's fill, when inactive.
    constexpr inline sf::Color slider_inactive{palette::blue};
} // namespace config::theme
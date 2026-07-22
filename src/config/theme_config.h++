#pragma once

/// @brief This macro is used for conveniently importing color palette.
/// @note DO NOT USE THIS MACRO
#define rgb(r, g, b) r, g, b
namespace theme_config {

    namespace palette {
        constexpr inline sf::Color rosewater{rgb(245, 224, 220)};
        constexpr inline sf::Color flamingo{rgb(242, 205, 205)};
        constexpr inline sf::Color pink{rgb(245, 194, 231)};
        constexpr inline sf::Color mauve{rgb(203, 166, 247)};
        constexpr inline sf::Color red{rgb(243, 139, 168)};
        constexpr inline sf::Color maroon{rgb(235, 160, 172)};
        constexpr inline sf::Color peach{rgb(250, 179, 135)};
        constexpr inline sf::Color yellow{rgb(249, 226, 175)};
        constexpr inline sf::Color green{rgb(166, 227, 161)};
        constexpr inline sf::Color teal{rgb(148, 226, 213)};
        constexpr inline sf::Color sky{rgb(137, 220, 235)};
        constexpr inline sf::Color sapphire{rgb(116, 199, 236)};
        constexpr inline sf::Color blue{rgb(137, 180, 250)};
        constexpr inline sf::Color lavender{rgb(180, 190, 254)};

        constexpr inline sf::Color text{rgb(205, 214, 244)};
        constexpr inline sf::Color subtext1{rgb(186, 194, 222)};
        constexpr inline sf::Color subtext0{rgb(166, 173, 200)};

        constexpr inline sf::Color overlay2{rgb(147, 153, 178)};
        constexpr inline sf::Color overlay1{rgb(127, 132, 156)};
        constexpr inline sf::Color overlay0{rgb(108, 112, 134)};

        constexpr inline sf::Color surface2{rgb(88, 91, 112)};
        constexpr inline sf::Color surface1{rgb(69, 71, 90)};
        constexpr inline sf::Color surface0{rgb(49, 50, 68)};

        constexpr inline sf::Color base{rgb(30, 30, 46)};
        constexpr inline sf::Color mantle{rgb(24, 24, 37)};
        constexpr inline sf::Color crust{rgb(17, 17, 27)};
    } // namespace palette

    /// *******************************
    /// ***** Main Stuffs *************
    /// *******************************

    /// @brief Background color of the simulator window.
    constexpr inline sf::Color background{palette::mantle};

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
} // namespace theme_config
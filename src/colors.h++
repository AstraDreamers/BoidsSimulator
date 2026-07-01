#pragma once

namespace color_palette {
    /// @brief Background color of the simulator window.
    constexpr sf::Color background{10, 10, 15};

    /// @brief Body color of entities.
    constexpr sf::Color boids{0, 255, 204};

    /// @brief The color of the title on the top of the simulator window.
    constexpr sf::Color text_title{255, 0, 128};

    /// @brief The color of the name beyond the slider.
    constexpr sf::Color text_slider_name{150, 160, 175};

    /// @brief the color of the value beyond the slider.
    constexpr sf::Color text_slider_value{0, 255, 204};

    /// *******************************
    /// Slider Colors
    /// *******************************

    /// @brief The color of the slider's track.
    constexpr sf::Color slider_background{30, 30, 45};

    /// @brief The color of the slider's fill, when active.
    /// @details When hovering on or clicking this slider, it will fade from the inactive color to this color.
    /// @see color_palette::slider_inactive
    constexpr sf::Color slider_active{255, 0, 128};

    /// @brief The color of the slider's fill, when inactive.
    /// @details When not hovering on the slider, it will return to this color.
    /// @see color_palette::slider_active
    constexpr sf::Color slider_inactive{80, 80, 100};
}; // namespace color_palette
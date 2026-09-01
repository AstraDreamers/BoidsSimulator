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

class slider {
  public:
    /// @brief Constructor for slider UI component.
    /// @param value Reference to the float variable that the slider will control.
    /// @param clamp Clamp pair, mathematical model is [`clamp.first`, `clamp.second`].
    slider(float &value, std::pair<float, float> clamp);
    ~slider() = default;

    /// @brief Set the position of the slider.
    /// @param position The new position of the slider.
    auto set_position(sf::Vector2f position) -> void;

    /// @brief Set the size of the slider.
    /// @param size The new size of the slider.
    auto set_size(sf::Vector2f size) -> void;

    /// @brief Set the color of the inactive (unfilled) portion of the slider.
    /// @param color The new color for the inactive portion.
    auto set_color_inactive(sf::Color color) -> void;

    /// @brief Set the color of the active (filled) portion of the slider.
    /// @param color The new color for the active portion.
    auto set_color_active(sf::Color color) -> void;

    /// @brief Set the color of the background (track) of the slider.
    /// @param color The new color for the background.
    auto set_color_background(sf::Color color) -> void;

    /// @brief Update the slider's state based on user interaction and internal logic.
    /// @param mouse_position The current mouse's position in the window, relatively to the window.
    /// @param mouse_clicked `true` when clicked, `false otherwise`.
    auto update(sf::Vector2f mouse_position, bool mouse_clicked) -> void;

    /// @brief Render the slider onto the given SFML render window.
    /// @param window The SFML render window to draw the slider on.
    auto render(sf::RenderWindow &window) const -> void;

  private:
    float *value_{nullptr};
    float  value_clamp_min_{0.F};
    float  value_clamp_max_{0.F};
    float  value_clamp_range_{0.F};
    float  value_internal_{0.F};
    float  value_internal_last_{0.F};

    sf::Vector2f position_{0.F, 0.F};
    sf::Vector2f size_{1.F, 1.F};

    sf::Color color_active_{sf::Color::Cyan};
    sf::Color color_inactive_{sf::Color::Blue};

    sf::CircleShape    circle_left_;
    sf::CircleShape    circle_right_;
    sf::CircleShape    circle_knob_;
    sf::RectangleShape rectangle_background_;
    sf::RectangleShape rectangle_foreground_;

    bool  mouse_click_last_{false};
    bool  mouse_is_locked_{false};
    float knob_scale_{0.F};
    float color_scale_{0.F};

    [[nodiscard]] static auto half_of(const float value) noexcept -> float {
        constexpr float half{0.5F};
        return value * half;
    }

    [[nodiscard]] static auto twice_of(const float value) noexcept -> float {
        constexpr float two{2.F};
        return value * two;
    }

    [[nodiscard]] static auto interpolate_color(const sf::Color &color_a, const sf::Color &color_b,
                                                const float value) noexcept -> sf::Color {
        const auto interpolate = [value](const std::uint8_t color_a,
                                         const std::uint8_t color_b) noexcept -> std::uint8_t {
            const auto result{static_cast<float>(color_a) +
                              (((static_cast<float>(color_b) - static_cast<float>(color_a)) * value))};

            return static_cast<std::uint8_t>(result);
        };

        return sf::Color{interpolate(color_a.r, color_b.r), interpolate(color_a.g, color_b.g),
                         interpolate(color_a.b, color_b.b), interpolate(color_a.a, color_b.a)};
    }

    static constexpr float knob_scale_step{0.05F};
    static constexpr float color_scale_step{0.05F};
    static constexpr float knob_rotation_rate_degrees{10.F};
};
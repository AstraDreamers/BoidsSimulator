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

#include "manager/manager_ui.h++"
#include "config/simulation.h++"
#include "config/theme.h++"
#include "config/ui.h++"

namespace manager {
    manager_ui::manager_ui(const sf::Vector2u window_size, core::simulation_parameters &simulation_parameters)
        : window_size_(window_size), simulation_parameters_(&simulation_parameters) {

        /// ****************************
        /// ***** Font loading *********
        /// ****************************

        try {
            cmrc::embedded_filesystem embedded_filesystem{cmrc::assets::get_filesystem()};
            const std::string         embedded_font_path{"assets/fonts/google_sans.ttf"};

            if (!embedded_filesystem.exists(embedded_font_path)) {
                throw std::unexpected<std::string>("Can't open file " + embedded_font_path);
            }

            cmrc::file font{embedded_filesystem.open(embedded_font_path)};

            if (!font_.openFromMemory(font.begin(), font.size())) {
                throw std::unexpected<std::string>("Can't open stream " + embedded_font_path);
            }

        } catch (const std::exception &exception) {
            std::println(stderr, "Exception: {}\n", exception.what());
            exit(-1);
        }

        /// ****************************
        /// ***** Text *****************
        /// ****************************
        text_title_ = std::make_unique<sf::Text>(font_);
        text_title_->setString("Boids Algorithm");
        text_title_->setCharacterSize(config::ui::size_text_title);
        text_title_->setPosition({20.F, 20.F});
        text_title_->setOrigin(text_title_->getLocalBounds().position);
        text_title_->setFillColor(config::theme::text_title);

        text_fps_ = std::make_unique<sf::Text>(font_);
        text_fps_->setCharacterSize(20U);
        text_fps_->setPosition({window_size_.x - 20.F, 20.F});

        for (uint8_t i = 0U; i < 4U; i++) {
            text_slider_name_.at(i) = std::make_unique<sf::Text>(font_);
            text_slider_name_.at(i)->setCharacterSize(config::ui::size_text_slider_name);
            text_slider_name_.at(i)->setPosition({((static_cast<float>(i) / 4.F) * static_cast<float>(window_size_.x)) +
                                                      (0.05F * static_cast<float>(window_size_.x)),
                                                  0.85F * static_cast<float>(window_size_.y)});
            text_slider_name_.at(i)->setOrigin(text_slider_name_.at(i)->getLocalBounds().position);
            text_slider_name_.at(i)->setFillColor(config::theme::text_slider_name);
            text_slider_name_.at(i)->setString(slider_names.at(i));

            text_slider_value_.at(i) = std::make_unique<sf::Text>(font_);
            text_slider_value_.at(i)->setCharacterSize(config::ui::size_text_slider_value);
            text_slider_value_.at(i)->setPosition(
                {text_slider_name_.at(i)->getPosition().x + text_slider_name_.at(i)->getGlobalBounds().size.x + 10.F,
                 text_slider_name_.at(i)->getPosition().y});
            text_slider_value_.at(i)->setOrigin(text_slider_name_.at(i)->getLocalBounds().position);
            text_slider_value_.at(i)->setFillColor(config::theme::text_slider_value);
        }

        /// ****************************
        /// ***** Slider ***************
        /// ****************************

        slider_[0] = std::make_unique<ui::slider>(simulation_parameters_->gain_separation,
                                                  config::simulation::range_gain_separation);
        slider_[1] = std::make_unique<ui::slider>(simulation_parameters_->gain_alignment,
                                                  config::simulation::range_gain_alignment);
        slider_[2] = std::make_unique<ui::slider>(simulation_parameters_->gain_cohesion,
                                                  config::simulation::range_gain_cohesion);
        slider_[3] =
            std::make_unique<ui::slider>(simulation_parameters_->vision_range, config::simulation::range_vision_range);

        for (uint32_t i = 0; i < 4; i++) {
            slider_.at(i)->set_position({((static_cast<float>(i) / 4.F) * static_cast<float>(window_size_.x)) +
                                             (0.05f * static_cast<float>(window_size_.x)),
                                         0.9f * static_cast<float>(window_size_.y)});
            slider_.at(i)->set_size({0.15f * static_cast<float>(window_size_.x), 10.F});

            slider_.at(i)->set_color_background(config::theme::slider_background);
            slider_.at(i)->set_color_active(config::theme::slider_active);
            slider_.at(i)->set_color_inactive(config::theme::slider_inactive);
        }
    }

    manager_ui::~manager_ui() = default;

    auto manager_ui::update(const float time_dt) -> void {
        const sf::Vector2f mouse_position{sf::Mouse::getPosition()};
        const bool         mouse_clicked{sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)};

        for (const auto &slider : slider_) {
            slider->update(mouse_position, mouse_clicked);
        }

        text_slider_value_[0]->setString(std::format("{:.2f}", simulation_parameters_->gain_separation));
        text_slider_value_[1]->setString(std::format("{:.2f}", simulation_parameters_->gain_alignment));
        text_slider_value_[2]->setString(std::format("{:.2f}", simulation_parameters_->gain_cohesion));
        text_slider_value_[3]->setString(std::format("{:.2f}", simulation_parameters_->vision_range));

        fps_clock_ += time_dt;
        fps_count_++;

        if (fps_clock_ >= 1.F) {
            text_fps_->setString(std::format("FPS: {}", fps_count_));
            text_fps_->setOrigin(text_fps_->getLocalBounds().position +
                                 sf::Vector2f(text_fps_->getLocalBounds().size.x, 0.F));

            fps_clock_ = 0.F;
            fps_count_ = 0U;
        }
    }

    auto manager_ui::render(sf::RenderWindow &window) const -> void {
        window.draw(*text_title_);
        window.draw(*text_fps_);

        for (uint8_t i = 0; i < 4; i++) {
            slider_.at(i)->render(window);
            window.draw(*text_slider_name_.at(i));
            window.draw(*text_slider_value_.at(i));
        }
    }
} // namespace manager
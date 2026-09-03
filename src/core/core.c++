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
#include "config/system_config.h++"
#include "config/theme_config.h++"

core::core() {
    /// Get current user screen size
    sf::VideoMode desktop_mode{sf::VideoMode::getDesktopMode()};
    window_size_ = desktop_mode.size;

    sf::ContextSettings context_settings{};
    context_settings.antiAliasingLevel = system_config::antialiasing_level;

    window_.create(sf::VideoMode(window_size_, system_config::bits_per_pixel), system_config::window_title,
                   sf::Style::Close, sf::State::Fullscreen, context_settings);
    window_.setFramerateLimit(system_config::framerate_limit);

    manager_entity_ = std::make_unique<manager_entity>(window_size_, simulation_parameters_);
    manager_ui_     = std::make_unique<manager_ui>(window_size_, simulation_parameters_);

    clear_window_shape_[0].position = {0.F, 0.F};
    clear_window_shape_[1].position = {static_cast<float>(window_size_.x), 0.F};
    clear_window_shape_[2].position = {static_cast<float>(window_size_.x), static_cast<float>(window_size_.y)};
    clear_window_shape_[3].position = {0.F, static_cast<float>(window_size_.y)};

    for (auto &indices : clear_window_shape_) {
        indices.color = {theme_config::background.r, theme_config::background.g, theme_config::background.b, 150U};
    }
}

core::~core() = default;

auto core::run() -> void {
    while (window_.isOpen()) {
        handle_events();
        if (window_.hasFocus()) {
            update();
            render();
        } else {
            clock_.restart();
            render();
        }
    }
}

auto core::handle_events() -> void {
    while (const auto event{window_.pollEvent()}) {
        if (event->is<sf::Event::Closed>()) {
            window_.close();
        }
    }
}

auto core::update() -> void {
    dt_ = clock_.restart();
    manager_entity_->update(dt_.asSeconds());
    manager_ui_->update();
}

auto core::render() -> void {
    window_.draw(clear_window_shape_);
    manager_entity_->render(window_);
    manager_ui_->render(window_);
    window_.display();
}
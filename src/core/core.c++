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
#include "config/system.h++"
#include "config/theme.h++"

namespace core {
    core::core() {
        /// Get current user screen size
        const sf::VideoMode desktop_mode{sf::VideoMode::getDesktopMode()};
        window_size_ = desktop_mode.size;

        sf::ContextSettings context_settings{};
        context_settings.antiAliasingLevel = config::system::antialiasing_level;

        window_.create(sf::VideoMode(window_size_, config::system::bits_per_pixel), config::system::window_title,
                       sf::Style::Close, sf::State::Fullscreen, context_settings);
        window_.setFramerateLimit(config::system::framerate_limit);

        manager_entity_ = std::make_unique<manager::manager_entity>(window_size_, simulation_parameters_);
        manager_ui_     = std::make_unique<manager::manager_ui>(window_size_, simulation_parameters_);
    }

    core::~core() = default;

    auto core::run() -> void {
        while (window_.isOpen()) {
            handle_events();
            if (window_.hasFocus()) {
                update();
                render();
            } else {
                dt_ = clock_.restart();
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
        manager_ui_->update(dt_.asSeconds());
    }

    auto core::render() -> void {
        window_.clear(config::theme::background);
        manager_entity_->render(window_);
        manager_ui_->render(window_);
        window_.display();
    }
} // namespace core
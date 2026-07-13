#include "core.h++"
#include "../config/system_config.h++"
#include "../config/theme_config.h++"

core::core() {
    sf::VideoMode video_mode = sf::VideoMode::getDesktopMode();
    window_size_             = video_mode.size;

    sf::ContextSettings settings;
    settings.antiAliasingLevel = system_config::antialiasing_level;
    window_.create(sf::VideoMode(window_size_, system_config::bits_per_pixel), "Boids Simulator", sf::Style::Close,
                   sf::State::Fullscreen, settings);
    window_.setFramerateLimit(system_config::framerate_limit);
    window_.clear(theme_config::background);

    manager_entity_ = std::make_unique<manager_entity>(window_size_, boids_packet_);
    manager_ui_     = std::make_unique<manager_ui>(window_size_, boids_packet_);
}

void core::run() {
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

void core::handle_events() {
    while (const std::optional<sf::Event> event = window_.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window_.close();
        }
    }
}

void core::update() {
    dt_ = clock_.restart().asSeconds();
    manager_entity_->update(dt_);
    manager_ui_->update();
}

void core::render() {
    window_.clear(theme_config::background);
    manager_entity_->render(window_);
    manager_ui_->render(window_);
    window_.display();
}
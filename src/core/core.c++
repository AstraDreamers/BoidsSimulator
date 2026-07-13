#include "core.h++"
#include "../colors.h++"

core::core() {
    sf::VideoMode video_mode = sf::VideoMode::getDesktopMode();
    window_size_ = video_mode.size;

    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8.f;
    window_.create(sf::VideoMode(window_size_, 32), "Boids Simulator", sf::Style::Close, sf::State::Fullscreen,
                   settings);
    window_.setFramerateLimit(60);
    window_.clear(color_palette::background);

    manager_entity_ = std::make_unique<manager_entity>(window_size_, m_boids_packet);
    manager_ui_ = std::make_unique<manager_ui>(window_size_, m_boids_packet);
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
    window_.clear(color_palette::background);
    manager_entity_->render(window_);
    manager_ui_->render(window_);
    window_.display();
}
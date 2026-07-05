#include "core.h++"

core::core() {
    sf::VideoMode video_mode = sf::VideoMode::getDesktopMode();
    m_window_size = video_mode.size;

    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8.f;
    m_window.create(sf::VideoMode(m_window_size, 32), "Boids Simulator", sf::Style::Close, sf::State::Fullscreen,
                    settings);
    m_window.setFramerateLimit(60);
    m_window.clear(color_palette::background);

    m_manager_entity =
        std::make_unique<manager_entity>(m_window_size, m_boids_packet.gain_separation, m_boids_packet.gain_alignment,
                                         m_boids_packet.gain_cohesion, m_boids_packet.vision_range);
    m_manager_ui = std::make_unique<manager_ui>(m_window_size, m_boids_packet);
}

void core::run() {
    while (m_window.isOpen()) {
        handle_events();
        if (m_window.hasFocus()) {
            update();
            render();
        } else {
            m_clock.restart();
            render();
        }
    }
}

void core::handle_events() {
    while (const std::optional<sf::Event> event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        }

        m_manager_entity->handle_events(event);
    }
}

void core::update() {
    m_dt = m_clock.restart().asSeconds();

    m_manager_entity->update(m_dt);
    m_manager_ui->update();
}

void core::render() {
    m_window.clear(color_palette::background);
    m_manager_entity->render(m_window);
    m_manager_ui->render(m_window);
    m_window.display();
}
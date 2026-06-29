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

    m_clearscreen_array.resize(4);
    m_clearscreen_array.setPrimitiveType(sf::PrimitiveType::TriangleFan);

    m_clearscreen_array[0].position = {0.f, 0.f};
    m_clearscreen_array[1].position = {static_cast<float>(m_window_size.x), 0.f};
    m_clearscreen_array[2].position = {static_cast<float>(m_window_size.x), static_cast<float>(m_window_size.y)};
    m_clearscreen_array[3].position = {0.f, static_cast<float>(m_window_size.y)};

    for (int i = 0; i < 4; i++) {
        m_clearscreen_array[i].color = color_palette::background;
        m_clearscreen_array[i].color.a = 100;
    }

    m_manager_entity = std::make_unique<manager_entity>(m_window_size, m_ws, m_wa, m_wc, m_vision);
    m_manager_ui = std::make_unique<manager_ui>(m_window_size, m_ws, m_wa, m_wc, m_vision);
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
        m_manager_ui->handle_events(event);
    }
}

void core::update() {
    m_dt = m_clock.restart().asSeconds();

    m_manager_entity->update(m_dt);
    m_manager_ui->update(m_dt);
}

void core::render() {
    m_window.draw(m_clearscreen_array);
    m_manager_entity->render(m_window);
    m_manager_ui->render(m_window);
    m_window.display();
}
#include "core.h++"

core::core() {
  m_window_size = {1366, 768};

  sf::ContextSettings settings;
  settings.antiAliasingLevel = 8.f;
  m_window.create(sf::VideoMode(m_window_size, 32), "Boids Simulator",
                  sf::Style::Close, sf::State::Fullscreen, settings);
  m_window.setFramerateLimit(60);
  m_window.clear(GraphitePalette::White);

  m_clearscreen_shape.setSize(sf::Vector2f(m_window_size));
  m_clearscreen_shape.setPosition({0.f, 0.f});
  m_clearscreen_shape.setOrigin({0.f, 0.f});
  m_clearscreen_shape.setFillColor({GraphitePalette::White.r,
                                    GraphitePalette::White.g,
                                    GraphitePalette::White.b, 50});

  m_manager_entity = std::make_unique<manager_entity>(m_window_size, m_ws, m_wa,
                                                      m_wc, m_vision);
  m_manager_ui =
      std::make_unique<manager_ui>(m_window_size, m_ws, m_wa, m_wc, m_vision);
}

void core::run() {
  while (m_window.isOpen()) {
    handle_events();
    update();
    render();
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
  m_window.draw(m_clearscreen_shape);
  m_manager_entity->render(m_window);
  m_manager_ui->render(m_window);
  m_window.display();
}
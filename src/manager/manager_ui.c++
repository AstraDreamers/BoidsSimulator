#include "manager_ui.h++"

manager_ui::manager_ui(sf::Vector2u window_size, float &ws, float &wa,
                       float &wc, float &vision) {
  m_window_size = window_size;
  m_ws = &ws;
  m_wa = &wa;
  m_wc = &wc;
  m_vision = &vision;

  if (!m_font_google_sans.openFromFile("assets/Google Sans.ttf")) {
    MessageBoxA(NULL, "Can't load font.", "Error", MB_ICONERROR | MB_OK);
  }

  m_text_header = std::make_unique<sf::Text>(m_font_google_sans);
  m_text_header->setCharacterSize(100);
  m_text_header->setString("Boids Algorithm");
  m_text_header->setPosition({0.f, 0.f});
  m_text_header->setOrigin({0.f, 0.f});
  m_text_header->setFillColor(GraphitePalette::Green);
}

void manager_ui::handle_events(const std::optional<sf::Event> &event) {}

void manager_ui::update(float dt) {}

void manager_ui::render(sf::RenderWindow &window) {
  window.draw(*m_text_header);
}
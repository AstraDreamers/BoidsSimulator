#include "manager_ui.h++"

manager_ui::manager_ui(sf::Vector2u window_size, float &ws, float &wa, float &wc, float &vision) {
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

  m_slider[0] = std::make_unique<slider>(*m_ws, 0.f, 10.f);
  m_slider[1] = std::make_unique<slider>(*m_wa);
  m_slider[2] = std::make_unique<slider>(*m_wc);
  m_slider[3] = std::make_unique<slider>(*m_vision, 0.f, 100.f);

  for (uint8_t i = 0; i < 4; i++) {
    m_slider[i]->set_position({(static_cast<float>(i) / 4.f) * static_cast<float>(m_window_size.x) +
                                   0.05f * static_cast<float>(m_window_size.x),
                               0.9f * static_cast<float>(m_window_size.y)});
    m_slider[i]->set_size({0.15f * static_cast<float>(m_window_size.x), 10.f});
    m_slider[i]->set_color_background(GraphitePalette::Gray);
    m_slider[i]->set_color_active(GraphitePalette::Blue);
    m_slider[i]->set_color_inactive(GraphitePalette::Pink);

    m_slider_text[i] = std::make_unique<sf::Text>(m_font_google_sans);
    m_slider_text[i]->setCharacterSize(20);
    m_slider_text[i]->setPosition({(static_cast<float>(i) / 4.f) * static_cast<float>(m_window_size.x) +
                                       0.05f * static_cast<float>(m_window_size.x),
                                   0.85f * static_cast<float>(m_window_size.y)});
    m_slider_text[i]->setOrigin({0.f, 0.f});
    m_slider_text[i]->setFillColor(GraphitePalette::Green);
  }

  m_slider_text[0]->setString("Separation");
  m_slider_text[1]->setString("Alignment");
  m_slider_text[2]->setString("Cohesion");
  m_slider_text[3]->setString("Vision");
}

void manager_ui::handle_events(const std::optional<sf::Event> &event) {}

void manager_ui::update(float dt) {
  for (uint8_t i = 0; i < 4; i++) {
    m_slider[i]->update();
  }
}

void manager_ui::render(sf::RenderWindow &window) {
  window.draw(*m_text_header);
  for (uint8_t i = 0; i < 4; i++) {
    m_slider[i]->render(window);
    window.draw(*m_slider_text[i]);
  }
}
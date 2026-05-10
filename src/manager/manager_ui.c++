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

  m_slider_ws = std::make_unique<slider>(*m_ws, 0.f, 10.f);
  m_slider_wa = std::make_unique<slider>(*m_wa);
  m_slider_wc = std::make_unique<slider>(*m_wc);
  m_slider_vision = std::make_unique<slider>(*m_vision, 0.f, 100.f);

  m_slider_ws->set_position({100.f, 400.f});
  m_slider_wa->set_position({100.f, 500.f});
  m_slider_wc->set_position({100.f, 600.f});
  m_slider_vision->set_position({100.f, 700.f});

  m_slider_ws->set_size({500.f, 20.f});
  m_slider_wa->set_size({500.f, 20.f});
  m_slider_wc->set_size({500.f, 20.f});
  m_slider_vision->set_size({500.f, 20.f});

  m_slider_ws->set_color_active({255, 128, 128, 255});
  m_slider_ws->set_color_inactive({255, 77, 77, 255});
  m_slider_ws->set_color_background({225, 204, 204, 255});

  m_slider_wa->set_color_active({128, 255, 128, 255});
  m_slider_wa->set_color_inactive({77, 255, 77, 255});
  m_slider_wa->set_color_background({204, 225, 204, 255});

  m_slider_wc->set_color_active({128, 128, 255, 255});
  m_slider_wc->set_color_inactive({77, 77, 255, 255});
  m_slider_wc->set_color_background({204, 204, 225, 255});

  m_slider_vision->set_color_active({255, 128, 255, 255});
  m_slider_vision->set_color_inactive({225, 77, 255, 255});
  m_slider_vision->set_color_background({225, 204, 225, 255});
}

void manager_ui::handle_events(const std::optional<sf::Event> &event) {}

void manager_ui::update(float dt) {
  m_slider_ws->update();
  m_slider_wa->update();
  m_slider_wc->update();
  m_slider_vision->update();
}

void manager_ui::render(sf::RenderWindow &window) {
  window.draw(*m_text_header);
  m_slider_ws->render(window);
  m_slider_wa->render(window);
  m_slider_wc->render(window);
  m_slider_vision->render(window);
}
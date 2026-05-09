#pragma once

class manager_ui {
public:
  manager_ui(sf::Vector2u window_size, float &ws, float &wa, float &wc,
             float &vision);
  ~manager_ui() = default;

  void handle_events(const std::optional<sf::Event> &event);
  void update(float dt);
  void render(sf::RenderWindow &window);

private:
  sf::Vector2u m_window_size;

  sf::Font m_font_google_sans;

  std::unique_ptr<sf::Text> m_text_header;

  float *m_ws = nullptr;
  float *m_wa = nullptr;
  float *m_wc = nullptr;
  float *m_vision = nullptr;
};
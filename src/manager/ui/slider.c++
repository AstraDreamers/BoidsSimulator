#include "slider.h++"

slider::slider(float &value, float clamp_min, float clamp_max) {
  m_value = &value;
  m_clamp_min = clamp_min;
  m_clamp_max = clamp_max;

  *m_value = std::clamp(*m_value, clamp_min, clamp_max);
  m_value_based = (*m_value - clamp_min) / clamp_max;

  /// ? First initialization
  set_position({0.f, 0.f});
  set_size({100.f, 10.f});
  set_color_inactive(sf::Color::Blue);
  set_color_active(sf::Color::Cyan);
  set_color_background(sf::Color::White);
}

void slider::set_position(sf::Vector2f position) {
  m_position = position;
  m_line.setPosition(position);
  m_line_start.setPosition(position);
  m_line_end.setPosition(position + sf::Vector2f(m_size.x, 0));
  m_line_override.setPosition(position);
}

void slider::set_size(sf::Vector2f size) {
  m_size = size;

  m_line.setSize(size);
  m_line.setOrigin({0.f, size.y / 2.f});

  m_line_start.setRadius(size.y / 2.f);
  m_line_start.setOrigin({size.y / 2.f, size.y / 2.f});

  m_line_end.setRadius(size.y / 2.f);
  m_line_end.setPosition(m_position + sf::Vector2f(size.x, 0));
  m_line_end.setOrigin({size.y / 2.f, size.y / 2.f});

  m_line_override.setOrigin({0.f, size.y / 2.f});

  m_circle.setRadius(size.y * 0.75f);
  m_circle.setOrigin({size.y * 0.75f, size.y * 0.75f});
}

void slider::set_color_inactive(sf::Color color) { m_color_inactive = color; }

void slider::set_color_active(sf::Color color) { m_color_active = color; }

void slider::set_color_background(sf::Color color) {
  m_color_background = color;
  m_line.setFillColor(color);
  m_line_end.setFillColor(color);
}

void slider::update() {
  /// ? Update circle position
  m_circle.setPosition({m_position.x + m_value_based * m_size.x, m_position.y});
  m_line_override.setSize({m_value_based * m_size.x, m_size.y});

  /// ? Sliding logic
  sf::Vector2f mouse_position = sf::Vector2f(sf::Mouse::getPosition());
  sf::Vector2f circle_position = m_circle.getPosition();
  sf::Vector2f d = mouse_position - circle_position;
  float r = m_circle.getRadius();

  if (m_locked) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      m_value_based = (mouse_position.x - m_position.x) / m_size.x;
      m_value_based = std::clamp(m_value_based, 0.f, 1.f);
    } else {
      m_locked = false;
    }
  } else if (d.x * d.x + d.y * d.y <= r * r) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      m_value_based = (mouse_position.x - m_position.x) / m_size.x;
      m_value_based = std::clamp(m_value_based, 0.f, 1.f);
      m_locked = true;
    }
  }

  /// ? Update circle size when hover
  if (d.x * d.x + d.y * d.y <= r * r || m_locked) {
    m_size_fade += 0.075f;
    if (m_size_fade > 1.f)
      m_size_fade = 1.f;
  } else {
    m_size_fade -= 0.075f;
    if (m_size_fade < 0.f)
      m_size_fade = 0.f;
  }

  m_circle.setRadius(m_size.y * (0.75f + 0.25f * m_size_fade));
  m_circle.setOrigin({m_circle.getRadius(), m_circle.getRadius()});

  /// ? Update colors
  if (m_locked) {
    m_color_fade += 0.075f;
    if (m_color_fade > 1.f)
      m_color_fade = 1.f;
  } else {
    m_color_fade -= 0.075f;
    if (m_color_fade < 0.f)
      m_color_fade = 0.f;
  }

  sf::Color color = {static_cast<uint8_t>(m_color_inactive.r + m_color_fade * (m_color_active.r - m_color_inactive.r)),
                     static_cast<uint8_t>(m_color_inactive.g + m_color_fade * (m_color_active.g - m_color_inactive.g)),
                     static_cast<uint8_t>(m_color_inactive.b + m_color_fade * (m_color_active.b - m_color_inactive.b)),
                     static_cast<uint8_t>(m_color_inactive.a + m_color_fade * (m_color_active.a - m_color_inactive.a))};

  m_line_start.setFillColor(color);
  m_line_override.setFillColor(color);
  m_circle.setFillColor(color);

  *m_value = m_clamp_min + m_value_based * m_clamp_max;
}

void slider::render(sf::RenderWindow &window) {
  window.draw(m_line);
  window.draw(m_line_override);
  window.draw(m_line_start);
  window.draw(m_line_end);
  window.draw(m_circle);
}
#pragma once

class slider {
public:
  /// @brief Construction function
  /// @param value The value that the slider have to hook to
  /// @param clamp_min Minimum value for the slider to set
  /// @param clamp_max Maximum value for the slider to set
  slider(float &value, float clamp_min = 0.f, float clamp_max = 1.f);
  ~slider() = default;

  /// @brief Set the position of the slider
  /// @param position The new position of the slider
  void set_position(sf::Vector2f position);

  /// @brief Set the size of the slider
  /// @param size The new size of the slider
  void set_size(sf::Vector2f size);

  /// @brief Set the color of the slider when it's inactive
  /// @param color The new color of the slider when it's inactive
  void set_color_inactive(sf::Color color);

  /// @brief Set the color of the slider when it's active
  /// @param color The new color of the slider when it's active
  void set_color_active(sf::Color color);

  /// @brief Set the color of the slider background
  /// @param color The new color of the slider background
  void set_color_background(sf::Color color);

  /// @brief Update slider logic
  void update();

  /// @brief Render the slider
  /// @param window The window to render the slider on
  void render(sf::RenderWindow &window);

private:
  sf::RectangleShape m_line;
  sf::RectangleShape m_line_override;
  sf::CircleShape m_line_start;
  sf::CircleShape m_line_end;
  sf::CircleShape m_circle;

  float *m_value = nullptr;
  float m_value_based = 0.f;
  float m_clamp_min;
  float m_clamp_max;

  sf::Vector2f m_position;
  sf::Vector2f m_size;

  sf::Color m_color_inactive;
  sf::Color m_color_active;
  sf::Color m_color_background;

  bool m_locked = false;
  float m_color_fade = 0.f;
  float m_size_fade = 0.f;
};
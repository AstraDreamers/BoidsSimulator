#pragma once

class slider {
public:
  /// @brief Constructor for slider UI component.
  /// @param value Reference to the float variable that the slider will control.
  /// @param clamp_min Minimum value for the slider.
  /// @param clamp_max Maximum value for the slider.
  slider(float &value, float clamp_min, float clamp_max);
  ~slider() = default;

  /// @brief Set the position of the slider.
  /// @param position The new position of the slider.
  void set_position(sf::Vector2f position);

  /// @brief Set the size of the slider.
  /// @param size The new size of the slider.
  void set_size(sf::Vector2f size);

  /// @brief Set the color of the inactive (unfilled) portion of the slider.
  /// @param color The new color for the inactive portion.
  void set_color_inactive(sf::Color color);

  /// @brief Set the color of the active (filled) portion of the slider.
  /// @param color The new color for the active portion.
  void set_color_active(sf::Color color);

  /// @brief Set the color of the background (track) of the slider.
  /// @param color The new color for the background.
  void set_color_background(sf::Color color);

  /// @brief Update the slider's state based on user interaction and internal logic.
  void update();

  /// @brief Render the slider onto the given SFML render window.
  /// @param window The SFML render window to draw the slider on.
  void render(sf::RenderWindow &window);

private:
  void update_geometry();

  sf::VertexArray m_vertices;

  float *m_value = nullptr;
  float m_value_based{};
  float m_clamp_min{};
  float m_clamp_max{};

  sf::Vector2f m_position{};
  sf::Vector2f m_size{100.f, 10.f};

  sf::Color m_color_inactive{sf::Color::Blue};
  sf::Color m_color_active{sf::Color::Cyan};
  sf::Color m_color_background{sf::Color::White};

  bool m_locked{false};
  float m_color_fade{};
  float m_size_fade{};

  static constexpr uint16_t m_circle_segments{30};

  std::array<float, m_circle_segments + 1> m_lut_cos;
  std::array<float, m_circle_segments + 1> m_lut_sin;
};
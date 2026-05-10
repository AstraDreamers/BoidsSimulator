#pragma once

#include "ui/slider.h++"

/// @brief Managing the user interface of the simulation.
class manager_ui {
public:
  /// @brief Construct a new manager_ui object.
  /// @param window_size The size of the window.
  /// @param ws The weight of the separation behavior.
  /// @param wa The weight of the alignment behavior.
  /// @param wc The weight of the cohesion behavior.
  /// @param vision The vision radius of the boids.
  manager_ui(sf::Vector2u window_size, float &ws, float &wa, float &wc, float &vision);
  ~manager_ui() = default;

  /// @brief Handle the events of the simulation.
  /// @param event The event to handle.
  void handle_events(const std::optional<sf::Event> &event);

  /// @brief Update the simulation.
  /// @param dt The delta time since the last update.
  void update(float dt);

  /// @brief Render the simulation.
  /// @param window The window to render to.
  void render(sf::RenderWindow &window);

private:
  sf::Vector2u m_window_size;

  sf::Font m_font_google_sans;

  std::unique_ptr<sf::Text> m_text_header;

  std::unique_ptr<slider> m_slider_ws;
  std::unique_ptr<slider> m_slider_wa;
  std::unique_ptr<slider> m_slider_wc;
  std::unique_ptr<slider> m_slider_vision;

  float *m_ws = nullptr;
  float *m_wa = nullptr;
  float *m_wc = nullptr;
  float *m_vision = nullptr;
};
#pragma once

#include "ui/slider.h++"
#include "../core/boids_packet.h++"

/// @brief Managing the user interface of the simulation.
class manager_ui {
  public:
    /// @brief Construct a new manager_ui object.
    /// @param window_size The size of the window.
    /// @param boids_packet The variable packets for boids.
    manager_ui(sf::Vector2u window_size, boids_packet& boids_packet);
    ~manager_ui() = default;

    /// @brief Update the simulation.
    /// @param dt The delta time since the last update.
    void update(float dt) const;

    /// @brief Render the simulation.
    /// @param window The window to render to.
    void render(sf::RenderWindow &window) const;

  private:
    sf::Vector2u m_window_size{0,0};

    sf::Font m_font;

    std::unique_ptr<sf::Text> m_text_title;
    std::unique_ptr<sf::Text> m_text_slider_name[4];
    std::unique_ptr<sf::Text> m_text_slider_value[4];
    std::unique_ptr<slider> m_slider[4];

    boids_packet* m_boids_packet{nullptr};
};
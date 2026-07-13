#pragma once

#include "../core/boids_packet.h++"
#include "ui/slider.h++"


/// @brief Managing the user interface of the simulation.
class manager_ui {
  public:
    /// @brief Construct a new manager_ui object.
    /// @param window_size The size of the window.
    /// @param boids_packet The variable packets for boids.
    manager_ui(const sf::Vector2u window_size, boids_packet &boids_packet);
    ~manager_ui() = default;

    /// @brief Update the simulation.
    void update() const;

    /// @brief Render the simulation.
    /// @param window The window to render to.
    void render(sf::RenderWindow &window) const;

  private:
    sf::Vector2u window_size_{0, 0};
    boids_packet *boids_packet_{nullptr};

    sf::Font font_{};

    std::unique_ptr<sf::Text> text_title_{nullptr};
    std::array<std::unique_ptr<sf::Text>, 4> text_slider_name_{nullptr};
    std::array<std::unique_ptr<sf::Text>, 4> text_slider_value_{nullptr};
    std::array<std::unique_ptr<slider>, 4> slider_{nullptr};

    const std::array<std::string, 4> slider_names_{"Separation", "Alignment", "Cohesion", "Vision"};
};
#pragma once

#include "../core/boids_packet.h++"
#include "ui/slider.h++"

/// @brief Managing the user interface of the simulation.
class manager_ui {
  public:
    /// @brief Construct a new manager_ui object.
    /// @param window_size The size of the window.
    /// @param boids_packet The variable packets for boids.
    manager_ui(sf::Vector2u window_size, boids_packet &boids_packet);
    ~manager_ui();

    manager_ui(const manager_ui &)                         = delete;
    auto operator=(const manager_ui &) -> manager_ui &     = delete;
    manager_ui(manager_ui &&) noexcept                     = default;
    auto operator=(manager_ui &&) noexcept -> manager_ui & = delete;

    /// @brief Update the simulation.
    auto update() const -> void;

    /// @brief Render the simulation.
    /// @param window The window to render to.
    auto render(sf::RenderWindow &window) const -> void;

  private:
    sf::Vector2u  window_size_{0, 0};
    boids_packet *boids_packet_{nullptr};

    sf::Font font_;

    std::unique_ptr<sf::Text>                text_title_{nullptr};
    std::array<std::unique_ptr<sf::Text>, 4> text_slider_name_{nullptr};
    std::array<std::unique_ptr<sf::Text>, 4> text_slider_value_{nullptr};
    std::array<std::unique_ptr<slider>, 4>   slider_{nullptr};

    static constexpr std::array<std::string, 4> slider_names = {"Separation", "Alignment", "Cohesion", "Vision"};
};
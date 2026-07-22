#pragma once

#include "../config/simulation_config.h++"
#include "../manager/manager_entity.h++"
#include "../manager/manager_ui.h++"
#include "simulation_parameters.h++"

/// @brief Entry point of the whole program.
class core {
  public:
    core();
    ~core();

    core(const core &)                         = delete;
    auto operator=(const core &) -> core &     = delete;
    core(core &&) noexcept                     = default;
    auto operator=(core &&) noexcept -> core & = delete;

    /// @brief Start the program
    auto run() -> void;

  private:
    auto handle_events() -> void;
    auto update() -> void;
    auto render() -> void;

    sf::RenderWindow window_;
    sf::Vector2u     window_size_{0U, 0U};

    std::unique_ptr<manager_entity> manager_entity_{nullptr};
    std::unique_ptr<manager_ui>     manager_ui_{nullptr};

    sf::Clock clock_;
    sf::Time  dt_;

    simulation_parameters simulation_parameters_{
        .gain_separation = simulation_config::init_gain_separation,
        .gain_alignment  = simulation_config::init_gain_alignment,
        .gain_cohesion   = simulation_config::init_gain_cohesion,
        .vision_range    = simulation_config::init_vision_range,
    };
};
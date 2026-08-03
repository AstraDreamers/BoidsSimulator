#pragma once

inline constexpr uint8_t simulation_parameters_size{16U};

/// @brief Simulation parameters mainly for communicating between modules.
struct alignas(simulation_parameters_size) simulation_parameters {
    float gain_separation{0.F};
    float gain_alignment{0.F};
    float gain_cohesion{0.F};
    float vision_range{0.F};
};

static_assert(sizeof(simulation_parameters) == simulation_parameters_size, "simulation_parameters layout broken.");
static_assert(std::is_trivially_copyable_v<simulation_parameters>, "simulation_parameters must be trivially copyable.");
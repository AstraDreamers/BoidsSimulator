#pragma once

namespace system_config {

    /// @brief Window's anti-aliasing level.
    /// @details The higher it gets, the better the anti-aliasing is, but with the cost of significantly more GPU usage.
    /// @note Minimum is 0U, maximum is 8U, according to SFML API.
    constexpr inline uint32_t antialiasing_level{8U};

    /// @brief Window's framerate limit (FPS).
    constexpr inline uint32_t framerate_limit{60U};

    /// @brief Pixel's size in OpenGL backend. Default is 32 bits per pixel (RGBA, 8 bits or 1 byte per pixel, 8x4=32).
    constexpr inline uint32_t bits_per_pixel{32U};

    /// @brief Window's title.
    constexpr inline std::string window_title{"BoidsSimulator"};
} // namespace system_config
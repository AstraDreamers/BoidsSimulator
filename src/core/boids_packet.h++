#pragma once

struct boids_packet {
    float gain_separation{0.f};
    float gain_alignment{0.f};
    float gain_cohesion{0.f};
    float vision_range{0.f};
};
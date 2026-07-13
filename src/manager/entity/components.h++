#pragma once

namespace components {
    struct position {
        float x{0.F};
        float y{0.F};
    };

    struct velocity {
        float x{0.F};
        float y{0.F};
    };

    struct acceleration {
        float x{0.F};
        float y{0.F};
    };

    namespace drawable {
        struct circle {
            sf::CircleShape shape;
        };
    } // namespace drawable
} // namespace components
#pragma once

namespace components {
    struct position {
        float x;
        float y;
    };

    struct velocity {
        float x;
        float y;
    };

    struct acceleration {
        float x;
        float y;
    };

    namespace drawable {
        struct circle {
            sf::CircleShape shape;
        };
    } // namespace drawable
} // namespace components
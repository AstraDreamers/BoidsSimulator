#pragma once

namespace Components {
    namespace Movement {
        struct Position {
            float x;
            float y;
        };

        struct Velocity {
            float x;
            float y;
        };

        struct Acceleration {
            float x;
            float y;
        };
    } // namespace Movement

    namespace Drawable {
        struct Circle {
            sf::CircleShape shape;
        };
    } // namespace Drawable
} // namespace Components
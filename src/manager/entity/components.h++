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

    namespace Drawable {
        struct Circle {
            sf::CircleShape shape;
        };
    }
}
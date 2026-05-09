#include "core/core.h++"

int main() {
  core _core;
  _core.run();
  return 0;
}

/*#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

namespace GraphitePallete {
  constexpr sf::Color Gray{193, 192, 194, 255};  // #C1C0C2
  constexpr sf::Color White{245, 233, 231, 255}; // #F5E9E7
  constexpr sf::Color Pink{236, 197, 198, 255};  // #ECC5C6
  constexpr sf::Color Green{131, 125, 104, 255}; // #837D68
  constexpr sf::Color Blue{138, 157, 177, 255};  // #8A9DB1
} // namespace GraphitePallete

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

void update_velocity(entt::registry &registry, float dt);
void update_position(entt::registry &registry, float dt);
void draw_entities(entt::registry &registry, sf::RenderWindow &window);

int main() {
  srand(time(nullptr));

  sf::ContextSettings settings;
  settings.antiAliasingLevel = 8;

  sf::RenderWindow window(sf::VideoMode({1366, 768}, 32),
                          "Boids Algorithm Demonstration", sf::Style::Close,
                          sf::State::Fullscreen, settings);
  window.setFramerateLimit(60);

  entt::registry registry;

  for (uint16_t i = 0; i < 100; i++) {
    entt::entity entity = registry.create();

    registry.emplace<Components::Movement::Position>(
        entity, static_cast<float>(rand() % 1366),
        static_cast<float>(rand() % 768));
    registry.emplace<Components::Movement::Velocity>(entity, 0.f, 0.f);
    registry.emplace<Components::Movement::Acceleration>(entity, 0.f, 0.f);
    registry.emplace<Components::Drawable::Circle>(entity);

    auto &circle = registry.get<Components::Drawable::Circle>(entity);
    circle.shape.setRadius(10.f);
    circle.shape.setOrigin({10.f, 10.f});
    circle.shape.setPointCount(5);
    circle.shape.setFillColor(GraphitePallete::Blue);
  }

  sf::Font font_google_sans;
  if (!font_google_sans.openFromFile("GoogleSans-Bold.ttf"))
    return -1;

  sf::Text text_title(font_google_sans);
  text_title.setCharacterSize(100);
  text_title.setString("Boids Algorithm");
  text_title.setPosition({0.f, 0.f});
  text_title.setOrigin({0.f, 0.f});
  text_title.setFillColor({131, 125, 104, 255});

  sf::Clock clock;
  float dt = 0.f;
  float ws = 70.0f;
  float wa = 70.50f;
  float wc = 1000.50f;
  float perception_radius = 100.f;

  while (window.isOpen()) {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    dt = clock.restart().asSeconds();

    auto flock_view = registry.view<Components::Movement::Position,
                                    Components::Movement::Velocity,
                                    Components::Movement::Acceleration>();

    flock_view.each([&](entt::entity entity, Components::Movement::Position &p,
                        Components::Movement::Velocity &v,
                        Components::Movement::Acceleration &a) {
      sf::Vector2f vs{0.f, 0.f}; // separation vector
      sf::Vector2f va{0.f, 0.f}; // alignment vector
      sf::Vector2f vc{0.f, 0.f}; // cohesion vector
      uint32_t neighbor_count = 0;

      for (auto other : flock_view) {
        if (entity == other)
          continue;

        auto &op = flock_view.get<Components::Movement::Position>(other);
        auto &ov = flock_view.get<Components::Movement::Velocity>(other);

        float dx = op.x - p.x;
        float dy = op.y - p.y;
        float dist2 = dx * dx + dy * dy;
        if (dist2 < perception_radius * perception_radius && dist2 > 0.01f) {
          float dist = std::sqrtf(dist2);

          vs.x -= dx / dist;
          vs.y -= dy / dist;

          va.x += ov.x;
          va.y += ov.y;

          vc.x += op.x;
          vc.y += op.y;

          neighbor_count++;
        }
      }

      if (neighbor_count > 0) {
        float inv_nbc = 1.f / static_cast<float>(neighbor_count);

        vs *= inv_nbc;
        va *= inv_nbc;
        vc *= inv_nbc;

        vc -= {p.x, p.y};

        vs -= {v.x, v.y};
        va -= {v.x, v.y};
        vc -= {v.x, v.y};

        vs *= ws;
        va *= wa;
        vc *= wc;

        a.x = vs.x + va.x + vc.x;
        a.y = vs.y + va.y + vc.y;
      } else {
        a.x = 0;
        a.y = 0;
      }
    });

    update_velocity(registry, dt);
    update_position(registry, dt);

    window.clear(GraphitePallete::White);
    draw_entities(registry, window);
    window.draw(text_title);
    window.display();
  }

  return 0;
}

void update_velocity(entt::registry &registry, float dt) {
  registry
      .view<Components::Movement::Acceleration,
            Components::Movement::Velocity>()
      .each([dt](Components::Movement::Acceleration &a,
                 Components::Movement::Velocity &v) {
        v.x += a.x * dt;
        v.y += a.y * dt;
      });
}

void update_position(entt::registry &registry, float dt) {
  registry
      .view<Components::Movement::Velocity, Components::Movement::Position>()
      .each([dt](Components::Movement::Velocity &v,
                 Components::Movement::Position &p) {
        p.x += v.x * dt;
        p.y += v.y * dt;
      });

  registry.view<Components::Movement::Position, Components::Drawable::Circle>()
      .each([](Components::Movement::Position &p,
               Components::Drawable::Circle &circle) {
        circle.shape.setPosition({p.x, p.y});
      });
}

void draw_entities(entt::registry &registry, sf::RenderWindow &window) {
  registry.view<Components::Drawable::Circle>().each(
      [&window](Components::Drawable::Circle &circle) {
        window.draw(circle.shape);
      });
}*/
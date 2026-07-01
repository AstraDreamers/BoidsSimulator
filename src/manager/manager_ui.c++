#include "manager_ui.h++"
#include "../colors.h++"

manager_ui::manager_ui(const sf::Vector2u window_size, boids_packet &boids_packet) {
    m_window_size = window_size;
    m_boids_packet = &boids_packet;

    if (!m_font.openFromFile("assets/Google Sans.ttf")) {
        std::println(stderr, "Can't open file assets/Google Sans.ttf");
        exit(-1);
    }

    m_text_title = std::make_unique<sf::Text>(m_font);
    m_text_title->setString("Boids Algorithm");
    m_text_title->setCharacterSize(100);
    m_text_title->setPosition({0.f, 0.f});
    m_text_title->setOrigin({0.f, 0.f});
    m_text_title->setFillColor(color_palette::text_title);

    m_slider[0] = std::make_unique<slider>(m_boids_packet->gain_separation, 0.f, 10.f);
    m_slider[1] = std::make_unique<slider>(m_boids_packet->gain_alignment, 0.f, 10.f);
    m_slider[2] = std::make_unique<slider>(m_boids_packet->gain_cohesion, 0.f, 10.f);
    m_slider[3] = std::make_unique<slider>(m_boids_packet->vision_range, 0.f, 100.f);

    const std::string slider_names[4] = {"Separation", "Alignment", "Cohesion", "Vision"};

    for (uint8_t i = 0; i < 4; i++) {
        m_slider[i]->set_position({(static_cast<float>(i) / 4.f) * static_cast<float>(m_window_size.x) +
                                       0.05f * static_cast<float>(m_window_size.x),
                                   0.9f * static_cast<float>(m_window_size.y)});
        m_slider[i]->set_size({0.15f * static_cast<float>(m_window_size.x), 10.f});
        m_slider[i]->set_color_background(color_palette::slider_background);
        m_slider[i]->set_color_active(color_palette::slider_active);
        m_slider[i]->set_color_inactive(color_palette::slider_inactive);

        m_text_slider_name[i] = std::make_unique<sf::Text>(m_font);
        m_text_slider_name[i]->setCharacterSize(20);
        m_text_slider_name[i]->setPosition({(static_cast<float>(i) / 4.f) * static_cast<float>(m_window_size.x) +
                                           0.05f * static_cast<float>(m_window_size.x),
                                       0.85f * static_cast<float>(m_window_size.y)});
        m_text_slider_name[i]->setOrigin({0.f, 0.f});
        m_text_slider_name[i]->setFillColor(color_palette::text_slider_name);
        m_text_slider_name[i]->setString(slider_names[i]);

        m_text_slider_value[i] = std::make_unique<sf::Text>(m_font);
        m_text_slider_value[i]->setCharacterSize(15);
        m_text_slider_value[i]->setPosition(
            {m_text_slider_name[i]->getPosition().x + m_text_slider_name[i]->getGlobalBounds().size.x + 10.f,
             m_text_slider_name[i]->getPosition().y});
        m_text_slider_value[i]->setOrigin({0.f, 0.f});
        m_text_slider_value[i]->setFillColor(color_palette::text_slider_value);
    }
}

void manager_ui::update(float dt) const {
    for (const auto &slider : m_slider) {
        slider->update();
    }

    m_text_slider_value[0]->setString(std::format("{:.2f}", m_boids_packet->gain_separation));
    m_text_slider_value[1]->setString(std::format("{:.2f}", m_boids_packet->gain_alignment));
    m_text_slider_value[2]->setString(std::format("{:.2f}", m_boids_packet->gain_cohesion));
    m_text_slider_value[3]->setString(std::format("{:.2f}", m_boids_packet->vision_range));
}

void manager_ui::render(sf::RenderWindow &window) const {
    window.draw(*m_text_title);
    for (uint8_t i = 0; i < 4; i++) {
        m_slider[i]->render(window);
        window.draw(*m_text_slider_name[i]);
        window.draw(*m_text_slider_value[i]);
    }
}
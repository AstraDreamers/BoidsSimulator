#include "manager_ui.h++"
#include "../colors.h++"

manager_ui::manager_ui(const sf::Vector2u window_size, boids_packet &boids_packet) {
    /// ****************************
    /// ***** Value Inheritance ****
    /// ****************************
    window_size_ = window_size;
    boids_packet_ = &boids_packet;

    /// ****************************
    /// ***** Font loading *********
    /// ****************************
    if (!font_.openFromFile("assets/Google Sans.ttf")) {
        std::println(stderr, "Can't open file assets/Google Sans.ttf");
        exit(-1);
    }

    /// ****************************
    /// ***** Text *****************
    /// ****************************
    text_title_ = std::make_unique<sf::Text>(font_);
    text_title_->setString("Boids Algorithm");
    text_title_->setCharacterSize(100);
    text_title_->setPosition({0.f, 0.f});
    text_title_->setOrigin({-20.f, 0.f});
    text_title_->setFillColor(color_palette::text_title);

    for (uint8_t i = 0; i < 4; i++) {
        text_slider_name_[i] = std::make_unique<sf::Text>(font_);
        text_slider_name_[i]->setCharacterSize(20);
        text_slider_name_[i]->setPosition({(static_cast<float>(i) / 4.f) * static_cast<float>(window_size_.x) +
                                               0.05f * static_cast<float>(window_size_.x),
                                           0.85f * static_cast<float>(window_size_.y)});
        text_slider_name_[i]->setOrigin({0.f, 0.f});
        text_slider_name_[i]->setFillColor(color_palette::text_slider_name);
        text_slider_name_[i]->setString(slider_names_[i]);

        text_slider_value_[i] = std::make_unique<sf::Text>(font_);
        text_slider_value_[i]->setCharacterSize(15);
        text_slider_value_[i]->setPosition(
            {text_slider_name_[i]->getPosition().x + text_slider_name_[i]->getGlobalBounds().size.x + 10.f,
             text_slider_name_[i]->getPosition().y});
        text_slider_value_[i]->setOrigin({0.f, 0.f});
        text_slider_value_[i]->setFillColor(color_palette::text_slider_value);
    }

    /// ****************************
    /// ***** Slider ***************
    /// ****************************
    slider_[0] = std::make_unique<slider>(boids_packet_->gain_separation, 0.f, 10.f);
    slider_[1] = std::make_unique<slider>(boids_packet_->gain_alignment, 0.f, 10.f);
    slider_[2] = std::make_unique<slider>(boids_packet_->gain_cohesion, 0.f, 10.f);
    slider_[3] = std::make_unique<slider>(boids_packet_->vision_range, 0.f, 100.f);

    for (int i = 0; i < 4; i++) {
        slider_[i]->set_position({(static_cast<float>(i) / 4.f) * static_cast<float>(window_size_.x) +
                                      0.05f * static_cast<float>(window_size_.x),
                                  0.9f * static_cast<float>(window_size_.y)});
        slider_[i]->set_size({0.15f * static_cast<float>(window_size_.x), 10.f});
        slider_[i]->set_color_background(color_palette::slider_background);
        slider_[i]->set_color_active(color_palette::slider_active);
        slider_[i]->set_color_inactive(color_palette::slider_inactive);
    }
}

void manager_ui::update() const {
    for (const auto &slider : slider_) {
        slider->update();
    }

    text_slider_value_[0]->setString(std::format("{:.2f}", boids_packet_->gain_separation));
    text_slider_value_[1]->setString(std::format("{:.2f}", boids_packet_->gain_alignment));
    text_slider_value_[2]->setString(std::format("{:.2f}", boids_packet_->gain_cohesion));
    text_slider_value_[3]->setString(std::format("{:.2f}", boids_packet_->vision_range));
}

void manager_ui::render(sf::RenderWindow &window) const {
    window.draw(*text_title_);
    for (uint8_t i = 0; i < 4; i++) {
        slider_[i]->render(window);
        window.draw(*text_slider_name_[i]);
        window.draw(*text_slider_value_[i]);
    }
}
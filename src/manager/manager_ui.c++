#include "manager_ui.h++"
#include "../config/theme_config.h++"
#include "../config/ui_config.h++"

manager_ui::manager_ui(const sf::Vector2u window_size, simulation_parameters &simulation_parameters)
    : window_size_(window_size), simulation_parameters_(&simulation_parameters) {
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
    text_title_->setCharacterSize(ui_config::size_text_title);
    text_title_->setPosition({0.F, 0.F});
    text_title_->setOrigin({-20.F, 0.F});
    text_title_->setFillColor(theme_config::text_title);

    for (uint8_t i = 0; i < 4; i++) {
        text_slider_name_.at(i) = std::make_unique<sf::Text>(font_);
        text_slider_name_.at(i)->setCharacterSize(ui_config::size_text_slider_name);
        text_slider_name_.at(i)->setPosition({((static_cast<float>(i) / 4.F) * static_cast<float>(window_size_.x)) +
                                                  (0.05F * static_cast<float>(window_size_.x)),
                                              0.85F * static_cast<float>(window_size_.y)});
        text_slider_name_.at(i)->setOrigin({0.F, 0.F});
        text_slider_name_.at(i)->setFillColor(theme_config::text_slider_name);
        text_slider_name_.at(i)->setString(slider_names.at(i));

        text_slider_value_.at(i) = std::make_unique<sf::Text>(font_);
        text_slider_value_.at(i)->setCharacterSize(ui_config::size_text_slider_value);
        text_slider_value_.at(i)->setPosition(
            {text_slider_name_.at(i)->getPosition().x + text_slider_name_.at(i)->getGlobalBounds().size.x + 10.F,
             text_slider_name_.at(i)->getPosition().y});
        text_slider_value_.at(i)->setOrigin({0.F, 0.F});
        text_slider_value_.at(i)->setFillColor(theme_config::text_slider_value);
    }

    /// ****************************
    /// ***** Slider ***************
    /// ****************************
    slider_[0] = std::make_unique<slider>(simulation_parameters_->gain_separation, 0.F, 10.F);
    slider_[1] = std::make_unique<slider>(simulation_parameters_->gain_alignment, 0.F, 10.F);
    slider_[2] = std::make_unique<slider>(simulation_parameters_->gain_cohesion, 0.F, 10.F);
    slider_[3] = std::make_unique<slider>(simulation_parameters_->vision_range, 0.F, 100.F);

    for (int i = 0; i < 4; i++) {
        slider_.at(i)->set_position({((static_cast<float>(i) / 4.F) * static_cast<float>(window_size_.x)) +
                                         (0.05f * static_cast<float>(window_size_.x)),
                                     0.9f * static_cast<float>(window_size_.y)});
        slider_.at(i)->set_size({0.15f * static_cast<float>(window_size_.x), 10.F});
        slider_.at(i)->set_color_background(theme_config::slider_background);
        slider_.at(i)->set_color_active(theme_config::slider_active);
        slider_.at(i)->set_color_inactive(theme_config::slider_inactive);
    }
}

manager_ui::~manager_ui() = default;

auto manager_ui::update() const -> void {
    for (const auto &slider : slider_) {
        slider->update();
    }

    text_slider_value_[0]->setString(std::format("{:.2f}", simulation_parameters_->gain_separation));
    text_slider_value_[1]->setString(std::format("{:.2f}", simulation_parameters_->gain_alignment));
    text_slider_value_[2]->setString(std::format("{:.2f}", simulation_parameters_->gain_cohesion));
    text_slider_value_[3]->setString(std::format("{:.2f}", simulation_parameters_->vision_range));
}

auto manager_ui::render(sf::RenderWindow &window) const -> void {
    window.draw(*text_title_);
    for (uint8_t i = 0; i < 4; i++) {
        slider_.at(i)->render(window);
        window.draw(*text_slider_name_.at(i));
        window.draw(*text_slider_value_.at(i));
    }
}
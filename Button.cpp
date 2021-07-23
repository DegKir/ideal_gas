#include "Button.hpp"
#include "string.h"
#include "iostream"
sf::Font font;

Button::Button(double x_pos, double y_pos, double width, double hight, std::string string) : x_pos_(x_pos), y_pos_(y_pos), width_(width), hight_(hight)
{
    text_.setString(string);
    text_.setPosition(x_pos_ + 5, y_pos_);
    if (!font.loadFromFile("arial.ttf"))
    {
        ;
    }
    text_.setFont(font);
    text_.setCharacterSize(hight_ / 2);
    text_.setFillColor(sf::Color::Black);
    rectangle_.setSize(sf::Vector2f(width_, hight_));
    rectangle_.setPosition(x_pos_, y_pos_);
    rectangle_.setFillColor(sf::Color::White);
    rectangle_.setOutlineColor(sf::Color::Black);
    rectangle_.setOutlineThickness(5);
}

bool Button::mouse_on_button(sf::RenderWindow &window)
{
    double x = sf::Mouse::getPosition(window).x;
    double y = sf::Mouse::getPosition(window).y;
    // std::cout<<"checking, x = "<<x<<" y = "<<y<<std::endl;
    if ((x > x_pos_) && (x < x_pos_ + width_))
    {
        // std::cout<<"X is true"<<std::endl;
        if ((y > y_pos_) && (y < y_pos_ + hight_))
        {
            // std::cout<<"Y is true"<<std::endl;
            return true;
        }
    }

    return false;
}

void Button::draw(sf::RenderWindow &window)
{
    window.draw(rectangle_);
    window.draw(text_);
}

void Button::action()
{
    std::cout << "Action Action Action" << std::endl;
}

void Button::set_x_pos(double x_pos)
{
    x_pos_ = x_pos;
}
void Button::set_y_pos(double y_pos)
{
    y_pos_ = y_pos;
}
void Button::set_width(double width)
{
    width_ = width;
}
void Button::set_hight(double hight)
{
    hight_ = hight;
}
double Button::get_x_pos(void)
{
    return x_pos_;
}
double Button::get_y_pos(void)
{
    return y_pos_;
}
double Button::get_width(void)
{
    return width_;
}
double Button::get_hight(void)
{
    return hight_;
}
void Interface_Window::set_x_pos(double x_pos)
{
    x_pos_ = x_pos;
}
void Interface_Window::set_y_pos(double y_pos)
{
    y_pos_ = y_pos;
}
void Interface_Window::set_width(double width)
{
    width_ = width;
}
void Interface_Window::set_hight(double hight)
{
    hight_ = hight;
}
double Interface_Window::get_x_pos(void)
{
    return x_pos_;
}
double Interface_Window::get_y_pos(void)
{
    return y_pos_;
}
double Interface_Window::get_width(void)
{
    return width_;
}
double Interface_Window::get_hight(void)
{
    return hight_;
}

Interface_Window::Interface_Window(double x_pos, double y_pos, double width, double hight) : x_pos_(x_pos), y_pos_(y_pos), width_(width), hight_(hight)
{
    rectangle_.setSize(sf::Vector2f(width_, hight_));
    rectangle_.setPosition(x_pos_, y_pos_);
    rectangle_.setFillColor(sf::Color::White);
    rectangle_.setOutlineColor(sf::Color::Black);
    rectangle_.setOutlineThickness(5);
}

void Interface_Window::draw(sf::RenderWindow &window)
{
    window.draw(rectangle_);
}

Graphic::Graphic(Interface_Window window, std::map<double, double> dependency) :
 Interface_Window(window.get_x_pos(), window.get_y_pos(), window.get_width(), window.get_hight()),
 dependency_(dependency) {}


sf::RectangleShape get_gistogramm_column(double x_pos, double y_pos,double width, double hight)
{
    sf::RectangleShape gistogramm_column;
    gistogramm_column.setPosition(x_pos,y_pos);
    gistogramm_column.setSize(sf::Vector2f(width, hight));
    gistogramm_column.setFillColor(sf::Color::Black);
    return gistogramm_column;
}

void Graphic::draw_graphic(sf::RenderWindow &window, double v_0, double v_end, double n_0, double n_end)
{
    sf::RectangleShape rectangle;
    std::vector<sf::RectangleShape> gistogramm;
    double k = (v_end - v_0) / get_width();
    double n = (n_end - n_0) / get_hight();
    for (auto &element : dependency_)
    {
        gistogramm.push_back
        (
        get_gistogramm_column(
        get_x_pos() + (element.first - v_0) / k,
        get_y_pos() + get_hight() - (element.second - n_0) / n,
        5,(element.second - n_0) / n)
        );
        // window.draw(rectangle);
    }
    for (auto &gistogramm_column : gistogramm)
    {
        window.draw(gistogramm_column);
    }
}
void Graphic::update_dependency(std::map<double,double> dependency)
{
    dependency_=dependency;
}
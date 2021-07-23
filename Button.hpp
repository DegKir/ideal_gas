#include <SFML/Graphics.hpp>
#include <map>
class Button 
{
public:
    Button(double x_pos, double y_pos, double width, double hight, std::string string);
    bool mouse_on_button(sf::RenderWindow&);
    void draw(sf::RenderWindow &);
    void action(void);
    void set_x_pos(double);
    void set_y_pos(double);
    void set_width(double);
    void set_hight(double);
    double get_x_pos(void);
    double get_y_pos(void);
    double get_width(void);
    double get_hight(void);

private:
    sf::RectangleShape rectangle_;
    sf::Color color_;
    sf::Text text_;
    double x_pos_;
    double y_pos_;
    double width_;
    double hight_;
};

class Interface_Window
{
public:
    Interface_Window(double,double,double,double);
    void draw(sf::RenderWindow &);
    void set_x_pos(double);
    void set_y_pos(double);
    void set_width(double);
    void set_hight(double);
    double get_x_pos(void);
    double get_y_pos(void);
    double get_width(void);
    double get_hight(void);
private:
    sf::RectangleShape rectangle_;
    double x_pos_;
    double y_pos_;
    double width_;
    double hight_;
};

class Graphic: public Interface_Window
{  
public: 
    Graphic(Interface_Window, std::map<double,double>);
    // Graphic();
    void draw_graphic(sf::RenderWindow&,double,double,double,double);
    void update_dependency(std::map<double,double>);
private:
    std::map<double,double> dependency_; 
};
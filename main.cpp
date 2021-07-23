#include <iostream>
#include <random>
#include <cmath>
#include <cstdlib>
#include "Molecule.hpp"
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include "Button.hpp"
#include <map>

double atomnaya_massa = 1.6E-27;
double boltzman = 1.38E-23;
double tick_factor = 1E-4;
double amount_molecules = 1E4;
double amount_ticks = 1E4;
double pistron_speed = -0.001;
double acceleration_mss = 0;
double passed_time = 0;

//Oxygen molecules
void generate_molecules(int num = 10000, double biggest_probability = 350, double sigma = 50, double generation_border = 1)
{
    int direction_x_par = 0;
    int direction_y_par = 0;
    std::default_random_engine generator;
    std::normal_distribution<double> distribution_dxdy(biggest_probability, sigma);
    std::default_random_engine generator_real;
    std::uniform_real_distribution<double> distribution_x(0.1, generation_border);
    std::uniform_real_distribution<double> distribution_y(0.1, Vessel::Instance().get_H());
    std::uniform_int_distribution<int> distribution_vec_vx(0, 1);
    distribution_vec_vx(generator) ? direction_x_par = 1 : direction_x_par = -1;
    std::uniform_int_distribution<int> distribution_vec_vy(0, 1);
    distribution_vec_vy(generator) ? direction_y_par = 1 : direction_y_par = -1;

    for (int i = 0; i < num; ++i)
        Molecule(direction_x_par * distribution_dxdy(generator), direction_y_par * distribution_dxdy(generator), distribution_x(generator_real), distribution_y(generator_real), 32 * atomnaya_massa);
}

void molecules_move(double tick_factor = 1)
{
    for (auto &molecule : All_molecules::Instance().molecules)
        molecule.move(tick_factor);
}

void check_colission()
{
    for (auto &molecule : All_molecules::Instance().molecules)
    {
        if (((std::abs(molecule.get_x() - 0) < 0.05)) || (std::abs(molecule.get_x() - Vessel::Instance().get_W()) < 0.05))
        {
            molecule.get_dx() > 0 ? molecule.set_dx(molecule.get_dx() - Vessel::Instance().get_dx())
                                  : molecule.set_dx(molecule.get_dx() + Vessel::Instance().get_dx());
            molecule.set_dx(-molecule.get_dx());
        }
        if (((std::abs(molecule.get_y() - 0) < 0.05)) || (std::abs(molecule.get_y() - Vessel::Instance().get_H()) < 0.05))
        {
            molecule.set_dy(-molecule.get_dy());
        }
    }
}

void acceleration(double acceleration, double tick_factor = 1)
{
    for (auto &molecule : All_molecules::Instance().molecules)
    {
        molecule.set_dx(molecule.get_dx() + acceleration * tick_factor);
    }
}

double concentration(double a)
{
    int n = 0;
    for (auto &molecule : All_molecules::Instance().molecules)
        if (std::abs(molecule.get_x() - a) < 0.05)
            n++;
    return n;
}

std::map<double, double> velocity_dependency()
{

    std::map<double, double> dependency;
    double min = All_molecules::Instance().molecules[0].get_velocity();
    double max = min;
    for (auto &molecule : All_molecules::Instance().molecules)
    {
        double speed = molecule.get_velocity();
        if (speed > max)
            max = speed;
        if (speed < min)
            min = speed;
    }
    double dv = (max - min) / 100;
    for (int i = 1; i < 100; i++)
        dependency[min + dv * i] = 0;

    for (auto &molecule : All_molecules::Instance().molecules)
    {
        double distance = molecule.get_velocity() - min;
        double mod = fmod(distance, dv);
        int n = static_cast<int>((distance - mod) / dv);
        mod > dv / 2 ? dependency[min + (n + 1) * dv]++ : dependency[min + n * dv]++;
    }
    return dependency;
}

void simulate(int ticks)
{
    Vessel::Instance().set_dx(pistron_speed);
    for (int i = 0; i < ticks; ++i)
    {
        Vessel::Instance().move(tick_factor);
        check_colission();
        molecules_move(tick_factor);
    }
}

int main()
{
    generate_molecules(amount_molecules, 350, 50, 0.5);

    double window_W = 800;
    double window_H = 800;
    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(window_W, window_H), "SFML Works!");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        ;


    sf::Text text;
    text.setFont(font);
    text.setPosition(sf::Vector2f(window_W / 2 + 10, window_H / 2 + window_H / 20));
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::Red);

    std::vector<double> temperatures;
    std::vector<std::vector<double>> concentrations;
    temperatures.push_back(All_molecules::Instance().get_Temperatue());
    window.display();

    std::vector<Button> buttons;
    Button restart_button(window_W / 20, window_H / 2 + window_H / 20, window_W / 4, window_H / 10, "Restart");
    Button make_faster_button(window_W / 20, window_H / 2 + 3 * window_H / 20,
                                 window_W / 8, window_H / 10, "Fast");
    Button make_slower_button(window_W / 20 + window_W / 8, window_H / 2 + 3 * window_H / 20, 
                                window_W / 8, window_H / 10, "Slow");
    Button stop_button(window_W/20,window_H/2+5*window_H/20, 
                                window_W / 4, window_H / 10, "Pause");
    buttons.push_back(restart_button);
    buttons.push_back(make_faster_button);
    buttons.push_back(make_slower_button);

    bool render;

    Interface_Window main_window(0, 0, window_W, window_H);
    Interface_Window commands(0, window_H / 2, window_W / 2, window_H / 2);
    Interface_Window statistic(window_W / 2, window_H / 2, window_W / 2, window_H / 2);
    Interface_Window visualisation(0, 0, window_W, window_H / 2);
    std::map<double, double> rero;
    Graphic MaxWell(visualisation, velocity_dependency());

    while (window.isOpen())
    {
        render = true;

        temperatures.push_back(All_molecules::Instance().get_Temperatue());
        double current_temperature = All_molecules::Instance().get_Temperatue();
        text.setString(
            " Current temperature = " + std::to_string(current_temperature) +
            "\n Time passed = " + std::to_string(passed_time) +
            "\n Last dT = " + std::to_string(temperatures[temperatures.size() - 1] - temperatures[temperatures.size() - 2])+
            "\nSpeed of piston is " + std::to_string(pistron_speed) + " m/s" +
            "\nPistron position is " + std::to_string(Vessel::Instance().get_W()));


        simulate(amount_ticks);

        passed_time += tick_factor * amount_ticks;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {

                    if (restart_button.mouse_on_button(window))
                    {
                        std::cout << "really" << std::endl;
                        All_molecules::Instance().erase_molecules();
                        generate_molecules(amount_molecules, 350, 50, 0.5);
                        Vessel::Instance().set_W(1);
                        double passed_time = 0;
                    }
                    if(make_faster_button.mouse_on_button(window))
                    {
                        std::cout<<"faster"<<std::endl;
                        pistron_speed+=0.001;
                    }
                    if(make_slower_button.mouse_on_button(window))
                    {
                        std::cout<<"slower"<<std::endl;
                        pistron_speed-=0.001;
                    }
                }   
            }
        }

        if (render)
        {
            render = false;
            window.clear(sf::Color::White);
            main_window.draw(window);
            commands.draw(window);
            statistic.draw(window);
            visualisation.draw(window);
            MaxWell.update_dependency(velocity_dependency());
            MaxWell.draw_graphic(window, 200, 1200, 0, amount_molecules / 15);

            window.draw(text);
            restart_button.draw(window);
            make_faster_button.draw(window);
            make_slower_button.draw(window);
            stop_button.draw(window);
            window.display();
        }
    }
    return 0;
}
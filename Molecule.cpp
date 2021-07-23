#include "Molecule.hpp"
#include <cmath>
#include <iostream>

Object::Object(){}
Object::Object(double dx, double dy, double x, double y) : dx_(dx), dy_(dy), x_(x), y_(y) {}

void Object::set_dx(double dx)
{
    dx_ = dx;
}
void Object::set_dy(double dy)
{
    dy_ = dy;
}
void Object::set_x(double x)
{
    x_ = x;
}
void Object::set_y(double y)
{
    y_ = y;
}
double Object::get_dx()
{
    return dx_;
}
double Object::get_dy()
{
    return dy_;
}
double Object::get_x()
{
    return x_;
}
double Object::get_y()
{
    return y_;
}

void Molecule::move(double tick_factor=1)
{
    x_ += dx_ * tick_factor;
    y_ += dy_ * tick_factor;
}

//BUG SHOULD BE CHANGED !!!!!

void Vessel::move(double tick_factor=1)
{
    W_ += dx_*tick_factor;
}


Molecule::Molecule(double dx, double dy, double x, double y, double mass) : Object(dx,dy,x,y), mass_(mass) 
{
    All_molecules::Instance().new_molecule(*this);
}

double Molecule::get_velocity()
{
    return std::sqrt(dx_ * dx_ + dy_ * dy_);
}

double Molecule::get_kenergy()
{
    return mass_ * get_velocity() * get_velocity() / 2;
}

void All_molecules::new_molecule(Molecule molecule)
{
    molecules.push_back(molecule);
}
int All_molecules::get_num()
{
    return molecules.size();
}
double All_molecules::get_mean_kenergy()
{
    double summ_kenergy = 0;
    // std::cout<<molecules.size()<<std::endl;
    for (auto &molecule : molecules)
    {
        summ_kenergy += molecule.get_kenergy();
        // std::cout<< molecule.get_kenergy()<<std::endl;
    }
    return summ_kenergy / molecules.size();
}
double All_molecules::get_Temperatue()
{
    double boltzman = 1.38E-23;
    return 2 * this->get_mean_kenergy() / (3 * boltzman);
}
void All_molecules::print_velocities()
{
    for (int i = 0; i < 10; ++i)
    {
        int gap = 0;
        std::cout << i * 100 << "-" << (i + 1) * 100 << ": ";
        for (auto molecule : molecules)
        {
            if ((molecule.get_velocity() > i * 100) && (molecule.get_velocity() < (i + 1) * 100))
                gap++;
        }
        // std::cout<<(100*gap/molecules.size())<<std::endl;
        std::cout << std::string(int(100 * gap / molecules.size()), '*') << std::endl;
    }
}

void All_molecules::erase_molecules()
{
    molecules.clear();
}


All_molecules &All_molecules::Instance()
{
    static All_molecules theSingleInstace;
    return theSingleInstace;
}

double Vessel::get_H()
{
    return H_;
}
double Vessel::get_W()
{
    return W_;
}
void Vessel::set_dx(double dx)
{
    dx_=dx;
}
double Vessel::get_dx(void)
{
    return dx_;
}
void Vessel::set_W(double W)
{
    W_=W;
}
Vessel &Vessel::Instance()
{
    static Vessel theSingleInstace;
    return theSingleInstace;
}
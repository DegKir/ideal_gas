#include <vector>
#include <map>
class Object
{
public:
    Object();
    Object(double dx, double dy, double x, double y);
    void set_x(double);
    void set_y(double);
    void set_dx(double);
    void set_dy(double);
    double get_dx();
    double get_dy();
    double get_x();
    double get_y();
    double x_=0;
    double y_=0;
    double dx_=0;
    double dy_=0;
    virtual void move(double)=0;
    virtual ~Object(){}
}; 

class Temperature
{

};
class Energy
{

};


class Molecule: public Object
{
public:
    Molecule(double dx, double dy, double x, double y, double mass);
    double mass_;
    double get_kenergy();
    double get_velocity();
    virtual void move(double);
    virtual ~Molecule(){}
};

class All_molecules
{
public:
    void new_molecule(Molecule molecule);
    int get_num();
    double get_mean_kenergy();
    double get_Temperatue();
    void print_velocities();
    void erase_molecules();

private:
    std::vector<Molecule> molecules;

public:
    static All_molecules &Instance();
    friend void check_colission();
    friend void molecules_move(double);
    friend double concentration(double);
    friend void acceleration(double,double);
    friend std::map<double,double> velocity_dependency();
private:
    All_molecules() {}
    All_molecules(const All_molecules &root) = delete;
    All_molecules &operator=(const All_molecules &) = delete;
};

class Vessel
{
public:
    double get_W();
    double get_H();
    void set_W(double);
    void set_dx(double);
    double get_dx(void);
    void move(double);
    ~Vessel(){}

private:
    double W_ = 1;
    double H_ = 1;
    double dx_=1;
public:
    static Vessel &Instance();

private:
    Vessel() {}
    Vessel(const Vessel &root) = delete;
    Vessel &operator=(const Vessel &) = delete;
};
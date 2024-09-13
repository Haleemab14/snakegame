// C++ program to illustrate the deepcopy and shallow copy
#include <iostream>
#include <vector>
using namespace std;
// Class of Car
class Car {
public:
    string name;
    double* price;
    Car(string name, double p)
    {
        this->name = name;
        price = new double;
        *price = p;
    }
    // Deep Copy of car 
    Car(Car &obj){
        this->name = obj.name;
        price = new double;
        *price = *obj.price;
         *obj.price = 42;//-->this will change the original price as well as copy price
    }
    void display(){
        cout << "Name: " << name << endl;
        cout << "Price: " << *price << endl;
    }
};
int main()
{
    Car c1("bugatti",23);
    c1.display();
    // Shallow copy of car
    Car c2(c1);
    *c2.price = 44;//-->this will not change the original price but will change the copy price
    c2.display();
    c1.display();
    return 0;
}

#include <iostream>
using namespace std;

class complex
{
public:
    int real, img;

    complex()
    {
        real = 0; img = 0;
    }

    complex operator +(complex b)
    {
        complex r;
        r.real = real + b.real;
        r.img = img + b.img;
        return r;
    }

    complex operator -(complex b)
    {
        complex r;
        r.real = real - b.real;
        r.img = img - b.img;
        return r;
    }

    complex operator *(complex b)
    {
        complex r;
        r.real = (real * b.real) - (img * b.img);
        r.img = (real * b.img) + (img * b.real);
        return r;
    }

    friend ostream & operator << (ostream &os, const complex &z);
    friend istream & operator >> (istream &is, complex &z);
};

ostream & operator << (ostream &os, const complex &z)
{
    os << "(" <<  z.real << ")" <<  "+i" << "(" <<  z.img << ")";
    return os;
}

istream & operator >> (istream &is, complex &z)
{
    is >> z.real >> z.img;
    return is;
}

int main()
{
    int option;
    char cont;
    complex z1, z2;

    cout << "Welcome to Complex Calculator!";
    while(true){
        cout <<    "\nOptions Menu : "
             << "\n1 - Addition"
             << "\n2 - Multiplication"
             << "\n\nEnter your choice :";
        cin >> option;

        switch(option){
            case 1: //addition

                cout << "\nEnter real and imaginary part of complex number z1 :\n";
                cin >> z1;
                cout << "\nEnter real and imaginary part of complex number z2 :\n";
                cin >> z2;
                cout << "Addition of complex numbers = ";
                cout << z1+z2;
                break;

            case 2: //multiplication

                cout << "\nEnter real and imaginary part of complex number z1 :\n";
                cin >> z1;
                cout << "\nEnter real and imaginary part of complex number z2 :\n";
                cin >> z2;
                cout << "Product of complex numbers = ";
                cout << z1*z2;
                break;

            default:
                cout << "\nInvalid choice!" << endl;
                break;
        }

        cout << "\nDo you wish to continue? (y/n)\n";
        cin >> cont;
        if (cont == 'n' || cont == 'N'){
            break;
        }
    }

    return 0;
}

#include <iostream>
inline double square(double x){ return x * x; }

int main()
{
    using namespace std;
    double a, b;
    double c = 13.0;

    a = square(5.0);
    b = square(4.5 + 7.5); /* if defined by macro definition, then 
    b = 4.5 + 7.5 * 4.5 + 7.5, more brackets should be added */
    cout << "a = " << a << ", b = " << b << "\n";
    cout << "c = " << c;
    cout << ", c squared = " << square(c++) << "\n";
    cout << "Now c = " << c << "\n";
    return 0;
}
#include <iostream>
#include <array>
#include <string>

const int Seasons = 4;
const std::array <std::string , Seasons> Snames =
    {"Spring", "Summer", "Fall", "Winter"}; // 常量， 整个源代码文件共享， const

void fill(std::array <double, Seasons> * pa);
void show(std::array <double, Seasons> da);

int main()
{
    std::array <double, Seasons> expenses;
    fill(&expenses);
    show(expenses);
    return 0; 
}

void fill(std::array <double, Seasons> * pa) // pa 对象的指针
{
    using namespace std;
    for (int i = 0; i < Seasons; i++)
    {
        cout << "Enter " << Snames[i] << " expenses: ";
        cin >> (*pa)[i];
    }
}

void show(std::array <double, Seasons> da) // da 对象
{
    using namespace std;
    double total = 0.0;
    cout << "\nEXPENSES\n";
    for (int i = 0; i < Seasons; i++)
    {
        cout << Snames[i] << ": $" << da[i] << endl;
        total += da[i];
    }
    cout << "Total Expenses: $" << total << endl;
}
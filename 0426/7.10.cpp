#include <iostream>
char * buildstr(char c, int n);
int main()
{
    using namespace std;
    int times;
    char ch;

    cout << "Enter a character: ";
    cin >> ch;
    cout << "Enter an integer: ";
    cin >> times;
    char *ps = buildstr(ch, times);
    cout << ps << endl;
    delete [] ps; //释放内存
    ps = buildstr('+', 20); //函数复用
    cout << ps << "-DONE-" << ps << endl;
    delete [] ps; //释放内存
    return 0;
}

char * buildstr(char c, int n)
{
    char * pstr = new char[n + 1]; //分配空间
    pstr[n] = '\0'; //字符串的结束
    while (n-- > 0)
        pstr[n] = c;
    return pstr;
}
#include <iostream>
const int Len = 66;
const int Divs = 6;
void subdivide(char ar[], int low, int high, int level);
int main()
{
    char ruler[Len];
    int i;
    for (i = 1; i < Len - 2; i++)
        ruler[i] = ' '; // 设置第2个到倒数第2个
    ruler[Len - 1] = '\0'; // 设置结束符
    int max = Len - 2;
    int min = 0;
    ruler[min] = ruler[max] = '|'; // 设置第1个和倒数第1个
    std::cout << ruler << std::endl;
    for (i = 1; i <= Divs; i++)
    {
        subdivide(ruler, min, max, i); // 每次都是从i = 1从头递归下去，而不是继续上一次
        std::cout << ruler << std::endl; // 输出横着看 不是竖着看
        for (int j = 1; j < Len - 2; j++)
            ruler[j] = ' '; // 复原，虽然由于循环中的函数调用方式看起来不影响结果
    }
    return 0;
}

void subdivide(char ar[], int low, int high, int level)
{
    if (level == 0)
        return;
    int mid = (high + low) / 2;
    ar[mid] = '|'; 
    subdivide(ar, low, mid, level - 1);
    subdivide(ar, mid, high, level - 1); // 可参考汉诺塔理解
}
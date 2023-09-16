//编写一个程序，输入a、b、c三个值，输出其中最大值。
#include <iostream>
    void max_select(){
    int a,b,c,max;
    std::cout << "输入三个整数: " << "\n";
    std::cin >> a >> b >> c;
    std::cout << "最大値为: \n";
    max = (a>b?a:b)>c? (a>b?a:b) : c;
    std::cout << max;
    std::cout << std::endl;
    return;
    }
int main(void) {
    max_select();
    system("pause");
    return 0;
}
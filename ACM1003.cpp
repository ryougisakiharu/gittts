/*要将"China"译成密码，译码规律是：用原来字母后面的第4个字母代替原来的字母．
例如，字母"A"后面第4个字母是"E"．"E"代替"A"。因此，"China"应译为"Glmre"。
请编一程序，用赋初值的方法使cl、c2、c3、c4、c5五个变量的值分别为，’C’、’h’、’i’、’n’、’a’，
经过运算，使c1、c2、c3、c4、c5分别变为’G’、’l’、’m’、’r’、’e’，并输出。*/
#include<iostream>
void add_sub(){
    char ch1,ch2,ch3,ch4,ch5;
    std::cout << "请输入五个字母: \n";
    std::cin >> ch1 >> ch2 >> ch3 >> ch4 >> ch5;
    ch1 +=4;
    ch2 +=4;
    ch3 +=4;
    ch4 +=4;
    ch5 +=4;
    std::cout << ch1 << ch2 << ch3 << ch4 << ch5;
    std::cout << std::endl;
    return;
}
int main(void){
    add_sub();
    system("pause");
    return 0;
}
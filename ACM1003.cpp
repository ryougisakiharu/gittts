/*Ҫ��"China"������룬��������ǣ���ԭ����ĸ����ĵ�4����ĸ����ԭ������ĸ��
���磬��ĸ"A"�����4����ĸ��"E"��"E"����"A"����ˣ�"China"Ӧ��Ϊ"Glmre"��
���һ�����ø���ֵ�ķ���ʹcl��c2��c3��c4��c5���������ֵ�ֱ�Ϊ����C������h������i������n������a����
�������㣬ʹc1��c2��c3��c4��c5�ֱ��Ϊ��G������l������m������r������e�����������*/
#include<iostream>
void add_sub(){
    char ch1,ch2,ch3,ch4,ch5;
    std::cout << "�����������ĸ: \n";
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
//��дһ����������a��b��c����ֵ������������ֵ��
#include <iostream>
    void max_select(){
    int a,b,c,max;
    std::cout << "������������: " << "\n";
    std::cin >> a >> b >> c;
    std::cout << "���Ϊ: \n";
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
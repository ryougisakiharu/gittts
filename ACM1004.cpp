/*��һͷĸţ����ÿ�������һͷСĸţ��ÿͷСĸţ�ӵ��ĸ���ͷ��ʼ��ÿ�����Ҳ��һͷСĸţ��
����ʵ���ڵ�n���ʱ�򣬹��ж���ͷĸţ��*/
#include <iostream>
int funfun(int n){
    if(n==1||n==2||n==3){
        return n;
    }
    else{
        return funfun(n-1)+funfun(n-3);
    }
}
int main(void){
    int n;
    while(std::cin>>n){
        std::cout<<funfun(n)<<std::endl;
    }
    return 0;
}
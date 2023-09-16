/*有一头母牛，它每年年初生一头小母牛。每头小母牛从第四个年头开始，每年年初也生一头小母牛。
请编程实现在第n年的时候，共有多少头母牛？*/
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
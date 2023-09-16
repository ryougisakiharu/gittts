#include <iostream>
using namespace std;
float price[100];
int discount[100];
int main(void){
    int i;
    freopen("111.txt","r",stdin);
    while(cin>>price[i]>>discount[i]){
        i++;
}
i = 0;
float sum = 0;
while(price[i]!=0){
    if(discount[i]<10){
    sum += price[i]*discount[i]/10;
}
else{
    sum += price[i]*discount[i]/100;
}
}
 cout  << sum <<endl;
}
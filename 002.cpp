#include<iostream>
long int fact(int n);
int main (void){
{int k;
long int y;
k=5;
y=fact(k);
printf("%d,%ld\n",k,y);
}
        return 0;
}
long int fact(int n){
long f;
if(n>1)f=n*fact(n-1);
else f=1;
return(f);
}
#include <iostream>
using namespace std;
int funfun(int n){
    if(n==1||n==2||n==3){
        return n;
    }
    else{
        return funfun(n-1)+funfun(n-3);
    }
}
int main(){
    int n;
    cout << ""<< endl;
    cin >> n;
    cout << funfun(n);
    return 0;
}
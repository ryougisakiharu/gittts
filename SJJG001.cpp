#include <iostream>
#include<iomanip>

using namespace std;

#define LIST_TNIT_SIZE 100
#define NUM 5

typedef struct {
    int *elem;
    int length;
    int listsize;
}SqList;
//结构体

void initList(SqList &L){
    L.elem = new int[LIST_TNIT_SIZE];
    L.length = 0;
    L.listsize = LIST_TNIT_SIZE;
}//初始化


int locateElem(SqList L,int e){
    int i;
    for(i = 0;i<L.length;i++){
        if(L.elem[i]==e)
        return i+1;
    }
    return 0;
}
//找到位置


void getElem(SqList L,int i,int &e){
    if(i<1||i>L.length){
        return;
    }else{
        e = L.elem[i-1];
    }
}
//得到这个数的在这个数组里面的位置

 
void insertElem(SqList &L,int i,int e){
    int j ;
    if(i<1||i>L.length+1){
        return;
    }
    for(j = L.length;j>=i;j--){
        L.elem[j]=L.elem[j-1];
    }
    L.elem[i-1]=e;
    L.length++;
}
//插入一个数，左面的数移到右面，这些数想要移动的话，可以从右面到左面想


void deleteElem(SqList &L,int i,int &e){
    int j;
    if(i<1||i>L.length)
    {
        return;    
    }
    e = L.elem[i-1];
    for(j = i;j<L.length;j++)
    {
    L.elem[i-1] = L.elem[i];
    }
    L.length--;
}//删除一个数

void xiaohudeleteElem(SqList &L,int i,int &e){
    delete[] L.elem;
    L.length = 0;
    L.listsize = 0;
}
//销毁线性表
void showList(SqList L){ 
    for(int i = 0;i<L.length;i++){
        cout << setw(4)<< L.elem[i] << endl;
}
}
int main(void){
    int a[NUM];
    int b[NUM];
    int e;
    cout << "这是A数组" << endl;
    for(int i = 0;i<NUM;i++){
        cin >> a[i];
    }
    cout << "这是B数组" << endl;
    for(int i = 0;i<NUM;i++){
        cin >> b[i];
    }
    SqList La,Lb;
    initList(La);
    initList(Lb);
    for(int i = 0;i<NUM;i++)
    {
    insertElem(La,La.length+1,a[i]);
    insertElem(Lb,Lb.length+1,b[i]);
    }
    cout << "set a"<< endl;
    //这是啥呗老婆留下的记号wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
    showList(La);
    cout << "set b"<< endl; 
    showList(Lb);
    for(int i = La.length;i>=1;i--){
        getElem(La,i,e);
        if(locateElem(Lb,e)!=0){
            deleteElem(La,i,e);
    }
    }
    cout << "set a"<< endl;
    showList(La);
return 0;}    






















































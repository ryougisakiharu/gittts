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
//�ṹ��

void initList(SqList &L){
    L.elem = new int[LIST_TNIT_SIZE];
    L.length = 0;
    L.listsize = LIST_TNIT_SIZE;
}//��ʼ��


int locateElem(SqList L,int e){
    int i;
    for(i = 0;i<L.length;i++){
        if(L.elem[i]==e)
        return i+1;
    }
    return 0;
}
//�ҵ�λ��


void getElem(SqList L,int i,int &e){
    if(i<1||i>L.length){
        return;
    }else{
        e = L.elem[i-1];
    }
}
//�õ����������������������λ��

 
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
//����һ��������������Ƶ����棬��Щ����Ҫ�ƶ��Ļ������Դ����浽������


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
}//ɾ��һ����

void xiaohudeleteElem(SqList &L,int i,int &e){
    delete[] L.elem;
    L.length = 0;
    L.listsize = 0;
}
//�������Ա�
void showList(SqList L){ 
    for(int i = 0;i<L.length;i++){
        cout << setw(4)<< L.elem[i] << endl;
}
}
int main(void){
    int a[NUM];
    int b[NUM];
    int e;
    cout << "����A����" << endl;
    for(int i = 0;i<NUM;i++){
        cin >> a[i];
    }
    cout << "����B����" << endl;
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
    //����ɶ���������µļǺ�wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
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






















































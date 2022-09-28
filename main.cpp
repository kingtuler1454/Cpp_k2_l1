#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;
class Polynomial{
public:
    struct Node {
	int coefficent;
    int degree;
	struct Node *next;
    };


    Polynomial( int start_degree,int start_coefficent){
    Node *head = NULL;
    Node *tmp=(Node*)malloc(sizeof(Node)); // создаем узел
    tmp->degree=start_degree;
    tmp->next =head;
    head = tmp;
    tmp->coefficent=start_coefficent;
    }

    void operator [](int  x)
    {   
        cout<<x; 
    }

    
    void set(int coefficent, int degree )
    {
    Node *tmp=(Node*)malloc(sizeof(Node)); // создаем узел
    tmp->degree=degree;
    //tmp->next =head;
    //head = tmp;
    tmp->coefficent=coefficent;
    }
};
int main(){
    int degree, coefficent;
    do:
        cout<<"Введите степень многочлена: ";
        cin>> degree;
        cout<<"Выберите  коэффицент для  степени "<<degree;
        cin>> coefficent;
        cout<<"Будем ли вводить еще коеффицет? ";
        cin>>
    Polynomial A(degree, coefficent);
    while()
    A[5];
    //printf("%d", 5);
}

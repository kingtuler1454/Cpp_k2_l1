#include <stdio.h>
#include <iostream>
using namespace std;
class Equalization
{
public:
struct list{
    int degree;
    int coefficent;
    list* next;
} *head;

    Equalization (int coefficent,int degree){ 
    this->head=(struct list*)malloc(sizeof(struct list));
    this->head->degree = degree;
    this->head->coefficent=coefficent;
    this->head->next = NULL; // это последний узел списка
    }
    ~Equalization(){
        list *p;
        while (p=head)
        {
          head=p->next;
          delete p;
        }
    }
    void Add(int coefficent,int degree){
        list * pointer, *p;
        pointer->coefficent=coefficent;
        pointer->degree=degree;
        pointer->next= new list;
        pointer->next=this->head->next;
        this->head->next=pointer;
    
    }
    void Print(){
        while(this->head){
            std::cout<<"Экран "<<head->coefficent<<"x^"<<head->degree<<"+";
            head=head->next;
        }

    }
};
int main(){
    Equalization A(1,1);
    A.Print();
    A.Add(2,2);
    A.Print();
    A.Add(3,3);
    A.Print();

}
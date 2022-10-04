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
    void Set(int coefficent,int degree){
        if(coefficent!=0){
        list * pointer;
        pointer=(list*)malloc(sizeof(list));
        pointer->coefficent=coefficent;
        pointer->degree=degree;
        pointer->next= this->head;
        this->head=pointer;
        }
    }
    void Print(){
        if(head) {
            cout<<head->coefficent<<"x^"<<head->degree;
            head=head->next;}
        while(head){
            if (head->coefficent) cout<<"+";
            cout<<head->coefficent<<"x^"<<head->degree;     
            head=head->next;   
        }
    }
    void Derivative(){
        while(head){
            cout<<"\n"<<head->coefficent*head->degree<<"x^"<<head->degree-1;
            head=head->next;
        }
    }
};
int main(){
    Equalization A(1,1);
    A.Set(2,2);
    A.Set(3,3);
    A.Print();
    A.Derivative();

}

#include <stdio.h>
#include <iostream>
#include <cmath>
using namespace std;
/* конструктор с параметрами: начальную степень многочлена;
• оператор [] для чтения коэффициента при заданной степени (обеспечить корректное поведение при любой неотрицательной степени);
 метод set для установки коэффициента при заданной степени (обеспечить корректное поведение в случае нулевого значения коэффициента и при любой неотрицательной степени);
• операторы сложения и вычитания многочленов;
 ооператор умножения многочлена на скаляр (обеспечить коммутативность);
вычисление значения многочлена при указанном значении х.
*/
class Equalization
{

struct list{
    double degree;
    double coefficent;
    list* next;
} *head;
public:
    Equalization (double coefficent,double degree){ 
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
    bool DetectOldDegree(double coefficent,double degree){
        list *StartHead=head;
        int index;
        while(head){
            if (head->degree==degree) {
                head->coefficent=+coefficent;
                cout<<"\nСтепени "<<head->degree<<" просуммирован  коэффицент "<<head->coefficent<<endl;   
                head=StartHead;
                return true;}
            head=head->next;   }
        head=StartHead;
        return false;    
    }
    void Set(double coefficent,double degree)
    {
        if (!DetectOldDegree(coefficent,degree))
        {if(coefficent!=0){
        list * pointer;
        pointer=(list*)malloc(sizeof(list));
        pointer->coefficent=coefficent;
        pointer->degree=degree;
        pointer->next= this->head;
        this->head=pointer;
        }}
    }
    void Print(){
        list *StartHead=head;
        bool FirstStart=true;
        cout<<"Наша последовательность: ";
        while(head){
            if(!FirstStart &&head->coefficent >0&&head->degree!=0) cout<<"+";
            if(head->coefficent!=1) cout<<head->coefficent; 
            if(head->degree!=0)cout<<"x";
            if(head->degree<0){cout<<"^("<<head->degree<<")";}
            else if(head->degree!=1 &&head->degree!=0) cout<<"^"<<head->degree;    
            head=head->next;
            FirstStart=false;   
        }
        cout<<"\n";
        head=StartHead;
    }
    void Derivative(){
        list *StartHead=head;
        while(head){
            head->coefficent=head->coefficent*head->degree;
            head->degree--;   
            head=head->next;   
        }
        head=StartHead;
        cout<<"\nПроизводная высчитана...\n";
    }
    void Multiplication(double value){
        list *StartHead=head;
        while(head){
            head->coefficent=head->coefficent*value;
            head=head->next;   
        }
        head=StartHead;
        cout<<"\nСкалярное произведение высчитано...\n";
    }
    void Calculation(double x){
        list *StartHead=head;
        double sum=0;
        while(head){
            sum+=head->coefficent*pow(x,head->degree);
            head=head->next;
        }
        head=StartHead;
        cout <<"При x="<<x<<" значение последовательности равно "<<sum<<endl;
    }
    void Sum(Equalization &src)
    {
        list *StartHeadA=head;
        list *StartHeadB=src.head;
        while(head){
            while(src.head){
            if(head->degree==src.head->degree)
            {
                head->coefficent+=src.head->coefficent;
                break;
            }
            src.head=src.head->next;
            }
            src.head=StartHeadB;
            head=head->next;
        }
        head=StartHeadA;
    }
};
int main(){
    Equalization A(-1,1);
    A.Set(1,3);
    A.Set(-2,3);
    A.Print();
    //A.Derivative();
    A.Print();
   // A.Multiplication(4.5);
    A.Print();
    A.Calculation(5);
    A.Print();
    Equalization B(-1,1);
    B.Set(-2,3);
    B.Set(-33,2);
    A.Sum(B);
    A.Print();
}

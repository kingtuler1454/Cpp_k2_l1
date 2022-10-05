#include <stdio.h>
#include <iostream>
#include <window.h>
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
        cout<<"\nНаша последовательность: ";
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
        bool SearchSuccesesful;
        while(src.head){
            SearchSuccesesful=false;
            while(head){
                if(head->degree==src.head->degree)
                    {
                        SearchSuccesesful=true;
                        head->coefficent+=src.head->coefficent;
                        break;
                    }
                head=head->next;
            }
            if(!SearchSuccesesful)
            {   cout<<"dsf";
                list * pointer;
                pointer=(list*)malloc(sizeof(list));
                pointer->coefficent=src.head->coefficent;
                pointer->degree=src.head->degree;
                pointer->next=StartHeadA;
                StartHeadA=pointer;
            }
            head=StartHeadA;
            src.head=src.head->next;
        }
        src.head=StartHeadB;
        head=StartHeadA;
    }
   
};
int main(){
    double coefficent, degree;
    int vibor;
    cout<<"Многочлен пока не создан, введите коэффицент первого элемента: "<<endl;
    cin>>coefficent;
    cout<<"Введите его степень: "<<endl;
    cin>>degree;
    Equalization A(coefficent,degree);
    A.Print();
    bool flag=true;
    while(flag){
    cout<<"Выберите действие:\n1)Добавить новый элемент\n2)Умножить на скаляр\n3)Вычислить х\n4)Найти производную\n5)Сумма с другим многочленом\n6)Вычесть из него другой многочлен\n7)Средактировать коэффицент\n";
    cin>>vibor;
    switch (vibor)
    {
    case 1:
        cout<<"Введите коэффицент нового элемента: "<<endl;
        cin>>coefficent;
        cout<<"Введите его степень: "<<endl;
        cin>>degree;
        A.Set(coefficent,degree);
        
    case 2:
        cout<<"Введите значение на которое хотите умножить: "<<endl;
        cin>>degree;
        A.Multiplication(degree);
        break;
    case 3:
        cout<<"Введите значение х: "<<endl;
        cin>>degree;
        A.Calculation(degree);
        break;
    case 4:
        A.Derivative();
        break;
    case 5:
        /* code */
        break;
    case 6/* constant-expression */:
        /* code */
        break;
    case 7/* constant-expression */:
        /* code */
        break;
    default:
        break;
    system("CLS");
    }}
    
}

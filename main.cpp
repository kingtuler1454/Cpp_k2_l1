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
    if(coefficent!=0){ 
        this->head=(struct list*)malloc(sizeof(struct list));
        this->head->degree = degree;
        this->head->coefficent=coefficent;
        this->head->next = NULL; // это последний узел списка
    }
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
            {
                if(coefficent!=0){
                    list * pointer;
                    pointer=(list*)malloc(sizeof(list));
                    pointer->coefficent=coefficent;
                    pointer->degree=degree;
                    pointer->next= this->head;
                    this->head=pointer;
        }}
    }
    int DeleteElement(double degree)
{
    list *StartHead=head;
    while(head)
  {
    if(head->degree==degree) // если голова
    {
        list *deleted=head;
        head=head->next;
        free(deleted);
        return 1;
    }
    if(head->next &&(head->next)->degree==degree)// если не голова
        {
            list *pred=head;
            head=head->next;
            pred->next=head->next;
            free(head);
            head=StartHead;
            return 1;
            }
    head=head->next;
  }
   head=StartHead;
   return 0; 
  }
    void Print(){
        list *StartHead=head;
        bool FirstStart=true;
        cout<<"\nНаша последовательность: ";
        while(head){
            if(head->coefficent==0)
            {
                DeleteElement(head->degree);
                StartHead=head;
                FirstStart=true;
            }
            if(!FirstStart &&head->coefficent >0) cout<<"+";
            if(head->coefficent!=1) cout<<head->coefficent; 
            if(head->degree!=0)cout<<"x";
            if(head->degree==0 && head->coefficent==1) cout<<head->coefficent;
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
    void Sum(Equalization &src,bool SumOperation)
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
                        if(SumOperation) head->coefficent+=src.head->coefficent;
                        else head->coefficent-=src.head->coefficent;
                        break;
                    }
                head=head->next;
            }
            if(!SearchSuccesesful)
            {   
                list * pointer;
                pointer=(list*)malloc(sizeof(list));
                if(SumOperation)
                    pointer->coefficent=src.head->coefficent;//+++++++++
                else  pointer->coefficent=src.head->coefficent*(-1);
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
   int operator[](double degree)
   {
        list * StartHead=head;
        while (head){
            if (head->degree==degree)
            {
                cout<<"Введите новый коэффицент степени "<<head->degree<<": ";
                cin>>head->coefficent;
                head=StartHead;
                return 0;
            }
            head=head->next;
        }
        cout<<"Нет такой степени :( \n";
        head=StartHead;
        return 0;    
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
    
    bool flag=true;
    while(flag){
    A.DeleteElement(0);
    A.Print();
    cout<<"Выберите действие:\n1)Добавить новый элемент\n2)Умножить на скаляр\n3)Вычислить х\n4)Найти производную\n5)Сумма с другим многочленом\n6)Вычесть из него другой многочлен\n7)Средактировать коэффицент\n8)Удалить элемент\n9)Выход\n";
    cin>>vibor;
    if (vibor==1)
    {
        cout<<"Введите коэффицент нового элемента: "<<endl;
        cin>>coefficent;
        cout<<"Введите его степень: "<<endl;
        cin>>degree;
        A.Set(coefficent,degree);
    }    
    else if(vibor==2){
        cout<<"Введите значение на которое хотите умножить: "<<endl;
        cin>>degree;
        A.Multiplication(degree);
    }
    else if(vibor==3){
        cout<<"Введите значение х: "<<endl;
        cin>>degree;
        A.Calculation(degree);
    }
    else if(vibor==4){
        A.Derivative();
    }
    else if(vibor==5 || vibor==6){
        bool SumOperation=false;
        if(vibor==5) SumOperation=true; 
        Equalization B(0,0);
        do{
        cout<<"Выберите коэффицент элемента нового многочлена: ";
        cin>>coefficent;
        cout<<"Выберите степень элемента нового многочлена: ";
        cin>>degree;
        B.Set(coefficent,degree);
        cout<<"Добавить еще один элемент к многочлену? \n1)Да\n2)Нет";
        cin>>vibor;
        }
        while(vibor==1);
        A.Sum(B, SumOperation);
    }
    else if(vibor==7){
        cout<<"Выберите степень элемента который редактируем: ";
        cin>>degree;
        A[degree];
    }
    else if(vibor==8){
        cout<<"Выберите степень элемента который удаляем: ";
        cin>>degree;
        A.DeleteElement(degree);
    }
    else if(vibor==9){
        flag=false;
    }
    else{
    system("CLS");
    }
    }
    
}

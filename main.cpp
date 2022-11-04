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
   
public:
    double epsilon=0.1;
    struct list {
        double degree;
        double coefficent;
        list* next;
    } *head;
    int count = 0;
    Equalization(double coefficent, double degree) {
        if (coefficent != 0) {
            this->head = new list;
            this->head->degree = degree;
            this->head->coefficent = coefficent;
            this->head->next = NULL; // это последний узел списка
            count = 1;
        }
    }
    ~Equalization() {
        list* p;
        count = 0;
        while (p = head)
        {
            head = p->next;
            delete p;
        }
    }
    list* GetHead() { return head; }
    void SetHead(list* head) { this->head = head; }
    bool DetectOldDegree(double coefficent, double degree) {
        list* FunctionHead = GetHead();
        while (FunctionHead) {
            if (FunctionHead->degree == degree) {
                FunctionHead->coefficent = FunctionHead->coefficent+ coefficent;
                std::cout << "\nСтепени " << FunctionHead->degree << " просуммирован  коэффицент на " << coefficent << endl;
                return true;
            }
            FunctionHead = FunctionHead->next;
        }
        return false;
    }
    void Set(double coefficent, double degree)
    {
        if (!DetectOldDegree(coefficent, degree))
        {
            if (coefficent != 0) {
                list* pointer;
                pointer = new list;
                pointer->coefficent = coefficent;
                pointer->degree = degree;
                pointer->next = this->head;
                this->head = pointer;
                count++;
            }
        }

    }
    int DeleteElement(double degree)//1x1+2x2+3x3   2
    {
        int NowCount = 0;
        list* FunctionHead = GetHead();
        list* pred = FunctionHead;
        while (NowCount < count)
        {
            if (FunctionHead->degree == degree)
            {
                if (NowCount == 0)
                {
                    SetHead(FunctionHead->next);
                   
                }
                else if (NowCount == count - 1)
                {
                    pred->next = nullptr;
                }
                else {
                    pred->next = FunctionHead->next;
                }
                delete FunctionHead;
                count--;
                return 1;
            }
            pred = FunctionHead;
            FunctionHead = FunctionHead->next;
            NowCount++;
        }
        return 0;
    }
    void Derivative() {
        list* FunctionHead = GetHead();
        cout << "\nНаша производная: ";
        bool FirstStart = true;
        while (FunctionHead) {
            if (!FirstStart) {
               
                if (FunctionHead->coefficent * FunctionHead->degree > 0) cout << "+";
            }
            cout<<FunctionHead->coefficent * FunctionHead->degree;
            if (FunctionHead->degree != 1) {
                cout << "x^"<<FunctionHead->degree-1;
            }
            FirstStart = false;
            FunctionHead = FunctionHead->next;
        }

    }
    void Multiplication(double value) {
        list* FunctionHead = GetHead();
        while (FunctionHead) {
            FunctionHead->coefficent = FunctionHead->coefficent * value;
            FunctionHead = FunctionHead->next;
        }
        cout << "\nСкалярное произведение высчитано...\n";
    }
    void Calculation(double x) {
        list* FunctionHead = GetHead();
        double sum = 0;
        while (FunctionHead) {
            sum += FunctionHead->coefficent * pow(x, FunctionHead->degree);
            FunctionHead = FunctionHead->next;
        }
        cout << "При x=" << x << " значение последовательности равно " << sum << endl;
    }
    bool operator==(Equalization& src)
    {
        list* FunctionHead = GetHead();
        list* StartHeadB = src.head;
        int SearchSuccesesful=0;
        if (count != src.count) return false;
        while (src.head) {
            while (FunctionHead) {
           
                //          ||degree1|  -   |degree2||   <  |epsilon|
                if (abs(abs(FunctionHead->degree) - abs(src.head->degree)) <= abs(epsilon) &&
                    abs(abs(FunctionHead->coefficent)-abs(src.head->coefficent))<=abs(epsilon)) SearchSuccesesful++;
                FunctionHead = FunctionHead->next;
            }
            src.head = src.head->next;
        }
        src.head = StartHeadB;

        if (SearchSuccesesful == count) return true;
        else return false;

    }
    void operator -(Equalization& src)
    {
        list* FunctionHead = GetHead();
        list* StartHeadB = src.head;
        bool SearchSuccesesful;
        while (src.head) {
            SearchSuccesesful = false;
            while (FunctionHead) {
                if (FunctionHead->degree == src.head->degree)
                {
                    SearchSuccesesful = true;
                    FunctionHead->coefficent -= src.head->coefficent;

                    break;
                }
                FunctionHead = FunctionHead->next;
            }
            if (!SearchSuccesesful)
            {
                Set(src.head->coefficent * (-1), src.head->degree);
            }
            src.head = src.head->next;
        }
        src.head = StartHeadB;
    }
    void operator +(Equalization& src)
    {
        list* FunctionHead = GetHead();
        list* StartHeadB = src.head;
        bool SearchSuccesesful;
        while (src.head) {
            SearchSuccesesful = false;
            while (FunctionHead) {
                if (FunctionHead->degree == src.head->degree)
                {
                    SearchSuccesesful = true;
                    FunctionHead->coefficent += src.head->coefficent;
                    if (FunctionHead->coefficent == 0) count--;
                }
                FunctionHead = FunctionHead->next;
            }
            if (!SearchSuccesesful)
            {
                Set(src.head->coefficent,src.head->degree );
            }
            src.head = src.head->next;
        }
        src.head = StartHeadB;
    }
    int operator[](double degree)
    {
        list* FunctionHead = GetHead();
        while (FunctionHead) {
            if (FunctionHead->degree == degree)
            {
                double coefficent;
                cout << "Введите новый коэффицент степени " << FunctionHead->degree << ": ";
                cin >> coefficent;
                if (coefficent != 0) {
                    FunctionHead->coefficent=coefficent;
                }
                else { cout << "Нельзя поменять на ноль"; }
                return 0;
            }
            FunctionHead = FunctionHead->next;
        }
        cout << "Нет такой степени :( \n";
        return 0;
    }
    friend ostream& operator<<(ostream& os, Equalization obj);
};
ostream& operator<<(ostream& os,Equalization obj)
{
    bool FirstStart = true;
    cout << "\nНаша последовательность: ";
    while (obj.head) {
        if (obj.head->coefficent == 0)
        {
            obj.DeleteElement(obj.head->degree);
            FirstStart = true;
        }
        if (!FirstStart && obj.head->coefficent > 0) cout << "+";
        if (obj.head->coefficent != 1) cout << obj.head->coefficent;
        if (obj.head->degree != 0) cout << "x";
        else cout << obj.head->coefficent;
        if (obj.head->degree < 0) { cout << "^(" << obj.head->degree << ")"; }
        else if (obj.head->degree != 1 && obj.head->degree != 0) cout << "^" << obj.head->degree;
       
        obj.head = obj.head->next;
        FirstStart = false;
    }
    cout << "\n";
    return os;
}
class EClassException
{
protected:
    char _err[256];
public:
    EClassException(const char* err) {
        strncpy_s(_err, err, 255);
        _err[255] = 0;
    }
    void Print()
    {
        std::cout << _err << std::endl;
    }
};


int main() {
    try
    {
        double coefficent, degree;
        int vibor;
        setlocale(LC_ALL, "RUS");
        cout << "Многочлен пока не создан, введите коэффицент первого элемента: " << endl;
        cin >> coefficent;
        cout << "Введите его степень: " << endl;
        cin >> degree;
        Equalization A(coefficent, degree);
        bool flag = true;
        while (flag) {
            A.DeleteElement(0);
            cout << A;
            cout << "Выберите действие:\n1)Добавить новый элемент\n2)Умножить на скаляр\n3)Вычислить х\n4)Найти производную\n5)Сумма с другим многочленом\n6)Вычесть из него другой многочлен\n7)Средактировать коэффицент\n8)Удалить элемент\n9)Сравнить многочлены\n10)Выход\n";
            cin >> vibor;
            if (vibor == 1)
            {
                cout << "Введите коэффицент нового элемента: " << endl;
                cin >> coefficent;
                cout << "Введите его степень: " << endl;
                cin >> degree;
                A.Set(coefficent, degree);
            }
            else if (vibor == 2) {
                cout << "Введите значение на которое хотите умножить: " << endl;
                cin >> degree;
                A.Multiplication(degree);
            }
            else if (vibor == 3) {
                cout << "Введите значение х: " << endl;
                cin >> degree;
                A.Calculation(degree);
            }
            else if (vibor == 4) {
                A.Derivative();
            }
            else if (vibor == 5 || vibor == 6) {
                bool SumOperation = false;
                if (vibor == 5) SumOperation = true;
                Equalization B(0, 0);
                do {
                    cout << "Выберите коэффицент элемента нового многочлена: ";
                    cin >> coefficent;
                    cout << "Выберите степень элемента нового многочлена: ";
                    cin >> degree;
                    B.Set(coefficent, degree);
                    cout << "Добавить еще один элемент к многочлену? \n1)Да\n2)Нет";
                    cin >> vibor;
                } while (vibor == 1);
                if (SumOperation) A + B;
                else A - B;
            }
            else if (vibor == 7) {
                cout << "Выберите степень элемента который редактируем: ";
                cin >> degree;
                A[degree];
            }
            else if (vibor == 8) {
                cout << "Выберите степень элемента который удаляем: ";
                cin >> degree;
                if (A.DeleteElement(degree) == 0) cout << "Нет такого элемента :("<<endl;
            }
            else if (vibor == 9)
            {
               
                cout << "Какую точность  желаете выбрать? напшите в формате " << 0.001 << "\n";
                cin>>A.epsilon;

                Equalization B(0, 0);
                do {
                   
                    cout << "Выберите коэффицент элемента нового многочлена: ";
                    cin >> coefficent;
                    cout << "Выберите степень элемента нового многочлена: ";
                    cin >> degree;
                    B.Set(coefficent, degree);
                    cout << "Добавить еще один элемент к многочлену? \n1)Да\n2)Нет";
                    cin >> vibor;
                } while (vibor == 1);
                cout << B;
                if (A == B)cout << "Многочлены равны\n";
                else cout << "Многочлены НЕ равны\n";
            }
            else if (vibor == 10) {
                flag = false;
            }
            else {
                system("CLS");
            }

        }
    }
    catch (EClassException& err)
    {
        err.Print();
    }
}

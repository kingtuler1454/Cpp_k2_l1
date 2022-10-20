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
    struct list {
        double degree;
        double coefficent;
        list* next;
    } *head;
    
    Equalization(double coefficent, double degree) {
        if (coefficent != 0) {
            this->head = new list;
            this->head->degree = degree;
            this->head->coefficent = coefficent;
            this->head->next = NULL; // это последний узел списка
        }
    }
    ~Equalization() {
        list* p;
        while (p = head)
        {
            head = p->next;
            delete p;
        }
    }
    list* GetHead() { return head; }

    bool DetectOldDegree(double coefficent, double degree) {
        list* FunctionHead = GetHead();
        while (FunctionHead) {
            if (FunctionHead->degree == degree) {
                FunctionHead->coefficent = coefficent;
                std::cout << "\nСтепени " << FunctionHead->degree << " изменён  коэффицент на " << FunctionHead->coefficent << endl;
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
            }
        }

    }
    int DeleteElement(double degree)
    {
        list* FunctionHead = GetHead();
        while (FunctionHead)
        {
            if (FunctionHead->degree == degree) // если голова
            {
                list* deleted = FunctionHead;
                if (FunctionHead->next)FunctionHead = FunctionHead->next; // если не последний элемент
                delete deleted;
                return 1;
            }
            else if (FunctionHead->next )// если не голова
            {
                if ((FunctionHead->next)->degree == degree) {
                    list* pred = FunctionHead;
                    FunctionHead = FunctionHead->next;
                    pred->next = FunctionHead->next;
                    delete FunctionHead;

                    return 1;
                }
            }
            FunctionHead = FunctionHead->next;
        }
        return 0;
    }
    
    void Derivative() {
        list* FunctionHead = GetHead();
        while (FunctionHead) {
            FunctionHead->coefficent *= FunctionHead->degree;
            FunctionHead->degree--;
            cout << FunctionHead->coefficent << "x^" << FunctionHead->degree;
            FunctionHead = FunctionHead->next;
        }
        cout << "\nПроизводная высчитана...\n";
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
                list* pointer;
                pointer = new list;
                pointer->coefficent = src.head->coefficent * (-1);
                pointer->degree = src.head->degree;
                pointer->next = GetHead();
                head = pointer;
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
                    
                    break;
                }
                FunctionHead = FunctionHead->next;
            }
            if (!SearchSuccesesful)
            {
                list* pointer;
                pointer = new list;
                pointer->coefficent = src.head->coefficent;//+++++++++

                pointer->degree = src.head->degree;
                pointer->next = GetHead();
                head = pointer;
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
class PolynominalError : public exception
{
protected:
    const char* Message;

    PolynominalError() { cout << "Error exception! " << endl; }

    void SetMessage(const char* Message)
    {
        if (Message != nullptr && strcmp(Message, "") != 0)
            this->Message = Message;
    }
    void PrintInfo() const
    {
        cout << Message << endl;
    }
};


int main() {
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
        cout<<A;
        cout << "Выберите действие:\n1)Добавить новый элемент\n2)Умножить на скаляр\n3)Вычислить х\n4)Найти производную\n5)Сумма с другим многочленом\n6)Вычесть из него другой многочлен\n7)Средактировать коэффицент\n8)Удалить элемент\n9)Выход\n";
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
            A.DeleteElement(degree);
        }
        else if (vibor == 9) {
            flag = false;
        }
        else {
            system("CLS");
        }
       
    }

}


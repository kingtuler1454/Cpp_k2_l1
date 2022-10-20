#include <stdio.h>
#include <iostream>
#include <cmath>
using namespace std;
/* ����������� � �����������: ��������� ������� ����������;
� �������� [] ��� ������ ������������ ��� �������� ������� (���������� ���������� ��������� ��� ����� ��������������� �������);
 ����� set ��� ��������� ������������ ��� �������� ������� (���������� ���������� ��������� � ������ �������� �������� ������������ � ��� ����� ��������������� �������);
� ��������� �������� � ��������� �����������;
 ��������� ��������� ���������� �� ������ (���������� ���������������);
���������� �������� ���������� ��� ��������� �������� �.
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
            this->head->next = NULL; // ��� ��������� ���� ������
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
                std::cout << "\n������� " << FunctionHead->degree << " ������  ���������� �� " << FunctionHead->coefficent << endl;
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
            if (FunctionHead->degree == degree) // ���� ������
            {
                list* deleted = FunctionHead;
                if (FunctionHead->next)FunctionHead = FunctionHead->next; // ���� �� ��������� �������
                delete deleted;
                return 1;
            }
            else if (FunctionHead->next )// ���� �� ������
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
        cout << "\n����������� ���������...\n";
    }
    void Multiplication(double value) {
        list* FunctionHead = GetHead();
        while (FunctionHead) {
            FunctionHead->coefficent = FunctionHead->coefficent * value;
            FunctionHead = FunctionHead->next;
        }
        cout << "\n��������� ������������ ���������...\n";
    }
    void Calculation(double x) {
        list* FunctionHead = GetHead();
        double sum = 0;
        while (FunctionHead) {
            sum += FunctionHead->coefficent * pow(x, FunctionHead->degree);
            FunctionHead = FunctionHead->next;
        }
        cout << "��� x=" << x << " �������� ������������������ ����� " << sum << endl;
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
                cout << "������� ����� ���������� ������� " << FunctionHead->degree << ": ";
                cin >> coefficent;
                if (coefficent != 0) {
                    FunctionHead->coefficent=coefficent;
                }
                else { cout << "������ �������� �� ����"; }
                return 0;
            }
            FunctionHead = FunctionHead->next;
        }
        cout << "��� ����� ������� :( \n";
        return 0;
    }
    friend ostream& operator<<(ostream& os, Equalization obj);
};
ostream& operator<<(ostream& os,Equalization obj)
{
    bool FirstStart = true;
    cout << "\n���� ������������������: ";
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
    cout << "��������� ���� �� ������, ������� ���������� ������� ��������: " << endl;
    cin >> coefficent;
    cout << "������� ��� �������: " << endl;
    cin >> degree;
    Equalization A(coefficent, degree);

    bool flag = true;
    while (flag) {
        A.DeleteElement(0);
        cout<<A;
        cout << "�������� ��������:\n1)�������� ����� �������\n2)�������� �� ������\n3)��������� �\n4)����� �����������\n5)����� � ������ �����������\n6)������� �� ���� ������ ���������\n7)�������������� ����������\n8)������� �������\n9)�����\n";
        cin >> vibor;
        if (vibor == 1)
        {
            cout << "������� ���������� ������ ��������: " << endl;
            cin >> coefficent;
            cout << "������� ��� �������: " << endl;
            cin >> degree;
            A.Set(coefficent, degree);
        }
        else if (vibor == 2) {
            cout << "������� �������� �� ������� ������ ��������: " << endl;
            cin >> degree;
            A.Multiplication(degree);
        }
        else if (vibor == 3) {
            cout << "������� �������� �: " << endl;
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
                cout << "�������� ���������� �������� ������ ����������: ";
                cin >> coefficent;
                cout << "�������� ������� �������� ������ ����������: ";
                cin >> degree;
                B.Set(coefficent, degree);
                cout << "�������� ��� ���� ������� � ����������? \n1)��\n2)���";
                cin >> vibor;
            } while (vibor == 1);
            if (SumOperation) A + B;
            else A - B;
        }
        else if (vibor == 7) {
            cout << "�������� ������� �������� ������� �����������: ";
            cin >> degree;
            A[degree];
        }
        else if (vibor == 8) {
            cout << "�������� ������� �������� ������� �������: ";
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


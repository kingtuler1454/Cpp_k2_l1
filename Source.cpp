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
    int count = 0;
    struct list {
        double degree;
        double coefficent;
        list* next;
    } *head;
public:
    Equalization(double coefficent, double degree) {
        if (coefficent != 0) {
            this->head = (struct list*)malloc(sizeof(struct list));
            this->head->degree = degree;
            this->head->coefficent = coefficent;
            this->count= 1;
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
        int index;
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
                pointer = (list*)malloc(sizeof(list));
                pointer->coefficent = coefficent;
                pointer->degree = degree;
                pointer->next = this->head;
                this->head = pointer;
            }
        }
        this->count++;
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
                this->count--;
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
    void Print() {
        list* FunctionHead = GetHead();
        bool FirstStart = true;
        cout << "\n���� ������������������: "; 
            while (FunctionHead) {
                if (FunctionHead->coefficent == 0)
                {
                    DeleteElement(FunctionHead->degree);
                    FirstStart = true;
                }
                if (!FirstStart && FunctionHead->coefficent > 0) cout << "+";
                if (FunctionHead->coefficent != 1) cout << FunctionHead->coefficent;
                if (FunctionHead->degree != 0) cout << "x";
                else cout << FunctionHead->coefficent;
                if (FunctionHead->degree < 0) { cout << "^(" << FunctionHead->degree << ")"; }
                else if (FunctionHead->degree != 1 && FunctionHead->degree != 0) cout << "^" << FunctionHead->degree;
                FunctionHead = FunctionHead->next;
                FirstStart = false;

            }
        cout << "\n";
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
    void Sum(Equalization& src, bool SumOperation)
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
                    if (SumOperation) FunctionHead->coefficent += src.head->coefficent;
                    else FunctionHead->coefficent -= src.head->coefficent;
                    break;
                }
                FunctionHead = FunctionHead->next;
            }
            if (!SearchSuccesesful)
            {
                list* pointer;
                pointer = (list*)malloc(sizeof(list));
                if (SumOperation)
                    pointer->coefficent = src.head->coefficent;//+++++++++
                else  pointer->coefficent = src.head->coefficent * (-1);
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
                    FunctionHead->coefficent;
                }
                else { cout << "������ �������� �� ����"; }
                return 0;
            }
            FunctionHead = FunctionHead->next;
        }
        cout << "��� ����� ������� :( \n";
        return 0;
    }
};
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

class MemoryError : PolynominalError
{
public:
    MemoryError(const char* Message)
    {
        SetMessage(Message);
        PrintInfo();
    }
};

class RangeError : PolynominalError
{
public:
    RangeError(const char* Message)
    {
        SetMessage(Message);
        PrintInfo();
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
        A.Print();
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
            A.Sum(B, SumOperation);
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


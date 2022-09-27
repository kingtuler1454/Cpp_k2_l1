class Polynomial{
    struct Node {
	int coefficent;
    int degree;
	struct Node *next;
    };
    Polynomial( int start_degree){
    Node *head = NULL;
    Node *tmp=(Node*)malloc(sizeof(Node)); # создаем узел
    tmp->coefficent=1;
    tmp->degree=start_degree;
    tmp->next=(*head)
    (*head)=tmp;
    }
    int operator [](int & x){
        printf('%d', x.coefficent);    
    }
};
int main(){

    Polynomial A(5);
    A[5];
}

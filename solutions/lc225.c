/**
 * lc 225, easy, implement-stack-using-queues
*/


typedef struct {
    int d[101]; // capacity 100
    int cap;
    int front;
    int rear;
} Q;

Q* qNew() {
    Q *q = malloc(sizeof(Q));
    q->cap = 101;
    q->front = q->rear = 0;
    return q;
}

void qPush(Q *q, int n) {
    q->d[q->rear] = n;
    q->rear = (q->rear + 1) % q->cap;
}

int qOffer(Q *q) {
    int front = q->d[q->front];
    q->front = (q->front + 1) % q->cap;
    return front;
}

int qSize(Q *q) {
    return (q->rear - q->front + q->cap) % q->cap;
}

bool qIsEmpty(Q *q) {
    return q->front == q->rear;
}

typedef struct {
    Q *q1;
    Q *q2;
} MyStack;

MyStack* myStackCreate() {
    MyStack *stk = malloc(sizeof(MyStack));
    stk->q1 = qNew();
    stk->q2 = qNew();
    return stk;
}

void myStackPush(MyStack* obj, int x) {
    // push into q2, move all elements in q1 to q2
    qPush(obj->q2, x);
    while (!qIsEmpty(obj->q1)) {
        qPush(obj->q2, qOffer(obj->q1));
    }
    // swap q1, q2
    Q *tmp = obj->q1;
    obj->q1 = obj->q2;
    obj->q2 = tmp;
}

int myStackPop(MyStack* obj) {
    return qOffer(obj->q1);
}

int myStackTop(MyStack* obj) {
    return obj->q1->d[obj->q1->front];
}

bool myStackEmpty(MyStack* obj) {
    return qIsEmpty(obj->q1);
}

void myStackFree(MyStack* obj) {
    free(obj->q1);
    free(obj->q2);
    free(obj);
}

/**
 * Your MyStack struct will be instantiated and called as such:
 * MyStack* obj = myStackCreate();
 * myStackPush(obj, x);
 
 * int param_2 = myStackPop(obj);
 
 * int param_3 = myStackTop(obj);
 
 * bool param_4 = myStackEmpty(obj);
 
 * myStackFree(obj);
*/
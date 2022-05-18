#include<stdio.h>
#include<stdlib.h>

#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1

typedef int Status;
typedef int ElemType;

//使用数组实现,为防止 由于进出队列，front增大，导致前面的空间无法使用，造成内存泄露，所以采用循环列表
#define MAXSIZE 10
typedef struct{
    ElemType *base;     
    int front;
    int rear;
} cycleQueue;

Status InitQueue(cycleQueue *q){    //初始化队列
    q->base = (ElemType *)malloc(MAXSIZE * sizeof(ElemType));
    if(q->base == NULL){
        exit(0);
    }
    q->front = q->rear = 0;
    return OK;
}

Status QueueEmpty(cycleQueue q){    //判断队列是否为空
    if(q.front == q.rear){
        return TRUE;
    }
    return FALSE;
}

#define SATCKINCREMENT 5
Status QueueEnter(cycleQueue *q, ElemType e){       //元素进队
    if((q->rear + 1)%MAXSIZE == q->front){  //判断队列是否已满, 所以队列已满时，元素 q-> rear 指向的下标不存元素
        return ERROR;                   // 队列中最少存在一个空位置
    }
    q->base[q->rear] = e;
    q->rear = (q->rear + 1) % MAXSIZE;  //循环，若 q->rear + 1 等于 MAXSIZE，即将 q->rear = 1
    printf(" %d ", e);
    return OK;
}

Status QueueDelete(cycleQueue *q, ElemType *e){     //元素出队
    if(QueueEmpty(*q)){     //判断队列是否已空
        return ERROR;
    }
    *e = q->base[q->front];
    q->front = (q->front + 1) % MAXSIZE;    //循环， 若 q->front + 1 等于 MAXSIZE,即将 q->front = 1
    return OK;
}

Status ClearQueue(cycleQueue *q){   //队列清空
    q->rear = q->front;
    return OK;
}

Status DestroyQueue(cycleQueue *q){ //队列销毁
    if(!QueueEmpty(*q)){
        ClearQueue(q);
    }
    free(q->base);
    return OK;
}

int main(void){     //队列测试
    cycleQueue q;
    ElemType e;
    
    printf("\n\n队列初始化......");
    InitQueue(&q);

    printf("\n\n 此时 q->front = %d", q.front);
    printf("\n\n 此时 q->rear = %d", q.rear);

    printf("\n\n元素进队: ");
    for(int i=1; i <= MAXSIZE; i++){
        QueueEnter(&q, i);
       
    }

    printf("\n\n元素出队: ");
    while (!QueueEmpty(q))
    {
        QueueDelete(&q, &e);
        printf(" %d ", e);
    }
    printf("\n\n 此时 q->front = %d", q.front);
    printf("\n\n 此时 q->rear = %d", q.rear);

    printf("\n\n元素进队: ");
    for(int i=1; i <= 5; i++){
        QueueEnter(&q, i);
    }

/*     printf("\n\n 清除队列......");
    ClearQueue(&q); */

    printf("\n\n元素出队: ");
    while (!QueueEmpty(q))
    {
        QueueDelete(&q, &e);
        printf(" %d ", e);
    }
    if(QueueEmpty(q)){
        printf(" 队列为空");
    }

    printf("\n\n 此时 q->front = %d", q.front);
    printf("\n\n 此时 q->rear = %d", q.rear);

    

    return 0;
}
#include<stdio.h>
#include<stdlib.h>

#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1

typedef int Status;
typedef int ElemType;


//队列：属于 FIFO(先进先出),所以链表使用 尾插法
//使用单链表创建队列

typedef struct QNode{       //节点创建
    ElemType Data;
    struct QNode *next;
} QNode, *QueuePtr;

//本次队列使用含有头节点的单链表
typedef struct {        //队列创建
    QueuePtr front, rear;       //front指向头节点，rear初始化指向头节点
    int size;
} LinkQueue;

Status InitQueue(LinkQueue *q){     //队列初始化
    q->front = q->rear = (QueuePtr)malloc(sizeof(QNode));   //申请一个节点，作为头节点
    if(!q->front){
        exit(0);
    }
    q->front->next = NULL;
    q->size = 0;
    return OK;
}

Status QueueEmpty(LinkQueue q){     //判断队列是否为空
    if(q.front == q.rear){      
        return TRUE;
    }
    return FALSE;
}

int QueueLength(LinkQueue q){       //返回队列的长度
    return q.size;
}

Status QueueEnter(LinkQueue *q, ElemType e){    //元素进入队列（尾插法）  FIFO
    QueuePtr temp;
    temp = (QueuePtr)malloc(sizeof(QNode));
    if(!temp){
        exit(0);
    }
    temp->Data = e;

    temp->next = q->rear->next;
    q->rear->next = temp;
    q->rear = temp;
    q->size++;
    return OK;
}

Status QueueDelete(LinkQueue *q, ElemType *e){  //元素出队 FIFO
    if(!QueueEmpty(*q)){ 
        QueuePtr temp;
        temp = q->front->next;
        *e = temp->Data;
        q->front->next = q->front->next->next;  //q->front->next指向第二个节点
        free(temp);     //释放第一个节点的空间
        q->size--;
        if(q->size == 0){
            q->rear = q->front;
        }
        return OK;
    }
    return ERROR;
}

Status ClearQueue(LinkQueue *q){
    QueuePtr temp;
    while (!QueueEmpty(*q))
    {
        temp = q->front->next;
        q->front->next = q->front->next->next;
        free(temp);
        q->size--;
        if(q->size == 0){   //长度为0时，将 q-rear 与 q->front 指向头节点
            q->rear = q->front;
        }
    }
    q->rear = q->front;
    return OK;
}

Status DestroyQueue(LinkQueue *q){
    ClearQueue(q);
    q->front = q->rear = NULL;      //当队列为空时，将 q->front 与 q->rear 指向 NULL
    return OK;
}


int main(void){     //队列测试
    LinkQueue q;
    ElemType e;

    printf("\n\n队列初始化......");
    InitQueue(&q);
    printf("\n\n队列长度: %d", q.size);

    printf("\n\n元素进入队列:");
    for(int i=1; i <= 10; i++){
        QueueEnter(&q, i);
        printf(" %d ", i);
    }
    printf("\n\n队列长度: %d", q.size);

    /* printf("\n\n清除队列......");
    ClearQueue(&q);

    printf("\n\n销毁队列......");
    DestroyQueue(&q); */

    printf("\n\n元素出队: ");
    if(QueueEmpty(q) && q.front != NULL){
        printf("队列已空");
    }else if(q.front == NULL)
    {
       printf("队列已被销毁");
    }
    
    while (!QueueEmpty(q))
    {
        QueueDelete(&q, &e);
        printf(" %d ", e);
    }
    printf("\n\n队列长度: %d", q.size);

    return 0;
}
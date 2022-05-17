#include<stdio.h>
#include<stdlib.h>

#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1

typedef int Status;
typedef int ElemType;

//使用链表的栈，使用单链表的头插法即可

typedef struct StackNode{   //节点创建
    ElemType data;
    struct StackNode *next;
} StackNode, *LinkStackPtr;

typedef struct{     //栈的创建
    LinkStackPtr top;   //top指针
    int count;      //栈元素计数器
} LinkStack;

//无头节点的单链表
Status InitStack(LinkStack *s){     //栈的初始化
    s->top = NULL;
    s->count = 0;   
    return OK;
}

Status StackEmpty(LinkStack s){     //判断链表是否为空
    if(s.top == NULL){
        return TRUE;
    }
    return FALSE;
}

Status Push(LinkStack *s, ElemType e){  //进栈：使用单链表的头插法
    LinkStackPtr temp;
    temp = (LinkStackPtr)malloc(sizeof(StackNode));
    if(temp == NULL){
        exit(0);
    }
    temp->data = e;
    
    temp->next = s->top;
    s->top = temp;
    s->count++;
    return OK;
}

Status Pop(LinkStack *s, ElemType *e){      //退栈
    if(!StackEmpty(*s)){
        *e = s->top->data;
        s->top = s->top->next;
        s->count--;
        return OK;
    }
    return ERROR;
}

Status ClearStack(LinkStack *s){    //清空栈
    LinkStackPtr temp;
    while(s->top != NULL){
        temp = s->top;
        s->top = s->top->next;
        s->count--;
        free(temp);
    }
    s->top == NULL;
    return OK;
}

int main(void){     //栈的测试
    LinkStack s;
    ElemType e;

    InitStack(&s);
    printf("\n\n栈的初始化......");

    printf("\n\n栈的长度: %d", s.count);

    printf("\n\n元素入栈:");
    for(int i=1; i <= 20; i++){
        Push(&s, i);
        printf(" %d ", i);
    }

    printf("\n\n栈的长度: %d", s.count);

    printf("\n\n清空栈......");
    ClearStack(&s);

    printf("\n\n元素出栈:");
    if(StackEmpty(s)){
        printf(" 链表为空");
    }
    while (!StackEmpty(s))  //链表为空后，退出循环
    {
        Pop(&s, &e);
        printf(" %d ", e);
    }
    
    printf("\n\n栈的长度: %d", s.count);

    return 0;
}
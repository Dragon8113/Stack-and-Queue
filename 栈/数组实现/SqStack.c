#include<stdio.h>
#include<stdlib.h>

#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1
#define STACK_INIT_SIZE 10

typedef int Status;
typedef int ElemType;

typedef struct {
    ElemType *base; //使用指针，配合malloc申请空间，另外一种可以使用数组，
    ElemType *top;  //如果是使用数组的的话，base、top开始指向 下标-1，push后，pop++即可；
    int stackSize;
} sqStack;

Status InitStack(sqStack *s){
    s->base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
    if(!s->base){
        exit(0);
    }
    s->top = s->base;
    s->stackSize = STACK_INIT_SIZE;
    return OK;
}

Status StackEmpty(sqStack s){       //栈是否为空
    if(s.base == s.top){    //栈顶指针等于栈底指针，则栈为空
        return TRUE;
    }
    return FALSE;
}

int StackLength(sqStack s){     //返回栈已填充的长度
    return s.top - s.base;
}

#define SATCKINCREMENT 5
Status Push (sqStack *s, ElemType e){
    if(StackLength(*s) >= s->stackSize){
            s->base = (ElemType *)realloc(s->base, (s->stackSize + SATCKINCREMENT) * sizeof(ElemType));
            if(s->base == NULL){
                exit(0);
            }
            s->top = s->base + s->stackSize;
            s->stackSize += SATCKINCREMENT;
    }
    *s->top = e;
    s->top++;
    return OK;
}

Status Pop (sqStack *s, ElemType *e){
    if(StackEmpty(*s)){
        return ERROR;
    }
    *e = *--(s->top);
    return OK;
}

Status ClearStack(sqStack *s){  //栈的清空
    s->top = s->base;
    return OK;
}

Status DestroyStack(sqStack *s){    ///栈的销毁
    int len;
    free(s->base);  //只需要知道申请空间的首地址，即可释放空间
    s->base = s->top = NULL;
    s->stackSize = 0;
    return OK;
}

int main(void){     //栈的测试
    sqStack s;
    ElemType e;
    int len;
    InitStack(&s);  //初始化
    printf("\n\n元素入栈: ");
    for(int i=1; i <= 12; i++){
        printf(" %d ", i);
        Push(&s, i);
    }
    
   
    printf("\n\n栈已存储的长度: %d", StackLength(s));

    printf("\n\n栈的长度:  %d ", s.stackSize);

    printf("\n\n清空栈...... ");
    ClearStack(&s);
    printf("\n\n栈已储存的长度: %d", StackLength(s));

/*     printf("\n\n销毁栈 ");
    DestroyStack(&s);  */
    
    printf("\n\n元素出栈: ");
    if(StackEmpty(s)){
        printf(" 栈已为空");
    }
    while(!StackEmpty(s)){
        Pop(&s, &e);
        printf(" %d ", e);
    }
    

    printf("\n\n栈已储存的长度: %d", StackLength(s));


    printf("\n\n");
    return 0;
}
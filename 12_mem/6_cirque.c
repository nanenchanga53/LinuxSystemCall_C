#include <stdio.h>
#define MAX 5
// 작업 front 변수 초기값 설정-----
int front = 0;
// 작업 rear 변수 초기값 설정-----
int rear = 0;

int queue[MAX];
 
int IsEmpty(void)
{
// 작업 빈 큐인지 검사 시작 -----
    if(front == rear)
        return 1;
    else
        return 0;
// 작업 빈 큐인지 검사 종료 -----
}

int IsFull(void)
{
// 작업 꽉찬 큐인지 검사 시작 -----
    int tmp=(rear+1)%MAX;
    if(tmp==front)
        return 1;
    else
        return 0;
// 작업 꽉찬 큐인지 검사 종료 -----
}


int printque()
{
    for(int i=0;i<MAX;i++)
    {
        printf("%-6d", queue[i]);
    }
    printf("\n");
}

void addq(int value)
{
    if(IsFull() == 1)
        printf("Queue is Full.\n");
    else
    {
// 작업 큐 등록 시작 -----
        queue[rear] = value;
        rear = (rear+1)%MAX;
// 작업 큐 등록 종료 -----
    }
    printque();
}

int subq(){
	int rtn = 0;
    if(IsEmpty() == 1)
        printf("Queue is Empty.\n");
    else
    {
// 작업 큐 추출 시작 -----
        rtn = queue[front];
        queue[front] = 999;
        front = (front+1)%MAX;
// 작업 큐 추출 종료 -----
    }
    return rtn;
}
 
int main()
{
    addq(1);
    addq(2);
    addq(3);
    addq(4);

    printf("%d\n",subq());
    printf("%d\n",subq());
    printf("%d\n",subq());
    printf("%d\n",subq());

    addq(5);
    addq(6);
    addq(7);

    printf("%d\n",subq());
    printf("%d\n",subq());
    
    return 0;
}


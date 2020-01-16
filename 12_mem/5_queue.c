#include <stdio.h>

typedef struct _dnode{
    int key;
    struct _dnode *prev;
    struct _dnode *next;
}dnode;

dnode *head, *tail;

void init(void)
{
    head = (dnode*)malloc(sizeof(dnode));
    tail = (dnode*)malloc(sizeof(dnode));
    head->prev = head;
    head->next = tail;
    tail->prev = head;
    tail->next = tail;
}

void clear_queue(void)
{
    dnode *t;
    dnode *s;
    t = head->next;
    while (t != tail)
    {
        s = t;
        t = t->next;
        free(s);
    }
    head->next = tail;
    tail->prev = head;
}

int putque(int k)
{
    dnode *t;
    if ((t = (dnode*)malloc(sizeof(dnode))) == NULL){
        printf("\n  Out of memory.");
        return -1;
    }
    t->key = k;
    tail->prev->next = t;
    t->prev = tail->prev;
    tail->prev = t;
    t->next = tail;
    return k;
}

int getque(void)
{
    dnode *t;
    int i;
    t = head->next;
    if (t == tail){
        printf("\n  Queue underflow");
        return -1;
    }
    i = t->key;
    head->next = t->next;
    t->next->prev = head;
    free(t);
    return i;
}

void print_queue(void)
{
    dnode *t;
    t = head->next;
    printf("\n ");
    while (t != tail){
        printf("%-6d", t->key);
        t = t->next;
    }
}

void main(void)
{

    int i;
    init();

    for (i = 1; i <= 5; i++)//1~5까지 큐에 보관
    {
        putque(i);
    }
    printf("\n  Queue contents : Front -----------> Rear \n");
    print_queue();
    i = getque();
    print_queue();
    i = getque();
    print_queue();
    i = getque();
    print_queue();
    i = getque();
    print_queue();

    printf("\nInitialize queue");
    clear_queue();

    return 0;
}

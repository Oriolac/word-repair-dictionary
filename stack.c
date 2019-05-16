#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "corrector.h"

struct stack create_a_stack()
{
    struct stack s;
    s.top = -1;
    return s;
}



int is_empty(struct stack s)
{
    if(s.top == -1)
    {
        return 1;
    }
    return 0;
}

int is_full(struct stack s)
{
    if(s.top == MAX_WORDS)
    {
        return 1;
    }
    return 0;
}

struct element_of_stack top(struct stack s)
{
    struct element_of_stack elem;
    if(!is_empty(s))
    {
        return s.elem[s.top];
    }
    memset(&elem, 0, sizeof(elem));
    return elem;
}

struct element_of_stack pop(struct stack *s)
{
    struct element_of_stack elem;
    if(!is_empty(*s))
    {
        elem = s->elem[s->top];
        s->top = s->top - 1;
        return elem;
    } else {
        memset(&elem, 0, sizeof(elem));
        return elem;
    }
}

int push(struct stack *s, struct element_of_stack elem)
{
    if(!is_full(*s))
    {
        s->top++;
        s->elem[s->top] = elem;
        return 1;
    } else {
        return 0;
    }
}
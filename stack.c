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

char* top(struct stack s)
{
    char *str;
    str = (char *) malloc(WORD_MAX_LENGTH);
    strcpy(str, s.stack[s.top]);
    return str;
}

char* pop(struct stack *s)
{
    char *str;
    if(!is_empty(*s))
    {
        str = (char *) malloc(WORD_MAX_LENGTH);
        strcpy(str,s->stack[s->top]);
        s->top = s->top - 1;
        return str;
    } else {
        return "";
    }
}

int push(struct stack *s, char word[WORD_MAX_LENGTH])
{
    if(!is_full(*s))
    {
        s->top++;
        strcpy(s->stack[s->top], word);
        return 1;
    } else {
        return 0;
    }
}
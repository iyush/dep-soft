
/*
 * Code Contributions made by:
 * Aayush Sharma Acharya
 * Drishti Maharjan
*/

#include <stdio.h>
#include <stdlib.h>

#include "rpn-stack.h"


rpn_stack_t*
rpn_stack_new()
{
    rpn_stack_t* ptr;
    ptr = (rpn_stack_t *) malloc(sizeof(rpn_stack_t));
    if (ptr == NULL) abort();
    ptr->top = NULL;
    return ptr;
}


void
rpn_stack_push(rpn_stack_t *s, void *data)
{
    rpn_stack_node_t* node;
    node = (rpn_stack_node_t *) malloc(sizeof(rpn_stack_node_t));
    if (node == NULL) abort();
    node->data = data;
    node->next = s->top;
    s->top = node;
    return;
}


void*
rpn_stack_pop(rpn_stack_t *s)
{
    if (rpn_stack_empty(s)) return NULL;
    void * data = s->top->data;
    s->top = s->top->next;
    return data;
}


void*
rpn_stack_peek(rpn_stack_t *s)
{
    return s->top->data;
}


int
rpn_stack_empty(rpn_stack_t *s)
{
    return (s->top == NULL) ? 1: 0;
}

void
rpn_stack_del(rpn_stack_t *s)
{
    free(s);
    s = NULL;
    return;
}

/*
 * rpn-stack.h --
 */

/** @file */

#ifndef _RPN_STACK_H
#define _RPN_STACK_H

/*
 * Prefixing all global symbols with rpn_ to avoid clashes with
 * symbols defined in the C library (e.g., signal stack definitions)
 * since we use this stack for building an RPN calculator.
 */


typedef struct _rpn_stack_node
{
    void* data;
    struct _rpn_stack_node * next;    
}
rpn_stack_node_t;

typedef struct _rpn_stack
{
    struct _rpn_stack_node* top;
}
rpn_stack_t;

/**
 * \brief Create a new empty stack.
 *
 * \return A pointer acting as a handle for the new stack.
 */

rpn_stack_t*
rpn_stack_new();

/**
 * \brief Push data (allocated by the caller) on the stack.
 *
 * \param s The stack to push data on.
 * \param data The pointer to data to be pushed on the stack.
 */

void
rpn_stack_push(rpn_stack_t *s, void *data);

/**
 * \brief Pop data from the top of the stack.
 *
 * \param s The stack to pop data from.
 * \return The data or NULL if the stack is empty.
 */

void*
rpn_stack_pop(rpn_stack_t *s);

/**
 * \brief Peek on the data at the top of the stack.
 *
 * \param s The stack to peek on.
 * \return The data or NULL if the stack is empty.
 */

void*
rpn_stack_peek(rpn_stack_t *s);

/**
 * \brief Test whether a stack is empty.
 *
 * \param s The stack to test.
 * \return A non-zero value if the stack is empty, 0 otherwise.
 */

int
rpn_stack_empty(rpn_stack_t *s);

/**
 * \brief Delete a stack.
 *
 * \param s The stack to delete.
 */

void
rpn_stack_del(rpn_stack_t *s);

#endif
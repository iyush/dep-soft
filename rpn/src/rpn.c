
/*
 * Code Contributions made by:
 * Aayush Sharma Acharya
 * Drishti Maharjan
*/


#include "rpn.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "rpn.h"
#include "rpn-stack.h"

#define PLUS 0
#define MINUS 1
#define MULTIPLY 2
#define DIVISION 3
#define NO_OP -1
#define DIGIT 1
#define NO_DIG -1

int no_of_tokens = 0;

int digit_check(char *a_token)
{
    int size_token = strlen(a_token);

    for (int i = 0; i < size_token; i++)
    {
        if (a_token[i] >= '0' && a_token[i] <= '9')
        {
        }
        else
        {
            //not a digit
            return NO_DIG;
        }
    }
    return DIGIT;
}

int operator_check(char *a_token)
{
    if (strcmp(a_token, "+") == 0)
    {
        return PLUS;
    }
    else if (strcmp(a_token, "-") == 0)
    {
        return MINUS;
    }
    else if (strcmp(a_token, "*") == 0)
    {
        return MULTIPLY;
    }
    else if (strcmp(a_token, "/") == 0)
    {
        return DIVISION;
    }
    else
    {
        return NO_OP;
    }
}

int rpn_eval_token(char *token[], char **result)
{

    rpn_stack_t *stk;
    stk = rpn_stack_new();
 
     //Check for invalid tokens
     for (int i = 0; i < no_of_tokens; i++)
     {
         if (operator_check(token[i]) == NO_OP)
         {
             if (digit_check(token[i]) == NO_DIG)
                 return RPN_INVALID_TOKEN;
         }
     }

    for(int i = 0; i < no_of_tokens; i++ ) 
    {
        if (operator_check(token[i]) == PLUS) 
        {
            // pop 2 stack members and add
            char * firstPopped = rpn_stack_pop(stk);
            if (firstPopped == NULL) return RPN_MISSING_OPERAND;

            char * secondPopped = rpn_stack_pop(stk);
            if (secondPopped == NULL) return RPN_MISSING_OPERAND;

            int first = atoi(firstPopped);
            int second = atoi(secondPopped);
            int sum = first + second;

            char str[10];

            sprintf(str, "%d", sum);
            rpn_stack_push(stk, str);

        }
        else if (operator_check(token[i]) == MINUS) 
        {
            // pop 2 stack members and minus
            char * firstPopped = rpn_stack_pop(stk);
            if (firstPopped == NULL) return RPN_MISSING_OPERAND;

            char * secondPopped = rpn_stack_pop(stk);


            if (secondPopped == NULL) return RPN_MISSING_OPERAND;

            int first = atoi(firstPopped);
            int second = atoi(secondPopped);


            int minus = first - second;
            char str[10];
            sprintf(str, "%d", minus);
            rpn_stack_push(stk, str);
        }
        else if (operator_check(token[i]) == MULTIPLY) 
        {
            // pop 2 stack members and multiply
            char * firstPopped = rpn_stack_pop(stk);
            if (firstPopped == NULL) return RPN_MISSING_OPERAND;
            char * secondPopped = rpn_stack_pop(stk);

            if (secondPopped == NULL) return RPN_MISSING_OPERAND;

            int first = atoi(firstPopped);
            int second = atoi(secondPopped);
            int prod = first * second;
            char str[10];
            sprintf(str, "%d", prod);
            rpn_stack_push(stk, str);

            // pop 2 stack members and minus
        }
        else if (operator_check(token[i]) == DIVISION) 
        {
            // pop 2 stack members and divide
            char * firstPopped = rpn_stack_pop(stk);
            if (firstPopped == NULL) return RPN_MISSING_OPERAND;
            char * secondPopped = rpn_stack_pop(stk);
            if (secondPopped == NULL) return RPN_MISSING_OPERAND;

            int first = atoi(firstPopped);
            int second = atoi(secondPopped);
            if (first == 0) return RPN_ARITHMETIC_ERROR;
            int divide = second / first;
            char str[10];
            sprintf(str, "%d", divide);
            rpn_stack_push(stk, str);
        } 
        else 
        {
            rpn_stack_push(stk, token[i]);
        }
    }

    strcpy(*result, (char *) rpn_stack_pop(stk));

    if (rpn_stack_empty(stk))
    {
        rpn_stack_del(stk);
        return RPN_OK;
    }
    else 
    {
        rpn_stack_del(stk);
        return RPN_MISSING_OPERATOR;
    }
}

int rpn_eval_expr(const char *expr, char **result)
{
    // declarations
    no_of_tokens = 0;
    const char delimiter[] = " ";
    char *tmp_expr;
    char *second_tmp_exp;
    tmp_expr = (char *)malloc(sizeof(char) * strlen(expr) + 1);
    second_tmp_exp = (char *)malloc(sizeof(char) * strlen(expr) + 1);
    if (second_tmp_exp == NULL)
    {
        printf("Error during malloc");
        exit(EXIT_FAILURE);
    }
    if (tmp_expr == NULL)
    {
        printf("Error during malloc");
        exit(EXIT_FAILURE);
    }
    char *pch;

    // copying expression to temporary variables 
    // second_tmp_exp --> for seperation
    // tmp_expr --> for counting tokens
    strcpy(second_tmp_exp, expr);
    strcpy(tmp_expr, expr);


    // counting the number of tokens in our result
    pch = strtok(tmp_expr, delimiter);
    while (pch != NULL)
    {
        no_of_tokens++;
        pch = strtok(NULL, delimiter);
    }


    char * tokens[no_of_tokens];
    for(int i = 0; i < no_of_tokens; i++ ) 
    {
        tokens[i] = malloc (sizeof(char) * 255);
        if (tokens[i] == NULL) 
        {
            exit(EXIT_FAILURE);
        } 
    }


    // seperating expression into tokens
    // we use the delimiter as space " "
    int index = 0;
    pch = strtok(second_tmp_exp, delimiter);
    while (pch != NULL)
    {
        strcpy(tokens[index], pch);
        index++;
        pch = strtok(NULL, " ");
    }


    char * sub_result = malloc(sizeof(char) * 255);

    if (sub_result == NULL)
    {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    // using evaluating function
    int rval_token_fct;
    rval_token_fct = rpn_eval_token(tokens, &sub_result);

    // result handling
    switch (rval_token_fct)
    {
    case RPN_OK:
        strcpy(*result, sub_result);
        break;
    case RPN_INVALID_TOKEN:
        strcpy(*result, "Invalid token");
        break;
    case RPN_MISSING_OPERAND:
        strcpy(*result, "missing operand");
        break;
    case RPN_MISSING_OPERATOR:
        strcpy(*result, "missing operator");
        break;
    case RPN_ARITHMETIC_ERROR:
        strcpy(*result, "arithmetic error");
        break;
    }

    // memory freeing
    free(tmp_expr);
    free(second_tmp_exp);
    free(sub_result);
    for(int i = 0; i < no_of_tokens; i++ ) 
    {
        free(tokens[i]);
    }

    return rval_token_fct;
}

/*
 * rpn.h --
 */

/** @file */

#ifndef _RPN_H
#define _RPN_H


/** RPN evaluation was successful. */
#define RPN_OK                  0
/** RPN evaluation failed due to an invalid token. */
#define RPN_INVALID_TOKEN       -1
/** RPN evaluation failed due to a missing operand. */
#define RPN_MISSING_OPERAND     -2
/** RPN evaluation failed due to a missing operator. */
#define RPN_MISSING_OPERATOR    -3
/** RPN evaluation failed due to an arithmetic error. */
#define RPN_ARITHMETIC_ERROR    -4

/**
 * \brief Evaluate an expression in reverse polish notation.
 *
 * This functions takes an array of strings that are interpreted as
 * tokens of an expression in reverse polish notation. The function
 * returns the results as a string via the second argument. The result
 * is allocated using malloc() and must be freed by the caller of this
 * function. Note that the function may return a NULL pointer if no
 * result was calculated. The return value of the function indicates
 * whether the evaluation of the expression in reverse polish notation
 * was successful or there were any errors.
 *
 * \param token Array of tokens making up the expression.
 * \param result Pointer to the string which will hold the result (malloced).
 * \result One of the error codes defined above.
 */

int rpn_eval_token(char *token[], char **result);

/**
 * \brief Evaluate an expression in reverse polish notation.
 *
 * This function splits the expression contained in the string expr
 * into an array of strings and then interpretes the array as tokens
 * of an expression in reverse polish notation. The function returns
 * the results as a string via the second argument. The result is
 * allocated using malloc() and must be freed by the caller of this
 * function. Note that the function may return a NULL pointer if no
 * result was calculated. The return value of the function indicates
 * whether the evaluation of the expression in reverse polish notation
 * was successful or there were any errors.
 *
 * \param expr The expression (whitespace separated numbers and operators)
 * \param result Pointer to the string which will hold the result (malloced).
 * \result One of the error codes defined above.
 */ 

int rpn_eval_expr(const char *expr, char **result);

#endif

/*
 * stats/src/main.c --
 *
 * Parse numbers out of white space separated text files and calculate
 * basic statistics.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "stats.h"

#define DIGIT 0
#define NO_DIG -1
#define OK 0

//count number of columns in a given vector input
int count_no_of_cols(char *str)
{
    int col_count = 0;
    char *delimiter = " ";
    char *pch;
    pch = strtok(str, delimiter);

    while (pch != NULL)
    {

        col_count++;

        pch = strtok(NULL, delimiter);
    }

    return col_count;
}

//check if given string is combined of valid digits only
int digit_check(char *a_token)
{
    int size_token = strlen(a_token);

    /* code */

    for (int i = 0; i < size_token; i++)
    {

        if (a_token[i] >= '0' && a_token[i] <= '9')
        {
            //it is a digit
        }
        else
        {
            //printf(" not digit %c\n", a_token[i]);
            return NO_DIG;
            /* code */
        }
    }
    return DIGIT;
}

//parses all values passed in a 1-D vector
int parse_vector(char *str, double *vec, int *continue_index)
{

    char *delimiter = " \n";
    char *pch;
    pch = strtok(str, delimiter);
    //printf("Initial pch %s", pch);

    while (pch != NULL)
    {
        if (digit_check(pch) == NO_DIG)
        {

            perror("Invalid vector data");
            exit(EXIT_FAILURE);
        }

        vec[*continue_index] = atoi(pch);

        (*continue_index)++;
        pch = strtok(NULL, delimiter);
    }

    return OK;
}

//check if current_idx is bounded [0, max_index)
int bound_check(int current_idx, int max_idx)
{
    if (current_idx < 0 || current_idx >= max_idx)
    {
        perror("Invalid column number");
        exit(EXIT_FAILURE);
    }

    return OK;
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    char str[1000];
    char temp_row_vals[50];
    int row_no = 0;
    int col_no = 0;
    double *input_str = malloc(sizeof(double) * 500);
    int continue_index = 0;

    if (input_str == NULL)
    {
        perror("Malloc error");
        exit(EXIT_FAILURE);
    }

    //read input and store each line in temp_row_vals
    while (fgets(str, 1000, stdin))
    {
        strcpy(temp_row_vals, str);

        col_no = count_no_of_cols(str);

        if (parse_vector(temp_row_vals, input_str, &continue_index) != OK)
        {
            perror("Invalid vector data");
            exit(EXIT_FAILURE);
        }

        row_no++;
    }

    //Store column vector in column_vec

    double *column_vec = malloc(sizeof(double) * 50);

    if (column_vec == NULL)
    {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    //Statistics of column_vec in s1
    stats_t *s1 = (stats_t *)malloc(sizeof(stats_t));

    if (s1 == NULL)
    {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }

    double min[col_no], max[col_no], mean[col_no], median[col_no];

    //do calculation in form of matrix
    for (int j = 0; j < col_no; j++)
    {
        //store each column data in column_vec
        for (int i = 0; i < row_no; i++)
        {
            column_vec[i] = input_str[j + i * col_no];
        }
        //calculate stats for jth column:
        stats(column_vec, row_no, s1);
        min[j] = s1->min;
        max[j] = s1->max;
        mean[j] = s1->mean;
        median[j] = s1->median;

        //free column_vec to reuse freshly in next iteration
        free(column_vec);
        double *column_vec = malloc(sizeof(double) * 50);
        if (column_vec == NULL)
        {
            perror("malloc error");
            exit(EXIT_FAILURE);
        }
    }

    //Parse arguments and print required statistics if valid arguments given
    for (int i = 1; i < argc; i++)
    {
        if (i % 2 == 1)
        {
            if (strcmp(argv[i], "mean") == 0 || strcmp(argv[i], "Mean") == 0 || strcmp(argv[i], "MEAN") == 0)
            {
                int col = atoi(argv[i + 1]);

                if (bound_check(col, col_no) != OK)
                {
                    exit(EXIT_FAILURE);
                }

                printf("%.3f ", mean[col]);
            }
            else if (strcmp(argv[i], "min") == 0 || strcmp(argv[i], "Min") == 0 || strcmp(argv[i], "MIN") == 0)
            {
                int col = atoi(argv[i + 1]);

                if (bound_check(col, col_no) != OK)
                {
                    exit(EXIT_FAILURE);
                }

                printf("%.3f ", min[col]);
            }
            else if (strcmp(argv[i], "max") == 0 || strcmp(argv[i], "Max") == 0 || strcmp(argv[i], "MAX") == 0)
            {
                int col = atoi(argv[i + 1]);
                if (bound_check(col, col_no) != OK)
                {
                    exit(EXIT_FAILURE);
                }

                printf("%.3f ", max[col]);
            }
            else if (strcmp(argv[i], "median") == 0 || strcmp(argv[i], "Median") == 0 || strcmp(argv[i], "MEDIAN") == 0)
            {
                int col = atoi(argv[i + 1]);
                if (bound_check(col, col_no) != OK)
                {
                    exit(EXIT_FAILURE);
                }

                printf("%.3f ", median[col]);
            }
            else
            {
                perror("Invalid args");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            if (digit_check(argv[i]) == NO_DIG)
            {
                perror("Invalid column");
                exit(EXIT_FAILURE);
            }

            if (bound_check(atoi(argv[i]), col_no) != OK)
            {
                exit(EXIT_FAILURE);
            }
        }
    }

    //free memory
    free(column_vec);
    free(input_str);

    return EXIT_SUCCESS;
}

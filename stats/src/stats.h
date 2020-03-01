/*
 * stats/src/stats.h --
 */

/** @file */

#ifndef _STATS_H
#define _STATS_H

typedef struct  {
    double min;
    double max;
    double sum;
    double mean;
    double median;
} stats_t;

/**
 * \brief Calculate basic statistics for a vector of double values.
 *
 * \param vec The vector of doube values
 * \param nelem The number of elements in the vector
 * \result The struct holding the results (min, max, mean, median, ...)
 */

void stats(double *vec, unsigned int nelem, stats_t *res);

#endif

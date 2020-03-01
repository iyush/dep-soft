/*
 * stats/src/stats.c --
 *
 * A simple implementation of basic statistics.
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "stats.h"

static int
cmp(const void *a, const void *b)
{
    double *da = (double *)a;
    double *db = (double *)b;

    return (*da < *db) ? -1 : (*da > *db) ? 1 : 0;
}

#undef BROKEN

#ifdef BROKEN

void stats(double *vec, unsigned int nelem, stats_t *res)
{
    (void)nelem;

    res->min = vec[0];
    res->max = vec[0];
    res->mean = vec[0];
    res->median = vec[0];
}

#else

void stats(double *vec, unsigned int nelem, stats_t *res)
{

    unsigned int i;

    /*
     * Calling this function with 'empty' arguments is a programming
     * mistake. Hence use an assert to detect such bugs.
     */

    assert(vec && nelem && res);

    /*
     * In case the assert gets disabled at compile time, we prefer to
     * be defensive instead of crashing hard. We also clear the result
     * 
     */

    if (!res)
    {
        return;
    }
    memset(res, 0, sizeof(*res));
    if (!vec || !nelem)
    {
        return;
    }

    /*
     * Here the actual calculations start. We now have to trust the
     * pointers and the nelem to be meaningful.
     */

    res->sum = 0;
    for (i = 0; i < nelem; i++)
    {
        res->sum += vec[i];
    }
    qsort(vec, nelem, sizeof(double), cmp);

    res->min = vec[0];
    res->max = vec[nelem - 1];
    res->mean = res->sum / nelem;
    res->median = (nelem & 0x01)
                      ? vec[nelem / 2]
                      : (vec[nelem / 2 - 1] + vec[nelem / 2]) / 2;
}

#endif

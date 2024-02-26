/*
 * Copyright (c)           Amazon.com, Inc. or its affiliates.
 *                         All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 */

/**
 * @file
 *
 * Shared utility functions
 */

#include "ompi/mca/coll/base/coll_base_functions.h"
#include "coll_han.h"

/**
 * Calculate the Greatest Common Denominator of a list of non-negative integers
 *
 * @param[in]   numerators      A list of numerators that should be divisible by
 *                              the denominator
 * @param[in]   size            Number of numerators
 * @returns     The GCD, where 1 <= GCD
 */
size_t coll_han_utils_gcd(const size_t *numerators, const size_t size)
{
    size_t denominator = numerators[0], numerator, tmp;

    for (size_t i = 1; i < size; ++i) {
        numerator = numerators[i];

        if (0 == denominator) {
            denominator = numerator;
            continue;
        }

        if (0 == numerator) {
            continue;
        }

        while (0 < numerator % denominator && 0 < denominator % numerator) {
            tmp = MIN(numerator, denominator);
            denominator = MAX(numerator, denominator) - tmp;
            numerator = tmp;
        }
    }

    if (0 == denominator) {
        denominator = 1;
    }

    return denominator;
}

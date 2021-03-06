/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2011 Sebastian Pancratz
    Copyright (C) 2011 Fredrik Johansson

******************************************************************************/

#include "perm.h"
#include "flint.h"
#include "ulong_extras.h"

int _perm_randtest(long *vec, long n, flint_rand_t state)
{
    long i, j, t;

    int parity = 0;

    for (i = 0; i < n; i++)
        vec[i] = i;

    for (i = n - 1; i > 0; i--)
    {
        j = n_randint(state, i + 1);
        parity ^= (i != j);
        t = vec[i];
        vec[i] = vec[j];
        vec[j] = t;
    }

    return parity;
}

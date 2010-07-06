/*============================================================================

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

===============================================================================*/
/****************************************************************************

   Copyright (C) 2010 William Hart

*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "nmod_poly.h"
#include "ulong_extras.h"

int main(void)
{
   int result;
   printf("bit_pack/bit_unpack....");
   fflush(stdout);
   
   // check aliasing of a and c
   for (ulong i = 0; i < 10000UL; i++) 
   {
      nmod_poly_t a, b, c;

      mp_limb_t n;
	  
	  do { n = n_randtest_not_zero(); } while (n == 1);
	  ulong bits = 2*FLINT_BIT_COUNT(n) + n_randint(FLINT_BITS);
      
	  nmod_poly_init(a, n);
      nmod_poly_init(b, n);
	  do { nmod_poly_randtest(a, n_randint(100)); } while (a->length == 0);

      mp_ptr mpn = malloc(sizeof(mp_limb_t)*((bits * a->length - 1)/FLINT_BITS + 1));
	  
      _nmod_poly_bit_pack(mpn, a->coeffs, a->length, bits);
      nmod_poly_fit_length(b, a->length);
	  _nmod_poly_bit_unpack(b->coeffs, mpn, a->length, bits, a->mod);
      b->length = a->length;

      result = (nmod_poly_equal(a, b));
      if (!result)
      {
         printf("Error:\n");
		 nmod_poly_print(a); printf("\n\n");
         nmod_poly_print(b); printf("\n\n");
         abort();
      }

      nmod_poly_clear(a);
      nmod_poly_clear(b);
   }

   printf("PASS\n");
   return 0;
}
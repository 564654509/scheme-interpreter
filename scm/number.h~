/*
  Copyright (c) 2014 Xianfei Shen
  All rights reserved.

  Permission is hereby granted, without written agreement and without
  license or royalty fees, to use, copy, modify, and distribute this
  software and its documentation for any purpose, provided that the
  above copyright notice and the following two paragraphs appear in
  all copies of this software.
 
  IN NO EVENT SHALL BRENT BENSON BE LIABLE TO ANY PARTY FOR DIRECT,
  INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
  OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF BRENT
  BENSON HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  BRENT BENSON SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT
  NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
  FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER
  IS ON AN "AS IS" BASIS, AND BRENT BENSON HAS NO OBLIGATION TO
  PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR
  MODIFICATIONS.
*/

#ifndef _NUMBER_H
#define _NUMBER_H

#include "scm.h"

/*	procedure: (+ ...)  */
extern scm_obj *num_add(const scm_obj *obj);

/*	procedure: (- number ...), at least 1 argument  */
extern scm_obj *num_sub(const scm_obj *obj);

/*	procedure: (* ...)  */
extern scm_obj *num_mul(const scm_obj *obj);

/*	procedure: (/ number ...), at least 1 argument  */
extern scm_obj *num_div(const scm_obj *obj);

/*	procedure: (quotient n1 n2)
	procedure: (remainder n1 n2)
	procedrue: (modulo n1 n2)
	
	These procedures implement number-theoretic (integer) di-
	vision. n2 should be non-zero. All three procedures return
	integers. If n1/n2 is an integer:
	
		(quotient n1 n2)    ==> n1/n2
		(remainder n1 n2)   ==> 0
		(modulo n1 n2)      ==> 0
		
	If n1/n2 is not an integer:
	
		(quotient n1 n2)    ==> nq
		(remainder n1 n2)   ==> nr
		(modulo n1 n2)      ==> nm

	where nq is n1/n2 rounded towards zero, 0 < |nr| < |n2|,
	0 < |nm| < |n2|, nr and nm differ from n1 by a multiple of
	n2 , nr has the same sign as n1 , and nm has the same sign
	as n2 .
	
	From this we can conclude that for integers n1 and n2 with
	n2 not equal to 0,

		(= n1 (+ (* n2 (quotient n1 n2))
			  (remainder n1 n2)))
			  				==> #t
*/	
extern scm_obj *num_mod(const scm_obj *obj);
extern scm_obj *num_quotient(const scm_obj *obj);
extern scm_obj *num_remainder(const scm_obj *obj);

/*	procedure: (gcd n1 ...)
	procedure: (lcm n1 ...)
	
	These procedures return the greatest common divisor or
	least common multiple of their arguments. The result is
	always non-negative.
*/
extern scm_obj *num_gcd(const scm_obj *obj);
extern scm_obj *num_lcm(const scm_obj *obj);


extern scm_obj *num_abs(const scm_obj *obj);
extern scm_obj *num_max(const scm_obj *obj);
extern scm_obj *num_min(const scm_obj *obj);

/*	procedure: (floor x)
	procedure: (ceiling x)
	procedure: (truncate x)
	procedure: (round x)

	These procedures return integers. Floor returns the
	largest integer not larger than x. Ceiling returns the
	smallest integer not smaller than x. Truncate returns the
	integer closest to x whose absolute value is not larger than
	the absolute value of x. Round returns the closest integer
	to x, rounding to even when x is halfway between two
	integers.
*/
extern scm_obj *num_floor(const scm_obj *obj);
extern scm_obj *num_round(const scm_obj *obj);
extern scm_obj *num_ceiling(const scm_obj *obj);
extern scm_obj *num_truncate(const scm_obj *obj);


extern scm_obj *num_expt(const scm_obj *obj);
extern scm_obj *num_denom(const scm_obj *obj);
extern scm_obj *num_numer(const scm_obj *obj);
extern scm_obj *num_real(const scm_obj *obj);
extern scm_obj *num_image(const scm_obj *obj);
extern scm_obj *num_eq(const scm_obj *obj);
extern scm_obj *num_le(const scm_obj *obj);
extern scm_obj *num_lt(const scm_obj *obj);
extern scm_obj *num_ge(const scm_obj *obj);
extern scm_obj *num_gt(const scm_obj *obj);
extern scm_obj *num_pred_number(const scm_obj *obj);
extern scm_obj *num_pred_complex(const scm_obj *obj);
extern scm_obj *num_pred_real(const scm_obj *obj);
extern scm_obj *num_pred_rational(const scm_obj *obj);
extern scm_obj *num_pred_integer(const scm_obj *obj);
/*	procedure: (zero? z)  */
extern scm_obj *num_pred_zero(const scm_obj *obj);

/*	procedure: (positive? x)  */
extern scm_obj *num_pred_positive(const scm_obj *obj);

/*	procedure: (negative? x)  */
extern scm_obj *num_pred_negative(const scm_obj *obj);
extern scm_obj *num_pred_odd(const scm_obj *obj);
extern scm_obj *num_pred_even(const scm_obj *obj);
extern scm_obj *num_pred_exact(const scm_obj *obj);
extern scm_obj *num_pred_inexact(const scm_obj *obj);
extern scm_obj *num_sqrt(const scm_obj *obj);
extern scm_obj *num_exp(const scm_obj *obj);
extern scm_obj *num_log(const scm_obj *obj);
extern scm_obj *num_sin(const scm_obj *obj);
extern scm_obj *num_cos(const scm_obj *obj);
extern scm_obj *num_tan(const scm_obj *obj);
extern scm_obj *num_asin(const scm_obj *obj);
extern scm_obj *num_acos(const scm_obj *obj);
extern scm_obj *num_atan(const scm_obj *obj);
extern scm_obj *num_number_to_string(const scm_obj *obj);
extern scm_obj *num_string_to_number(const scm_obj *obj);
extern scm_obj *num_exact_to_inexact(const scm_obj *obj);
extern scm_obj *num_inexact_to_exact(const scm_obj *obj);

extern void scm_init_number();

#endif

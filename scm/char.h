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

#ifndef _CHAR_H
#define _CHAR_H

#include "scm.h"

/*  procedure: (char=? char1 char2)
	procedure: (char<? char1 char2)
	procedure: (char>? char1 char2)
	procedure: (char<=? char1 char2)
	procedure: (char>=? char1 char2)
*/

extern scm_obj *char_pred_char(const scm_obj *obj);
extern scm_obj *char_pred_char_eq(const scm_obj *obj);
extern scm_obj *char_pred_char_le(const scm_obj *obj);
extern scm_obj *char_pred_char_lt(const scm_obj *obj);
extern scm_obj *char_pred_char_ge(const scm_obj *obj);
extern scm_obj *char_pred_char_gt(const scm_obj *obj);


/*  procedure: (char-ci=? char1 char2)
	procedure: (char-ci<? char1 char2)
	procedure: (char-ci>? char1 char2)
	procedure: (char-ci<=? char1 char2)
	procedure: (char-ci>=? char1 char2)
  
    These procedures are similar to char=? et cetera, but they
	treat upper case and lower case letters as the same. For
	example, (char-ci=? #\A #\a) returns #t. Some imple-
	mentations may generalize these procedures to take more
	than two arguments, as with the corresponding numerical
	predicates.
*/
extern scm_obj *char_pred_char_ci_eq(const scm_obj *obj);
extern scm_obj *char_pred_char_ci_le(const scm_obj *obj);
extern scm_obj *char_pred_char_ci_lt(const scm_obj *obj);
extern scm_obj *char_pred_char_ci_ge(const scm_obj *obj);
extern scm_obj *char_pred_char_ci_gt(const scm_obj *obj);

/*  procedure: (char-alphabetic? char)
	procedure: (char-numeric? char)
	procedure: (char-whitespace? char)
	procedure: (char-upper-case? letter)
    procedure: (char-lower-case? letter)
    
    These procedures return #t if their arguments are alpha-
	betic, numeric, whitespace, upper case, or lower case char-
	acters, respectively, otherwise they return #f. The follow-
	ing remarks, which are specific to the ASCII character set,
	are intended only as a guide: The alphabetic characters are
	the 52 upper and lower case letters. The numeric charac-
	ters are the ten decimal digits. The whitespace characters
	are space, tab, line feed, form feed, and carriage return.
*/
extern scm_obj *char_pred_char_alphabetic(const scm_obj *obj);
extern scm_obj *char_pred_char_numeric(const scm_obj *obj);
extern scm_obj *char_pred_char_whitespace(const scm_obj *obj);
extern scm_obj *char_pred_char_upper_case(const scm_obj *obj);
extern scm_obj *char_pred_char_lower_case(const scm_obj *obj);
extern scm_obj *char_char_to_integer(const scm_obj *obj);
extern scm_obj *char_integer_to_char(const scm_obj *obj);
extern scm_obj *char_char_upcase(const scm_obj *obj);
extern scm_obj *char_char_downcase(const scm_obj *obj);

extern void scm_init_char();

#endif

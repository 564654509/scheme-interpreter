/*
  Copyright (c) 2014 Xianfei Shen
  All rights reserved.

  Permission is hereby granted, without written agreement and without
  license or royalty fees, to use, copy, modify, and distribute this
  software and its documentation for any purpose, provided that the
  above copyright notice and the following two paragraphs appear in
  all copies of this software.
 
  IN NO EVENT SHALL XIANFEI SHEN BE LIABLE TO ANY PARTY FOR DIRECT,
  INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
  OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF XIANFEI
  SHEN HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  XIANFEI SHEN SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT
  NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
  FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER
  IS ON AN "AS IS" BASIS, AND XIANFEI SHEN HAS NO OBLIGATION TO
  PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR
  MODIFICATIONS.
*/

#ifndef _BOOLEAN_H
#define _BOOLEAN_H

#include "scm.h"

extern scm_obj *scm_false;
extern scm_obj *scm_true;

/*	procedure: (eq? obj1 obj2)  
	
	Eq? and eqv? are guaranteed to have the same behavior on
	symbols, booleans, the empty list, pairs, procedures, and
	non-empty strings and vectors. Eq?’s behavior on numbers
	and characters is implementation-dependent, but it will al-
	ways return either true or false, and will return true only
	when eqv? would also return true. Eq? may also behave
	differently from eqv? on empty vectors and empty strings.
*/
extern scm_obj *bool_pred_eq(const scm_obj *obj);

/*	procedure: (eqv? obj1 obj2)	 
	
	The eqv? procedure defines a useful equivalence relation
	on objects. Briefly, it returns #t if obj 1 and obj 2 should
	normally be regarded as the same object. This relation is
	left slightly open to interpretation, but the following par-
	tial specification of eqv? holds for all implementations of
	Scheme.
	
	The eqv? procedure returns #t if:
		1. obj1 and obj2 are both #t or both #f.
		2. obj1 and obj2 are both symbols and 
			(string=? (symbol->string obj1)
					  (symbol->string obj2))
					  					==>  #t
		3. obj1 and obj2 are both numbers, are numerically equal
	       , and are either both exact or both inexact.
		4. obj1 and obj2 are both characters and are the same
		   character according to the char=? procedure.
        5. both obj1 and obj2 are the empty list.
        6. obj1 and obj2 are pairs, vectors, or strings that denote
		   the same locations in the store (section 3.4).
		7. obj1 and obj2 are procedures whose location tags are
		   equal.
		   
	The eqv? procedure returns #f if:
		1. obj1 and obj2 are of different types.
		2. one of obj1 and obj2 is #t but the other is #f.
		3. obj1 and obj2 are symbols but
			(string=? (symbol->string obj1)
				      (symbol->string obj2))
				      					==>  #f
		4. one of obj1 and obj2 is an exact number but the other
		   is an inexact number.
 		5. obj1 and obj2 are numbers for which the = procedure
		   returns #f.
		6. obj1 and obj2 are characters for which the char=? pro-
		   cedure returns #f.
        7. one of obj1 and obj2 is the empty list but the other is
           not.
        8. obj1 and obj2 are pairs, vectors, or strings that denote
           distinct locations.
        9. obj1 and obj2 are procedures that would behave differ-
		   ently (return different value(s) or have different side
		   effects) for some arguments.
	
*/
extern scm_obj *bool_pred_eqv(const scm_obj *obj);

/*  procedure: (equal? obj1 obj2)

	Equal? recursively compares the contents of pairs, vectors,
	and strings, applying eqv? on other objects such as num-
	bers and symbols. A rule of thumb is that objects are
	generally equal? if they print the same. Equal? may fail
	to terminate if its arguments are circular data structures.
*/
extern scm_obj *bool_pred_equal(const scm_obj *obj);

/*  procedure: (not obj)

	Not returns #t if obj is false, and returns #f otherwise.
*/
extern scm_obj *bool_pred_not(const scm_obj *obj);

extern void scm_init_boolean();

#endif

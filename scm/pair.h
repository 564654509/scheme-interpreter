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

#ifndef _PAIR_H
#define _PAIR_H

#include "scm.h"

/*	procedure: (pair? obj)

	Pair? returns #t if obj is a pair, and otherwise returns #f.
*/
extern scm_obj *pair_pred_pair(const scm_obj *obj);

/*	procedure: (cons obj1 obj2)
	
	Returns a newly allocated pair whose car is obj1 and whose
	cdr is obj2. The pair is guaranteed to be different(in the
	sense of eqv?) from every existing object.
*/
extern scm_obj *pair_cons(const scm_obj *obj);

/*	procedure: (car pair)

	Returns the contents of the car field of pair. Note that it
	is an error to take the car of the empty list.
*/
extern scm_obj *pair_car(const scm_obj *obj);

/*	procedure: (cdr pair) 
 
	Returns the contents of the cdr field of pair. Note that it
	is an error to take the cdr of the empty list.
*/
extern scm_obj *pair_cdr(const scm_obj *obj);

/*	procedure: (set-car! pair obj)

	Stores obj in the car field of pair. The value returned by
	set-car! is unspecified.
*/
extern scm_obj *pair_set_car(const scm_obj *obj);

/*	procedure: (set-cdr! pair obj)

	Stores obj in the cdr field of pair. The value returned by
	set-cdr! is unspecified.
*/
extern scm_obj *pair_set_cdr(const scm_obj *obj);

extern void scm_init_pair();

#endif

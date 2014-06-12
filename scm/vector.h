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


#ifndef _VECTOR_H
#define _VECTOR_H

#include "scm.h"

/*	procedure: (make-vector k) or (make-vector k fill)

	Returns a newly allocated vector of k elements. If a second
	argument is given, then each element is initialized to fill.
	Otherwise the initial contents of each element is unspecified.
*/
extern scm_obj *vec_make_vector(const scm_obj *obj);

/*	procedure: (vector obj ...)

	Returns a newly allocated vector whose elements contain
	the given arguments. Analogous to list.
*/
extern scm_obj *vec_cons_vector(const scm_obj *obj);

/*	procedure:(vector-length vector)
	
	Returns the number of elements in vector as an exact integer.
*/
extern scm_obj *vec_vector_length(const scm_obj *obj);

/*	procedure:	(vector-ref vector k)

	k must be a valid index of vector. Vector-ref returns the
	contents of element k of vector.
*/
extern scm_obj *vec_vector_ref(const scm_obj *obj);

/*	procedure: (vector-set! vector k obj)

	k must be a valid index of vector. Vector-set! stores obj
	in element k of vector. The value returned by vector-set!
	is unspecified.
*/
extern scm_obj *vec_vector_set(const scm_obj *obj);

/*	procedure: (vector->list vector)
	procedure: (list->vector list)
	
	Vector->list returns a newly allocated list of the objects
	contained in the elements of vector. List->vector returns a newly
	created vector initialized to the elements of the list list.
*/
extern scm_obj *vec_list_to_vector(const scm_obj *obj);
extern scm_obj *vec_vector_to_list(const scm_obj *obj);

/*	procedure:	(vector-fill! vector fill)

	Stores fill in every element of vector. The value returned
	by vector-fill! is unspecified.
*/
extern scm_obj *vec_vector_fill(const scm_obj *obj);

/*	procedure: (vector? obj)

	Returns #t if obj is a vector, otherwise returns #f.
*/
extern scm_obj *vec_pred_vector(const scm_obj *obj);

extern void scm_init_vector();

#endif



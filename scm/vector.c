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

#include "header.h"

scm_obj *vec_make_vector(const scm_obj *obj)
{
	if (!((obj != scm_null && cdr(obj) == scm_null) ||
	      (obj != scm_null && cdr(obj) != scm_null && cddr(obj) == scm_null))) {
		error0("procedure: make-vector\nexpected: 1 to 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != INTEGER || fixnum(car(obj)) < 0) {
		error0("procedure: make-vector\nexpected: a nonnegative integer\nbad argument(s)", car(obj));
	} else {
		scm_obj *elt, *vec_obj;
		
		if (cdr(obj) != scm_null) {
			elt = cadr(obj);
		} else {
			elt = make_integer(0);
		}
		
		vec_obj = scm_alloc_obj();
		type(vec_obj) = VECTOR;
		vlen(vec_obj) = fixnum(car(obj));
		vec(vec_obj) = scm_alloc_vec(vlen(vec_obj));
		
		for (unsigned i = 0; i < vlen(vec_obj); i++) {
			(vec(vec_obj))[i] = scm_alloc_obj();
			*((vec(vec_obj))[i]) = *elt;
		}
		
		return vec_obj;
	}
} 

inline scm_obj *vec_vector_length(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: vector-length\nexpected: 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != VECTOR) {
		error0("procedure: vector-length\nexpected: vector\nbad argument(s)", car(obj));
	} else {
		return make_integer(vlen(car(obj)));
	}
}

scm_obj *vec_vector_ref(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: vector-ref\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != VECTOR) {
		error0("procedure: vector-ref\nexpected: vector\nbad argument(s)", car(obj));
	} else if (type(cadr(obj)) != INTEGER || fixnum(cadr(obj)) < 0 ||
			                     fixnum(cadr(obj)) >= vlen(car(obj))) {	
		error0("procedure: vector-ref\nexpected: a valid index of vector\nbad argument(s)", cadr(obj));
	} else {
		return (vec(car(obj)))[fixnum(cadr(obj))];
	}
}

scm_obj *vec_vector_set(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null ||
		cddr(obj) == scm_null || cdddr(obj) != scm_null) {
		error0("procedure: vector-set!\nexpected: 3 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != VECTOR) {
		error0("procedure: vector-set!\nexpected: vector\nbad argument(s)", car(obj));
	} else if (type(cadr(obj)) != INTEGER || fixnum(cadr(obj)) < 0 ||
			                     fixnum(cadr(obj)) >= vlen(car(obj))) {	
		error0("procedure: vector-set!\nexpected: a valid index of vector\nbad argument(s)", cadr(obj));;
	} else {
		(vec(car(obj)))[fixnum(cadr(obj))] = caddr(obj);
		return scm_unspecified;
	}
}

inline scm_obj *vec_pred_vector(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: vector?\nexpected: 1 argument\nbad argument(s)", obj);
	} else {
		return type(car(obj)) == VECTOR ? scm_true : scm_false;
	}
}

void scm_init_vector()
{
	scm_add_prim("make-vector", vec_make_vector);
	scm_add_prim("vector-length", vec_vector_length);
	scm_add_prim("vector-ref", vec_vector_ref);
	scm_add_prim("vector-set!", vec_vector_set);
	scm_add_prim("vector?", vec_pred_vector);
}
			
	
	
	
	
	
	
	
	

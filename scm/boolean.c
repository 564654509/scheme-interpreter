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

/*  constant false  */
scm_obj *scm_false;

/*  constant true  */
scm_obj *scm_true;

scm_obj *bool_pred_eq(const scm_obj *obj)
{
	const scm_obj *obj1, *obj2;
	
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: eq?\nexpected: 2 arguments\nbad argument(s)", obj);
	}
	
	obj1 = car(obj);
	obj2 = cadr(obj);
	
	return bool_pred_eqv(cons(obj1, cons(obj2, scm_null)));
}
	
scm_obj *bool_pred_eqv(const scm_obj *obj)
{
	const scm_obj *obj1, *obj2;
	
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: eqv?\nexpected: 2 arguments\nbad argument(s)", obj);
	}
	
	obj1 = car(obj);
	obj2 = cadr(obj);
	
	if (type(obj1) == STRING && type(obj2) == STRING) {
		if (obj1 == obj2) {
			return scm_true;
		} else {
			return scm_false;
		}
	} else if (type(obj1) == SYMBOL && type(obj2) == SYMBOL) {
		if (!strcmp(str(obj1), str(obj2))) {
			return scm_true;
		} else {
			return scm_false;
		}
	} else if (type(obj1) == INTEGER && type(obj2) == INTEGER) {
		if (fixnum(obj1) == fixnum(obj2)) {
			return scm_true;
		} else {
			return scm_false;
		}
	} else if (type(obj1) == CHAR && type(obj2) == CHAR) {
		if (Char(obj1) == Char(obj2)) {
			return scm_true;
		} else {
			return scm_false;
		}
	} else if (type(obj1) == VECTOR && type(obj2) == VECTOR) {
		if (obj1 == obj2) {
			return scm_true;
		} else {
			return scm_false;
		}
	} else if (obj1 == obj2) {
		return scm_true;
	} else {
		return scm_false;
	}
}

scm_obj *bool_pred_equal(const scm_obj *obj)
{
	const scm_obj *obj1, *obj2;
	
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: equal?\nexpected: 2 arguments\nbad argument(s)", obj);
	}
	
	obj1 = car(obj);
	obj2 = cadr(obj);
	
	if (bool_pred_eqv(cons(obj1, cons(obj2, scm_null))) == scm_true) {
		return scm_true;
	} else if (type(obj1) == VECTOR && type(obj2) == VECTOR) {
		unsigned int i, j;	
		
		for (i = vlen(obj1), j = vlen(obj2); i > 0 && j > 0; i--, j--) {
			if (bool_pred_equal(cons(vec(obj1)[i - 1], 
			        cons(vec(obj2)[j - 1], scm_null))) == scm_true) {
				;
			} else {
				return scm_false;
			}
		}
		if (i == 0 && j == 0) {
			return scm_true;
		} else {
			return scm_false;
		}
	} else if (type(obj1) == PAIR && type(obj2) == PAIR) {
		const scm_obj *p, *q;
		
		if (car(obj1) == scm_closure || car(obj2) == scm_closure ||
			car(obj1) == scm_macro || car(obj2) == scm_macro) {
			return scm_false;
		} else {
			for (p = obj1, q = obj2; p != scm_null && q != scm_null 
				 && type(p) == PAIR && type(q) == PAIR; p = cdr(p), q = cdr(q)) {
				if (bool_pred_equal(cons(car(p), cons(car(q), scm_null))) == scm_false) {
					return scm_false;
				}
			}
			if (bool_pred_equal(cons(p, cons(q, scm_null))) == scm_true) {
				return scm_true;
			} else {
				return scm_false;
			}
		}
	} else if (type(obj1) == STRING && type(obj2) == STRING) {
		if (!strcmp(str(obj1), str(obj2))) {
			return scm_true;
		} else {
			return scm_false;
		}
	} else {
		return scm_false;
	}
}
			
scm_obj *bool_pred_not(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: not\nexpected: 1 argument\nbad argument(s)", obj);
	} else {
		return car(obj) == scm_false ? scm_true : scm_false;
	}
}

void scm_init_boolean()
{
	scm_obj *false_obj;
	scm_obj *true_obj;
	
	false_obj = scm_alloc_obj();
	true_obj = scm_alloc_obj();
	type(false_obj) = BOOLEAN;
	type(true_obj) = BOOLEAN;
	
	scm_false = false_obj;
	scm_true = true_obj;
	
	scm_add_prim("eq?", bool_pred_eq);
	scm_add_prim("eqv?", bool_pred_eqv);
	scm_add_prim("equal?", bool_pred_equal);
	scm_add_prim("not", bool_pred_not);
}


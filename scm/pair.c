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

inline scm_obj *pair_pred_pair(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: pair?\nexpected: 1 argument\nbad argument(s)", obj);
	} else {
		return type(car(obj)) == PAIR && caar(obj) != scm_closure? scm_true : scm_false;
	}
}

inline scm_obj *pair_cons(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: cons\nexpected: 2 arguments\nbad argument(s)", obj);
	} else {
		return cons(car(obj), cadr(obj));
	}
}

scm_obj *pair_car(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: car\nexpected: 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != PAIR) {
		error0("procedure: car\nexpected: pair\nbad argument(s)", car(obj));
	} else {
		return caar(obj);
	}
}

scm_obj *pair_cdr(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: cdr\nexpected: 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != PAIR) {
		error0("procedure: cdr\nexpected: pair\nbad argument(s)", car(obj));
	} else {
		return cdar(obj);
	}
}

scm_obj *pair_set_car(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: set-car!\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != PAIR) {
		error0("procedure: set-car!\nexpected: pair\nbad argument(s)", car(obj));
	} else {
		caar(obj) = cadr(obj);
		return scm_unspecified;
	}
}

scm_obj *pair_set_cdr(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: set-cdr!\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != PAIR) {
		error0("procedure: set-cdr!\nexpected: pair\nbad argument(s)", car(obj));
	} else {
		cdar(obj) = cadr(obj);
		return scm_unspecified;
	}
}

void scm_init_pair()
{
	scm_add_prim("pair?", pair_pred_pair);
	scm_add_prim("cons", pair_cons);
	scm_add_prim("car", pair_car);
	scm_add_prim("cdr", pair_cdr);
	scm_add_prim("set-car!", pair_set_car);
	scm_add_prim("set-cdr!", pair_set_cdr);
}
		
		
		
		
		
		
		
		
		
		
	

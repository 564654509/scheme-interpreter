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

inline scm_obj *list_pred_null(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: null?\nexpected: 1 argument\nbad argument(s)", obj);
	} else {
		return car(obj) == scm_null ? scm_true : scm_false;
	}
}

scm_obj *list_pred_list(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: list?\nexpected: 1 argument\nbad argument(s)", obj);
	} else {
		const scm_obj *p = car(obj);	
		while (p != scm_null && type(p) == PAIR) {
			p = cdr(p);
		}	
		if (type(car(obj)) == PAIR && caar(obj) == scm_closure) {
			return scm_false;
		} else { 
			return p == scm_null ? scm_true : scm_false;
		}
	}
}

scm_obj *list_length(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: length\nexpected: 1 argument\nbad argument(s)", obj);
	} else {
		const scm_obj *p = car(obj);
		long len = 0;
		
		for (; p != scm_null && type(p) == PAIR; len++, p = cdr(p))
			;
		if (p == scm_null) {
			return make_integer(len);
		} else {
			error0("procedure: length\nexpected: list\nbad argument(s)", obj);
		}
	}
}

void scm_init_list()
{
	scm_add_prim("null?", list_pred_null);
	scm_add_prim("length", list_length);
	scm_add_prim("list?", list_pred_list);
}



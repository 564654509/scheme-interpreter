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

/*  procedure: (apply proc arg1 arg2 ... args)  */
scm_obj *ctrl_apply(const scm_obj *obj)
{
	scm_obj *env;
	scm_obj *exp;
	scm_obj *p;
	scm_obj *q;
	scm_obj *proc;
	
	if (obj == scm_null || cdr(obj) == scm_null) {
		error0("procedure: apply\nexpected: at least 2 arugments\nbad argument(s)", obj);
	} else if (type(car(obj)) != PRIM && (type(car(obj)) != PAIR || caar(obj) != scm_closure)) {
		error0("procedure: apply\nexpected: procedure\nbad argument(s)", car(obj));
	} else {
		if (cddr(obj) != scm_null) {
			for (p = obj; cddr(p) != scm_null; p = cdr(p))
			;
			q = cdr(p);
			cdr(p) = car(q);
			q = cdr(obj);
		} else {
			q = cadr(obj);
		}
		
		for (p = q; p != scm_null && type(p) == PAIR; p = cdr(p))
			;
		if (p != scm_null) {
			error0("procedure: apply\nexpected: list as last argument\nbad argument(s)", q);
		}
		
		proc = car(obj);
		if (type(proc) == PRIM) {
			return apply(proc, q);
		} else {
			exp = cons(scm_begin, caddr(proc));
			env = extend(cadr(proc),q, cadddr(proc), scm_null);
			return eval(exp, env);
		}
	}
}

scm_obj *ctrl_callcc(const scm_obj *obj)
{
	return scm_unspecified;
}

scm_obj *ctrl_pred_procedure(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: procedure?\nexpected: 1 argument\nbad argument(s)", obj);
	} else {
		if (type(car(obj)) == PRIM) {
			return scm_true;
		} else if (type(car(obj)) == PAIR && caar(obj) == scm_closure) {
			return scm_true;
		} else {
			return scm_false;
		}
	}
}

void scm_init_control()
{
	scm_add_prim("apply", ctrl_apply);
	scm_add_prim("call/cc", ctrl_callcc);
	scm_add_prim("procedure?", ctrl_pred_procedure);
}

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


#include "header.h"

/*  evaluates the arguments of a procedure  */
static scm_obj *eval_args(const scm_obj *exp, const scm_obj *env);

static scm_obj *eval_cont(const scm_obj *exp, const scm_obj *env);

/*  evaluates expression  */
scm_obj *eval(const scm_obj *exp, const scm_obj *env)
{
	const scm_obj *args, *first;
	const scm_obj *proc, *val;
	const scm_obj *p;
	scm_type type;
	
repeat:

	type = type(exp);
	
	/*  evaluates a constant exprssion  */
	if ((type <= VECTOR && type >= BOOLEAN) || exp == scm_null || exp == scm_unspecified) {
		return exp;
		
	/*  looks up a symbol from current environment  */
	} else if (type == SYMBOL) {
		val = lookup(exp, env);
		
		if (val == scm_null) {
			error0("unbounded variable", exp);
		} else {
			return cdr(val);
		}
	} else if (type == PAIR) {
		first = car(exp);
		
		/*  quoted expression : (quote exp)  */
		if (first == scm_quote) {
			return cadr(exp);
			
			
		/*	if expression : (if pred then else)  */			
		} else if (first == scm_if) {
		
			if (cdr(exp) == scm_null || type(cdr(exp)) != PAIR ||
				cddr(exp) == scm_null || type(cddr(exp)) != PAIR ||
				cdddr(exp) == scm_null || type(cdddr(exp)) != PAIR ||
				cddddr(exp) != scm_null) {
				error0("bad syntax: an illegal if expression", exp);
			}
			
			if (eval(cadr(exp), env) != scm_false) {
				exp = caddr(exp);
			} else if (cdddr(exp) != scm_null) {
				exp = cadddr(exp);
			}
			goto repeat;
			
			
		/*  lambda expression : (lambda params body)  */		
		} else if (first == scm_lambda) {
	
			if (cdr(exp) == scm_null || type(cdr(exp)) != PAIR ||
			    cddr(exp) == scm_null || type(cddr(exp)) != PAIR) {
				error0("bad syntax: an illegal lambda expression", exp);
			}
			return cons(scm_closure, cons(cadr(exp), 
					    cons(cddr(exp), cons(env, scm_null))));
					    
					    
		/*  begin expression : (begin body1 body2 ...)  */				    
		} else if (first == scm_begin) {
		
			for (p = exp; p != scm_null && type(p) == PAIR; p = cdr(p))
		    	;
		    if (p != scm_null) {
		    	error0("bad syntax: an illegal begin expression", exp);
		    }
		    
			exp = cdr(exp);
			if (exp == scm_null)
				return scm_unspecified;
			while (cdr(exp) != scm_null && type(cdr(exp)) == PAIR) {
				eval(car(exp), env);
				exp = cdr(exp);
			}
			exp = car(exp);
			goto repeat;
			
			
		/*  definition expression : (define var val) or (define (proc params) body)  */		
		} else if (first == scm_define) {
			
			if (cdr(exp) == scm_null || type(cdr(exp)) != PAIR ||
				cddr(exp) == scm_null || type(cddr(exp)) != PAIR) {
				error0("bad syntax: an illegal definition expression", exp);
			}
			
			if (type(cadr(exp)) == SYMBOL) {
				val = eval(caddr(exp), env);
				return add_binding(cadr(exp), val, env);
			} else {
				val = eval(cons(scm_lambda, cons(cdadr(exp), cddr(exp))), env);
				return add_binding(caadr(exp), val, env);
			}
			
		
		/*  assignment expression : (set! var val)  */
		} else if (first == scm_set) {
			
			if (cdr(exp) == scm_null || type(cdr(exp)) != PAIR ||
				cddr(exp) == scm_null || type(cddr(exp)) != PAIR ||
				cdddr(exp) != scm_null) {
				error0("bad syntax: an illegal assignment expression", exp);
			}
			if (type(cadr(exp)) != SYMBOL) {
				error0("bad syntax: requires a symbol in assignment expression", cadr(exp));
			}
			
			return assign(cadr(exp), eval(caddr(exp), env), env);

				
		/*  macro-definition expresssion : (define-macro var params body)  */	
		} else if (first == scm_define_macro) {
			
			if (cdr(exp) == scm_null || type(cdr(exp)) != PAIR ||
				cddr(exp) == scm_null || type(cddr(exp)) != PAIR ||
				cdddr(exp) == scm_null || type(cdddr(exp)) != PAIR) {
				error0("bad syntax: an illegal macro-definition expression", exp);
			}
			if (type(cadr(exp)) != SYMBOL) {
				error0("bad syntax: requires a symbol as a macro name", exp);
			}
			
			val = cons(scm_macro, cons(caddr(exp), cons(cdddr(exp), scm_null)));
			return add_binding(cadr(exp), val, env);
				
			
		/*  procedure and macro  */	
		} else {
		
		    for (p = exp; p != scm_null && type(p) == PAIR; p = cdr(p))
		    	;
		    if (p != scm_null) {
		    	error0("bad syntax: requires a list form for procedure expression", exp);
		    }
		
			/*if (first == scm_apply) {
			
				if (cdr(exp) == scm_null || type(cdr(exp)) != PAIR ||
					cddr(exp) == scm_null) {
				    error0("procedure: apply!\nexpected: at least 2 arguments\nbad argument(s)", cdr(exp));
				} else {
					exp = cons(cadr(exp), eval(caddr(exp), env));
				    goto repeat;
				}*/
				
		    /*  Notice : only supports a limited call/cc functionality.
		        You can't store the continuation because I use the c 
		        functions: setjmp and longjmp to implement it.  Just use
		        it as a break or throw structure. 
		    */
			if (first == scm_callcc || first == scm_call_with_cc) {
				return eval_cont(exp, env);
			}
				
			proc = eval(first, env);  
			
	        /*  expands macro expression  */
			if (type(proc) == PAIR && car(proc) == scm_macro) {
				scm_obj *body = eval(cons(scm_begin, caddr(proc)), 
							         extend(cadr(proc), cdr(exp), env, first));
							
				if (type(body) == PAIR) {
					exp = body;
				} else {
					exp = cons(scm_begin, cons(body, scm_null));
				}
				goto repeat;
			} else {		
				args = eval_args(cdr(exp), env);
				
				/*  evaluates a compound procedure  */
				if (type(proc) == PAIR && car(proc) == scm_closure) {
					exp = cons(scm_begin, caddr(proc));
					env = extend(cadr(proc), args, cadddr(proc), first);
					goto repeat;
				
				} else if (type(proc) == PAIR && car(proc) == scm_cont) {
					if (cdr(args) != scm_null) {
						error0("procedure: call/cc\nexpected: 1 argument\nbad argument(s)", cdr(exp));
					} else {
						longjmp(*(buf(cdr(proc))), (int)car(args));
					}
				/*  evaluates a primitive procedure  */
				} else if (type(proc) == PRIM) {
					return apply(proc, args);
				} else {
					error0("an illegal procedure", exp);
				}
			}
		}
	} else {
		error0("unknow expression type", exp);
	}					
}

static scm_obj *eval_args(const scm_obj *exp, const scm_obj *env)
{
	scm_obj *p, *q, *r;
	
	if (exp == scm_null) {
		return scm_null;
	} else {
		q = p = scm_alloc_obj();	
		while (exp != scm_null) {
			type(q) = PAIR;
			car(q) = eval(car(exp), env);
			cdr(q) = scm_alloc_obj();
			r = q;
			q = cdr(q);
			exp = cdr(exp);
		}
		cdr(r) = scm_null;
	    return p;
	}
}

static scm_obj *eval_cont(const scm_obj *exp, const scm_obj *env)
{
	jmp_buf cont_buf;
	scm_obj *cont;
	scm_obj *proc;
	scm_obj *ret;
	

	if (cdr(exp) == scm_null || type(cdr(exp)) != PAIR || 
		cddr(exp) != scm_null) {
		error0("procedure: call/cc\nexpected: 1 argument\nbad argument(s)", cdr(exp));
	}
	ret = (scm_obj *)setjmp(cont_buf);
	if (ret) {
		return ret;
	} else {
		proc = eval(cadr(exp), env);
		
		if (type(proc) != PAIR || car(proc) != scm_closure) {
			error0("procedure: call/cc\nexpected: procedure\nbad argument(s)", cadr(exp));
		} else if (type(cadr(proc)) != PAIR || cdadr(proc) != scm_null) {
			error0("procedure: call/cc\nexpected: procedure with 1 argument\n"
				   "bad argument(s)", cadr(proc));
		} else {
			cont = scm_alloc_obj();
			buf(cont) = &cont_buf;
		    
		    exp = cons(scm_begin, caddr(proc));
			env = extend(cadr(proc), cons(cons(scm_cont, cont), scm_null), cadddr(proc), cadr(exp));
		
			return eval(exp, env);
		}
	}
	
}

scm_obj *eval_eval(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: eval\nexpected: 1 argument\nbad argument(s)", obj);	
	} else {
		return eval(car(obj), init_env);
	}
}

void scm_init_eval()
{
	scm_add_prim("eval", eval_eval);
}

			
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
			
		

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

scm_obj *init_env;

scm_obj *add_binding(const scm_obj *var, const scm_obj *val, scm_obj *env)
{
	scm_obj *frame = car(env);
	
	while (frame != scm_null) {
		if (caar(frame) == var) {
			cdar(frame) = val;
			break;
		} else {
			frame = cdr(frame);
		}
	}
	car(env) = cons(cons(var, val), car(env));
	
	return scm_unspecified;
}

scm_obj *assign(const scm_obj *var, const scm_obj *val, const scm_obj *env)
{
	scm_obj *rib = lookup(var, env);
	
	if (rib == scm_null) {
		error0("unbounded variable", var);
	} else {
		cdr(rib) = val;
	}
	
	return scm_unspecified;
}
						          
scm_obj *extend(const scm_obj *vars, const scm_obj *vals, 
                scm_obj *env, const scm_obj *name)
{
	const scm_obj *frame = scm_null;
	const scm_obj *_vals = vals;
	
	while (vals != scm_null) {
		if (vars == scm_null) {
			if (type(name) == PAIR) {
				fprintf(stderr, "anonymous procedure\n");
			} else {
				fprintf(stderr, "procedure: %s\n", str(name));
			}
			error0("too much arguments\nbad argument(s)", _vals);
		} else {
			if (type(vars) == PAIR) {
				frame = cons(cons(car(vars), car(vals)), frame);
				vars = cdr(vars);
				vals = cdr(vals);
			} else {
				frame = cons(cons(vars, vals), frame);
				env = cons(frame, env);
				return env;
			}
		}
	}
	
	if (vars != scm_null && type(vars) != PAIR) {
		frame = cons(cons(vars, vals), frame);
	} else if (vars != scm_null) {
		if (type(name) == PAIR) {
				fprintf(stderr, "anonymous procedure\n");
			} else {
				fprintf(stderr, "procedure: %s\n", str(name));
			}
		error0("too less arguments\nbad argument(s)", _vals);
	}
	env = cons(frame, env);
	
	return env;
}
		
scm_obj *lookup(const scm_obj *var, const scm_obj *env)
{
	const scm_obj *frame;

	while (env != scm_null) {
		frame = car(env);
		while (frame != scm_null) {
			if (caar(frame) == var) {
				return car(frame);
			} else {
				frame = cdr(frame);
			}
		}
		env = cdr(env);
	}
	
	return scm_null;
}

void scm_add_prim(char *str, routine proc)
{
	scm_obj *name, *obj;

	name = scm_alloc_obj();
	type(name) = SYMBOL;
	slen(name) = strlen(str);
	str(name) = scm_alloc_str(slen(name) + 1);
	strcpy(str(name), str);
	name = scm_add_obj(name);
	
	obj = scm_alloc_obj();
	type(obj) = PRIM;
	proc(obj) = proc;
	
	car(init_env) = cons(cons(name, obj), car(init_env));
}

void scm_init_env()
{
	init_env = cons(scm_null, scm_null);
}








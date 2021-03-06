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

scm_obj *scm_closure;
scm_obj *scm_cont;
scm_obj *scm_eof;
scm_obj *scm_macro;
scm_obj *scm_null;
scm_obj *scm_syntax;

static scm_obj *oblist;

scm_obj *scm_add_obj(const scm_obj *obj)
{
	const scm_obj *p;
	
	for (p = oblist; p != scm_null; p = cdr(p)) {
		if (car(p) == obj) {
			return car(p);
		} else if (type(car(p)) == type(obj)) {
			if (type(obj) == SYMBOL) {
				if (!strcmp(str(obj), str(car(p))))
					return car(p);
			} 
		} 
	}
	
	oblist = cons(obj, oblist);
	return obj;	
}

scm_obj *make_char(char c)
{
	scm_obj *char_obj;
	
	char_obj = scm_alloc_obj();
	type(char_obj) = CHAR;
	Char(char_obj) = c;
	
	return char_obj;
}

scm_obj *make_integer(long long num)
{
	scm_obj *int_obj;
	
	int_obj = scm_alloc_obj();
	type(int_obj) = INTEGER;
	fixnum(int_obj) = num;
	
	return int_obj;
}

scm_obj *make_pair(const scm_obj *car, const scm_obj *cdr)
{
	scm_obj *pair_obj;
	
	pair_obj = scm_alloc_obj();
	type(pair_obj) = PAIR;
	car(pair_obj) = car;
	cdr(pair_obj) = cdr;
	
	return pair_obj;
}

scm_obj *make_port(FILE *fp, scm_type type)
{
	scm_obj *obj;
	
	obj = scm_alloc_obj();
	type(obj) = type;
	port(obj) = fp;
	
	return obj;
}	

scm_obj *make_string(const char *str)
{
	scm_obj *str_obj;
	
	str_obj = scm_alloc_obj();
	type(str_obj) = STRING;
	slen(str_obj) = strlen(str);
	str(str_obj) = scm_alloc_str(slen(str_obj) + 1);
	strcpy(str(str_obj), str);
	
	return str_obj;
}

scm_obj *make_symbol(const char *str)
{
	scm_obj *sym_obj;
	
	if (!strcmp(str, "quasiquote")) {
		return scm_quasiquote;
	} else if (!strcmp(str, "quote")) {
		return scm_quote;
	} else if (!strcmp(str, "unquote")) {
		return scm_unquote;
	} else if (!strcmp(str, "unquote-splicing")) {
		return scm_unquote_splicing;
	} else {
		sym_obj = scm_alloc_obj();
		type(sym_obj) = SYMBOL;
		slen(sym_obj) = strlen(str);
		str(sym_obj) = scm_alloc_str(slen(sym_obj) + 1);
		strcpy(str(sym_obj), str);
		
		return scm_add_obj(sym_obj);
	}
}

void scm_init_oblist()
{
	oblist = scm_null;
}

scm_obj *scm_add_keywd(const char *str)
{
	scm_obj *obj;
	
	obj = scm_alloc_obj();
	type(obj) = SYMBOL;
	slen(obj) = strlen(str);
	str(obj) = scm_alloc_str(slen(obj) + 1);
	strcpy(str(obj), str);
	
	return scm_add_obj(obj);
}

void scm_init_flags()
{
	scm_closure = scm_alloc_obj();
	scm_cont = scm_alloc_obj();
	scm_eof = scm_alloc_obj();
	scm_macro = scm_alloc_obj();
	scm_null = scm_alloc_obj();
	scm_syntax = scm_alloc_obj();
	
	type(scm_closure) = FLAG;
	type(scm_cont) = FLAG;
	type(scm_eof) = FLAG;
	type(scm_macro) = FLAG;
	type(scm_null) = FLAG;
	type(scm_syntax) = FLAG;
}

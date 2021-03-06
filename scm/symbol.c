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

scm_obj *scm_quasiquote;
scm_obj *scm_quote;
scm_obj *scm_unquote;
scm_obj *scm_unquote_splicing;
scm_obj *scm_unspecified;

inline scm_obj *sym_pred_symbol(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: symbol?\nexpected: 1 argument\nbad argument(s)", obj);
	} else {
		return type(car(obj)) == SYMBOL ? scm_true : scm_false;
	}
}

scm_obj *sym_symbol_to_string(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: symbol->string\nexpected: 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != SYMBOL) {
		error0("procedure: symbol->string\nexpected: symbol\nbad argument(s)", car(obj));
	} else {
		scm_obj *sym_obj = scm_alloc_obj();
		*sym_obj = *(car(obj));
		type(sym_obj) = STRING;
		
		return sym_obj;
	}
}

scm_obj *sym_string_to_symbol(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: string->symbol\nexpected: 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != STRING) {
		error0("procedure: string->symbol\nexpected: string\nbad argument(s)", car(obj));
	} else {
		scm_obj *sym_obj = scm_alloc_obj();
		*sym_obj = *(car(obj));
		type(sym_obj) = SYMBOL;
		
		return sym_obj;
	}
}

void scm_init_symbol()
{
	scm_quasiquote = make_symbol("`");
	scm_quote = make_symbol("'");
	scm_unquote = make_symbol(",");
	scm_unquote_splicing = make_symbol(",@");
	scm_unspecified = make_symbol("unspecified");
	
	scm_add_prim("symbol?", sym_pred_symbol);
	scm_add_prim("symbol->string", sym_symbol_to_string);
	scm_add_prim("string->symbol", sym_string_to_symbol);
}
	
	
	
	
	
	
	
	
	
	

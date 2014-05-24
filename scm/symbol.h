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

#ifndef _SYMBOL_H
#define _SYMBOL_H

#include "scm.h"

extern  scm_obj *scm_quasiquote;
extern  scm_obj *scm_quote;
extern  scm_obj *scm_unquote;
extern  scm_obj *scm_unquote_splicing;
extern  scm_obj *scm_unspecified;

/*	procedure: (symbol? obj)
	
	Returns #t if obj is a symbol, otherwise returns #f.
*/
extern scm_obj *sym_pred_symbol(const scm_obj *obj);

/*	procedure: (symbol->string symbol)

	Returns the name of symbol as a string. If the symbol was
	part of an object returned as the value of a literal expres-
	sionor by a call to the read procedure, and its name contains
	alphabetic characters, then the string returned will contain 
	characters in the implementation’s preferred standard case—some 
	implementations will prefer upper case, others lower case. If 
	the symbol was returned by string->symbol, the case of characters
	in the string returned will be the same as the case in the string 
	that was passed to string->symbol. It is an error to apply
	mutation procedures like string-set! to strings returned
	by this procedure.
*/
extern scm_obj *sym_symbol_to_string(const scm_obj *obj);

/*	procedure: (string->symbol)

	Returns the symbol whose name is string. This procedure
	can create symbols with names containing special charac-
	ters or letters in the non-standard case, but it is usually
	a bad idea to create such symbols because in some imple-
	mentations of Scheme they cannot be read as themselves.
*/
extern scm_obj *sym_string_to_symbol(const scm_obj *obj);

extern void scm_init_symbol();

#endif

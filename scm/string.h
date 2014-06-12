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

#ifndef _STRING_H
#define _STRING_H

#include "scm.h"

/*  procedure: (make-string k) or (make-string k char) 

	Make-string returns a newly allocated string of length k.
	If char is given, then all elements of the string are ini-
	tialized to char , otherwise the contents of the string are
	unspecified. But here we set them with '\0'.
*/
extern scm_obj *str_make_string(const scm_obj *obj);

/*  procedure: (string char ...)

	Returns a newly allocated string composed of the arguments.
*/
extern scm_obj *str_cons_string(const scm_obj *obj);

/*  procedure: (string-length string)

	Returns the number of characters in the given string.
*/
extern scm_obj *str_string_length(const scm_obj *obj);

/*  procedure: (string-ref string k)

	k must be a valid index of string. String-ref returns
	character k of string using zero-origin indexing.
*/
extern scm_obj *str_string_ref(const scm_obj *obj);


/*  procedure: (string-set! string k char)

	k must be a valid index of string. String-set! stores char
	in element k of string and returns an unspecified value.
*/
extern scm_obj *str_string_set(const scm_obj *obj);

/*  procedure: (string? obj )

	Returns #t if obj is a string, otherwise returns #f.
*/
extern scm_obj *str_pred_string(const scm_obj *obj);

/*  procedure: (string=? string1 string2)
	
	Returns #t if the two strings are the same length and con-
	tain the same characters in the same positions, otherwise
	returns #f.
*/
extern scm_obj *str_pred_string_eq(const scm_obj *obj);


/* 	procedure: (string<=? string1 string2)  */
extern scm_obj *str_pred_string_le(const scm_obj *obj);


/* 	procedure: (string<? string1 string2)  */
extern scm_obj *str_pred_string_lt(const scm_obj *obj);


/* 	procedure: (string>=? string1 string2)  */
extern scm_obj *str_pred_string_ge(const scm_obj *obj);

/* 	procedure: (string>? string1 string2)  */
extern scm_obj *str_pred_string_gt(const scm_obj *obj);

/* 	procedure: (string-ci=? string1 string2)

	String-ci=? treats upper and lower case let-
	ters as though they were the same character, but string=?
	treats upper and lower case as distinct characters.
*/
extern scm_obj *str_pred_string_ci_eq(const scm_obj *obj);

/* 	procedure: (string-ci<=? string1 string2)  */
extern scm_obj *str_pred_string_ci_le(const scm_obj *obj);

/* 	procedure: (string-ci<? string1 string2)  */
extern scm_obj *str_pred_string_ci_lt(const scm_obj *obj);

/* 	procedure: (string-ci>=? string1 string2)  */
extern scm_obj *str_pred_string_ci_ge(const scm_obj *obj);

/* 	procedure: (string-ci>? string1 string2)  */
extern scm_obj *str_pred_sring_ci_gt(const scm_obj *obj);

/* 	procedure: (substring start end)
	
	String must be a string, and start and end must be exact
	integers satisfying 0 ≤ start ≤ end ≤ (string-length string).
	Substring returns a newly allocated string formed from
	the characters of string beginning with index start (inclu-
	sive) and ending with index end (exclusive).
*/
extern scm_obj *str_substring(const scm_obj *obj);

/*  procedure: (string-append string ...)

	Returns a newly allocated string whose characters form the
	concatenation of the given strings.
*/
extern scm_obj *str_string_append(const scm_obj *obj);

/*  procedure: (string->list string)

	String->list returns a newly allocated list of the charac-
	ters that make up the given string.
*/	
extern scm_obj *str_string_to_list(const scm_obj *obj);

/* 	procedure: (list->string list)

	List->string returns a newly allocated string formed from the
	characters in the list list, which must be a list of characters.
*/	
extern scm_obj *str_list_to_string(const scm_obj *obj);

/* 	procedure: (string-copy string)

	Returns a newly allocated copy of the given string.
*/	
extern scm_obj *str_string_copy(const scm_obj *obj);

/* 	procedure: (string-fill! string char)

	Stores char in every element of the given string and returns
	an unspecified value.
*/
extern scm_obj *str_string_fill(const scm_obj *obj);

/*  This procedure is to initialize the part of string  */
extern void scm_init_string();

#endif


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

static scm_obj *create_str_obj(unsigned int len, char c)
{
	scm_obj *str_obj = scm_alloc_obj();
	char *p;
	
	type(str_obj) = STRING;
	slen(str_obj) = len;
	str(str_obj) = scm_alloc_str(len + 1);
	
	p = str(str_obj);
	for (unsigned int i = 0; i < len; ++i) {
		*(p++) = c;
	}	
	*p = '\0';
	
	return str_obj;
}

/*  procedure: (make-string k) or (make-string k char)  */
scm_obj *str_make_string(const scm_obj *obj)
{
	if (obj == scm_null) {
		error0("procedure: make-string\nexpected: 1 to 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != INTEGER) {
		error0("procedure: make-string\nexpected: exact-nonnegative-integer\nbad argument(s)", car(obj));
	} else if (fixnum(car(obj)) < 0) {
		error0("procedure: make-string\nexpected: exact-nonnegative-integer\nbad argument(s)", car(obj));
	} else if (cdr(obj) == scm_null) {
		return create_str_obj(fixnum(car(obj)), '\0');
	} else if (type(cadr(obj)) != CHAR) {
		error0("procedure: make-string\nexpected: char\nbad argument(s)", cadr(obj));
	} else if (cddr(obj) != scm_null) {
		error0("procedure: make-string\nexpected: 1 to 2 arguments\nbad argument(s)", obj);
	} else {
		return create_str_obj(fixnum(car(obj)), Char(cadr(obj)));
	}		
}

/*  procedure: (string char ...)  */
scm_obj *str_cons_string(const scm_obj *obj)
{
	scm_obj *str_obj;
	const scm_obj *q;
	unsigned int len = 0;
	char *p;
	
	for (scm_obj *p = obj; p != scm_null;) {
		if (type(car(p)) != CHAR) {
			error0("procedure: string\nexpected: char\nbad argument(s)", car(p));
		}
		p = cdr(p), ++len;
	}
	
	str_obj = scm_alloc_obj();
	
	type(str_obj) = STRING;
	slen(str_obj) = len;
	str(str_obj) = scm_alloc_str(len + 1);
	
	p = str(str_obj);
	q = obj;
	for (unsigned int i = 0; i < len;) {
	     p[i] = Char(car(q));
	     q = cdr(q), ++i;
	}
	
	return str_obj;
}

/*  procedure: (string-length string)  */
inline scm_obj *str_string_length(const scm_obj *obj)
{
	if (type(car(obj)) != STRING) {
		error0("procedure: string-length\nexpected: string\nbad argument(s)", obj);
	} else {
		return make_integer(slen(car(obj)));
	}
}	

/*  procedure: (string-ref string k)  */
scm_obj *str_string_ref(const scm_obj *obj)
{
	if (type(car(obj)) != STRING) {
		error0("procedure: string-ref\nexpected: string\nbad argument(s)", obj);
	} else if (cdr(obj) == scm_null) {
		error0("procedure: string-ref\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(cadr(obj)) != INTEGER || fixnum(cadr(obj))
			   < 0 || fixnum(cadr(obj)) >= slen(obj)) {
		error0("procedure: string-ref\nexpected: a valid index of string\nbad argument(s)", obj);
	} else if (cddr(obj) != scm_null) {
		error0("procedure: string-ref\nexpected: 2 arguments\nbad argument(s)", obj);
	} else {
		return make_char((str(car(obj)))[fixnum(cadr(obj))]);
	}
}

/*  procedure: (string-set! string k char)  */
scm_obj *str_string_set(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj)
	    == scm_null || cdddr(obj) != scm_null) {
		error0("procedure: string-set!\nexpected: 3 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != STRING) {
		error0("procedure: string-set!\nexpected: string\nbad argument(s)", car(obj));
	} else if (type(cadr(obj)) != INTEGER) {
		error0("procedure: string-set!\nexpected: nonnegative integer\nbad argument(s)", cadr(obj)); 
	} else if (fixnum(cadr(obj)) < 0 || fixnum(cadr(obj)) >= slen(car(obj))) {
		error0("procedure: string-set!\nexpected: a valid index of string\nbad argument(s)", cadr(obj));
	} else if (type(caddr(obj)) != CHAR) {
		error0("procedure: string-set!\nexpected: char\nbad argument(s)", caddr(obj));
	} else {
		(str(car(obj)))[fixnum(cadr(obj))] = Char(caddr(obj));
	}
	
	return scm_unspecified;
}

/*  procedure: (string? obj )  */
inline scm_obj *str_pred_string(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: string?\nexpected: 1 argument\nbad argument(s)", obj);
	} else {
		return type(car(obj)) == STRING ? scm_true : scm_false;
	}
} 

/*  procedure: (string=? string1 string2)  */
inline scm_obj *str_pred_string_eq(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: string=?\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != STRING || type(cadr(obj)) != STRING) {
		error0("procedure: string=?\nexpected: string\nbad argument(s)", obj);
	} else {
		return strcmp(str(car(obj)), str(cadr(obj))) == 0 ? scm_true : scm_false;
	}
}

/*  procedure: (string<=? string1 string2)  */
inline scm_obj *str_pred_string_le(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: string<=?\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != STRING || type(cadr(obj)) != STRING) {
		error0("procedure: string<=?\nexpected: string\nbad argument(s)", obj);
	} else {
		return strcmp(str(car(obj)), str(cadr(obj))) <= 0 ? scm_true : scm_false;
	}
}

/*  procedure: (string<? string1 string2)  */
inline scm_obj *str_pred_string_lt(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: string<?\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != STRING || type(cadr(obj)) != STRING) {
		error0("procedure: string<?\nexpected: string\nbad argument(s)", obj);
	} else {
		return strcmp(str(car(obj)), str(cadr(obj))) < 0 ? scm_true : scm_false;
	}
}

/*  procedure: (string>=? string1 string2)  */
inline scm_obj *str_pred_string_ge(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: string>=?\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != STRING || type(cadr(obj)) != STRING) {
		error0("procedure: string>=?\nexpected: string\nbad argument(s)", obj);
	} else {
		return strcmp(str(car(obj)), str(cadr(obj))) >= 0 ? scm_true : scm_false;
	}
}

/*  procedure: (string>? string1 string2)  */
inline scm_obj *str_pred_string_gt(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: string>?\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != STRING || type(cadr(obj)) != STRING) {
		error0("procedure: string>?\nexpected: string\nbad argument(s)", obj);
	} else {
		return strcmp(str(car(obj)), str(cadr(obj))) > 0 ? scm_true : scm_false;
	}
}

static scm_obj *upper_to_lower(const scm_obj *obj)
{
	scm_obj *str_obj;
	char *q;
	
	str_obj = scm_alloc_obj();
	type(str_obj) = STRING;
	slen(str_obj) = slen(obj);
	str(str_obj) = scm_alloc_str(slen(obj) + 1);
	q = str(str_obj);
	for (char *p = str(obj); *p != '\0'; ++p, ++q) {
		if (*p >= 'A' && *p <= 'Z') {
			*q = *p + 'a' - 'A';
		} else {
			*q = *p;
		}	
	}
	*q = '\0';
	return str_obj;
}

/*  procedure: (string-ci=? string1 string2)  */
scm_obj *str_pred_string_ci_eq(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: string-ci=?\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != STRING || type(cadr(obj)) != STRING) {
		error0("procedure: string-ci=?\nexpected: string\nbad argument(s)", obj);
	} else {
		scm_obj *p = upper_to_lower(car(obj));
		scm_obj *q = upper_to_lower(cadr(obj));
		
		return strcmp(str(p), str(q)) == 0 ? scm_true : scm_false;
	}
}

/*  procedure: (string-ci<=? string1 string2)  */
scm_obj *str_pred_string_ci_le(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: string-ci<=?\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != STRING || type(cadr(obj)) != STRING) {
		error0("procedure: string-ci<=?\nexpected: string\nbad argument(s)", obj);
	} else {
		scm_obj *p = upper_to_lower(car(obj));
		scm_obj *q = upper_to_lower(cadr(obj));
		
		return strcmp(str(p), str(q)) <= 0 ? scm_true : scm_false;
	}
}	

/*  procedure: (string-ci<? string1 string2)  */
scm_obj *str_pred_string_ci_lt(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: string-ci<?\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != STRING || type(cadr(obj)) != STRING) {
		error0("procedure: string-ci<?\nexpected: string\nbad argument(s)", obj);
	} else {
		scm_obj *p = upper_to_lower(car(obj));
		scm_obj *q = upper_to_lower(cadr(obj));
		
		return strcmp(str(p), str(q)) < 0 ? scm_true : scm_false;
	}
}

/*  procedure: (string-ci>=? string1 string2)  */
scm_obj *str_pred_string_ci_ge(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: string-ci>=?\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != STRING || type(cadr(obj)) != STRING) {
		error0("procedure: string-ci>+?\nexpected: string\nbad argument(s)", obj);
	} else {
		scm_obj *p = upper_to_lower(car(obj));
		scm_obj *q = upper_to_lower(cadr(obj));
		
		return strcmp(str(p), str(q)) >= 0 ? scm_true : scm_false;
	}
}

/*  procedure: (string-ci>? string1 string2)  */
scm_obj *str_pred_string_ci_gt(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: string-ci>?expected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != STRING || type(cadr(obj)) != STRING) {
		error0("procedure: string-ci>?expected: string\nbad argument(s)", obj);
	} else {
		scm_obj *p = upper_to_lower(car(obj));
		scm_obj *q = upper_to_lower(cadr(obj));
		
		return strcmp(str(p), str(q)) > 0 ? scm_true : scm_false;
	}
}

/* 	procedure: (substring start end)  */
scm_obj *str_substring(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj)
		== scm_null || cdddr(obj) != scm_null) {
		error0("procedure: substring\nexpected: 3 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != STRING) {
		error0("procedure: substring\nexpected: string\nbad argument(s)", car(obj));
	} else if (type(cadr(obj)) != INTEGER ||
			   type(caddr(obj)) != INTEGER ||
			   fixnum(cadr(obj)) < 0 || fixnum(cadr(obj)) > slen(car(obj)) ||
			   fixnum(caddr(obj)) < 0 || fixnum(caddr(obj)) > slen(car(obj))) {
		error0("procedure: substring\nexpected: a valid index of string\nbad argument(s)", obj);
	} else {
		int len = fixnum(caddr(obj)) - fixnum(cadr(obj));
		if (len < 0) {
			error0("procedure: substring\nexpected: ending index is smaller than starting"
			      "index\nbad argument(s)", obj);
		}
					
		scm_obj *str_obj = scm_alloc_obj();
		
		type(str_obj) = STRING;
		slen(str_obj) = len;
		str(str_obj) = scm_alloc_str(len + 1);
		strncpy(str(str_obj), str(car(obj)) + fixnum(cadr(obj)), len);
		*(str(str_obj) + len) = '\0';
		return str_obj;
	}
}

/*  procedure: (string-append string ...)  */
scm_obj *str_string_append(const scm_obj *obj)
{
	const scm_obj *p = obj;
	scm_obj *str_obj;
	unsigned int len = 0;
	char *q;
	
	for (; p != scm_null; p = cdr(p)) {
		if (type(car(p)) != STRING) {
			error0("procedure: string-append\nexpected: string\nbad argument(s)", obj);
		}
		len += slen(car(p));
	}
	
	str_obj = scm_alloc_obj();
	
	type(str_obj) = STRING;
	slen(str_obj) = len;
	str(str_obj) = scm_alloc_str(len + 1);
	
	for (q = str(str_obj), p = obj; p != scm_null;) {
		strcpy(q, str(car(p)));
		q += slen(car(p));
		p = cdr(p);
	}
	*q = '\0';
	
	return str_obj;
}

/* 	procedure: (list->string list)  */
scm_obj *str_list_to_string(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: list->string\nexpected: 1 argument\nbad argument(s)", obj);
	} else {
		const scm_obj *p = car(obj);
		unsigned int len = 0;
		
		while (p != scm_null && type(p) == PAIR) {
			if (type(car(p)) != CHAR) {
				error0("procedure: list->string\nexpected: list of char\nbad argument(s)", obj);
			}
			p = cdr(p), ++len;
		}
		
		if (p != scm_null) {
			error0("procedure: list->string\nexpected: list of char\nbad argument(s)", obj);
		} else {
			scm_obj *str_obj = scm_alloc_obj();
			
			type(str_obj) = STRING;
			slen(str_obj) = len;
			str(str_obj) = scm_alloc_str(len + 1);
			
			for (len = 0, p = car(obj); p != scm_null; p = cdr(p)) {
				(str(str_obj))[len++] = Char(car(p));
			}
			
			return str_obj;
		}
	}
}

/* 	procedure: (string-copy string)  */
scm_obj *str_string_copy(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: string-copy\nexpected: 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != STRING) {
		error0("procedure: string-copy\nexpected: string\nbad argument(s)", car(obj));
	} else {
		unsigned int len = slen(car(obj));
		scm_obj *str_obj = scm_alloc_obj();
		
		type(str_obj) = STRING;
		slen(str_obj) = len;
		str(str_obj) = scm_alloc_str(len + 1);
		strcpy(str(str_obj), str(car(obj)));
				
		return str_obj;
	}
}

/* 	procedure: (string-fill! string char)  */		
scm_obj *str_string_fill(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: string-fill!\nexpected: 2 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != STRING) {
		error0("procedure: string-fill!\nexpected: string\nbad argument(s)", car(obj));
	} else if (type(cadr(obj)) != CHAR) {
		error0("procedure: string-fill!\nexpected: char\nbad argument(s)", cadr(obj));
	} else {
		char *p = str(car(obj));
		const char c = Char(cadr(obj));
		
		for (unsigned int i = 0, len = slen(car(obj)); 
			 i < len; i++) {
			 p[i] = c;
		}		
		return scm_unspecified;
	}
}

void scm_init_string()
{
	scm_add_prim("string?", str_pred_string);
	scm_add_prim("make-string", str_make_string);
	scm_add_prim("string", str_cons_string);
	scm_add_prim("string-length", str_string_length);
	scm_add_prim("string-ref", str_string_ref);
	scm_add_prim("string-set!", str_string_set);
	scm_add_prim("string=?", str_pred_string_eq);	
	scm_add_prim("string<?", str_pred_string_lt);
	scm_add_prim("string>?", str_pred_string_gt);
	scm_add_prim("string<=?", str_pred_string_le);
	scm_add_prim("string>=?", str_pred_string_ge);
	scm_add_prim("string-ci=?", str_pred_string_ci_eq);
	scm_add_prim("string-ci<?", str_pred_string_ci_lt);
	scm_add_prim("string-ci>?", str_pred_string_ci_gt);
	scm_add_prim("string-ci<=?", str_pred_string_ci_le);
	scm_add_prim("string-ci>=?", str_pred_string_ci_ge);
	scm_add_prim("substring", str_substring);
	scm_add_prim("string-append", str_string_append);
	scm_add_prim("list->string", str_list_to_string);
	scm_add_prim("string-copy", str_string_copy);
	scm_add_prim("string-fill!", str_string_fill);
}

			








																		 
		

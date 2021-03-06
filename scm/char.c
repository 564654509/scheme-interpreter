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

scm_obj *char_pred_char(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: char?\nexpected: 1 argument\nbad argument(s)", obj);
	} else {
		return type(car(obj)) == CHAR ? scm_true : scm_false;
	}
}

scm_obj *char_pred_char_eq(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: char=?\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != CHAR) {
		error0("procedure: char=?\nexpected: char\nbad argument(s)", car(obj));
	} else if (type(cadr(obj)) != CHAR) {
		error0("procedure: char=?\nexpected: char\nbad argument(s)", cadr(obj));
	} else {
		return Char(car(obj)) == Char(cadr(obj)) ? scm_true : scm_false;
	}
}

scm_obj *char_pred_char_le(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: char<=?\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != CHAR) {
		error0("procedure: char<=?\nexpected: char\nbad argument(s)", car(obj));
	} else if (type(cadr(obj)) != CHAR) {
		error0("procedure: char<=?\nexpected: char\nbad argument(s)", cadr(obj));
	} else {
		return Char(car(obj)) <= Char(cadr(obj)) ? scm_true : scm_false;
	}
}

scm_obj *char_pred_char_lt(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: char<?\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != CHAR) {
		error0("procedure: char<?\nexpected: char\nbad argument(s)", car(obj));
	} else if (type(cadr(obj)) != CHAR) {
		error0("procedure: char<?\nexpected: char\nbad argument(s)", cadr(obj));
	} else {
		return Char(car(obj)) < Char(cadr(obj)) ? scm_true : scm_false;
	}
}

scm_obj *char_pred_char_ge(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: char>=?\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != CHAR) {
		error0("procedure: char>=?\nexpected: char\nbad argument(s)", car(obj));
	} else if (type(cadr(obj)) != CHAR) {
		error0("procedure: char>=?\nexpected: char\nbad argument(s)", cadr(obj));
	} else {
		return Char(car(obj)) >= Char(cadr(obj)) ? scm_true : scm_false;
	}
}

scm_obj *char_pred_char_gt(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: char>?\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != CHAR) {
		error0("procedure: char>?\nexpected: char\nbad argument(s)", car(obj));
	} else if (type(cadr(obj)) != CHAR) {
		error0("procedure: char>?\nexpected: char\nbad argument(s)", cadr(obj));
	} else {
		return Char(car(obj)) > Char(cadr(obj)) ? scm_true : scm_false;
	}
}

scm_obj *char_pred_char_ci_eq(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: char-ci=?\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != CHAR) {
		error0("procedure: char-ci=?\nexpected: char\nbad argument(s)", car(obj));
	} else if (type(cadr(obj)) != CHAR) {
		error0("procedure: char-ci=?\nexpected: char\nbad argument(s)", cadr(obj));
	} else {
		return toupper(Char(car(obj))) == toupper(Char(cadr(obj))) ? scm_true : scm_false;
	}
}

scm_obj *char_pred_char_ci_le(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: char-ci<=?\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != CHAR) {
		error0("procedure: char-ci<=?\nexpected: char\nbad argument(s)", car(obj));
	} else if (type(cadr(obj)) != CHAR) {
		error0("procedure: char-ci<=?\nexpected: char\nbad argument(s)", cadr(obj));
	} else {
		return toupper(Char(car(obj))) <= toupper(Char(cadr(obj))) ? scm_true : scm_false;
	}
}

scm_obj *char_pred_char_ci_lt(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: char-ci<?\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != CHAR) {
		error0("procedure: char-ci<?\nexpected: char\nbad argument(s)", car(obj));
	} else if (type(cadr(obj)) != CHAR) {
		error0("procedure: char-ci<?\nexpected: char\nbad argument(s)", cadr(obj));
	} else {
		return toupper(Char(car(obj))) < toupper(Char(cadr(obj))) ? scm_true : scm_false;
	}
}

scm_obj *char_pred_char_ci_ge(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: char-ci>=?\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != CHAR) {
		error0("procedure: char-ci>=?\nexpected: char\nbad argument(s)", car(obj));
	} else if (type(cadr(obj)) != CHAR) {
		error0("procedure: char-ci>=?\nexpected: char\nbad argument(s)", cadr(obj));
	} else {
		return toupper(Char(car(obj))) >= toupper(Char(cadr(obj))) ? scm_true : scm_false;
	}
}

scm_obj *char_pred_char_ci_gt(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: char-ci>?\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != CHAR) {
		error0("procedure: char-ci>?\nexpected: char\nbad argument(s)", car(obj));
	} else if (type(cadr(obj)) != CHAR) {
		error0("procedure: char-ci>?\nexpected: char\nbad argument(s)", cadr(obj));
	} else {
		return toupper(Char(car(obj))) > toupper(Char(cadr(obj))) ? scm_true : scm_false;
	}
}

scm_obj *char_pred_char_alphabetic(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: char-alphabetic?\nexpected: 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != CHAR) {
		error0("procedure: char-alphabetic?\nexpected: char\nbad argument(s)", car(obj));
	} else {
		return isalpha(Char(car(obj))) ? scm_true : scm_false;
    }
}

scm_obj *char_pred_char_numeric(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: char-numeric?\nexpected: 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != CHAR) {
		error0("procedure: char-numeric?\nexpected: char\nbad argument(s)", car(obj));
	} else {
		return isdigit(Char(car(obj))) ? scm_true : scm_false;
    }
}

scm_obj *char_pred_char_whitespace(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: char-whitespace?\nexpected: 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != CHAR) {
		error0("procedure: char-whitespace?\nexpected: char\nbad argument(s)", car(obj));
	} else {
		return Char(car(obj)) == ' ' || Char(car(obj)) == '\t' ||
		       Char(car(obj)) == '\r' || Char(car(obj)) == '\b' ||
		       Char(car(obj)) == '\f' ? scm_true : scm_false;
    }
}

scm_obj *char_pred_char_upper_case(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: char-upper-case?\nexpected: 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != CHAR) {
		error0("procedure: char-upper-case?\nexpected: char\nbad argument(s)", car(obj));
	} else {
		return isupper(Char(car(obj))) ? scm_true : scm_false;
    }
}

scm_obj *char_pred_char_lower_case(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: char-lower-case?\nexpected: 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != CHAR) {
		error0("procedure: char-lower-case?\nexpected: char\nbad argument(s)", car(obj));
	} else {
		return islower(Char(car(obj))) ? scm_true : scm_false;
    }
}

scm_obj *char_char_to_integer(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: char->integer\nexpected: 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != CHAR) {
		error0("procedure: char->integer\nexpected: char\nbad argument(s)", car(obj));
	} else {
		scm_obj *int_obj = scm_alloc_obj();
		type(int_obj) = INTEGER;
		fixnum(int_obj) = Char(car(obj));
		
		return int_obj;
	}
}

scm_obj *char_integer_to_char(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: integer->char\nexpected: 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != INTEGER) {
		error0("procedure: integer->char\nexpected: integer\nbad argument(s)", car(obj));
	} else {		
		if (fixnum(car(obj)) > 255 || fixnum(car(obj)) < 0) {
			error0("procedure: integer->char\nexpected: integer between 0 to 255\nbad argument(s)", car(obj));
		} else {
			scm_obj *char_obj = scm_alloc_obj();
			type(char_obj) = CHAR;
			Char(char_obj) = fixnum(car(obj));
		
			return char_obj;
		}
	}
}

scm_obj *char_char_upcase(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: char-upcase\nexpected: 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != CHAR) {
		error0("procedure: char-upcase\nexpected: char\nbad argument(s)", car(obj));
	} else {
		scm_obj *char_obj = scm_alloc_obj();
		type(char_obj) = CHAR;
		Char(char_obj) = toupper(Char(car(obj)));
		
		return char_obj;
	}
}

scm_obj *char_char_downcase(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: char-downcase\nexpected: 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != CHAR) {
		error0("procedure: char-downcase\nexpected: char\nbad argument(s)", car(obj));
	} else {
		scm_obj *char_obj = scm_alloc_obj();
		type(char_obj) = CHAR;
		Char(char_obj) = tolower(Char(car(obj)));
		
		return char_obj;
	}
}

void scm_init_char()
{
	scm_add_prim("char?", char_pred_char);
	scm_add_prim("char=?", char_pred_char_eq);
	scm_add_prim("char<=?", char_pred_char_le);
	scm_add_prim("char<?", char_pred_char_lt);
	scm_add_prim("char>=?", char_pred_char_ge);
	scm_add_prim("char>?", char_pred_char_gt);
	scm_add_prim("char-ci=?", char_pred_char_ci_eq);
	scm_add_prim("char-ci<=?", char_pred_char_ci_le);
	scm_add_prim("char-ci<?", char_pred_char_ci_lt);
	scm_add_prim("char-ci>=?", char_pred_char_ci_ge);
	scm_add_prim("char-ci>?", char_pred_char_ci_gt);
	scm_add_prim("char-alphabetic?", char_pred_char_alphabetic);
	scm_add_prim("char-numeric?", char_pred_char_numeric);
	scm_add_prim("char-whitespace?", char_pred_char_whitespace);
	scm_add_prim("char-upper-case?", char_pred_char_upper_case);
	scm_add_prim("char-lower-case?", char_pred_char_lower_case);
	scm_add_prim("char->integer", char_char_to_integer);
	scm_add_prim("integer->char", char_integer_to_char);
	scm_add_prim("char-upcase", char_char_upcase);
	scm_add_prim("char-downcase", char_char_downcase);
}

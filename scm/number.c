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

scm_obj *num_add(const scm_obj *obj)
{
	long long res = 0;
	
	while (obj != scm_null) {
		if (type(car(obj)) != INTEGER) {
			error0("procedure: +\nexpected: integer\nbad argument(s)", car(obj));
		} else {
			res += fixnum(car(obj));
			obj = cdr(obj);
		}
	}
	return make_integer(res);
}
		
scm_obj *num_sub(const scm_obj *obj)
{
	long long res = 0;
	
	if (obj == scm_null) {
		error0("procedure: -\nexpected: at least 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != INTEGER) {
		error0("procedure: -\nexpected: integer\nbad argument(s)", car(obj));
	} else {
		res = fixnum(car(obj));
		obj = cdr(obj);
		if (obj == scm_null) {
			return make_integer(-res);
		}
	}
	
	while (obj != scm_null) {
		if (type(car(obj)) != INTEGER) {
			error0("procedure: -\nexpected: integer\nbad argument(s)", car(obj));
		} else {
			res -= fixnum(car(obj));
			obj = cdr(obj);
		}
	}
	
	return make_integer(res);
}

scm_obj *num_mul(const scm_obj *obj)
{
	long long res = 1;
	
	while (obj != scm_null) {
		if (type(car(obj)) != INTEGER) {
			error0("procedure: *\nexpected: integer\nbad argument(s)", car(obj));
		} else {
			res *= fixnum(car(obj));
			obj = cdr(obj);
		}
	}
	
	return make_integer(res);
}

scm_obj *num_div(const scm_obj *obj)
{
	long long res = 0;
	
	if (obj == scm_null) {
		error0("procedure: /\nexpected: at least 1 argument\nbad argument(s)", car(obj));
	} else if (type(car(obj)) != INTEGER) {
		error0("procedure: /\nexpected: integer\nbad argument(s)", car(obj))
	} else {
		res = fixnum(car(obj));
		obj = cdr(obj);
	}
	
	while (obj != scm_null) {
		if (type(car(obj)) != INTEGER) {
			error0("procedure: /\nexpected: integer\nbad argument(s)", car(obj));
		} else if (fixnum(car(obj)) == 0) {
			error0("procedure: -\ndivision by zero\nbad argument(s)", car(obj));
		} else {
			res /= fixnum(car(obj));
			obj = cdr(obj);
		}
	}
	
	return make_integer(res);
}

scm_obj *num_mod(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: modulo\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != INTEGER) {
		error0("procedure: modulo\nexpected: integer\nbad argument(s)", car(obj));
	} else if (type(cadr(obj)) != INTEGER) {
		error0("procedure: modulo\nexpected: integer\nbad argument(s)", cadr(obj));
	} else if (fixnum(cadr(obj)) == 0) {
		error0("procedure: modulo\nsecond argument is zero\nbad argument(s)", cadr(obj));
	} else {
		long long res = fixnum(car(obj)) % fixnum(cadr(obj));
			
		if (fixnum(car(obj)) < 0 && fixnum(cadr(obj)) > 0) {
			if (res < 0) {
				res += fixnum(cadr(obj));
			}
		} else if (fixnum(car(obj)) > 0 && fixnum(cadr(obj)) < 0) {
			if (res > 0) {
				res += fixnum(cadr(obj));
			}
		}	
		
		return make_integer(res);
	}
}

scm_obj *num_eq(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: =\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != INTEGER) {
		error0("procedure: =\nexpected: integer\nbad argument(s)", car(obj));
	} else if (type(cadr(obj)) != INTEGER) {
		error0("procedure: =\nexpected: integer\nbad argument(s)", cadr(obj));
	} else {
		return fixnum(car(obj)) == fixnum(cadr(obj)) ? scm_true : scm_false;
	}
}

scm_obj *num_le(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: <=\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != INTEGER) {
		error0("procedure: <=\nexpected: integer\nbad argument(s)", car(obj));
	} else if (type(cadr(obj)) != INTEGER) {
		error0("procedure: <=\nexpected: integer\nbad argument(s)", cadr(obj));
	} else {
		return fixnum(car(obj)) <= fixnum(cadr(obj)) ? scm_true : scm_false;
	}
}

scm_obj *num_lt(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: <\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != INTEGER) {
		error0("procedure: <\nexpected: integer\nbad argument(s)", car(obj));
	} else if (type(cadr(obj)) != INTEGER) {
		error0("procedure: <\nexpected: integer\nbad argument(s)", cadr(obj));
	} else {
		return fixnum(car(obj)) < fixnum(cadr(obj)) ? scm_true : scm_false;
	}
}

scm_obj *num_ge(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: >=\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != INTEGER) {
		error0("procedure: >=\nexpected: integer\nbad argument(s)", car(obj));
	} else if (type(cadr(obj)) != INTEGER) {
		error0("procedure: >=\nexpected: integer\nbad argument(s)", cadr(obj));
	} else {
		return fixnum(car(obj)) >= fixnum(cadr(obj)) ? scm_true : scm_false;
	}
}

scm_obj *num_gt(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: >\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != INTEGER) {
		error0("procedure: >\nexpected: integer\nbad argument(s)", car(obj));
	} else if (type(cadr(obj)) != INTEGER) {
		error0("procedure: >\nexpected: integer\nbad argument(s)", cadr(obj));
	} else {
		return fixnum(car(obj)) > fixnum(cadr(obj)) ? scm_true : scm_false;
	}
}

scm_obj *num_abs(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: abs\nexpected: 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != INTEGER) {
		error0("procedure: abs\nexpected: integer\nbad argument(s)", car(obj));
	} else {
		long long num = fixnum(car(obj));
		num = num > 0 ? num : -num;
		return make_integer(num);
	}
}

scm_obj *num_max(const scm_obj *obj)
{
	if (obj == scm_null) {
		error0("procedure: max\nexpected: at least 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != INTEGER) {
		error0("procedure: max\nexpected: integer\nbad argument(s)", car(obj));
	} else {
		const scm_obj *p = cdr(obj);
		long long max = fixnum(car(obj));
		
		for (; p != scm_null; p = cdr(p)) {
			if (type(car(p)) != INTEGER) {
				error0("procedure: max\nexpected: integer\nbad argument(s)", car(p));
			}
			if (fixnum(car(p)) > max) {
				max = fixnum(car(p));
			}
		}	
		return make_integer(max);
	}
}


scm_obj *num_min(const scm_obj *obj)
{
	if (obj == scm_null) {
		error0("procedure: min\nexpected: at least 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != INTEGER) {
		error0("procedure: min\nexpected: integer\nbad argument(s)", car(obj));
	} else {
		const scm_obj *p = cdr(obj);
		long long min = fixnum(car(obj));
		
		for (; p != scm_null; p = cdr(p)) {
			if (type(car(p)) != INTEGER) {
				error0("procedure: min\nexpected: integer\nbad argument(s)", car(p));
			}
			if (fixnum(car(p)) < min) {
				min = fixnum(car(p));
			}
		}	
		return make_integer(min);
	}
}

scm_obj *num_number_to_string(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: number->string\nexpected: 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != INTEGER) {
		error0("procedure: number->string\nexpected: integer\nbad argument(s)", car(obj));
	} else {
		char buf[256];
		sprintf(buf, "%lld", fixnum(car(obj)));
		return make_string(&buf);
	}
}

scm_obj *num_remainder(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: remainder\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != INTEGER) {
		error0("procedure: remainder\nexpected: integer\nbad argument(s)", car(obj));
	} else if (type(cadr(obj)) != INTEGER) {
		error0("procedure: remainder\nexpected: integer\nbad argument(s)", cadr(obj));
	} else if (fixnum(cadr(obj)) == 0) {
		error0("procedure: remainder\nsecond argument is zero\nbad argument(s)", cadr(obj));
	} else {
		return make_integer(fixnum(car(obj)) % fixnum(cadr(obj)));
	}
}

scm_obj *num_quotient(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) == scm_null || cddr(obj) != scm_null) {
		error0("procedure: quotient\nexpected: 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != INTEGER) {
		error0("procedure: quotient\nexpected: integer\nbad argument(s)", car(obj));
	} else if (type(cadr(obj)) != INTEGER) {
		error0("procedure: quotient\nexpected: integer\nbad argument(s)", cadr(obj));
	} else if (fixnum(cadr(obj)) == 0) {
		error0("procedure: quotient\nsecond argument is zero\nbad argument(s)", cadr(obj));
	} else {
		return make_integer(fixnum(car(obj)) / fixnum(cadr(obj)));
	}
}
	
scm_obj *num_pred_even(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: even?\nexpected: 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != INTEGER) {
		error0("procedure: even?\nexpected: integer\nbad argument(s)", car(obj));
	} else {
		return fixnum(car(obj)) % 2 == 0 ? scm_true : scm_false;
	}
}

scm_obj *num_pred_integer(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: number?\nexpected: 1 argument\nbad argument(s)", obj);
	} else {
		return type(car(obj)) == INTEGER ? scm_true : scm_false;
	}
}

scm_obj *num_pred_negative(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: negative?\nexpected: 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != INTEGER) {
		error0("procedure: negative?\nexpected: integer\nbad argument(s)", car(obj));
	} else {
		return fixnum(car(obj)) < 0 ? scm_true : scm_false;
	}
}

scm_obj *num_pred_number(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: number?\nexpected: 1 argument\nbad argument(s)", obj);
	} else {
		return type(car(obj)) == INTEGER ? scm_true : scm_false;
	}
}

scm_obj *num_pred_positive(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: positive?\nexpected: 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != INTEGER) {
		error0("procedure: positive?\nexpected: integer\nbad argument(s)", car(obj));
	} else {
		return fixnum(car(obj)) > 0 ? scm_true : scm_false;
	}
}

scm_obj *num_pred_odd(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: odd?\nexpected: 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != INTEGER) {
		error0("procedure: odd?\nexpected: integer\nbad argument(s)", car(obj));
	} else {
		return fixnum(car(obj)) % 2 != 0 ? scm_true : scm_false;
	}
}

scm_obj *num_pred_zero(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: zero?\nexpected: 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != INTEGER) {
		error0("procedure: zero?\nexpected: integer\nbad argument(s)", car(obj));
	} else {
		return fixnum(car(obj)) == 0 ? scm_true : scm_false;
	}
}

void scm_init_number()
{
	scm_add_prim("+", num_add);
	scm_add_prim("-", num_sub);
	scm_add_prim("*", num_mul);
	scm_add_prim("/", num_div);
	scm_add_prim("=", num_eq);
	scm_add_prim("<=", num_le);
	scm_add_prim("<", num_lt);
	scm_add_prim(">=", num_ge);
	scm_add_prim(">", num_gt);
	scm_add_prim("abs", num_abs);
	scm_add_prim("max", num_max);
	scm_add_prim("min", num_min);
	scm_add_prim("modulo", num_mod);
	scm_add_prim("number->string", num_number_to_string);
	scm_add_prim("quotient", num_quotient);
	scm_add_prim("remainder", num_remainder);
	scm_add_prim("even?", num_pred_even);
	scm_add_prim("integer?", num_pred_integer);
	scm_add_prim("negative?", num_pred_negative);
	scm_add_prim("number?", num_pred_number);
	scm_add_prim("odd?", num_pred_odd);
	scm_add_prim("positive?", num_pred_positive);
	scm_add_prim("zero?", num_pred_zero);
}
	

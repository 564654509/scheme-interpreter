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

#define MAX_SYM_LEN 1024
#define MAX_NUM_LEN 1024
#define MAX_STR_LEN 1024

/*	reads binary number : e.g #b10, #b-111  */
static scm_obj *read_bin_num(FILE *fp);

/*	reads char const : e.g #\a, #\space	 */
static scm_obj *read_char(FILE *fp);

/*  reads false const : e.g #f  */
static scm_obj *read_false(FILE *fp);

/*	reads list : e.g (1 2 3 4)  */
static scm_obj *read_list(FILE *fp);

/*	reads hex number : e.g #x4, #xab  */
static scm_obj *read_hex_num(FILE *fp);

/*	reads a number or a symbol : e.g 345, 8ab  */
static scm_obj *read_num_or_sym(FILE *fp);

/*	reads octal number : e.g #o75  */
static scm_obj *read_oct_num(FILE *fp);

/*	reads the contents following '`'  */
static scm_obj *read_quasiquote(FILE *fp);

/*  reads the contents following '\''  */
static scm_obj *read_quote(FILE *fp); 

/*	reads s expression : e.g #(1 2 3), "hello"  */
static scm_obj *read_sexp(FILE *fp);

/*  reads string constant : e.g "123"  */
static scm_obj *read_string(FILE *fp);

/*  reads a symbol : e.g fib, map  */
static scm_obj *read_symbol(FILE *fp);

/*  reads true constant : e.g #t  */
static scm_obj *read_true(FILE *fp);

/*  reads the contents following ','  */
static scm_obj *read_unquote(FILE *fp);

/*  reads the contents following ',@"  */
static scm_obj *read_unquote_splicing(FILE *fp);

/*  reads vector : e.g #(1 2 3 4 5)  */
static scm_obj *read_vector(FILE *fp);


static char peek_char(FILE *fp)
{
	char ch = getc(fp);
	ungetc(ch, fp);
	return ch;
}

static char double_peek_char(FILE *fp)
{
	char ch1, ch2;
	
	ch1 = getc(fp);
	ch2 = getc(fp);
	ungetc(ch2, fp);
	ungetc(ch1, fp);
	
	return ch2;
}

static void skip_space_comment(FILE *fp)
{
	char ch;
	
	while (1) {
		while (isspace(ch = getc(fp)))
			;
		if (ch == ';') {
			while ((ch = getc(fp)) != '\n')
				;
		} else {
			ungetc(ch, fp);
			break;
		}
	}
}

scm_obj *in_read(const scm_obj *obj)
{
	FILE *fp;
	
	if (obj == scm_null) {
		fp = port(scm_cur_input_port);
	} else if (cdr(obj) != scm_null) {
		error0("procedure: read\nexpected: 0 to 1 argument\nbad argument(s)", obj);
	} else {
		if (type(car(obj)) != INPORT) {
			error0("procedure: read\nexpected: input-port\nbad argument(s)", car(obj));
		} else {
			fp = port(car(obj));
		}
	}
	
	return read_sexp(fp);
}

scm_obj *in_read_char(const scm_obj *obj)
{
	char ch;
	FILE *fp;
	
	if (obj == scm_null) {
		fp = port(scm_cur_input_port);
	} else if (cdr(obj) != scm_null) {
		error0("procedure: read-char\nexpected: 0 to 1 argument\nbad argument(s)", obj);
	} else {
		if (type(car(obj)) != INPORT) {
			error0("procedure: read-char\nexpected: input-port\nbad argument(s)", obj);
		} else {
			fp = port(car(obj));
		}
	}
	
	ch = getc(fp);
	if (ch == EOF) {
		return scm_eof;
	} else if (ch == '#' && peek_char(fp) == '\\'){
		getc(fp);
		return read_char(fp);
	} else {
		return make_char(ch);
	}
}

scm_obj *in_peek_char(const scm_obj *obj)
{
	char ch;
	FILE *fp;
	
	if (obj == scm_null) {
		fp = port(scm_cur_input_port);
	} else if (cdr(obj) != scm_null) {
		error0("procedure: peek-char\nexpected: 0 to 1 argument\nbad argument(s)", obj);
	} else {
		if (type(car(obj)) != INPORT) {
			error0("procedure: peek-char\nexpected: input-port\nbad argument(s)", obj);
		} else {
			fp = port(car(obj));
		}
	}
	
	ch = getc(fp);
	
	if (ch == EOF) {
		ungetc(ch, fp);
		return scm_eof;
	} else if (ch == '#' && peek_char(fp) == '\\'){
		getc(fp);
		return read_char(fp);
	} else {
		ungetc(ch, fp);
		return make_char(ch);
	}
}

scm_obj *in_pred_eof_object(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: eof-object?\nexpected: 1 argument\nbad argument(s)", obj);
	} else {
		return car(obj) == scm_eof ? scm_true : scm_false;
	}
}

scm_obj *in_pred_char_ready(const scm_obj *obj)
{
	return scm_true;
}
	

scm_obj *read_sexp(FILE *fp)
{
	char ch;

repeat:
	ch = getc(fp);
	while (isspace(ch)) {
		ch = getc(fp);
	}
	
	switch (ch) {
	case EOF:
		return scm_eof;
	case '(': 
		return read_list(fp);
	case ')': 
		error1("unexpected ')'");
	case '"': 
		return read_string(fp);
	case '\'': 
		return read_quote(fp);
	case '`': 
		return read_quasiquote(fp);
	case ',': 
		if (peek_char(fp) == '@') {
			ch = getc(fp);
			return read_unquote_splicing(fp);
		} else {
			return read_unquote(fp);
		}
	case ';':
		while ((ch = getc(fp)) != '\n') {
			if (ch == EOF) {
				return scm_eof;
			}
		}
		goto repeat;
	case '#':
		ch = getc(fp);
		
		switch (ch) {
		case '(': 
			ungetc(ch, fp);
			return read_vector(fp);
		case '\\':
			return read_char(fp);
		case 't':
			return read_true(fp);
		case 'f':
			return read_false(fp);
		case 'x':
			return read_hex_num(fp);
		case 'b':
			return read_bin_num(fp);
		case 'o':
			return read_oct_num(fp);
		case '|':
			do {
				ch = getc(fp);
				if (ch == EOF) {
					error1("end of file");
				} else if (ch == '|' && peek_char(fp) == '#') {
					ch = getc(fp);
					goto repeat;
				}
			} while (1);
			break;
		default:
			error1("unexpected '#'");
		}
	default:
		if (isdigit(ch) || ch == '-' || ch == '+') {
			ungetc(ch, fp);
			return read_num_or_sym(fp);
		} else {
			ungetc(ch, fp);
			return read_symbol(fp);
		}
	}
}

static scm_obj *read_bin_num(FILE *fp)
{
	char ch, neg;
	long long res = 0;
	
	ch = getc(fp);
	if (ch == '-') {
		neg = -1;
	} else if (ch == '+') {
		neg = 1;
	} else {
		ungetc(ch, fp);
	}
		
	while (1) {
		ch = getc(fp);
		if (ch == '0' || ch == '1') {
			res *= 2;
			res += ch - '0';
		} else if (ch != ';' && ch != EOF && !isspace(ch)) {
			error1("bad bin number");
		} else {
			ungetc(ch, fp);
			return make_integer(res * neg);
		}
	}
}

static int match_chars(FILE *fp, char *str)
{
	char ch;
	
	while (*str != '\0') {
		ch = getc(fp);
		if (tolower(ch) != tolower(*str))
			return 0;
		++str;
	}
	
	return 1;
}
			
static scm_obj *read_char(FILE *fp)
{
	char ch = getc(fp);
	
	switch (ch) {
	case 'n':
	case 'N':
		if (peek_char(fp) == 'e' || peek_char(fp)== 'E') {
			if (!match_chars(fp, "ewline")) {
				error1("bad char");
			} else {
				return make_char('\n');
			}
		} else {
			return make_char(ch);
		}
	case 's':
	case 'S':
		if (peek_char(fp) == 'p' || peek_char(fp) == 'P') {
			if (!match_chars(fp, "pace")) {
				error1("bad char");
			} else {
				return make_char(' ');
			}
		} else {
			return make_char(ch);
		}
	case 'r':
	case 'R':
		if (peek_char(fp) == 'u' || peek_char(fp) == 'U') {
			if (!match_chars(fp, "ubout")) {
				error1("bad char");
			} else {
				return make_char(0x7f);
			}
		} else if (peek_char(fp) == 'e' || peek_char(fp) == 'E') {
			if (!match_chars(fp, "eturn")) {
				error1("bad char");
			} else {
				return make_char('\r');
			}
		} else {
			return make_char(ch);
		}
	case 'p':
	case 'P':
		if (peek_char(fp) == 'a' || peek_char(fp) == 'A') {
			if (!match_chars(fp, "age")) {
				error1("bad char");
			} else {
				return make_char('\f');
			}
		} else {
			return make_char(ch);
		}
	case 't':
	case 'T':
		if (peek_char(fp) == 'a' || peek_char(fp) == 'A') {
			if (!match_chars(fp, "ab")) {
				error1("bad char");
			} else {
				return make_char('\t');
			}
		} else {
			return make_char(ch);
		}
	case 'b':
	case 'B':
		if (peek_char(fp) == 'a' || peek_char(fp) == 'A') {
			if (!match_chars(fp, "ackspace")) {
				error1("bad char");
			} else {
				return make_char('\b');
			}
		} else {
			return make_char(ch);
		}
	case 'l':
	case 'L':
		if (peek_char(fp) == 'i' || peek_char(fp) == 'I') {
			if (!match_chars(fp, "inefeed")) {
				error1("bad char");
			} else {
				return make_char('\n');
			}
		} else {
			return make_char(ch);
		}
	default:
		return make_char(ch);
	}
}

static scm_obj *read_false(FILE *fp)
{
	if (peek_char(fp) == '\n' || peek_char(fp) == EOF || 
	    isspace(peek_char(fp)) || peek_char(fp) == '(' ||
	    peek_char(fp) == ')') {
		return scm_false;
	} else {
		error1("bad constant: false");
	}
}

static scm_obj *read_hex_num(FILE *fp)
{
	char ch, neg;
	long long res = 0;
	
	ch = getc(fp);
	if (ch == '-') {
		neg = -1;
	} else if (ch == '+') {
		neg = 1;
	} else {
		neg = 1;
		ungetc(ch, fp);
	}	
		
	while (1) {
		ch = getc(fp);
		if (ch >= '0' && ch <= '9') {
			res *= 16;
			res += ch - '0';
		} else if (ch >= 'a' && ch <= 'f') {
			res *= 16;
			res += ch - 'a' + 10;
		} else if (ch >= 'A' && ch <= 'F') {
			res *= 16;
			res += ch - 'A' + 10;
		} else if (ch != ';' && ch != EOF && !isspace(ch)
				   && ch != '(' && ch != ')') {
			error1("bad hex number");
		} else {
			ungetc(ch, fp);
			return make_integer(res * neg);
		}
	}
}

static scm_obj *read_list(FILE *fp)
{
	scm_obj *car;
	scm_obj *cdr;
	scm_obj *obj;
	char ch;
	
	skip_space_comment(fp);
	if (peek_char(fp) == ')') {
		ch = getc(fp);
		return scm_null;
	} else {
		car = read_sexp(fp);
		skip_space_comment(fp);
		
		if (peek_char(fp) == ')') {
			ch = getc(fp);
			cdr = scm_null;
		} else if (peek_char(fp) == '.' && 
				   isspace(double_peek_char(fp))) {
				   
			ch = getc(fp);
			cdr = read_sexp(fp);
			skip_space_comment(fp);
			
			if (peek_char(fp) != ')') {
				error1("bad syntax .");
			} else {
				ch = getc(fp);
			}
		} else {
			cdr = read_list(fp);
		}
	}
	
	return make_pair(car, cdr);
}

static scm_obj *read_num_or_sym(FILE *fp)
{
	char buf[MAX_NUM_LEN];
	unsigned i = 0;
	unsigned neg = 1;
	unsigned sym = 0;
	char ch = getc(fp);
	
	if (ch == '+') {
		buf[i++] = '+';
		ch = getc(fp);
		if (ch == ' ' || ch == ';' || ch == '(' || 
		    ch == ')' || ch == EOF || ch == '\n') {
		    ungetc(ch, fp);
		    return make_symbol("+");
		}
	} else if (ch == '-') {
		buf[i++] = '-';
		neg = -1;
		ch = getc(fp);
		if (ch == ' ' || ch == ';' || ch == '(' || 
		    ch == ')' || ch == EOF || ch == '\n') {
		    ungetc(ch, fp);
		    return make_symbol("-");
		}
	}
	
	ungetc(ch, fp);
	while (i < MAX_NUM_LEN) {
		ch = getc(fp);
		if (ch == ' ' || ch == ';' || ch == '(' || 
		    ch == ')' || ch == EOF || ch == '\n') {
			ungetc(ch, fp);
		    break;
		}    
		if (!isdigit(ch)) {
			sym = 1;
		}
		buf[i++] = ch;				
	}
	buf[i] = '\0';
	
	if (sym == 0) {
		return make_integer(atoll(buf));
	} else {
		return make_symbol(buf);
	}
}
	
	
static scm_obj *read_oct_num(FILE *fp)
{
	char ch, neg;
	long long res = 0;
				
	ch = getc(fp);
	if (ch == '-') {
		neg = -1;
	} else if (ch == '+') {
		neg = 1;
	} else {
		neg = 1;
		ungetc(ch, fp);
	}
	
	while (1) {
		ch = getc(fp);
		if (ch >= '0' && ch <= '7') {
			res *= 8;
			res += ch - '0';
		} else if (ch != ';' && ch != EOF && !isspace(ch)) {
			error1("bad oct number");
		} else {
			ungetc(ch, fp);
			return make_integer(res * neg);
		}
	}
}
	
static scm_obj *read_quasiquote(FILE *fp)
{
	return make_pair(scm_quasiquote, make_pair(read_sexp(fp), scm_null));
}

static scm_obj *read_quote(FILE *fp)
{
	return make_pair(scm_quote, make_pair(read_sexp(fp), scm_null));
}

static scm_obj *read_string(FILE *fp)
{
	char ch, buf[MAX_STR_LEN];
	unsigned i = 0;
	
	while ((ch = getc(fp)) != '"') {
		if (ch == '\\') {
			ch = getc(fp);
		}
		if (i > MAX_STR_LEN) {
			error1("too long input string");
		}
		buf[i++] = ch;
	}
	buf[i] = '\0';
	
	return make_string(buf);
}
	
static scm_obj *read_true(FILE *fp)
{
	if (peek_char(fp) == '\n' || peek_char(fp) == EOF || 
		isspace(peek_char(fp)) || peek_char(fp) == '(' || peek_char(fp) == ')') {
		return scm_true;
	} else {
		error1("bad constant: true");
	}
}
	
static scm_obj *read_unquote(FILE *fp)
{
	return make_pair(scm_unquote, make_pair(read_sexp(fp), scm_null));
}
			
static scm_obj *read_unquote_splicing(FILE *fp)
{
	return make_pair(scm_unquote_splicing, make_pair(read_sexp(fp), scm_null));
}

static scm_obj *read_vector(FILE *fp)
{
	scm_obj *len;
	scm_obj *obj;
	scm_obj *vec_obj;
	
	obj = read_sexp(fp);
	len = list_length(cons(obj, scm_null));
	
	vec_obj = scm_alloc_obj();
	type(vec_obj) = VECTOR;
	vlen(vec_obj) = fixnum(len);
	vec(vec_obj) = scm_alloc_vec(fixnum(len));
	
	for (unsigned i = 0; i < fixnum(len); i++) {
		vec(vec_obj)[i] = car(obj);
		obj = cdr(obj);
	}
	
	return vec_obj;
}
	
static scm_obj *read_symbol(FILE *fp)
{
	char ch, buf[MAX_SYM_LEN];
	unsigned i = 0;
	
	while (!isspace(ch = getc(fp)) && ch != '('
		   && ch != ')' && ch != '"' && ch != EOF) {
		buf[i++] = ch;
	}
	
	if (ch != EOF) {
		ungetc(ch, fp);
	}
	buf[i] = '\0';
	
	return make_symbol(&buf);
}

void scm_init_input()
{
	scm_add_prim("read", in_read);
	scm_add_prim("read-char", in_read_char);
	scm_add_prim("peek-char", in_peek_char);
	scm_add_prim("eof-object?", in_pred_eof_object);
	scm_add_prim("char-ready?", in_pred_char_ready);
}			

	












	

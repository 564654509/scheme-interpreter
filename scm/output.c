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

#define MAX_OUT_LEN 65536

/*  before print an object, we use sprintf function to store it
    in buf array, and then print this char array.
*/
static char buf[MAX_OUT_LEN];

/*  print s expression  */
static int print(char *str, int index, const scm_obj *obj, int escaped);

/*  print char  */
static int print_char(char *str, int index, scm_obj *obj, int escaped);

/*  print pair  */
static int print_pair(char *str, int index, scm_obj *obj, int escaped);

/*  print string  */
static int print_string(char *str, int index, scm_obj *obj, int escaped);

/*  print vector  */
static int print_vector(char *str, int index, scm_obj *obj, int escaped);

/*  print an object to some certain output port  */
static void print_to_port(const scm_obj *obj, scm_obj *port, int escaped)
{
	FILE *fp = port(port);
	int index = 0;
	
	index = print(buf, index, obj, escaped);
	if (index == 0) {
		return ;
	} else {
		buf[index] = '\0';
		fprintf(fp, "%s", buf);
		printf("\n");
	}
}

/*  procedure: (write obj) or (write obj port)  */
scm_obj *out_write(const scm_obj *obj)
{
	scm_obj *port;
	
	if (obj == scm_null) {
		error0("procedure: write\nexpected: 1 to 2 arguments\nbad argument(s)", obj);
	} else if (cdr(obj) == scm_null) {
		port = scm_cur_output_port;
	} else if (cddr(obj) != scm_null) {
		error0("procedure: write\nexpected: 1 to 2 arguments\nbad argument(s)", obj);
	} else if (type(cadr(obj)) != OUTPORT) {
		error0("procedure: write\nexpected: output-port\nbad argument(s)", cadr(obj));
	} else {
		port = cadr(obj);
	}
	print_to_port(car(obj), port, 1);
	
	return scm_unspecified;
}

/*  procedure: (display obj) or (display obj port)  */
scm_obj *out_display(const scm_obj *obj)
{
	scm_obj *port;
	
	if (obj == scm_null) {
		error0("procedure: display\nexpected: 1 to 2 arguments\nbad argument(s)", obj);;
	} else if (cdr(obj) == scm_null) {
		port = scm_cur_output_port;
	} else if (cddr(obj) != scm_null) {
		error0("procedure: display\nexpected: 1 to 2 arguments\nbad argument(s)", obj);;
	} else if (type(cadr(obj)) != OUTPORT) {
		error0("procedure: write\nexpected: output-port\nbad argument(s)", cadr(obj));
	} else {
		port = cadr(obj);
	}		
	print_to_port(car(obj), port, 0);
	
	return scm_unspecified;
}

/*  procedure: (newline) or (newline obj)  */
scm_obj *out_newline(const scm_obj *obj)
{
	const scm_obj *port;
	scm_obj *newline;
	
	if (obj == scm_null) {
		port = scm_cur_output_port;
	} else if (cdr(obj) == scm_null) {
		if (type(car(obj)) != OUTPORT) {
			error0("procedure: newline\nexpected: output-port\nbad argument(s)", car(obj));
		} else {
			port = car(obj);
		}
	} else {
		error0("procedure: newline\nexpected: 0 to 1 arguments\nbad argument(s)", obj);
	}
	
	fprintf(port(port), "%c", '\n');
	return scm_unspecified;
}

static int print(char *str, int index, const scm_obj *obj, int escaped)
{
	if (obj == scm_null) {
		sprintf(str + index, "()");
		index += 2; 
	} else if (obj == scm_false) {
		sprintf(str + index, "#f");
		index += 2;
	} else if (obj == scm_true) {
		sprintf(str + index, "#t");
		index += 2;
	} else if (obj == scm_unspecified) {
		;
	} else {
		scm_type type = type(obj);

		if (type == SYMBOL) {
			sprintf(str + index, "%s", str(obj));
			index += slen(obj);
		} else if (type == STRING) {
			index = print_string(str, index, obj, escaped);
		} else if (type == CHAR) {
			index = print_char(str, index, obj, escaped);
		} else if (type == INTEGER) {
			sprintf(str + index, "%ld", fixnum(obj));
			index += strlen(str + index); 
		} else if (type == VECTOR) {
			index = print_vector(str, index, obj, escaped);
		} else if (type == PAIR && car(obj) == scm_closure) {
			sprintf(str + index, "#<procedure>");
			index += 12;
		} else if (type == PAIR && car(obj) == scm_macro) {
			sprintf(str + index, "#<macro>");
			index += 8;
		} else if (type == PAIR && car(obj) == scm_cont) {
			sprintf(str + index, "#<continuation>");
			index += 15;
		} else if (type == PRIM) {
			sprintf(str + index, "#<procedure>");
			index += 12;
		} else if (type == PAIR && car(obj) == scm_quote) {
			sprintf(str + index, "'");
			index += 1;
			index = print(str, index, cadr(obj), escaped);
		} else if (type == PAIR && car(obj) == scm_unquote) {
			sprintf(str + index, ",");
			index += 1;
			index = print(str, index, cadr(obj), escaped);
		} else if (type == PAIR && car(obj) == scm_quasiquote) {
			sprintf(str + index, "`");
			index += 1;
			index = print(str, index, cadr(obj), escaped);
		} else if (type == PAIR && car(obj) == scm_unquote_splicing) {
			sprintf(str + index, ",@");
			index += 2;
			index = print(str, index, cadr(obj), escaped);
		} else if (type == PAIR) {
			index = print_pair(str, index, obj, escaped);
		} else if (type == INPORT) {
			sprintf(str + index, "#<input-port>");
			index += 13;
		} else if (type == OUTPORT) {
			sprintf(str+ index, "#<output-port>");
			index += 14;
		}
	}
	
	return index;
}

static int print_char(char *str, int index, scm_obj *obj, int escaped)
{
	char ch = Char(obj);
	
	if (escaped){
		switch (ch) {
		case '\n':
			sprintf(str + index, "#\\newline");
			index += 9;
			break;
		case '\t':
			sprintf(str + index, "#\\tab");
			index += 5;
			break;
		case ' ':
			sprintf(str + index, "#\\space");
			index += 7;
			break;
		case '\r':
			sprintf(str + index, "#\\return");
			index += 8;
			break;
		case '\f':
			sprintf(str + index, "#\\page");
			index += 6;
			break;
		case '\b':
			sprintf(str + index, "#\\backspace");
			index += 11;
			break;
		default:
			sprintf(str + index, "#\\%c", ch);
			index += 3;
			break;
		}
	} else {
		str[index++] = ch;
	}
	
	return index;
}

static int print_pair(char *str, int index, scm_obj *obj, int escaped)
{
	scm_obj *cdr;
	
	str[index++] = '(';
	index = print(str, index, car(obj), escaped);
	cdr = cdr(obj);
	
	while (cdr != scm_null && type(cdr) == PAIR) {
		str[index++] = ' ';
		index = print(str, index, car(cdr), escaped);
		cdr = cdr(cdr);
	}
	
	if (cdr != scm_null) {
		str[index++] = ' ';
		str[index++] = '.';
		str[index++] = ' ';
		index = print(str, index, cdr ,escaped);
	}
	str[index++] = ')';
	
	return index;
}

static int print_string(char *str, int index, scm_obj *obj, int escaped)
{
	const char *s = str(obj);
	
	if (escaped) {
		str[index++] = '"';
	}
	while (*s) {
		if (escaped && (*s == '"' || *s == '\\')) {
			str[index++] = '\\';
		}
		str[index++] = *s;
		s++;
	}
	if (escaped) {
		str[index++] = '"';
	}
	
	return index;
}
		
	
static int print_vector(char *str, int index, scm_obj *obj, int escaped)
{
	str[index++] = '#';
	str[index++] = '(';
	
	for (unsigned i = 0; i < vlen(obj); ++i) {
		index = print(str, index, (vec(obj))[i], escaped);
		if (i < vlen(obj) - 1) {
			str[index++] = ' ';
		}
	}
	str[index++] = ')';
	
	return index;
}

/*  procedure: (write-char obj) or (write-char obj port)  */	
scm_obj *out_write_char(const scm_obj *obj)
{
	scm_obj *port;
	
	if (obj == scm_null) {
		error0("procedure: write-char\nexpected: 1 to 2 arguments\nbad argument(s)", obj);
	} else if (type(car(obj)) != CHAR) {
		error0("procedure: write-char\nexpected: char\nbad argument(s)", car(obj));
	} else if (cdr(obj) == scm_null) {
		port = scm_cur_output_port;
	} else if (cddr(obj) != scm_null) {
		error0("procedure: write-char\nexpected: 1 to 2 arguments\nbad argument(s)", obj);
	} else {
		if (type(cadr(obj)) == OUTPORT) {
			port = cadr(obj);
		} else {
			error0("procedure: write-char\nexpected: output-port\nbad argument(s)", cadr(obj));
		}
	}
	
	fprintf(port(port), "%c", Char(car(obj)));
	return scm_unspecified;
}

/*  procedure: (error obj1 obj2 ...)  */	
scm_obj *out_error(const scm_obj *obj)
{
	const scm_obj *p;
	FILE *fp = stderr;
	int index = 0;
	
	if (obj == scm_null) {
		error0("procedure: error\nexpected: at least 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != STRING) {
		error0("procedure: error\nexpected: string\nbad argument(s)", car(obj));
	} else {	
		for(p = obj; p != scm_null; p = cdr(p)) {
			index = print(buf, index, car(p), 0);
			buf[index++] = ' ';
		}
		buf[index] = '\0';
		fprintf(fp, "%s\n", buf);
		longjmp(env_buf, 1);
	}
	
	return scm_unspecified;
}

void scm_init_output()
{
	scm_add_prim("error", out_error);
	scm_add_prim("newline", out_newline);
	scm_add_prim("write", out_write);
	scm_add_prim("write-char", out_write_char);
	scm_add_prim("display", out_display);
}
	
	
	
	
	
	
	
	














	

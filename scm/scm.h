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

#ifndef _SCM_H
#define _SCM_H

#include <setjmp.h>
#include <stdio.h>

typedef struct scm_obj scm_obj;

typedef unsigned int scm_type;

typedef scm_obj *(*routine)(const scm_obj *);

/*  character: e.g #\a #\b  */
struct Char {
	char c;
};

/*  complex number: e.g 3+4i  */
struct complex {
	double real;
	double image;
};

/*  continuation  */
struct cont {
	jmp_buf *buf;
};

#ifdef INF_NUM
/*  unlimited fixed number  */
struct fixnum {
	unsigned int len;
	long *array;
};
#else 
/*  integer: no support for unlimited number  */
struct fixnum {
	long long num;
};
#endif

/*  port: input-port, output-port  */
struct port {
	FILE *port;
};

/*  pair  */
struct pair {
	scm_obj *car;
	scm_obj *cdr;
};

/*  primitive procedure  */
struct prim {
	unsigned int pos;
	routine proc;
};

/*  rational number: e.g 3/4  */
struct rational { 
	long numer; 
	long denom;
};

/*  float number: 3.1415926  */
struct real {
	double flonum; 
};

/*  string: "123" ""  */
struct string {
	unsigned int len;
	char *str;
};

/*  vector: #(1 2 3 4 5)  */
struct vector {
	unsigned int len;
	scm_obj **vec;
};

struct scm_obj {
	scm_type type;
	union {
		struct Char Char;	
		struct complex complex;
		struct cont cont;
		struct fixnum fixnum;
		struct pair pair;
		struct port port;
		struct prim prim;
		struct rational rational;
		struct real real;
		struct string string;
		struct vector vector;
	} value;
};

#define		FLAG		0x00	
#define		BOOLEAN		0x01
#define		CHAR		0x02
#define		INTEGER		0x03
#define		REAL		0x04
#define		STRING		0x05
#define		VECTOR		0x06

#define     INPORT		0x10
#define     OUTPORT		0x11
#define		PAIR		0x12
#define 	PRIM		0x13
#define     PROC		0x14
#define		SYMBOL		0x15

#define		buf(p)		((p)->value.cont.buf)
#define		Char(p)     ((p)->value.Char.c)
#define     car(p)      ((p)->value.pair.car)
#define     cdr(p)      ((p)->value.pair.cdr)
#define		fixnum(p)   ((p)->value.fixnum.num)
#define     flonum(p)   ((p)->value.real.flonum)
#define		port(p)		((p)->value.port.port)
#define		proc(p)		((p)->value.prim.proc)
#define 	slen(p)		((p)->value.string.len)
#define     str(p)      ((p)->value.string.str)
#define     type(p)     ((p)->type)
#define		vec(p)		((p)->value.vector.vec)
#define		vlen(p)		((p)->value.vector.len)
#define 	caar(p)    	(car(car(p)))
#define 	cadr(p)    	(car(cdr(p)))
#define 	cdar(p)    	(cdr(car(p)))
#define 	cddr(p)    	(cdr(cdr(p)))
#define		caadr(p)	(car(cadr(p)))
#define 	caddr(p)   	(car(cddr(p)))
#define 	cdadr(p)   	(cdr(cadr(p)))
#define		cdddr(p)   	(cdr(cddr(p)))
#define 	cadddr(p)  	(car(cdddr(p)))
#define		cddddr(p)   (cdr(cdddr(p)))

#endif
		
	



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

scm_obj *sys_load(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: load\nexpected: 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != STRING) {
		error0("procedure: load\nexpected: 1 argument\nbad argument(s)", car(obj));
	} else {
		scm_obj *exp, *ret;
		scm_obj *port_obj;
		FILE *fp = fopen(str(car(obj)), "r");
				
		if (fp == NULL) {
			error0("procedure: load\nfailed to open file\nbad argument(s)", car(obj));
		}
		
		port_obj = make_port(fp, INPORT);
		while ((exp = in_read(cons(port_obj, scm_null))) != scm_eof) {
			ret = eval(exp, init_env);
			out_write(cons(ret, scm_null));
		}
		
		fclose(fp);
		return scm_unspecified;
	}
}

void scm_init_system()
{
	scm_add_prim("load", sys_load);
}
		
		

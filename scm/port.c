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

scm_obj *scm_cur_input_port;
scm_obj *scm_cur_output_port;
		
inline scm_obj *port_pred_input_port(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: input-port?\nexpected: 1 argument\nbad argument(s)", obj);
	} else {
		return type(car(obj)) == INPORT ? scm_true : scm_false;
	}
}

inline scm_obj *port_pred_output_port(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: output-port?\nexpected: 1 argument\nbad argument(s)", obj);
	} else {
		return type(car(obj)) == OUTPORT ? scm_true : scm_false;
	}
}

inline scm_obj *port_current_input_port(const scm_obj *obj)
{
	if (obj != scm_null) {
		error0("procedure: current-input-port\nexpected: 0 argument\nbad argument(s)", obj);
	} else {
		return scm_cur_input_port;
	}
}

inline scm_obj *port_current_output_port(const scm_obj *obj)
{
	if (obj != scm_null) {
		error0("procedure: current-output-port\nexpected: 0 argument\nbad argument(s)", obj);
	} else {
		return scm_cur_output_port;
	}
}

scm_obj *port_open_input_file(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: open-input-file\nexpected: 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != STRING) {
		error0("procedure: open-input-file\nexpected: string\nbad argument(s)", car(obj));
	} else {
		scm_obj *port_obj;
		char *name = str(car(obj));
		FILE *fp = fopen(name, "r");
		
		if (fp == NULL) {
			error0("procedure: open-input-file\ncan't open input file\nbad argument(s)", car(obj));
		} else {
			port_obj = scm_alloc_obj();
			type(port_obj) = INPORT;
			port(port_obj) = fp;
			
			return port_obj;
		}
	}
}

scm_obj *port_open_output_file(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: open-output-file\nexpected: 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != STRING) {
		error0("procedure: open-output-file\nexpected: string\nbad argument(s)", car(obj));
	} else {
		scm_obj *port_obj;
		char *name = str(car(obj));
		FILE *fp = fopen(name, "w");
		
		if (fp == NULL) {
			error0("procedure: open-output-file\ncan't open output file\nbad argument(s)", car(obj));
		} else {
			port_obj = scm_alloc_obj();
			type(port_obj) = OUTPORT;
			port(port_obj) = fp;
			
			return port_obj;
		}
	}
}

scm_obj *port_close_input_port(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: close-input-port\nexpected: 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != INPORT) {
		error0("procedure: close-input-port\nexpected: input-port\nbad argument(s)", car(obj));
	} else {
		FILE *fp = port(car(obj));
		
		fclose(fp);
		return scm_unspecified;
	}
}
	
scm_obj *port_close_output_port(const scm_obj *obj)
{
	if (obj == scm_null || cdr(obj) != scm_null) {
		error0("procedure: close-output-port\nexpected: 1 argument\nbad argument(s)", obj);
	} else if (type(car(obj)) != OUTPORT) {
		error0("procedure: close-output-port\nexpected: output-port\nbad argument(s)", car(obj));
	} else {
		FILE *fp = port(car(obj));
		
		fclose(fp);
		return scm_unspecified;
	}
}	
	
void scm_init_port()
{
	scm_cur_input_port = make_port(stdin, INPORT);
	scm_cur_output_port = make_port(stdout, OUTPORT);
	
	scm_add_prim("input-port?", port_pred_input_port);
	scm_add_prim("output-port?", port_pred_output_port);
	scm_add_prim("current-input-port", port_current_input_port);
	scm_add_prim("current-output-port", port_current_output_port);
	scm_add_prim("open-input-file", port_open_input_file);
	scm_add_prim("open-output-file", port_open_output_file);
	scm_add_prim("close-input-port", port_close_input_port);
	scm_add_prim("close-output-port", port_close_output_port);
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
		

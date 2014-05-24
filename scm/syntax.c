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

scm_obj *scm_apply;
scm_obj *scm_begin;
scm_obj *scm_callcc;
scm_obj *scm_call_with_cc;
scm_obj *scm_define;
scm_obj *scm_define_macro;
scm_obj *scm_define_syntax;
scm_obj *scm_if;
scm_obj *scm_lambda;
scm_obj *scm_quit;
scm_obj *scm_set;

void scm_init_syntax()
{
	scm_begin = scm_add_keywd("begin");
	scm_callcc = scm_add_keywd("call/cc");
	scm_call_with_cc = scm_add_keywd("call-with-current-continuation");
	scm_define = scm_add_keywd("define");
	scm_define_macro = scm_add_keywd("define-macro");
	scm_define_syntax = scm_add_keywd("define-syntax");
	scm_if = scm_add_keywd("if");
	scm_lambda = scm_add_keywd("lambda");
	scm_quit = scm_add_keywd("quit");
	scm_set = scm_add_keywd("set!");
}

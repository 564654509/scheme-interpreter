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

#ifndef _GLOBAL_H
#define _GLOBAL_H

#include "scm.h"

extern scm_obj *scm_closure;
extern scm_obj *scm_cont;
extern scm_obj *scm_eof;
extern scm_obj *scm_macro;
extern scm_obj *scm_null;
extern scm_obj *scm_syntax;

extern jmp_buf env_buf;

extern scm_obj *make_char(char c);
extern scm_obj *make_integer(long long num);
extern scm_obj *make_pair(const scm_obj *car, const scm_obj *cdr);
extern scm_obj *make_port(FILE *fp, scm_type type);
extern scm_obj *make_string(const char *str);
extern scm_obj *make_symbol(const char *str);

extern scm_obj *scm_add_obj(const scm_obj *obj);
extern scm_obj *scm_add_keywd(const char *str);

extern void scm_init_flags();
extern void scm_init_oblist();

#define cons(car, cdr) make_pair(car, cdr)

#endif


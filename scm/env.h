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

#ifndef _ENV_H
#define _ENV_H

#include "scm.h"


/*  the global environment for scm interp  */
extern scm_obj *init_env;

/*  define  */
extern scm_obj *add_binding(const scm_obj *var, 
							const scm_obj *val,
						          scm_obj *env);

/*  set!  */						          
extern scm_obj *assign(const scm_obj *var,
					   const scm_obj *val,
					   const scm_obj *env);

/*  extend the input env and return a new one  */						          
extern scm_obj *extend(const scm_obj *vars,
					   const scm_obj *vals,
					         scm_obj *env,
					   const scm_obj *name);

/*  lookup a symbol  */					   
extern scm_obj *lookup(const scm_obj *var, const scm_obj *env);

/*  add new primitive procedure such as +, -...  */
extern void scm_add_prim(char *str, routine proc);

extern void scm_init_env();

#endif


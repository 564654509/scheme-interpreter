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


#ifndef _LIST_H
#define _LIST_H

#include "scm.h"

extern scm_obj *list_pred_null(const scm_obj *obj);
extern scm_obj *list_pred_list(const scm_obj *obj);
extern scm_obj *list_list(const scm_obj *obj);
extern scm_obj *list_length(const scm_obj *obj);
extern scm_obj *list_append(const scm_obj *obj);
extern scm_obj *list_reverse(const scm_obj *obj);
extern scm_obj *list_list_tail(const scm_obj *obj);
extern scm_obj *list_list_ref(const scm_obj *obj);
extern scm_obj *list_memq(const scm_obj *obj);
extern scm_obj *list_memv(const scm_obj *obj);
extern scm_obj *list_member(const scm_obj *obj);
extern scm_obj *list_assq(const scm_obj *obj);
extern scm_obj *list_assv(const scm_obj *obj);
extern scm_obj *list_assos(const scm_obj *obj);

#endif

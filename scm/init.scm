; Copyright (c) 2014 Xianfei Shen
; All rights reserved.

; Permission is hereby granted, without written agreement and without
; license or royalty fees, to use, copy, modify, and distribute this
; software and its documentation for any purpose, provided that the
; above copyright notice and the following two paragraphs appear in
; all copies of this software.

; IN NO EVENT SHALL XIANFEI SHEN BE LIABLE TO ANY PARTY FOR DIRECT,
; INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
; OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF XIANFEI
; SHEN HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

; XIANFEI SHEN SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT
; NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
; FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER
; IS ON AN "AS IS" BASIS, AND XIANFEI SHEN HAS NO OBLIGATION TO
; PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR
; MODIFICATIONS.

(load "scm/boolean.scm")
(load "scm/control.scm")
(load "scm/derived.scm")
(load "scm/extra.scm")
(load "scm/list.scm")
(load "scm/macro.scm")
(load "scm/number.scm")
(load "scm/pair.scm")
(load "scm/port.scm")
(load "scm/string.scm")
(load "scm/vector.scm")
     
(define gensym
  (let ((*gensym* 0))
    (lambda ()
      (set! *gensym* (+ *gensym* 1))
      (string->symbol (string-append 
                            "GenSym%" 
                             (number->string *gensym*))))))
                             

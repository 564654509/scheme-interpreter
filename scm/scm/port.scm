; Copyright (c) 2014 Xianfei Shen
; All rights reserved.

; Permission is hereby granted, without written agreement and without
; license or royalty fees, to use, copy, modify, and distribute this
; software and its documentation for any purpose, provided that the
; above copyright notice and the following two paragraphs appear in
; all copies of this software.

; IN NO EVENT SHALL BRENT BENSON BE LIABLE TO ANY PARTY FOR DIRECT,
; INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
; OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF BRENT
; BENSON HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

; BRENT BENSON SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT
; NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
; FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER
; IS ON AN "AS IS" BASIS, AND BRENT BENSON HAS NO OBLIGATION TO
; PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR
; MODIFICATIONS.

(define (port? x) (or (input-port? x) (output-port? x)))

(define (call-with-input-file file proc)
  (proc (open-input-file file)))

(define (call-with-output-file file proc)
  (proc (open-output-file file)))
 


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

(define (force x) (x))

(define (map proc . l*)
  (if (null? l*)
      (error "" "")
      (begin (define (map2 proc l)
               (if (null? l)
                   '()
                   (cons (proc (car l)) (map2 proc (cdr l)))))
             (define (loop l)
               (if (null? (car l))
                   '()
                   (cons (apply proc (map2 car l))
                         (loop (map2 cdr l)))))
             (loop l*))))
             
(define for-each map)

(define call-with-current-continuation call/cc)

(define make-promise
  (lambda (proc)
    (let ((result-ready? #f)
          (result #f))
      (lambda ()
        (if result-ready?
            result
            (let ((x (proc)))
              (if result-ready?
                  result
                  (begin (set! result-ready? #t)
                         (set! result x)
                         result))))))))



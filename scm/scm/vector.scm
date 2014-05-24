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


(define (list->vector l)
  (if (not (list? l))
      (begin (display "procedure: list->vector")
             (display "expected: list")
             (error "bad argument(s):" l))
      (let* ((len (length l))
             (v (make-vector len)))
        (letrec ((loop 
                  (lambda (n l)
                    (if (= n len)
                        v
                        (begin (vector-set! v n (car l))
                               (loop (+ n 1) (cdr l)))))))
          (loop 0 l)))))

(define (vector->list v)
  (if (vector? v)
      (let ((len (vector-length v)))
        (letrec ((loop 
                  (lambda (n l)
                    (if (< n 0)
                        l
                        (loop (- n 1) 
                              (cons (vector-ref v n) l))))))
          (loop (- len 1) '())))
      (begin (display "procedure: vector->list")
             (display "expected: vector")
             (error "bad argument(s):" v))))

(define (vector . l) (list->vector l))

(define (vector-fill! v x)
  (if (vector? v)
      (letrec ((loop 
                (lambda (n) 
                  (if (< n 0)
                      'ok
                      (begin (vector-set! v n x)
                             (loop (- n 1)))))))
        (loop (- (vector-length v) 1)))
      (begin (display "procedure: vector-fill!")
             (display "expected: vector")
             (error "bad argument(s):" v))))
             
             
             

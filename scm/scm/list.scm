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


(define (append2 l1* l2*)
  (define (loop l1 l2)
    (if (and (not (null? l1)) (pair? l1))
        (cons (car l1) (loop (cdr l1) l2))
        (if (null? l1)
            l2
            (begin (display "procedure: append")
                   (display "expected: list")
                   (error "bad argument(s):" l1*)))))
  (loop l1* l2*))

;;;Do not use letrec or let or something else than defined
;;;by define-macro, because the append procedure has been 
;;;used by expanding quasiquote firstly.
 
(define (append . l)
   (if (null? l)
       '()
       (if (null? (cdr l))
           (car l)
           (begin (define (loop l1 l2)
                          (if (null? (cdr l2))
                              (append2 l1 (car l2))
                              (loop (append2 l1 (car l2))
                                    (cdr l2))))
               (loop (car l) (cdr l))))))
  
(define (assoc item* table*)
  (define (loop item table)
    (if (null? table)
        #f
        (if (not (pair? table))
            (begin (display "procedure: assoc")
                   (display "not a proper list")
                   (error "bad argument(s):" table*))
            (if (not (pair? (car table)))
                (begin (display "procedure: assoc")
                       (display "no-pair found in list")
                       (error "bad argument(s):" table*))
                (if (equal? item (caar table))
                    (car table)
                    (loop item (cdr table)))))))
  (loop item* table*))

(define (assq item* table*)
  (define (loop item table)
    (if (null? table)
        #f
        (if (not (pair? table))
            (begin (display "procedure: assq")
                   (display "not a proper list")
                   (error "bad argument(s):" table*))
            (if (not (pair? (car table)))
                (begin (display "procedure: assq")
                       (display "no-pair found in list")
                       (error "bad argument(s):" table*))
                (if (eq? item (caar table))
                    (car table)
                    (loop item (cdr table)))))))
  (loop item* table*))

(define (assv item* table*)
  (define (loop item table)
    (if (null? table)
        #f
        (if (not (pair? table))
            (begin (display "procedure: assv")
                   (display "not a proper list")
                   (error "bad argument(s):" table*))
            (if (not (pair? (car table)))
                (begin (display "procedure: assv")
                       (display "no-pair found in list")
                       (error "bad argument(s):" table*))
                (if (eqv? item (caar table))
                    (car table)
                    (loop item (cdr table)))))))
  (loop item* table*))
  
(define (last l*)
  (letrec ((loop 
            (lambda (l)
              (if (pair? l)
                  (if (null? (cdr l))
                      (car l)
                      (loop (cdr l)))
                  (begin (display "procedure: last")
                         (display "expected: list")
                         (error "bad argument(s):" l*))))))
    (loop l*)))
  
(define list (lambda x x))

(define (list-tail x n)
  (cond ((zero? n) x)
        ((null? x) (wrong "list-tail: index out of range"))
        (else (list-tail (cdr x) (- n 1)))))
        
(define (list-ref l* k*)
  (if (not (pair? l*))
      (begin (display "procedure: list-ref")
             (display "expected: pair")
             (error "bad argument(s):" l*))
      (letrec ((loop 
                (lambda (l k)
                  (if (null? l)
                      (begin (display "procedure: list-ref")
                             (display "too large index for list")
                             (error "bad argument(s):" k*))
                      (if (pair? l)
                          (if (= k 0)
                              (car l)
                              (loop (cdr l) (- k 1)))
                          (begin (display "procedure: list-ref")
                                 (display "reaches a non-pair")
                                 (error "bad argument(s):" l*)))))))
        (loop l* k*))))
        
(define (memq item* lst*)
  (define (loop item lst)
    (if (null? lst)
        #f 
        (if (not (pair? lst))
            (begin (display "procedure: memq")
                   (display "not a proper list")
                   (error "bad argument(s):" lst*))
            (if (eq? item (car lst))
                lst
                (loop item (cdr lst))))))
  (loop item* lst*))

(define (memv item* lst*)
  (define (loop item lst)
    (if (null? lst)
        #f 
        (if (not (pair? lst))
            (begin (display "procedure: memv")
                   (display "not a proper list")
                   (error "bad argument(s):" lst*))
            (if (eqv? item (car lst))
                lst
                (loop item (cdr lst))))))
  (loop item* lst*))

(define (member item* lst*)
  (define (loop item lst)
    (if (null? lst)
        #f 
        (if (not (pair? lst))
            (begin (display "procedure: member")
                   (display "not a proper list")
                   (error "bad argument(s):" lst*))
            (if (equal? item (car lst))
                lst 
                (loop item (cdr lst))))))
  (loop item* lst*))
        
(define (reverse l*)
  (letrec ((loop 
            (lambda (l)
              (if (and (not (null? l)) (pair? l))
                  (append (loop (cdr l)) (list (car l)))
                  (if (null? l)
                      '()
                      (begin (display "procedure: reverse")
                             (display "expected: list")
                             (error "bad argument(s):" l*)))))))
    (loop l*)))



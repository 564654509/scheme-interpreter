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


(define (expt a b)
  (if (and (integer? a) (integer? b))
      (if (< b 0)
          (begin (display "procedure: expt")
                 (display "expected: a nonnegative number")
                 (error "bad argument(s):" b))
          (letrec ((loop 
                    (lambda (x y)
                      (if (= y 0)
                          1
                          (* x (loop x (- y 1)))))))
            (loop a b)))
      (begin (display "procedure: expt")
             (display "expected: two integers")
             (error "bad argument(s)" (list a b))))) 

(define (gcd . l)
  (define (gcd2 a b)
    (cond ((< a b) (gcd2 b a))
          ((= b 0) a)
          ((< b 0) (gcd2 a (- b)))
          (else (gcd2 (remainder a b) b))))                    
  (if (null? l)
      0
      (if (null? (cdr l))
          (if (integer? (car l))
              (car l)
              (begin (display "procedure: gcd")
                     (display "expected: integer")
                     (error "bad argument(s)" (car l))))
          
          (letrec ((loop 
                    (lambda (n l)
                      (if (null? (cdr l))
                          (gcd2 n (car l))
                          (loop (gcd2 n (car l)) (cdr l))))))
            (loop (car l) (cdr l))))))


(define (lcm . l)
  (define (lcm2 a b)
    (/ (* a b) (gcd a b))) 
  (if (null? l)
      1
      (if (null? (cdr l))
          (car l)
          (letrec ((loop 
                    (lambda (n l)
                      (if (null? (cdr l))
                          (lcm2 n (car l))
                          (loop (lcm2 n (car l))
                                (cdr l))))))
            (loop (car l) (cdr l))))))          

(define (sqrt n)
  (if (< n 0)
      (begin (display "procedure: sqrt")
             (display "expected: a nonnegative integer")
             (error "bad argument(s):" n))     
      (letrec ((find 
                (lambda (u)
                  (if (< (* u u) n)
                      (find (* u 2))
                      u)))     
               (loop
                (lambda (l r)
                  (let ((m (/ (+ l r) 2)))
                    (if (and (<= (* m m) n)
                             (> (* (+ m 1) (+ m 1)) n))
                        m
                        (if (> (* m m) n)
                            (loop l m)
                            (loop (+ m 1) r)))))))
        (loop 0 (find 1)))))












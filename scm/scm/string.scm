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


(define (string->list s*)
  (if (not (string? s*))
      (begin (display "procedure: string->list")
             (display "expected: string")
             (error "bad argument(s):" s*))
      (letrec ((loop
                (lambda (n)
                  (if (= n (string-length s*))
                      '()
                      (cons (string-ref s* n) (loop (+ n 1)))))))
        (loop 0))))
        
;;;taken from Scheme 9 from Empty Space.

(define (number->string n . radix)
  (letrec
    ((digits
       (string->list "0123456789abcdef"))
     (conv
       (lambda (n rdx res)
         (if (zero? n)
             (if (null? res) '(#\0) res)
             (conv (quotient n rdx)
                   rdx
                   (cons (list-ref digits (remainder n rdx))
                         res)))))
     (conv-int
       (lambda (n rdx)
         (if (negative? n)
             (list->string (cons #\- (conv (abs n) rdx '())))
             (list->string (conv n rdx '())))))
     (get-radix
       (lambda ()
         (cond ((null? radix)
                 10)
               ((and (<= 2 (car radix)) (<= (car radix) 16))
                 (car radix))
               (else
                 (error "number->string: invalid radix"
                        (car radix)))))))
    (conv-int n (get-radix))))

(define (string->number str . radix)
  (letrec
    ((digits
       (string->list "0123456789abcdef"))
     (value-of-digit
       (lambda (x)
         (letrec
           ((v (lambda (x d n)
                 (cond ((null? d) 17)
                       ((char=? x (car d)) n)
                       (else (v x (cdr d) (+ n 1)))))))
           (v (char-downcase x) digits 0))))
     (conv3
       (lambda (lst res rdx)
         (if (null? lst)
             res
             (let ((dval (value-of-digit (car lst))))
               (and (< dval rdx)
                    (conv3 (cdr lst)
                           (+ dval (* res rdx))
                           rdx))))))
     (conv
       (lambda (lst rdx)
         (and (not (null? lst))
              (conv3 lst 0 rdx))))
     (sconv
       (lambda (lst rdx)
         (cond ((null? lst)
                 #f)
               ((char=? (car lst) #\+)
                 (conv (cdr lst) rdx))
               ((char=? (car lst) #\-)
                 (let ((r (conv (cdr lst) rdx)))
                   (if r (- r) #f)))
               (else
                 (conv lst rdx)))))
     (get-radix
       (lambda ()
         (cond ((null? radix)
                 10)
               ((and (<= 2 (car radix)) (<= (car radix) 17))
                 (car radix))
               (else
                 (error "string->number: invalid radix" radix)))))
     (base-prefix?
       (lambda (s)
         (and (> (string-length s) 2)
              (char=? #\# (string-ref s 0))
              (memv (string-ref s 1) '(#\b #\d #\o #\x))
              #t))))
    (let ((r (if (base-prefix? str)
                 (let ((rc (string-ref str 1)))
                   (cond ((char=? rc #\b)  2)
                         ((char=? rc #\d) 10)
                         ((char=? rc #\o)  8)
                         (else            16)))
                 (get-radix)))
          (s (if (base-prefix? str)
                 (substring str 2 (string-length str))
                 str)))
      (and r (sconv (string->list s) r)))))

              
              
              
              
              
              
              
              
              
              
              
              
              
              
              
              











        
        

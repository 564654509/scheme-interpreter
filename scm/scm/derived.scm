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

(define-macro case 
  (key . clauses)
  ;; conditionally execute the clause eqv? to key
  (define (case-make-clauses key)
    `(cond ,@(map
              (lambda (clause)
                (if (pair? clause)
                    (let ((case (car clause))
                          (exprs (cdr clause)))
                      (cond ((eq? case 'else)
                             `(else ,@exprs))
                            ((pair? case)
                             (if (= (length case) 1)
                                 `((eqv? ,key ',(car case)) ,@exprs)
                                 `((memv ,key ',case) ,@exprs)))
                            (else
                             `((eqv? ,key ',case) ,@exprs))))
                    (error 'case "invalid syntax in ~a" clause)))
              clauses)))
  (if (pair? key)
      (let ((newkey (gensym)))
        `(let ((,newkey ,key))
           ,(case-make-clauses newkey)))
      (case-make-clauses key)))

(define-macro cond 
  clauses
  (if (null? clauses)
      #f
      (let ((test (caar clauses)) (exprs (cdar clauses)))
        (if (null? exprs)
            (if (eq? test 'else)
                #t
                `(or ,test (cond ,@(cdr clauses))))
            (if (eq? test 'else)
                `(begin ,@exprs)
                (if (and (pair? exprs) (eq? (car exprs) '=>))
                    (let ((result (string->uninterned-symbol "result")))
                      `(let ((,result ,test))
                         (if ,result
                             (,(cadr exprs) ,result)
                             (cond ,@(cdr clauses)))))
                    `(if ,test
                         (begin ,@exprs)
                         (cond ,@(cdr clauses)))))))))

(define-macro let 
  (bindings . body)
  (define (named-let name bindings body)
    `(let ((,name #f))
       (set! ,name (lambda ,(map car bindings) . ,body))
       (,name . ,(map cadr bindings))))
  (if (symbol? bindings) 
      (named-let bindings (car body) (cdr body))
      `((lambda ,(map car bindings) . ,body) . ,(map cadr bindings))))

(define-macro let* 
  (bindings . body)
  (if (null? bindings) `((lambda () . ,body))
      `(let (,(car bindings))
         (let* ,(cdr bindings) . ,body))))

(define-macro letrec 
  (bindings . body)
  (define (combine vars vals)
    (if (null? vars)
        (if (not (null? vals))
            (error "unmatched" vals)
            '())
        (if (null? vals)
            (error "unmatched" vals)
            (cons (list (car vars) (car vals))
                  (combine (cdr vars) (cdr vals))))))
  (let* ((vars (map car bindings)) 
         (vals (map cadr bindings))
         (pair (combine vars vals)))
    `(let ,(map (lambda (var) `(,var #f)) vars)
       ,@(map (lambda (p) `(set! ,(car p) ,(cadr p))) pair)
       . ,body)))

(define-macro do 
  (bindings test-and-result . body)
  (let ((variables (map car bindings))
        (inits (map cadr bindings))
        (steps (map (lambda (clause)
                      (if (null? (cddr clause))
                          (car clause)   
                          (caddr clause)))
                    bindings))
        (test (car test-and-result))
        (result (cdr test-and-result)))
    `(letrec ((__loop__
               (lambda ,variables
                 (if ,test
                     (begin . ,result)
                     (begin 
                       ,@body
                       (__loop__ . ,steps))))))
       (__loop__ . ,inits))))

(define-macro delay
  expr
  `(let ((value #f))
     (lambda ()
       (if value
           (car value)
           (let ((x ,expr))
             (if value
                 (car value)
                 (begin (set! value (list x))
                        (car value))))))))


(define-macro quasiquote 
  (x) 
  (define (constant? exp)
    (if (pair? exp) (eq? (car exp) 'quote) (not (symbol? exp))))
  (define (combine-skeletons left right exp)
    (if (and (constant? left) (constant? right))
        (if (and (eqv? (eval left) (car exp))
                 (eqv? (eval right) (cdr exp)))
            (list 'quote exp)
            (list 'quote (cons (eval left) (eval right))))
        (if (null? right)
            (list 'list left)
            (if (and (pair? right) (eq? (car right) 'list))
                (cons 'list (cons left (cdr right)))
                (list 'cons left right)))))
  (define (expand-quasiquote exp nesting)
    (if (vector? exp)
        (list 'apply 'vector (expand-quasiquote (vector->list exp) nesting))
        (if (not (pair? exp))
            (if (constant? exp)
                exp
                (list 'quote exp))
            (if (and (eq? (car exp) 'unquote) (= (length exp) 2))
                (if (= nesting 0)
                    (cadr exp)
                    (combine-skeletons ''unquote 
                                       (expand-quasiquote (cdr exp) (- nesting 1))
                                       exp))
                (if (and (eq? (car exp) 'quasiquote) (= (length exp) 2))
                    (combine-skeletons ''quasiquote 
                                       (expand-quasiquote (cdr exp) (+ nesting 1))
                                       exp)
                    (if (and (pair? (car exp)) (eq? (caar exp) 'unquote-splicing)
                             (= (length (car exp)) 2))
                        (if (= nesting 0)
                            (list 'append (cadr (car exp))
                                  (expand-quasiquote (cdr exp) nesting))
                            (combine-skeletons (expand-quasiquote (car exp) (- nesting 1))
                                               (expand-quasiquote (cdr exp) nesting)
                                               exp))
                        (combine-skeletons (expand-quasiquote (car exp) nesting)
                                           (expand-quasiquote (cdr exp) nesting)
                                           exp)))))))
  (expand-quasiquote x 0))




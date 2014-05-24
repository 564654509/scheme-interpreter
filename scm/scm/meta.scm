;#lang planet neil/sicp
#lang racket
(require rnrs/base-6) 
(require rnrs/mutable-pairs-6)

;(load "lib.scm")
;(load "macro.scm")

(define (eval exp env)
  (cond ((const? exp) exp)
        ((symbol? exp) 
         (let ((val (lookup exp env)))
           (if (null? val)
               (error "unbound variable" exp)
               (cdr val))))
        ((pair? exp)
         (cond ((eq? (car exp) 'quote) (cadr exp))
               ((eq? (car exp) 'if)
                (if (eval (cadr exp) env)
                    (eval (caddr exp) env)
                    (if (not (null? (cdddr exp)))
                        (eval (cadddr exp) env))))
               ((eq? (car exp) 'lambda)
                (list 'closure (cadr exp) (cddr exp) env))
               ((eq? (car exp) 'begin) (eval-seq (cdr exp) env))
               ;((eq? (car exp) 'cond) (eval (cond->if exp) env))
               ((eq? (car exp) 'set!)
                (assign env (cadr exp) (eval (caddr exp) env)))
               ((eq? (car exp) 'define)
                (if (symbol? (cadr exp))
                    (add-binding env (cadr exp) (eval (caddr exp) env))
                    (add-binding env (caadr exp)
                                 (eval (cons 'lambda (cons (cdadr exp) (cddr exp))) env))))
               ((eq? (car exp) 'define-macro)
                (add-binding env (cadr exp) (list 'macro (caddr exp) (cdddr exp))))
               ((eq? (car exp) 'macro) (list 'macro (cadr exp) (cddr exp)))
               (else 
                (let ((proc (eval (car exp) env)))
                  (if (and (pair? proc) (eq? (car proc) 'macro))
                      (let ((body (eval-seq (caddr proc)
                                            (extend env (cadr proc) (cdr exp)))))
                        (if (pair? body)
                            (eval body env) 
                            (eval (list 'begin body) env)))                    
                      (apply* proc
                              (map (lambda (exp) (eval exp env)) (cdr exp))))))))
        (else
         (error "unknow expression type" exp))))

(define (const? exp)
  (or (number? exp) (boolean? exp) (string? exp) (char? exp) (null? exp)))

(define (apply* proc args)
  (if (pair? proc)
      (eval-seq (caddr proc) (extend (cadddr proc) (cadr proc) args))
      (apply proc args)))

(define (eval-seq exp env)
  (if (null? (cdr exp))
      (eval (car exp) env)
      (begin
        (eval (car exp) env)
        (eval-seq (cdr exp) env))))

(define (eval* exp) (eval exp init-env))

(define (map* proc l)
  (if (null? l)
      '()
      (if (not (pair? proc))
          (cons (proc (car l)) (map* proc (cdr l)))
          (cons (eval-seq (caddr proc) (extend (cadddr proc) (cadr proc) (list (car l))))
                (map* proc (cdr l))))))

(define (lookup var e)
  (let nxtrib ((e e))
    (if (null? e)
        '()
        (let nxtelt ((frame (car e)))
          (cond 
            ((null? frame) (nxtrib (cdr e)))
            ((eq? (caar frame) var) (car frame))
            (else (nxtelt (cdr frame))))))))

(define (add-binding e var val)
  (let ((frame (car e)))
    (let loop ((f frame))
      (if (null? f)
          (begin 
            (set! frame (cons (cons var val) frame))
            (set-car! e frame))
          (if (eq? (caar f) var)
              (set-cdr! (car f) val)
              (loop (cdr f)))))))

(define (assign e var val)
  (let ((pair (lookup var e)))
    (if (null? pair)
        (error "unbound variable:" var)     
        (set-cdr! pair val))))

(define (extend e vars vals)
  (let ((frame '()))
    (define (loop vars vals)
      (if (not (null? vals))
          (if (null? vars)
              (error "too much arguments")
              (if (pair? vars)
                  (begin
                    (set! frame (cons (cons (car vars) (car vals)) frame))
                    (loop (cdr vars) (cdr vals)))
                  (set! frame (cons (cons vars vals) frame))))
          (if (and (not (null? vars)) (not (pair? vars)))
              (set! frame (cons (cons vars vals) frame))           
              (if (not (null? vars))
                  (error "too less arguments")))))
    (loop vars vals)
    (cons frame e)))

(define (memq* item lst)
  (if (null? lst) #f (if (not (pair? lst)) #f (if (eq? item (car lst)) lst (memq* item (cdr lst))))))

(define (memv* item lst)
  (if (null? lst) #f (if (eqv? item (car lst)) lst (memv* item (cdr lst)))))

(define (member* item lst)
  (if (null? lst) '() (if (equal? item (car lst)) lst (member* item (cdr lst)))))

(define (assq* item table)
  (if (null? table) #f
      (if (eq? item (caar table)) (car table) (assq* item (cdr table)))))

(define (assv* item table)
  (if (null? table) #f
      (if (eqv? item (caar table)) (car table) (assv* item (cdr table)))))

(define (assoc* item table)
  (if (null? table) #f
      (if (equal? item (caar table)) (car table) (assoc* item (cdr table)))))

(define init-env
  (list (list (cons '+ +) (cons '- -) (cons '* *) (cons '/ /) (cons '< <) (cons '#t #t) (cons '#f #f)
              (cons '<= <=) (cons '= =) (cons '>= >=) (cons '> >) (cons 'apply apply) (cons 'eval eval*)
              (cons 'car car) (cons 'cdr cdr) (cons 'cons cons) (cons 'eq? eq?) (cons 'abs abs)
              (cons 'eqv? eqv?) (cons 'list list) (cons 'null? null?) (cons 'newline newline)         
              (cons 'vector? vector?) (cons 'vector->list vector->list) (cons 'pair? pair?)
              (cons 'length length) (cons 'map map*) (cons 'symbol? symbol?) (cons 'not not)
              (cons 'cadr cadr) (cons 'caar caar) (cons 'vector vector) (cons 'display display)
              (cons 'append append) (cons 'sqrt sqrt) (cons 'member member*) (cons 'zero? zero?)
              (cons 'gensym gensym) (cons 'memv* memv*) (cons 'memq memq*) (cons 'string->symbol string->symbol)
              (cons 'make-vector make-vector) (cons 'vector-set! vector-set!) (cons 'cddr cddr)
              (cons 'caddr caddr) (cons 'odd? odd?) (cons 'even? even?) (cons 'assq assq*)
              (cons 'assv assv*) (cons 'assoc assoc*) (cons 'cdar cdar)
              (cons 'string->uninterned-symbol string->uninterned-symbol) (cons 'memv memv)
              (cons 'equal? equal?) (cons 'set-cdr! set-cdr!) (cons 'string-append string-append)
              (cons 'number->string number->string))))



;******************************lisp-style macro*****************************

;This macro is mainly taken from Peter Norvig http://norvig.com/jscheme/primitives.scm
;I have modified some details to make it works well on my interpreter.

(define macro-or
  '(define-macro or              
     args 
     (if (null? args) 
         #f
         (if (null? (cdr args))
             (car args)
             (list 'if (car args)
                   #t (cons 'or (cdr args)))))))

(define macro-and
  '(define-macro and             
     args 
     (if (null? args)
         #t
         (if (null? (cdr args))
             (car args)
             (list 'if (car args)
                   (cons 'and (cdr args)) #f)))))  
                   
(define macro-qquote  
  '(define-macro quasiquote 
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
     (expand-quasiquote x 0)))

			
(define macro-let
  '(define-macro let 
     (bindings . body)
     (define (named-let name bindings body)
       `(let ((,name #f))
          (set! ,name (lambda ,(map car bindings) . ,body))
          (,name . ,(map cadr bindings))))
     (if (symbol? bindings) 
         (named-let bindings (car body) (cdr body))
         `((lambda ,(map car bindings) . ,body) . ,(map cadr bindings)))))
			   
(define macro-let*
  '(define-macro let* 
     (bindings . body)
     (if (null? bindings) `((lambda () . ,body))
         `(let (,(car bindings))
            (let* ,(cdr bindings) . ,body)))))

(define macro-letrec
  '(define-macro letrec
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
          . ,body))))

(define macro-do
  '(define do
     (macro (bindings test-and-result . body)
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
                 (__loop__ . ,inits))))))


(define macro-case          
  '(define-macro case 
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
                                    `((memv* ,key ',case) ,@exprs)))
                               (else
                                `((eqv? ,key ',case) ,@exprs))))
                       (error 'case "invalid syntax in ~a" clause)))
                 clauses)))
     (if (pair? key)
         (let ((newkey (gensym)))
           `(let ((,newkey ,key))
              ,(case-make-clauses newkey)))
         (case-make-clauses key))))

(define macro-cond
  '(define-macro cond
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
                            (cond ,@(cdr clauses))))))))))
                            
(define macro-when                            
  '(define-macro when
     (test . body)
     `(if ,test (begin ,@body))))

(define macro-unless
  '(define-macro unless
     (test . body)
     `(if (not ,test) (begin ,@body))))

(eval macro-cond init-env)
(eval macro-qquote init-env)
(eval macro-and init-env)
(eval macro-or init-env)
(eval macro-let init-env)
(eval macro-let* init-env)
(eval macro-letrec init-env)
(eval macro-case init-env)
(eval macro-do init-env)
(eval macro-when init-env)
(eval macro-unless init-env)


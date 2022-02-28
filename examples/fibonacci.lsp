(define fib (number) (if (< number 2) (1) (0)))
(define fib (number) (if (< number 2) (1) (+ (fib (- x 1) (fib (- x 2))))))

(print (fib 3))

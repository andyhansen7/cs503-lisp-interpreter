(define fib (number) (if (< number 2) (1) (0)))

x = 1
y = 1

def fib(z):
    if(z < 2) return 1
    else
        set x fib(z - 1)
        set y fib(z - 2)
        print (x+y)

(define fib (number) (if (< number 2) (1) (+ (fib (- number 1) (fib (- number 2))))))

(define fib (number) (if (< number 2) (1) (begin (set fib_x (fib (- number 1))) (sex fib_y (fib (- number 2))) (+ fib_x fib_y))))

(print (fib 3))

(define incpr () (begin (set var (+ var 1)) (print var)))

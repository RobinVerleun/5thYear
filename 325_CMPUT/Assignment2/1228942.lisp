
#|
	CMPUT 325 Assignment 2
	March 2, 2017
	Robin Verleun
	1228942
|#

;Interpreter written for lisp. Takes in two parameters:
; E: A function call, including arguments. Must be passed in as a quoted argument.
; P: A program/function definition provided for and user functions called in E.
;fl-interp breaks down the argument E into it's smallest components, capturing function names and
;arguments. If a function name is captured, it is found in a list, and applied to the arguments.
;Recursive calls on fl-interp on those arguments break the problem down until atoms are found, and
;return the atom.
(defun fl-interp (E P)
	(cond
		((atom E) E) 				;Passing args into the function
		(t
			(let* ( (func (car E)) (args (cdr E)) (userFunc (parseFunction func P)) ) 
				(cond
					;Handle primitives

					;Primitives that require two arguments and can be called by name
					((member func '(+ - * > < = eq cons equal)) (apply func (two-args args P)))

					;Primitives which require one argument and can be called by name
					((member func '(null atom)) (apply func (list (car args))))

					;Primitives which require special interpretation to function
					((eq func 'and) (and (fl-interp (car args) P) (fl-interp (car (cdr args)) P)))
					((eq func 'or) (or (fl-interp (car args) P) (fl-interp (car (cdr args)) P)))
					((eq func 'isnumber) (numberp (fl-interp (car args) P)))
					((eq func 'first) (car (car args)))
					((eq func 'rest) (cdr (car args)))
					((eq func 'not) (not (fl-interp (car args) P)))
					((eq func 'if) (if (fl-interp (car args) P) (fl-interp (car (cdr args)) P) (fl-interp (car (cdr (cdr args))) P)))

					;If the above fail, it is a user defined function
					;Function was stored above in userFunc. 
					(userFunc (fl-interp (car (insertValues (parseVars (cdr userFunc)) (parseBody userFunc) args)) P ))

					;Return result of userFunc.
					(t E) 		
				)
			)	
		)
	)
)

;Takes in a list of n arguments and a function parameter P
;Send a single argument to the fl-interp function, and 
(defun two-args (args P)
	(if (null args)
		nil
		(cons (fl-interp (car args) P) (two-args (cdr args) P))
	)
)

;Check for the function name in the program call, to verify work needs to be done
;Example: functionCall = test, P = (test var1 var2 var3)
;Inputs: functionCall, a name. P, a program provided
;Outputs: The function definition as defined in P
(defun parseFunction (functionCall P)
	;Check if the Program is null
	(if (null P)
		nil
		(if (eq functionCall (caar P))
			(car P)
			(parseFunction functionCall (cdr P))
		)
	)
)

;Get all the variables before the equal sign. Pass in a user function without a 
;function name attached, due to CDR call in the main function.
(defun parseVars (L)
	(if (null L)
		nil
		(if (eq (car L) '=)
			nil
			(cons (car L) (parseVars (cdr L)))
		)
	)
)

;Get the body of the function. 
(defun parseBody (L)
	(if (null L)
		nil
		(if (eq (car L) '=)
			(cdr L)
			(parseBody (cdr L))
		)
	)
)

;Replace a single var throughout the entire body of the function
;The body is broken down into chunks and analyzed one at a time. If it's an atom
;and equals var, arg is returned in its place.
(defun replace_var (var body arg)
	(cond
		((null var) nil)
		((atom body) 
			(if (eq var body) ;Body element matches variable
				arg
				body
			)
		)
		(t (cons (replace_var var (car body) arg) (replace_var var (cdr body) arg)))
	)
)

;Swap the values given for the variables in the body of the program
;If there's one var left, replace it directly and return
;else, swap the current variable, and then recall with the next var/arg pair
(defun insertValues (vars body args)
	(if (null vars)
		body
		(if (null (cdr vars))
			(replace_var (car vars) body (car args))
			(insertValues (cdr vars) (replace_var (car vars) body (car args)) (cdr args))
		)
	)
)



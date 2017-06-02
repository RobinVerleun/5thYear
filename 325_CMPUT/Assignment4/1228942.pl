:- use_module(library(clpfd)).


% Question 1

fourSquares(N, [S1, S2, S3, S4]) :-
    S1 in 0..N, S2 in 0..N, S3 in 0..N, S4 in 0..N,
    S1 #=< S2, S2 #=< S3, S3 #=< S4,
    S1^2 + S2^2 + S3^2 + S4^2 #= N,
    label([S1, S2, S3, S4]).



% Question 2

disarm(Adivision, Bdivision, Solution) :- disarm(Adivision, Bdivision, Solution, 0).

%Base case for recursive calls - empty lists means that nothing is returned as a solution
disarm([], [], S, _) :- S=[].

% Handle case where Adivision surrenders two forces, Bdivision surrenders one
% Take two values from Adivision and one from Bdivision that are equal.
% Uses constraint programming to find elements which meet the above criteria.
% Compares the strength of the removed forces to the previous removal, and ensures it's greater.

disarm(Adivision, Bdivision, Solution, PastValue) :-
	Forces = [A1,A2,B], select(A1, Adivision, ARemainder1), select(A2, ARemainder1, ARemainder2), select(B, Bdivision, BRemainder),
	A1 #=< A2, A1+A2 #= B,
	B #>= PastValue,

	%Find the next iteration
	disarm(ARemainder2, BRemainder, S, B),

	%Append the found solution with S into Solutions
	append([[[A1,A2],[B]]], S, Solution),
	label(Forces).


% Handle case where BDivisions surrenders two forced, Adivision surrenders one
% Takes two values from Bdivision and one from Adivision that are equal.
% Uses constraint programming to find elements which meet the above criteria.
% Compares the strength of the removed forces to the previous removal, and ensures it's greater.

disarm(Adivision, Bdivision, Solution, PastValue) :-
	Forces = [A, B1, B2], select(A, Adivision, ARemainder), select(B1, Bdivision, BRemainder1), select(B2, BRemainder1, Bremainder2),
	B1 #=< B2, B1+B2 #= A,
	A #>= PastValue,

	%Find the next iteration
	disarm(ARemainder, Bremainder2, S, A),

	%Append the found solution with S into Solutions
	append([[[A], [B1, B2]]], S, Solution),
	label(Forces).
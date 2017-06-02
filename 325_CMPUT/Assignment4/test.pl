:- use_module(library(clpfd)).

fourSquares(N, [S1, S2, S3, S4]) :-
    S1 in 0..N, S2 in 0..N, S3 in 0..N, S4 in 0..N,
    S1 #=< S2, S2 #=< S3, S3 #=< S4,
    S1^2 + S2^2 + S3^2 + S4^2 #= N,
    label([S1, S2, S3, S4]).


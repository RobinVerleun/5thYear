
checkAppend(X, L, N) :- member(X, L); append([X], L, N).	

xunique([], []).
xunique([A|L1], L2) :- print(A), xunique(L1, N), member(A, N), append(A, N, L2).
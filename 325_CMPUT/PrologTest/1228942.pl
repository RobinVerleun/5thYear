/*
	1. xreverse

	Define the predicate xreverse(+L, ?R) to reverse a list, where L is a given list 
	and R is either a variable or another given list.

	Examples: 
		xreverse([7,3,4],[4,3,7]) should return true,
		xreverse([7,3,4],[4,3,5]) should return false,
		xreverse([7,3,4], R) should return R = [4,3,7].

	Your program should generate only one solution, so if the user presses ";" the next 
	answer should be "false".

	/////////////////////////////////////////////////////////////////////////////////////

	Description:
		Clause 1: 
			A base case given as a fact. If two empty lists are passed in, will
			return true.
		Clause 2:
			Takes in two lists and splits the first one. Recursively calls on the
			first list, splitting off all elements until the base case. When the 
			base case is called, begins to appends all the split variables in reverse
			order to N. On the top level call, N is unified into L2 - if L2 is given
			by the user, then the program will return true or false. Otherwise, L2 is
			returned.
*/

	xreverse([], []).
	xreverse([A|L1], L2) :- xreverse(L1, N), append(N, [A], L2).




/*
	2. xunique

	Define the predicate xunique(L1, L2) where L1 is a given list of atoms and 
	L2 is a copy of L1 where all the duplicates have been removed. L2 can be 
	either a variable or a given list. The elements of L2 should be in the order 
	in which they first appear in L1.

	Examples: 
		xunique([a,c,a,d], O) should return O = [a,c,d], 
		xunique([a,c,a,d], [a,c,d]) should return true, 
		xunique([a,c,a,d], [c,a,d]) should return false (because of wrong order), 
		xunique([a,a,a,a,a,b,b,b,b,b,c,c,c,c,b,a], O) should return O = [a,b,c], 
		xunique([], O) should return O = [].

	Your program should generate only one solution, so if the user presses ";" the next 
	answer should be "false".

	/////////////////////////////////////////////////////////////////////////////////////

	Description:
		The problem is a set of step by step rules.

		Clause 1: 
			Casts the public interface for the function into an internal representation,
			removing unecessary variables from the public interface. Initialized an 
			empty list for the unique atoms.

		Clause 2:
			Checks to see if the first atom of a given list L1 is already a member of the
			unique list. If so, xunique is called with the remainder of the list L1.

		Clause 3:
			If the first atom of a given list is not a member of the Unique list, clause
			3 appends the unique element to the Unique list, and calls xunique with the 
			NewUnique list.

		Clause 4:
			When the initial list is empty, the UniqueList is unified to variable A. If
			a list has not been given by the user of unique values, A is returned as the 
			list of unique variables. If a list has been given, Prolog will attempt to
			unify the two and return true if they match, and false if they do not.
*/

	xunique(L1, L2) :- xunique(L1, [], L2).
	xunique([A|Rest], Unique, L2) :- member(A, Unique), xunique(Rest, Unique, L2).
	xunique([A|Rest], Unique, L2) :- notMember(A, Unique), append(Unique, [A], NewUnique), xunique(Rest, NewUnique, L2).
	xunique([], A, A).

	%Recursive call over a list to see if Elem exists in the list. Returns true or false.
	notMember(Elem, [First|Rest]) :- 
		Elem \== First, notMember(Elem, Rest). 

	notMember(_, []).



/*
	3. xdiff

	Define the predicate xdiff(L1, L2, L) where L1 and L2 are given lists of atoms, and 
	L contains the elements that are contained in L1 but not L2 (set difference of L1 and L2). 

	Examples: 
		xdiff([a,b,f,c,d],[e,b,a,c],L) should return L=[f,d], 
		xdiff([p,u,e,r,k,l,o,a,g],[n,k,e,a,b,u,t],L) should return L = [p,r,l,o,g], 
		xdiff([],[e,b,a,c],L) should return L = [].

	Your program should generate only one solution, so if the user presses ";" the next 
	answer should be "false".

	/////////////////////////////////////////////////////////////////////////////////////

	Description:
		A simple function which finds the difference between the sets L1 and L2, then generates
		a list of unique elements from that intermediate list and returns it.
*/

	xdiff(L1, L2, L) :- 
		subtract(L1, L2, R), 
		xunique(R, L).



/*
	4. removeLast

	Define the predicate removeLast(L, L1, Last) where L is a given non-empty list, L1 is 
	the result of removing the last element from L, and Last is that last element. L1 and 
	Last can be either variables or given values.

	Examples: 
		removeLast([a,c,a,d], L1, Last) should return L1 = [a,c,a], Last = d, 
		removeLast([a,c,a,d], L1, d) should return L1 = [a,c,a], 
		removeLast([a,c,a,d], L1, [d]) should return false (why?), 
		removeLast([a], L1, Last) should return L1 = [], Last = a, 
		removeLast([[a,b,c]], L1, Last) should return L1 = [], Last = [a,b,c].

	Your program should generate only one solution, so if the user presses ";" the next 
	answer should be "false".

	/////////////////////////////////////////////////////////////////////////////////////

	Description:
		Passes the input list to reverse, and splits the output into the return value 
		Last and a temporary list R. R is then reversed again and stored in L1.

*/	

	removeLast(L, L1, Last) :- 
		reverse(L, [Last|R]), 
		reverse(R, L1). 



/*
	5. clique

The clique problem is a graph-theoretic problem of finding a subset of nodes where each node is 
connected to every other node in the subset. In this problem, a graph will be represented by a 
collection of predicates, node(A) and edge(A,B), where A and B are constants. Edges are undirected 
but only written once, so edge(A,B) also implies edge(B,A).

*/

/* Functions given in the assignment */

clique(L) :- findall(X,node(X),Nodes), 
			 xsubset(L,Nodes), 
			 allConnected(L).

xsubset([], _).

xsubset([X|Xs], Set) :-
	xappend(_, [X|Set1], Set), 
	xsubset(Xs, Set1).

xappend([], L, L).

xappend([H|T], L, [H|R]) :- 
	xappend(T, L, R).


/* My defined functions. */

/*
	5.1

	Use the predicates clique, xsubset and xappend above. Your job is to define the
	predicate allConnected(L) to test if each node in L is connected to each other 
	node in L. A node A is connected to another node B if either edge(A,B) or 
	edge(B,A) is true.

	This is a simple (and very slow) "generate and test" approach to solving the 
	clique problem. Upon backtracking, the subset predicate in your program will 
	generate all the subsets, and each subset will be tested by your allConnected 
	predicate.

	allConnected(L) is true for an empty list, L= []. The recursive case is: 
	allConnected([A|L]) if A is connected to every node in L and allConnected(L). Thus, 
	you need to define a predicate, say connect(A,L), to test if A is connected to 
	every node in L.
*/

	allConnected([]). 
	allConnected([A|L]) :- connect(A, L), allConnected(L).

	/* Check the edges for a connection, both ways. */

	connect(_, []).
	connect(Node, [L1|L2]) :- edge(Node, L1), connect(Node, L2).
	connect(Node, [L1|L2]) :- edge(L1, Node), connect(Node, L2).



/*
	5.2
	
	Write a predicate maxclique(+N, -Cliques) to compute all the maximal cliques of
	size N that are contained in a given graph. N is the given input, Cliques is the 
	output you compute: a list of cliques. A clique is maximal if there is no larger 
	clique that contains it. In the example above, cliques [a,b,c] and [a,d] are maximal, 
	but [a,b] is not, since it is contained in [a,b,c].

	Your program should generate only one solution (the list Cliques). If the user 
	presses ";" the next answer should be "false".
*/

	/* maxclique */
	maxclique(N, Clique) :- findall(C, filterCliqueBySize(N, C), Tmp1),
							findall(M, (member(M, Tmp1), isMaximum(M, Tmp1)), Tmp2),
							findall(D, (member(D, Tmp2), length(D, N)), Clique).

	/* 
		get a list of all cliques bigger than N
	*/
	filterCliqueBySize(Size, Clique) :- clique(Clique), length(Clique, G), G >= Size.


	/*
		Goes over the set of all cliques above a certain size N, and
		determines if the clique is a maximum at at least that size,
		and not a subset of a larger set.
	*/
	isMaximum(_, []).
	isMaximum(L, [H|T]) :- L \== H, isNotSubset(L, H), isMaximum(L, T).
	isMaximum(L, [H|T]) :- L == H, isMaximum(L, T).


	/*
		Determines if a given lists sublists is a subset of another given 
		master list.
	*/
	isNotSubset([H|_], X) :- notMember(H, X).
	isNotSubset([H|T], X) :- member(H, X), isNotSubset(T, X).





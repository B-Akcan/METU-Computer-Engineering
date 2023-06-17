:- module(main, [is_vote_wasted/2, is_candidate_elected/2, candidate_count_from_city/3, all_parties/1, all_candidates_from_party/2, all_elected_from_party/2, election_rate/2, council_percentage/2, alternative_debate_setups/2]).
:- [kb].

% DO NOT CHANGE THE UPPER CONTENT, WRITE YOUR CODE AFTER THIS LINE

is_vote_wasted(City, Party) :- not(elected(City, Party, X)).

is_candidate_elected(Name, Party) :- elected(City, Party, X), candidate(Name, Party, City, Y), Y =< X.

candidate_count_from_city([], City, Count) :- Count is 0.
candidate_count_from_city([H | T], City, Count) :- candidate_count_from_city(T, City, TempCount), candidate(H, _, City, _), Count is TempCount + 1.
candidate_count_from_city([H | T], City, Count) :- candidate_count_from_city(T, City, Count), not(candidate(H, _, City, _)).

all_parties(List) :- findall(X, party(X, _), List).

all_candidates_from_party(Party, List) :- findall(X, candidate(X, Party, _, _), List).

all_elected_from_party(Party, List) :- findall(X, is_candidate_elected(X, Party), List).

election_rate(Party, Percentage) :- all_elected_from_party(Party, L1), all_candidates_from_party(Party, L2), length(L1, R1), length(L2, R2), Percentage is R1 / R2, format('~2f', Percentage).

council_percentage(Party, Percentage) :- all_elected_from_party(Party, L), length(L,R), to_elect(X), Percentage is R / X, format('~1f', Percentage).

comb(_, [], 0).
comb([_ | R], Res, N) :- N > 0, comb(R, Res, N).
comb([H | R], [H | Res], N) :- N > 0, M is N-1, comb(R, Res, M).

alternative_debate_setups('', []).
alternative_debate_setups(Atom, List) :- atom_chars(Atom, [H | T]), party(P, H), all_candidates_from_party(P, L), comb(L, R, 1), append(List, R, NewList), atomic_list_concat(T, '', NewAtom), alternative_debate_setups(NewAtom, NewList).





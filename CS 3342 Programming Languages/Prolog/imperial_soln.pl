factor_in_inches(Unit1, InchFactor) :-
	Unit1 = inch,
	InchFactor is float(1);
	scale(Unit1, Factor1, Unit2),
	factor_in_inches(Unit2, Factor2),
	InchFactor is Factor1 * Factor2.

scale_factor(Unit1, Unit2, Factor) :-
	factor_in_inches(Unit1, Factor1),
	factor_in_inches(Unit2, Factor2),
	Factor is Factor2 / Factor1.

convert(Unit1, Quantity1, Unit2, Quantity2) :-
	scale_factor(Unit2, Unit1, Factor),
	Quantity2 is Quantity1 * Factor.
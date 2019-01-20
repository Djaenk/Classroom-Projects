//Anthony Wang
//47733248
//Lab 6 - Fall 2018

import java.util.ArrayList;

public class Field{
	private ArrayList<Base> bases = new ArrayList<Base>();

	public Field(){
		bases.add(new Base("Dugout"));
		bases.add(new Base("BatterBox"));
		bases.add(new Base("First"));
		bases.add(new Base("Second"));
		bases.add(new Base("Third"));
		bases.add(new Base("Home"));
	}
	public Base getDugout(){
		return bases.get(0);
	}
	public Base getBatterBox(){
		return bases.get(1);
	}
	public Base moveAhead(Base starting_base, int bases_run){
		int new_base_index = bases.indexOf(starting_base) + bases_run;
		int capped_new_base_index = Math.min(new_base_index, 5);
		return bases.get(capped_new_base_index);
	}
}
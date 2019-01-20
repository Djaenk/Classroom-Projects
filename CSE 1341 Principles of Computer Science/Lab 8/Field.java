//Anthony Wang
//47733248
//Lab 7 - Fall 2018

import java.util.ArrayList;

public class Field{
	private ArrayList<Base> bases = new ArrayList<Base>();

	public Field(){ //initializes a field creates a field with bases
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
		int new_base_index = bases.indexOf(starting_base) + bases_run; //the index of the base a player is running to is the sum of the index of the base the player is currently on plus how many bases they will run
		int capped_new_base_index = Math.min(new_base_index, 5); //if the base that the player will run to has an index greater than 5 (home plate) then set the index to 5
		return bases.get(capped_new_base_index);
	}
}
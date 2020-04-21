//Anthony Wang
//47733248
//Lab 7 - Fall 2018

import java.util.Random;

public class Dud extends Player{
	public Dud(String name, Base base){
		super(name, base);
	}
	public RollResults roll(){
		Random random = new Random();
		this.rolls = new int[2];
        this.rolls[0] = random.nextInt(10) + 1; //rolls ten sided die from 1-10 instead
		this.rolls[1] = random.nextInt(10) + 1;
		String output = " Rolled " + this.rolls[0] + " " + this.rolls[1];
		return new RollResults(this.rolls, output);
	}
}
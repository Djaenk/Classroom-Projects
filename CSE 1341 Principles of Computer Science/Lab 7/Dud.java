//Anthony Wang
//47733248
//Lab 7 - Fall 2018

import java.util.Random;

public class Dud extends Player{
	public Dud(String name, Base base){
		super(name, base);
	}
	public int[] roll(){
		Random random = new Random();
		int[] rolls = new int[2];
        rolls[0] = random.nextInt(10) + 1; //rolls ten sided die from 1-10 instead
		rolls[1] = random.nextInt(10) + 1;
		return rolls;
	}
}
//Anthony Wang
//47733248
//Lab 7 - Fall 2018

import java.util.Random;

public class Ringer extends Player{
	public Ringer(String name, Base base){
		super(name, base);
	}
	public int[] roll(){
		Random random = new Random();
		int[] rolls = new int[2];
        rolls[0] = random.nextInt(3) + 1; //rolls three sided die from 1-3 instead
		rolls[1] = random.nextInt(3) + 1;
		return rolls;
	}
}
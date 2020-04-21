//Anthony Wang
//47733248
//Lab 7 - Fall 2018

import java.util.Random;

public class Player{
	private String name;
	private int strikes;
	private int balls;
	private int hits;
	private int at_bats;
	protected int[] rolls;
	private RollResults roll_results;
	private String output;
	private Base base;
	public Field field = new Field();

	public Player(String name, Base base){
		this.name = name;
		this.base = field.getDugout();
		this.output = "";
		hits = 0;
		at_bats = 0;
	}
	public String getName(){
		return this.name;
	}
	public void setName(String name){
		this.name = name;
	}
	public void setOutput(String output){
		this.output = output;
	}
	public int getHits(){
		return this.hits;
	}
	public int getAt_bats(){
		return this.at_bats;
	}
	public String getOutput(){
		return output;
	}
	public Base getLocation(){
		return this.base;
	}
	public void resetOutput(){
		this.output = "";
	}
	public void setLocation(Base base){
		this.base = base;
	}
	public boolean isNotinDugout(){
		if(this.base.equals(field.getDugout())){ //if base is dugout then return false, else true
			return false;
		}
		else{
			return true;
		}
	}
	public int takeTurn(){
		this.balls = 0;
		this.strikes = 0;
		this.at_bats++;
		for(; (this.balls < 4) && (this.strikes < 3);){ //continue looping as long as there are less than 4 balls and less than 3 strikes
			int swing = bat();
			System.out.print("Rolled " + this.rolls[0] + " " + this.rolls[1]);
            if(swing == 1){
				output += " Single!\n";
				this.hits++;
				return 1;
            }
            else if(swing == 2){
				output += " Double!\n";
				this.hits++;
				return 2;
            }
            else if(swing == 3){
				output += " Triple!\n";
				this.hits++;
				return 3;
            }
            else if(swing == 4){
				output += " Home Run!\n";
				this.hits++;
				return 4;
            }
            else if(swing == -1){
				output += " Strike!\n";
				this.strikes++;
				if(this.strikes == 3){
					output += " Strikeout!\n";
					return 0;
				}
            }
            else if(swing == -2){
				output += " Ball!\n";
				this.balls++;
				if(this.balls == 4){
					output += " Base on Balls!\n";
					return 1;
				}

            }
            else{
                System.out.println(" how on earth did I manage to break this"); //acknowledges unnacounted event
			}
		}
	return 0;
	}
	public RollResults roll(){
		Random random = new Random();
		this.rolls = new int[2];
        this.rolls[0] = random.nextInt(6) + 1;
		this.rolls[1] = random.nextInt(6) + 1;
		String output = " Rolled " + this.rolls[0] + " " + this.rolls[1];
		return new RollResults(this.rolls, output);
	}
	public int bat(){
		this.roll_results = roll();
        if(this.rolls[0] == this.rolls[1] && this.rolls[0] <= 4){
            return this.rolls[0]; //returns value of dice if same and less than or equal to 4
        }
        else if((this.rolls[0] + this.rolls[1]) % 2 == 0){
            return -1; //returns -1 if dice have different values and sum to an even number
        }
        else{
            return -2; //returns -2 if sums to odd number
        }
	}
	public double getBattingAverage(){
		double batting_average = (double)this.hits / (double)this.at_bats; //cast the number of at bats and number of hits to double, then perform division and return quotient
		return batting_average;
	}
	public String toString(){
		return "player" + this.name + "base" + this.base;
	}
}
//Anthony Wang
//47733248
//Lab 6 - Fall 2018

import java.util.Random;

public class Player{
	private String name;
	private int strikes;
	private int balls;
	private Base base;
	private int die_1;
	private int die_2;
	public Field field = new Field();

	public Player(String name, Base base){
		this.name = name;
		this.base = field.getDugout();
	}
	public String getName(){
		return this.name;
	}
	public void setName(String name){
		this.name = name;
	}
	public Base getLocation(){
		return this.base;
	}
	public void setLocation(Base base){
		this.base = base;
	}
	public boolean isNotinDugout(){
		if(this.base == field.getDugout()){ //if position is -1 (in the dugout) then return false, else true
			return false;
		}
		else{
			return true;
		}
	}
	public int takeTurn(){
		this.balls = 0;
		this.strikes = 0;
		for(; (this.balls < 4) && (this.strikes < 3);){ //continue looping as long as there are less than 4 balls and less than 3 strikes
			int swing = bat();
			System.out.print("Rolled " + die_1 + " " + die_2);
            if(swing == 1){
				System.out.println(" SINGLE!");
				return 1;
            }
            else if(swing == 2){
				System.out.println(" DOUBLE!");
				return 2;
            }
            else if(swing == 3){
				System.out.println(" TRIPLE!");
				return 3;
            }
            else if(swing == 4){
				System.out.println(" HOME RUN!");
				return 4;
            }
            else if(swing == -1){
				System.out.println(" STRIKE!");
				this.strikes++;
				if(this.strikes == 3){
					System.out.println("Strikeout!");
					return 0;
				}
            }
            else if(swing == -2){
				System.out.println(" BALL!");
				this.balls++;
				if(this.balls == 4){
					System.out.println("Base on balls!");
					return 1;
				}

            }
            else{
                System.out.println(" how on earth did I manage to break this"); //acknowledges unnacounted event
			}
		}
	return 0;
	}
	public int bat(){
		Random random = new Random();
        die_1 = random.nextInt(6) + 1;
        die_2 = random.nextInt(6) + 1;
        if(die_1 == die_2 && die_1 <= 4){
            return die_1; //returns value of dice if same
        }
        else if((die_1 + die_2) % 2 == 0){
            return -1; //returns -1 if dice have different values and sum to an even number
        }
        else{
            return -2; //returns -2 if sums to odd number
        }
	}
	public String toString(){
		return "player" + this.name + "base" + this.base;
	}
}
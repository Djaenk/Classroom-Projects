import java.util.Random;

public class BatterUp5{
    public static int die_1;
	public static int die_2;
	public static String[] players = {"player1", "player2", "player3", "player4", "player5", "player6", "player7", "player8", "player9"};
	public static int[] locations = {-1, -1, -1, -1, -1, -1, -1, -1, -1}; //player locations, indices correspond
	public static int score = 0;

    public static int bat(){ //rolls two dice
        Random random = new Random();
        die_1 = random.nextInt(6) + 1;
        die_2 = random.nextInt(6) + 1;
        if(die_1 == die_2 && die_1 <= 4){
            return die_1; //returs value of dice if same
        }
        else if((die_1 + die_2) % 2 == 0){
            return -1; //returns -1 if dice have different values and sum to an even number
        }
        else{
            return -2; //returns -2 if sums to odd number
        }
	}
	public static boolean batterTakeTurn(){
		int balls = 0;
		int strikes = 0;
		boolean is_out = false; //if the batter gets a base, then the functions returns that they aren't out
		for(; (balls < 4) && (strikes < 3);){ //continue looping as long as there are less than 4 balls and less than 3 strikes
			int swing = bat();
			System.out.print("Rolled " + die_1 + " " + die_2);
            if(swing == 1){
				System.out.println(" SINGLE!");
				movePlayers(1);
				return is_out;
            }
            else if(swing == 2){
				System.out.println(" DOUBLE!");
				movePlayers(2);
				return is_out;
            }
            else if(swing == 3){
				System.out.println(" TRIPLE!");
				movePlayers(3);
				return is_out;
            }
            else if(swing == 4){
				System.out.println(" HOME RUN!");
				movePlayers(4);
				return is_out;
            }
            else if(swing == -1){
				System.out.println(" STRIKE!");
				strikes++;
				if(strikes == 3){
					System.out.println("Strikeout!");
					is_out = true; //upon striking out, is_out is true and is returned by the function
					return is_out;
				}
            }
            else if(swing == -2){
				System.out.println(" BALL!");
				balls++;
				if(balls == 4){
					System.out.println("Base on balls!");
					movePlayers(1);
					return is_out;
				}

            }
            else{
                System.out.println(" how on earth did I manage to break this"); //catches an error in the event an unaccounted scenario occurs
			}
		}
		return true;
	}
	public static void movePlayers(int advance){ //I don't know anything about baseball so I'm sorry if this isn't how the players actually move
		for(int i = 0; i < locations.length; i++){ //advances all the players on the field
			if(locations[i] != -1){
				locations[i] += advance;
			}
		}
		for(int i = 0; i < locations.length; i++){
			if(locations[i] >= 4){ //if a player has run all four bases, they've scored and return to the dugout
				score++;
				System.out.println(players[i] + " scored!!");
				locations[i] = -1;
			}
		}
	}
	public static void displayField(){
		String first_base = "empty";
		String second_base = "empty";
		String third_base = "empty";
		for(int i = 0; i < locations.length; i++){
			if(locations[i] == 1){
				first_base = players[i];
			}
			else if(locations[i] == 2){
				second_base = players[i];
			}
			else if(locations[i] == 3){
				third_base = players[i];
			}
		}
		System.out.println("[ 1 ] " + first_base + "  [ 2 ] " + second_base + "  [ 3 ] " + third_base);
	}
    public static void main(String[] args){
		int outs = 0;
		while(outs < 3){
			for(int i = 0; i < players.length; i++){
				System.out.println();
				System.out.println("SCORE: " + score);
				displayField();
				System.out.println(players[i] + " is at bat with " + outs + " out(s)");
				locations[i] = 0;
				if(batterTakeTurn() == true){
					outs++;
					locations[i] = -1;
				}
				if(outs >= 3){
					break;
				}
			}
		}
    }
}
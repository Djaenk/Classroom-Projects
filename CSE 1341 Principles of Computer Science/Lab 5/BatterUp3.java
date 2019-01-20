import java.util.Random;

public class BatterUp3{
    public static int die_1;
	public static int die_2;
	public static String[] players = {"player1", "player2", "player3", "player4", "player5", "player6", "player7", "player8", "player9"};

    public static int bat(){
        Random random = new Random();
        die_1 = random.nextInt(6) + 1;
        die_2 = random.nextInt(6) + 1;
        if(die_1 == die_2 && die_1 <= 4){
            return die_1;
        }
        else if((die_1 + die_2) % 2 == 0){
            return -1;
        }
        else{
            return -2;
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
				return is_out;
            }
            else if(swing == 2){
				System.out.println(" DOUBLE!");
				return is_out;
            }
            else if(swing == 3){
				System.out.println(" TRIPLE!");
				return is_out;
            }
            else if(swing == 4){
				System.out.println(" HOME RUN!");
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
					return is_out;
				}

            }
            else{
                System.out.println(" how on earth did you manage to break this"); //catches an error in the event an unaccounted scenario occurs
			}
		}
		return true;
	}
    public static void main(String[] args){
		int outs = 0;
		while(outs < 3){
			for(int i = 0; i < players.length; i++){
				System.out.println();
				System.out.println(players[i] + " is at bat with " + outs + " outs");
				if(batterTakeTurn() == true){
					outs++;
				}
				if(outs >= 3){
					break;
				}
			}
		}
    }
}
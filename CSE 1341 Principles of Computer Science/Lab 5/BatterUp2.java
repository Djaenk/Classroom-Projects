import java.util.Random;

public class BatterUp2{
    public static int die_1;
    public static int die_2;

    public static int bat(){ //rolls two dice to determine result of the bat
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
	public static void batterTakeTurn(){
		int balls = 0;
		int strikes = 0;
		for(; (balls < 4) && (strikes < 3);){ //continue looping as long as there are less than 4 balls and less than 3 strikes
			int swing = bat();
			System.out.print("Rolled " + die_1 + " " + die_2);
            if(swing == 1){
				System.out.println(" SINGLE!");
				break;
            }
            else if(swing == 2){
				System.out.println(" DOUBLE!");
				break;
            }
            else if(swing == 3){
				System.out.println(" TRIPLE!");
				break;
            }
            else if(swing == 4){
				System.out.println(" HOME RUN!");
				break;
            }
            else if(swing == -1){
				System.out.println(" STRIKE!");
				strikes++; //if a -1 is rolled, increment the strike counter and if strike counter hits three then strikeout
				if(strikes == 3){
					System.out.println("Strikeout!");
				}
            }
            else if(swing == -2){
				System.out.println(" BALL!");
				balls++;
				if(balls == 4){
					System.out.println("Base on balls!");
				}

            }
            else{
                System.out.println(" how on earth did I manage to break this"); //catches an error in the event an unaccounted scenario occurs
            }
		}
	}
    public static void main(String[] args){
        batterTakeTurn();
    }
}
import java.util.Random;

public class BatterUp1{
    public static int die_1;
    public static int die_2;

    public static int bat(){ //rolls two dice to determine result of the bat
        Random random = new Random();
        die_1 = random.nextInt(6) + 1;
        die_2 = random.nextInt(6) + 1;
        if(die_1 == die_2 && die_1 <= 4){
            return die_1; //if dice have the same values, it's a hit
        }
        else if((die_1 + die_2) % 2 == 0){
            return -1; //if dive have difference value, then strike or ball
        }
        else{
            return -2;
        }
    }
    public static void main(String[] args){
        for(int i = 0; i < 10; i++){
            int swing = bat();
            System.out.print("Rolled " + die_1 + " " + die_2);
            if(swing == 1){
                System.out.println(" SINGLE!");
            }
            else if(swing == 2){
                System.out.println(" DOUBLE!");
            }
            else if(swing == 3){
                System.out.println(" TRIPLE!");
            }
            else if(swing == 4){
                System.out.println(" HOME RUN!");
            }
            else if(swing == -1){
                System.out.println(" STRIKE!");
            }
            else if(swing == -2){
                System.out.println(" BALL!");
            }
            else{
                System.out.println(" how on earth did you manage to break this");
            }
        }
    }
}
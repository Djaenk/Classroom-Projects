import java.util.ArrayList;
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

public class printwritertest{
	public static void main(String[] args) throws FileNotFoundException{
		ArrayList<Player> players = new ArrayList<Player>();
		Field field = new Field();
		Scanner scan = new Scanner(new File("players.txt"));
		scan.useDelimiter(",|\n");
		while(scan.hasNextLine()){
			String player_name = scan.next();
			String player_type = scan.next();
			if(player_type.contains("Average")){
				players.add(new Player(player_name, field.getDugout()));
			}
			else if(player_type.contains("Ringer")){
				players.add(new Ringer(player_name, field.getDugout()));
			}
			else if(player_type.contains("Dud")){
				players.add(new Dud(player_name, field.getDugout()));
			}
		}
		scan.close();
		for(int i = 0; i < players.size(); i++){
			System.out.println(players.get(i).getName());
			System.out.println(players.get(i).getClass());
		} 
	}
}
//Anthony Wang
//47733248
//Lab 6 - Fall 2018

import java.util.ArrayList;

public class BatterUp{
	private int outs = 0;
	private int score = 0;
	private int next_player_index = 0;
	private ArrayList<Player> players = new ArrayList<Player>();
	public Field field = new Field();

	public BatterUp(){
		createPlayers();
	}
	public void createPlayers(){
		for(int i = 0; i < 9; i++){
			String player_name = "player" + (i + 1);
			players.add(new Player(player_name, field.getDugout()));
		}
	}
	public Player getNextPlayer(){
		Player next_player = players.get(next_player_index);
		next_player_index++;
		if(next_player_index >= 9){
			next_player_index = 0;
		}
		return next_player;
	}
	public void displayField(){
		String first_base = "empty";
		String second_base = "empty";
		String third_base = "empty";
		for(int i = 0; i < players.size(); i++){
			if(players.get(i).getLocation().getName().equals("First")){
				first_base = players.get(i).getName();
			}
			else if(players.get(i).getLocation().getName().equals("Second")){
				second_base = players.get(i).getName();
			}
			else if(players.get(i).getLocation().getName().equals("Third")){
				third_base = players.get(i).getName();
			}
		}
		System.out.println("[ 1 ] " + first_base + "  [ 2 ] " + second_base + "  [ 3 ] " + third_base);
	}
	public void movePlayers(int bases_advanced){
		for(int i = 0; i < 9; i++){
			if(players.get(i).isNotinDugout() == true){
				players.get(i).setLocation(field.moveAhead(players.get(i).getLocation(), bases_advanced));
				if(players.get(i).getLocation().isHome() == true){
					score++;
					System.out.println(players.get(i).getName() + "has scored!");
					players.get(i).setLocation(field.getDugout());
				}
			}
		}
	}
	public void play(){
		System.out.println();
		for(; outs < 3;){
			displayField();
			Player current_player = getNextPlayer();
			System.out.println(current_player.getName() + "is batting");
			current_player.setLocation(field.getBatterBox());
			int current_turn_result = current_player.takeTurn();
			if(current_turn_result == 0){
				outs++;
			}
			else{
				movePlayers(current_turn_result);
			}
			System.out.println("SCORE:" + score);
			System.out.println();
		}
	}
}
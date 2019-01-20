//Anthony Wang
//47733248
//Lab 7 - Fall 2018

import java.util.ArrayList;
import java.util.Scanner;
import java.io.PrintWriter;
import java.io.File;
import java.io.FileNotFoundException;

public class BatterUp{
	private int outs = 0;
	private int score = 0;
	private int next_player_index = 0;
	private ArrayList<Player> players = new ArrayList<Player>();
	public Field field = new Field();

	public BatterUp() {
		createPlayers();
	}
	public void createPlayers() {
		try{
		Scanner scan = new Scanner(new File("players.txt")); //initialize scanner to read from the players file
		scan.useDelimiter(",|\n"); //make the scanner tokenize using commas and newlines as delimiters(regex expression)
		while(scan.hasNextLine()){ //as long as there is another line for the scanner to scan then keep scanning
			String player_name = scan.next();
			String player_type = scan.next();
			if(player_type.contains("Average")){ //depending on what every other token scanned is, initialize a Player, Ringer, or Dud
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
		}
		catch(Exception e){

		}
	}
	public Player getNextPlayer(){
		Player next_player = players.get(next_player_index); //grabs the current player
		next_player_index++; //moves index to indicate next player
		if(next_player_index >= players.size()){ //if the index is out of bounds of the players arraylist, then roll it back to 0
			next_player_index = 0;
		}
		return next_player;
	}
	public String displayField(){
		String str = "";
		String first_base = "empty"; //declare strings to represent name of player in respective base
		String second_base = "empty";
		String third_base = "empty";
		for(int i = 0; i < players.size(); i++){
			if(players.get(i).getLocation().getName().equals("First")){ //if a player's location is a base named "First", "Second", or "Third" then change the base String value to that player's name
				first_base = players.get(i).getName();
			}
			else if(players.get(i).getLocation().getName().equals("Second")){
				second_base = players.get(i).getName();
			}
			else if(players.get(i).getLocation().getName().equals("Third")){
				third_base = players.get(i).getName();
			}
		}
		str += "[ 1 ] " + first_base + "  [ 2 ] " + second_base + "  [ 3 ] " + third_base;
		return str;
	}
	public String movePlayers(int bases_advanced){
		String str = "";
		for(int i = 0; i < players.size(); i++){
			if(players.get(i).getLocation() != field.getDugout()){ //if player's location is not the dugout
				players.get(i).setLocation(field.moveAhead(players.get(i).getLocation(), bases_advanced)); //then have him advance along the bases
			}
			if(players.get(i).getLocation().isHome() == true){ //if the player has advanced to home base then apply procecure for scoring
				this.score++;
				str += players.get(i).getName() + " has scored!";
				players.get(i).setLocation(field.getDugout());
			}
		}
		return str;
	}
	public String play(int number_of_innings) {
		String str = "";
		for(int inning = 1; inning <= number_of_innings; inning++){
			str += "Inning" + inning + "\n";
			this.outs = 0;
			for(; this.outs < 3;){
				displayField();
				Player current_player = getNextPlayer();
				System.out.println(current_player.getName() + " is batting");
				current_player.setLocation(field.getBatterBox());
				int current_turn_result = current_player.takeTurn();
				str += current_player.getOutput();
				if(current_turn_result == 0){ //if current player strikes out, then increment outs and send current player back to the dugout
					this.outs++;
					current_player.setLocation(field.getDugout());
					current_player.resetOutput();
				}
				else{ //else if the current player gets a hit or base on balls, move players according to returned value of Player.takeTurn()
					movePlayers(current_turn_result);
					current_player.resetOutput();
				}
				str += "\nSCORE:" + this.score +"\n";
			}
			for(int j = 0; j < players.size(); j++){ //when the previous loop completes (due to three strikeouts), send all players back to dugout in preparation for the next inning
				players.get(j).setLocation(field.getDugout());
			}
			str += "Inning " + inning + " completed with a score of " + this.score + "\n";
		}
		try{
		printStats();
		}
		catch(Exception e){

		}
		this.score = 0;
		return str;
	}
	public void printStats() {
		try{
		PrintWriter gamestat_printer = new PrintWriter("gamestats.txt"); //printwriter for printing player statistics to file
		gamestat_printer.println("GAME STATS");
		gamestat_printer.println("*****************************************");
		gamestat_printer.println("PLAYER          HITS     AT-BATS  AVERAGE");
		for(int i = 0; i < players.size(); i++){
			gamestat_printer.printf("%-16s%-9d%-9d%.3f%n", players.get(i).getName(), players.get(i).getHits(), players.get(i).getAt_bats(), players.get(i).getBattingAverage());
		}
		gamestat_printer.close();
		}
		catch(Exception e){

		}
	}
}
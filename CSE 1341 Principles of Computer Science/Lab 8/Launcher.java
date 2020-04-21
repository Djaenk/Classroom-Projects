//Anthony Wang
//47733248
//Lab 8 - Fall 2018

import java.io.FileNotFoundException;
import javax.swing.JFrame;

public class Launcher{
	public static void main(String[] args) throws FileNotFoundException{
		BatterUpGUI the_game = new BatterUpGUI();
		the_game.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		the_game.setSize(650,450);
		the_game.setVisible(true);
	}
}
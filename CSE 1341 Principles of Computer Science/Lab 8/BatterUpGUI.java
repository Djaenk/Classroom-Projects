import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

//Anthony Wang
//47733248
//Lab 8 - Fall 2018

public class BatterUpGUI extends JFrame{
	JScrollPane scroll_pane;
	JLabel number_of_innings;
	JTextField innings;
	JLabel team_name;
	JTextField name;
	JButton play;
	JButton reset;
	JTextArea output;

	public BatterUpGUI(){
		setLayout(new FlowLayout());
		
		Action action = new Action();
		number_of_innings = new JLabel("Number of Innings");
		innings = new JTextField(1);
		team_name = new JLabel("Team Name");
		name = new JTextField(15);
		play = new JButton("Play");
		reset = new JButton("Reset");
		output = new JTextArea(20,50);
		scroll_pane = new JScrollPane(output);
		play.addActionListener(action);
		reset.addActionListener(action);
		add(number_of_innings);
		add(innings);
		add(team_name);
		add(name);
		add(play);
		add(reset);
		add(output);
		add(scroll_pane);
		output.setEditable(false);
	}
	private class Action implements ActionListener{
		@Override
		public void actionPerformed(ActionEvent e) {
			if(e.getSource() == play){
				BatterUp game = new BatterUp();
				int ing = Integer.parseInt(innings.getText());
				output.append(game.play(ing));
			}
			if(e.getSource() == reset){
				output.setText(null);;
				innings.setText(null);
				name.setText(null);
			}
		}
	}
}
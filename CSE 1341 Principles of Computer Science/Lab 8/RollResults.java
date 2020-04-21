//Anthony Wang
//47733248
//Lab 8 - Fall 2018

public class RollResults{
	private int[] vals;
	private String output;

	public RollResults(int[] vals, String output){
		this.vals = vals;
		this.output = output;
	}

	public int[] getVals(){
		return vals;
	}

	public String getOutput(){
		return output;
	}

	public void setVals(int[] vals){
		this.vals = vals;
	}

	public void setOutput(String output){
		this.output = output;
	}
}
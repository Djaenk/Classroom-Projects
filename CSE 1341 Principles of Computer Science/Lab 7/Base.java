//Anthony Wang
//47733248
//Lab 7 - Fall 2018

public class Base{
	private String name;

	Base(String name){
		this.name = name;
	}
	public String getName(){
		return name;
	}
	public void setName(String new_name){
		this.name = new_name;
	}
	public boolean isDugout(){
		if(this.name == "Dugout"){ //if this base is the Dugout, then true
			return true;
		}
		else{
			return false;
		}
	}
	public boolean isHome(){
		if(this.name == "Home"){ //if this base is Home base, then true
			return true;
		}
		else{
			return false;
		}
	}
	public String toString(){
		return "Base" + this.name;
	}
}
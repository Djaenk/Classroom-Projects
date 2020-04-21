//Anthony Wang
//47733248
//Lab 6 - Fall 2018

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
		if(this.name == "Dugout"){
			return true;
		}
		else{
			return false;
		}
	}
	public boolean isHome(){
		if(this.name == "Home"){
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
import java.util.Scanner;

public class CircleProblem{
    public static void main(String[] args){
		Scanner scan = new Scanner(System.in);
		double radius = 0;
		double circumference = 0;
		double area = 0;
		String choice;
		System.out.println("What is the radius of the circle?");
		radius = scan.nextDouble();
		System.out.println("Would you like the circumference or the area of the circle? (C/A)");
		while(true){
			choice = scan.next();
			if(choice.equals("C")){
				circumference = 2 * Math.PI * radius;
				System.out.printf("The circumference of the circle is %.1f%n", circumference);
				break;
			}
			else if(choice.equals("A")){
				area = Math.PI * radius * radius;
				System.out.printf("The area of the circle is %.1f%n", area);
				break;
			}
			else{
				System.out.println("Please make a valid choice. Enter \"C\" for circumference or \"A\" for area.");
			}
		}
		scan.close();
	}
}
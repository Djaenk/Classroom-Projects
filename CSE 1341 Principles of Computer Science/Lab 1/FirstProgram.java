import java.util.Scanner;

public class FirstProgram
{
	public static void main(String[] args)
	{
		Scanner input = new Scanner(System.in);

		System.out.println("This is my firset Java program!");
		System.out.print("What is your name? ");
		String name = input.next();

		System.out.printf("Hello %s welcome to CSE 1341 at SMU! \n", name);

		System.out.println("I am pretty intelligent. I can count the numbers from 1 to 50 and find their sum!");

		int total = 0;
		for (int i=1; i<=50; i++)
		{
			System.out.print(i + " ");
			total = total + i;
		}
		System.out.printf("\nThe sum is %d. \n", total);
	}
}
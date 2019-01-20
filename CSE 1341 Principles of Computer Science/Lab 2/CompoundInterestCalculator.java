//Anthony Wang
//47733248
//Lab 2-Fall 2018

import java.util.Scanner;

public class CompoundInterestCalculator{
    public static void main(String[] args){
        System.out.println("Welcome to the compound interest calculator!\n");
        Scanner scanner = new Scanner(System.in);
        System.out.print("Please enter the princicle: ");
        double principal = scanner.nextDouble();
        System.out.print("Please enter the annual interest rate: ");
        double interest_rate = scanner.nextDouble() / 100;
        System.out.print("Please enter the compounding periods per year: ");
        int compounding_periods = scanner.nextInt();
        System.out.print("Please enter the term in years: ");
        int term = scanner.nextInt();
        double earnings = principal * Math.pow((1 + (interest_rate / compounding_periods)), (compounding_periods * term));
        System.out.printf("%nAmount Earned (A): $%.2f%n", earnings);
        double income = earnings - principal;
        System.out.printf("Total Interest Earned: $%.2f", income);
        scanner.close();
    }
}
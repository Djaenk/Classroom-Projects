//Anthony Wang
//47733248
//Lab 2-Fall 2018

import java.util.Scanner;

public class UnitConversion{
    public static void main(String[] args){
        final double LITERS_TO_GALLONS = 0.264172;
        final double GALLONS_TO_LITERS = 3.78541;
        final double KILOMETERS_TO_MILES = 0.621;
        final double MILES_TO_KILOMETERS = 1.609;
        Scanner scanner = new Scanner(System.in);
        double input;
        double output;

        System.out.println("1. liters to gallons:");
        System.out.print("Please enter a value for liters: ");
        input = scanner.nextDouble();
        output = input * LITERS_TO_GALLONS;
        System.out.printf("%.1f liters = %.2f gallons%n%n", input, output);

        System.out.println("2. gallons to liters:");
        System.out.print("Please enter a value for gallons: ");
        input = scanner.nextDouble();
        output = input * GALLONS_TO_LITERS;
        System.out.printf("%.1f gallons = %.2f liters%n%n", input, output);

        System.out.println("3. kilometers to miles:");
        System.out.print("Please enter a value for kilometers: ");
        input = scanner.nextDouble();
        output = input * KILOMETERS_TO_MILES;
        System.out.printf("%.1f kilometers = %.2f miles%n%n", input, output);

        System.out.println("4. miles to kilometers:");
        System.out.print("Please enter a value for liters: ");
        input = scanner.nextDouble();
        output = input * MILES_TO_KILOMETERS;
        System.out.printf("%.1f miles = %.2f kilometers%n%n", input, output);

        scanner.close();
    }
}
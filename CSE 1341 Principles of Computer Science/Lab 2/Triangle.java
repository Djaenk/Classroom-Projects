//Anthony Wang
//47733248
//Lab 2-Fall 2018

import java.util.Scanner;

public class Triangle{
    public static void main(String[] args){
        System.out.print("Please enter a value for the base of a triangle: ");
        Scanner scanner = new Scanner(System.in);
        int base = scanner.nextInt();
        System.out.print("Please enter a value for the height of the triangle: ");
        int height = scanner.nextInt();
        double area = 0.5 * height * base;
        System.out.printf("The height of the triangle is %.1f", area);
        scanner.close();
    }
}
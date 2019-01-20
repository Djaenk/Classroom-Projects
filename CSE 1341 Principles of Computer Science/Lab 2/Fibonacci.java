//Anthony Wang
//47733248
//Lab 2-Fall 2018

import java.util.Scanner;

public class Fibonacci{
    public static void main(String[] args){
        System.out.println("Fibonacci Sequence:");
        System.out.println("How many numbers do you want to have in the sequence? (It must be greater than 12)");
        Scanner scanner = new Scanner(System.in);
        int length = scanner.nextInt();
        System.out.println("Do you want to skip the odd numbers? 1=yes, 2=no");
        int even = scanner.nextInt();
        for(int i = 1, a = 0, b = 1, temp = 0; i <= length; i++){
            System.out.printf("%10d", i);
            if ((even == 1) && ((a % 2) == 1))
                System.out.println();
            else
                System.out.printf("%10d%n", a);
            a += b; //finds next fibonacci number then swaps a and b
            temp = a;
            a = b;
            b = temp;
        }
        scanner.close();
    }
}
import java.util.Scanner;

public class Density{
    public static void calculateDensity(double[] mass, double[] volume){
        for(int i = 0; i < 3; i++){
            double density = mass[i] / volume[i];
            System.out.printf("%nThe density for mass = %.2f g and volume = %.2f ml is %.2f g/ml", mass[i], volume[i], density);
        }
    }
    public static void main(String[] args){
        System.out.println("\nEnter the mass volume for your three compounds.");
        Scanner scanner = new Scanner(System.in);
        double[] mass = {0,0,0};
        double[] volume = {0,0,0};
        for(int i = 0; i < 3; i++){
            System.out.print("\nEnter mass in grams: ");
            mass[i] = scanner.nextDouble();
            System.out.print("Enter volume in millimeters: ");
            volume[i] = scanner.nextDouble();
        }
        calculateDensity(mass, volume);
    }
}
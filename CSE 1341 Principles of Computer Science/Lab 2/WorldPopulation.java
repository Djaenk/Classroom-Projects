//Anthony Wang
//47733248
//Lab 2-Fall 2018

public class WorldPopulation{
    public static void main(String[] args){
        System.out.println("Year\tWorld Population (billions)");
        System.out.println("-----------------------------------");
        double population = 7.644;
        for(int i = 2018; i <= 2043; i++){
            System.out.print(i);
            System.out.printf("%20.7f%n", population);
            population *= 1.0109;
        }
    }
}
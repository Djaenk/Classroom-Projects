import java.util.Scanner;

public class DVD1{
    public static void main(String[] args){
        int dvd = 10;
        double cash = 100;
        Scanner scanner = new Scanner(System.in);
        int choice = 0;
        int dvd_purchase_quantity = 0;
        int dvd_sale_quantity = 0; //lines 5-10 declare all necessary variables
        while(true){ //loop infinitely until breaksr when user chooses option 9
            System.out.println("\nWelcome to DVDs R Us. Please choose from the options below:");
            System.out.println("1 - Buy DVDs");
            System.out.println("2 - Sell DVDs");
            System.out.println("3 - Check how many DVDs we have in stock");
            System.out.println("4 - Check how much cash we have");
            System.out.println("9 - Exit the program");
            System.out.print("Enter Option: "); //lines 12-18 prints menu
            choice = scanner.nextInt(); //takes user's menu choice
            if(choice == 1){
                System.out.printf("%nEnter the number of DVDs to buy: ");
                dvd_purchase_quantity = scanner.nextInt();
                if(dvd_purchase_quantity * 9 <= cash){ //checks if funds are sufficient for buying DVDs, if so, then adds that many dvds stock and subtracts cost from cash
                    dvd += dvd_purchase_quantity;
                    cash -= dvd_purchase_quantity * 9;
                    System.out.printf("Number of DVDs: %d%n", dvd);
                    System.out.printf("Cash available: $%.2f%n%n", cash);
                }
                else{ //if insufficient funds, notify user and deny operation
                    System.out.printf("You do not have enough money for this transaction.%n%n");
                }
            }
            else if(choice == 2){
                System.out.printf("%nEnter the number of DVDs to sell: ");
                dvd_sale_quantity = scanner.nextInt();
                if(dvd_sale_quantity <= dvd){ //checks if enough dvds are in stock to sell desired quantity, if so, then subtract sale from dvd and add revenue to cash
                    dvd -= dvd_sale_quantity;
                    cash += dvd_sale_quantity * 10;
                    System.out.printf("Number of DVDs: %d%n", dvd);
                    System.out.printf("Cash available: %.2f%n%n", cash);
                }
                else{ //if insufficient dvds in stock, notify user and deny operation
                    System.out.printf("%nYou do not have enough DVDs for this transaction.%n%n");
                }
            }
            else if(choice == 3){
                System.out.printf("%nNumber of DVDs: %d%n%n", dvd);
            }
            else if(choice == 4){
                System.out.printf("%nCash available: %.2f%n%n", cash);
            }
            else if(choice == 9){
                System.out.printf("%nThank you for shopping with us! Please return soon!%n");
                break; //leaves loop, ending the program
            }
            else{
                System.out.printf("%nThis option is not acceptable.%n%n"); //if user does not input 1,2,3,4, or 9 as their option, inform them their choice is invalid
            }
        }
        scanner.close();
    }
}
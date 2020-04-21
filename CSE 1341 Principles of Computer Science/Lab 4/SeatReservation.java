import java.util.Scanner;

public class SeatReservation{
    public static void printRowSeat(String[] rowSeats){
        System.out.print("|");
        for(int i = 0; i < 3; i++){
            System.out.printf("%-10s", rowSeats[i]);
        }
        System.out.println("|");
    }

    public static void printRowPrices(double[] rowPrices){
        System.out.print("|");
        for(int i = 0; i < 3; i++){
            System.out.printf("$%-9.2f", rowPrices[i]);
        }
        System.out.println("|");
    }

    public static void display(String[] rowASeats, String[] rowBSeats, double[] rowAPrices, double[] rowBPrices){
        System.out.println();
        System.out.println("================================");
        printRowSeat(rowASeats);
        printRowPrices(rowAPrices);
        System.out.println("--------------------------------");
        printRowSeat(rowBSeats);
        printRowPrices(rowBPrices);
        System.out.println("================================");
        System.out.println();
    }

    public static String getRow(Scanner scan){
        System.out.print("Which row would you like to reserve a seat in? ");
        return scan.next();
    }

    public static double makeReservation(String[] rowSeats, double[] prices, String row, Scanner scan){
        System.out.println("================================");
        printRowSeat(rowSeats);
        printRowPrices(prices);
        System.out.println("================================");
        System.out.print("Enter the seat number you would like to reserve (0 to reselect row): ");
        int seatNum = 0;
        while(true){
            seatNum = scan.nextInt();
            if(seatNum >= 1 && seatNum <= 3){
                if(rowSeats[seatNum - 1].equals("X")){
                    System.out.print("Seat already reserved, select a different seat number: ");
                }
                else{
                    break;
                }
            }
            else if(seatNum == 0){
                return 0;
            }
            else{
                System.out.print("Invalid seat. Select a valid seat number: ");
            }
        }
        System.out.printf("You have chosen seat %d%s for a price of $%.2f%n", seatNum, row, prices[seatNum - 1]);
        updateSeatingChart(rowSeats, seatNum);
        System.out.println("================================");
        printRowSeat(rowSeats);
        printRowPrices(prices);
        System.out.println("================================");
        return prices[seatNum - 1];
    }

    public static void updateSeatingChart(String[] rowSeats, int seatNum){
        rowSeats[seatNum - 1] = "X";
    }

    public static void printReceipt(int numSeats, double total){
		System.out.println("Thank you for reserving with us. Here's your receipt:");
        System.out.println("-----------------------------------------------------");
        System.out.printf("Subtotal: $%.2f%n", total);
        double fees = numSeats * 14.99;
        System.out.printf("Fees: %d x $%.2f = $%.2f%n", numSeats, 14.99, fees);
        double taxes = (total + fees) * .0825;
        System.out.printf("Taxes: $%.2f%n", taxes);
        System.out.println("=====================================================");
        System.out.printf("Total: $%.2f%n", total + fees + taxes);
        System.out.println("-----------------------------------------------------");
    }

    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        String[] rowASeats = {"1A", "2A", "3A"};
        String[] rowBSeats = {"1B", "2B", "3B"};
        double[] rowAPrices = {99.99, 110.99, 99.99};
        double[] rowBPrices = {75.99, 85.99, 75.99};
        double total = 0;
        double reservation_cost = 0;
        display(rowASeats, rowBSeats, rowAPrices, rowBPrices);
        System.out.print("How many seats would you like to reserve? ");
        int numSeats = scan.nextInt();
        System.out.println();
        System.out.println("---");
        for(int i = 0; i < numSeats; i++){
            System.out.println();
            String row_selection = getRow(scan);
            if(row_selection.equals("A")){
                reservation_cost = makeReservation(rowASeats, rowAPrices, "A", scan);
                if(reservation_cost == 0){
                    i--;
                    continue;
                }
                else{
                    total += reservation_cost;
                    System.out.printf("Your subtotal is $%.2f%n", total);
                    System.out.println();
                    System.out.println("---");
                }
            }
            else if(row_selection.equals("B")){
                reservation_cost = makeReservation(rowBSeats, rowBPrices, "B", scan);
                if(reservation_cost == 0){
                    i--;
                    continue;
                }
                else{
                    total += reservation_cost;
                    System.out.printf("Your subtotal is $%.2f%n", total);
                    System.out.println();
                    System.out.println("---");
                }
            }
            else{
                System.out.print("That is not a valid row.");
                i--;
            }
        }
        printReceipt(numSeats, total);
    }
}
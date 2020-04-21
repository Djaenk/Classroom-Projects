public class FigurePrinter{
	static void printFig(int h, int w){
		for(int i = 1; i <= h; i++){ //loops through rows, starts at 1 instead of 0 to keeping track of rows and column easier
            for(int j = 1; j <= w; j++){ //loop from 1 to the number of columns in the rectangle
				if(i == 1 || i == h || j == 1 || j == w){ //print a character if on the first or last row or column
					if(i % 2 == 0){
						System.out.print("*");
					}
					else if(i % 2 == 1){
						System.out.print("@");
					}
					else{
						System.out.print("?"); //in case I somehow break this
					}
                }
                else{
                    System.out.print(" ");
                }
            }
            System.out.println();
		}
		System.out.println();
	}
    public static void main(String[] args){
		printFig(9,3);
		printFig(5,6);
		printFig(4,3);
		printFig(10,10);
		printFig((int) Math.ceil(Math.random() * 10),(int) Math.ceil(Math.random() * 10)); //calls printFig() with random integers from 1 to 10 as arguments
    }
}
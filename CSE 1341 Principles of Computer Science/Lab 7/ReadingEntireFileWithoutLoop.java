
// Java Program to illustrate reading from FileReader 
// using Scanner Class reading entire File 
// without using loop 
import java.io.File; 
import java.io.FileNotFoundException; 
import java.util.Scanner; 
  
public class ReadingEntireFileWithoutLoop 
{ 
  public static void main(String[] args) 
                        throws FileNotFoundException 
  { 
    Scanner sc = new Scanner(new File("players.txt")); 
  
    // we just need to use \\Z as delimiter 
	sc.useDelimiter("\n"); 
	for(int i = 0; i < 9; i++)
    System.out.println(sc.next()); 
  } 
} 

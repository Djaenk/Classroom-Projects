public class StarPyramid{
    public static void main(String[] args){
        int h = 10;
        for(int i = 0; i < h; i++){
            for(int j = 0; j <= i; j++){
                if(j == 0 || j == i || i == h - 1){
                    System.out.print("*");
                }
                else{
                    System.out.print(" ");
                }
            }
            System.out.print("\n");
        }

    }
}
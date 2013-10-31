

public class StdArrayIO {

	 /**
     * Read in and return an array of doubles from standard input.
     */
    public static double[] readDouble1D() {
    	//StdOut.println("Vector length");
        int N = StdIn.readInt();  
        double[] a = new double[N];
        for (int i = 0; i < N; i++) {
            a[i] = StdIn.readDouble();
        }
        return a;
    }
    
    public static double[] readDouble(int N) {
    	//StdOut.println("Vector length"); 
        double[] a = new double[N];
        for (int i = 0; i < N; i++) {
            a[i] = StdIn.readDouble();
        }
        return a;
    }
    public static double[] readEuclideanVector() {
        int N = 6;  //Para usar vectores de coordenadas, eje de rotacion
        double[] a = new double[N];
        for (int i = 0; i < N; i++) {
            a[i] = StdIn.readDouble();
        }
        return a;
    }
    
    public static double[][] readJoint() {
        int N = 3;  //Para usar vectores de coordenadas, eje de rotacion
        double[][] a = new double[N][N];
        for (int i = 0; i < N; i++) {
        	for(int j=0; j<N;j++){
        		
        		a[i][j] = StdIn.readDouble();
        	}
            
        }
        return a;
    }

    /**
     * Print an array of doubles to standard output.
     */
    public static void print(double[] a) {
        int N = a.length;
        //StdOut.println(N);
        for (int i = 0; i < N; i++) {
            StdOut.printf("%9.5f ", a[i]);
        }
        StdOut.println();
    }

        
    /**
     * Read in and return an M-by-N array of doubles from standard input.
     */
    public static double[][] readDouble2D() {
        int M = StdIn.readInt();
        int N = StdIn.readInt();
        double[][] a = new double[M][N];
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                a[i][j] = StdIn.readDouble();
            }
        }
        return a;
    }

    /**
     * Print the M-by-N array of doubles to standard output.
     */
    public static void print(double[][] a) {
        int M = a.length;
        int N = a[0].length;
        //StdOut.println(M + " " + N);
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                StdOut.printf("%9.5f ", a[i][j]);
            }
            StdOut.println();
        }
    }


    /**
     * Read in and return an array of ints from standard input.
     */
    public static int[] readInt1D() {
        int N = StdIn.readInt();
        int[] a = new int[N];
        for (int i = 0; i < N; i++) {
            a[i] = StdIn.readInt();
        }
        return a;
    }

    /**
     * Print an array of ints to standard output.
     */
    public static void print(int[] a) {
        int N = a.length;
        for (int i = 0; i < N; i++) {
            StdOut.printf("%9d ", a[i]);
        }
        StdOut.println();
    }
    

        
    /**
     * Read in and return an M-by-N array of ints from standard input.
     */
    public static int[][] readInt2D() {
        int M = StdIn.readInt();
        int N = StdIn.readInt();
        int[][] a = new int[M][N];
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                a[i][j] = StdIn.readInt();
            }
        }
        return a;
    }

    /**
     * Print the M-by-N array of ints to standard output.
     */
    public static void print(int[][] a) {
        int M = a.length;
        int N = a[0].length;
        StdOut.println(M + " " + N);
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                StdOut.printf("%9d ", a[i][j]);
            }
            StdOut.println();
        }
    }


    /**
     * Read in and return an array of booleans from standard input.
     */
    public static boolean[] readBoolean1D() {
        int N = StdIn.readInt();
        boolean[] a = new boolean[N];
        for (int i = 0; i < N; i++) {
            a[i] = StdIn.readBoolean();
        }
        return a;
    }

    /**
     * Print an array of booleans to standard output.
     */
    public static void print(boolean[] a) {
        int N = a.length;
        StdOut.println(N);
        for (int i = 0; i < N; i++) {
            if (a[i]) StdOut.print("1 ");
            else      StdOut.print("0 ");
        }
        StdOut.println();
    }
    public static String[] readString1D(int N) {
        String[] a = new String[N];
        for (int i = 0; i < N; i++) {
            a[i] = StdIn.readString();
        }
        return a;
    }
    public static void print(String[] a) {
        int N = a.length;
        for (int i = 0; i < N; i++) {
            StdOut.printf("%9d ", a[i]);
        }
        StdOut.println();
    }
    /**
     * Read in and return an M-by-N array of booleans from standard input.
     */
    public static boolean[][] readBoolean2D() {
        int M = StdIn.readInt();
        int N = StdIn.readInt();
        boolean[][] a = new boolean[M][N];
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                a[i][j] = StdIn.readBoolean();
            }
        }
        return a;
    }

   /**
     * Print the  M-by-N array of booleans to standard output.
     */
    public static void print(boolean[][] a) {
        int M = a.length;
        int N = a[0].length;
        StdOut.println(M + " " + N);
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (a[i][j]) StdOut.print("1 ");
                else         StdOut.print("0 ");
            }
            StdOut.println();
        }
    }


   /**
     * Test client.
     */

}



import org.apache.commons.math3.analysis.differentiation.*;
import org.apache.commons.math3.linear.*;
import Jama.Matrix;


public class MatrixOps {

	/**
	 * @param args
	 */
	/*public static void main(String[] args) {
		// TODO Auto-generated method stub
		double[] x={1,2,3};
		double[] y={4,5,6};
		double[] crossp=cross(x,y);
		StdArrayIO.print(crossp);
		
		double[][] A={{1,1},{2,2}};
		double[][] B={{3,3},{4,4}};
		StdArrayIO.print(multiply(A,B));

	}*/
	
	//return the rightmost column of a matrix
	public static double[] column(double[][] x){
		
		double[] var = new double[x.length];
		for(int i = 0; i < x.length; i++)
		{
			
		    for(int j=0;j<x[i].length;j++)
		    {
		    	var[i]=x[i][j];
		    }
		}
		return var;
	}
	public static DerivativeStructure[] column(DerivativeStructure[][] x){
		
		DerivativeStructure[] var = new DerivativeStructure[x.length];
		for(int i = 0; i < x.length; i++)
		{
			
		    for(int j=0;j<x[i].length;j++)
		    {
		    	var[i]=x[i][j];
		    }
		}
		return var;
	}
	


    // return a random m-by-n matrix with values between 0 and 1
    public static double[][] random(int m, int n) {
        double[][] C = new double[m][n];
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                C[i][j] = Math.random();
        return C;
    }

    // return n-by-n identity matrix I
    public static double[][] identity(int n) {
        double[][] I = new double[n][n];
        for (int i = 0; i < n; i++)
            I[i][i] = 1;
        return I;
    }

    // return x^T y
    public static double dot(double[] x, double[] y) {
        if (x.length != y.length) throw new RuntimeException("Illegal vector dimensions.");
        double sum = 0.0;
        for (int i = 0; i < x.length; i++)
            sum += x[i] * y[i];
        return sum;
    }
    
    public static DerivativeStructure dot(DerivativeStructure[] x, DerivativeStructure[] y) {
        if (x.length != y.length) throw new RuntimeException("Illegal vector dimensions.");
        int n=x[0].getFreeParameters();
        DerivativeStructure sum = new DerivativeStructure(n,1,0);
        for (int i = 0; i < x.length; i++)
            sum =sum.add(x[i].multiply(y[i]));//.multiply(y[i]));
        return sum;
    }
    public static double sum(double[] x){
    	double suma=0;
    	for(int i=0; i<x.length; i++){
    		suma+=x[i];
    		
    	}
    	return suma;
    }
    
    public static double[] cross(double[] x, double[] y){
        if (x.length != 3| y.length!= 3) throw new RuntimeException("Illegal vector dimensions.");

    	double[] cp= new double [3];
    	cp[0]=x[1]*y[2]-x[2]*y[1];
    	cp[1]=-(x[0]*y[2]-x[2]*y[0]);
    	cp[2]=x[0]*y[1]-x[1]*y[0];
    	return cp;
    }

    // return C = A^T
    public static double[][] transpose(double[][] A) {
        int m = A.length;
        int n = A[0].length;
        double[][] C = new double[n][m];
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                C[j][i] = A[i][j];
        return C;
    }
    public static DerivativeStructure[][] transpose(DerivativeStructure[][] A) {
        int m = A.length;
        int n = A[0].length;
        DerivativeStructure[][] C = new DerivativeStructure[n][m];
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                C[j][i] = A[i][j];
        return C;
    }

    // return C = A + B
    public static double[][] add(double[][] A, double[][] B) {
        int m = A.length;
        int n = A[0].length;
        double[][] C = new double[m][n];
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                C[i][j] = A[i][j] + B[i][j];
        return C;
    }

    // return C = A - B
    public static double[][] subtract(double[][] A, double[][] B) {
        int m = A.length;
        int n = A[0].length;
        double[][] C = new double[m][n];
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                C[i][j] = A[i][j] - B[i][j];
        return C;
    }

    // return C = A * B
    public static double[][] multiply(double[][] A, double[][] B) {
        int mA = A.length;
        int nA = A[0].length;
        int mB = B.length;
        int nB = A[0].length;
        if (nA != mB) throw new RuntimeException("Illegal matrix dimensions.");
        double[][] C = new double[mA][nB];
        for (int i = 0; i < mA; i++)
            for (int j = 0; j < nB; j++)
                for (int k = 0; k < nA; k++)
                    C[i][j] += (A[i][k] * B[k][j]);
        return C;
    }
    
    public static DerivativeStructure[][] multiply(DerivativeStructure[][] A,
    		DerivativeStructure[][] B){
        /*int mA = A.length;
        int nA = A[0].length;
        int mB = B.length;
        int nB = A[0].length;
        if (nA != mB) throw new RuntimeException("Illegal matrix dimensions.");*/
    	DerivativeStructure[][] Bt=transpose(B);
        DerivativeStructure[][] C= new DerivativeStructure[A.length][B[0].length];
        for (int i = 0; i < A.length; i++)
            for (int j = 0; j < B[0].length; j++)
                    C[i][j] = dot(A[i],Bt[j]);
        
    	
    	return C;
    }
    
    public static DerivativeStructure[][] derivStrEye(int N){
    	DerivativeStructure[][] eye=new DerivativeStructure[N][N];
    	for(int i=0; i<N; i++){
    		
    		eye[i][i]=new DerivativeStructure(1,1,1);
    	}
    	
    	return eye;
    }
    //Create DerivativeStructure[][] from double[][]
    public static DerivativeStructure[][] doubleToDerivStruct(double[][] x){
    	DerivativeStructure[][] y=new DerivativeStructure[x.length][];
    	for(int i=0; i<x.length; i++){
    		for(int j=0; i<x[i].length; j++){
    			y[i][j]=new DerivativeStructure(1,1,x[i][j]);
    		}
    		
    	}
    	return y;
    }
    //Moore-Penrose pseudoinverse
	public static double[][] pinv(double[][] values){
		Matrix a= new Matrix(values);
        Matrix x= a.times(a.transpose());
        Matrix y= a.transpose();
        Matrix z= y.times(x.inverse());
        double[][] lol=z.getArray();
		
		return lol;
	}
    //LUDecomposition Inverse
    
    public static RealMatrix inv(double[][] x){
    	RealMatrix a = new Array2DRowRealMatrix(x);
    	DecompositionSolver solver = new LUDecomposition(a).getSolver();
    	RealMatrix ainv=solver.getInverse();
    	return ainv;
    	
    }

    // matrix-vector multiplication (y = A * x)
    public static double[] multiply(double[][] A, double[] x) {
        int m = A.length;
        int n = A[0].length;
        if (x.length != n) throw new RuntimeException("Illegal matrix dimensions.");
        double[] y = new double[m];
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                y[i] += (A[i][j] * x[j]);
        return y;
    }


    // vector-matrix multiplication (y = x^T A)
    public static double[] multiply(double[] x, double[][] A) {
        int m = A.length;
        int n = A[0].length;
        if (x.length != m) throw new RuntimeException("Illegal matrix dimensions.");
        double[] y = new double[n];
        for (int j = 0; j < n; j++)
            for (int i = 0; i < m; i++)
                y[j] += (A[i][j] * x[i]);
        return y;
    }

    public static double[] robotOrigin(int n){
    	double[] q0 = new double[n];
    	
    	for(int i=0; i<n; i++){
    		q0[i] = 0;
    		
    	}
    	
    	return q0;
    }
}


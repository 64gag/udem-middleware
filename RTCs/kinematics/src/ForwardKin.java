import org.apache.commons.math3.analysis.differentiation.*;
import org.apache.commons.math3.util.*;

public class ForwardKin {

	/**
	 * @param args
	 */
	/*public static void main(String[] args) {
		// TODO Auto-generated method stub

	}*/
	
	public static double[][][] getJoints(int N){
		double[][][] joints = new double[N][3][3];
		for(int i=0; i<N; i++){
			/*StdOut.println("Input Joint" + "  "+ (i+1));
			StdOut.println("---------------------------------------------");*/
			double[][] joint=StdArrayIO.readJoint();
			joints[i]=joint;
		
		}
		return joints;
	}


	public static double[] prismaticParams(double[][] j1, double[][] j2){
		double[] param=new double[4];
		//Calculo del parametro a 'link length'
		if(j1[2][0]==1|j1[2][0]==-1){
			param[1]=FastMath.abs(j2[0][0]-j1[0][0]);
		}
		else if(j1[2][1]==1|j1[2][1]==-1){
			param[1]=FastMath.abs(j2[0][1]-j1[0][1]);
		}
		else if(j1[2][2]==1|j1[2][2]==-1){
			param[1]=FastMath.abs(j2[0][2]-j1[0][2]);
		}
		else{
			System.out.println("lol");
		}
		
		
			double[] f1=j1[1];
			double[] f2=j2[1];
			double[] crossP=MatrixOps.cross(f1,f2);
			param[0]=MatrixOps.sum(crossP)*FastMath.acos(MatrixOps.dot(f1, f2)); //parametro alpha

			double[] f3=j1[2];
			double[] f4=j2[2];
			double[] crossP2=MatrixOps.cross(f3,f4);
			param[3]=MatrixOps.sum(crossP2)*FastMath.acos(MatrixOps.dot(f3, f4)); //parametro theta
			
			return param;

	}
	
	public static double[] revoluteParams(double[][] j1, double[][] j2){
		double[] param=new double[4];
		//Calculo del parametro a 'link length'
		if(j1[2][0]==1|j1[2][0]==-1){
			param[1]=FastMath.abs(j2[0][0]-j1[0][0]);
		}
		else if(j1[2][1]==1|j1[2][1]==-1){
			param[1]=FastMath.abs(j2[0][1]-j1[0][1]);
		}
		else if(j1[2][2]==1|j1[2][2]==-1){
			param[1]=FastMath.abs(j2[0][2]-j1[0][2]);
		}
		else{
			System.out.println("lol");
		}
		//Calculo del parametro d 'link offset'
		if(j2[1][0]==1|j2[1][0]==-1){
			param[2]=FastMath.abs(j2[0][0]-j1[0][0]);
		}
		else if(j2[1][1]==1|j2[1][1]==-1){
			param[2]=FastMath.abs(j2[0][1]-j1[0][1]);
		}
		else if(j2[1][2]==1|j2[1][2]==-1){
			param[2]=FastMath.abs(j2[0][2]-j1[0][2]);
		}
		else{
			System.out.println("lol");
		}


			double[] f1=j1[1];
			double[] f2=j2[1];
			double[] crossP=MatrixOps.cross(f1,f2);
			param[0]=MatrixOps.sum(crossP)*FastMath.acos(MatrixOps.dot(f1, f2)); //parametro alpha
			
			return param;


	}
	
	public static double[][] linkParamsChart(int N, String[] jointTypes, double[][][] joints){
		double[][] DHT=new double[N][4];
		
		for(int i=0; i<N-1;i++)
		{

			if (jointTypes[i].equals("R")){
				DHT[i]=revoluteParams(joints[i],joints[i+1]);
				
			}
			else if(jointTypes[i].equals("P")){
				DHT[i]=prismaticParams(joints[i],joints[i+1]);
				
			}
			else{
				
			}
			
		}
		DHT=shift(DHT);
		return DHT;
		
	}
	public static double[][] shift(double[][] x){

		double[] y=x[x.length-1];
		for(int i=x.length-1; i>0; --i){
			x[i]=x[i-1];
			
		}
		x[0]=y;
		return x;
		
	}
	
	public static double[][] numericTransform(double[] params){
		
		double[][] DHtrans = new double[4][4];
		 DHtrans[0][0]=FastMath.cos(params[3]);
		 DHtrans[0][1]=-FastMath.sin(params[3]);
		 DHtrans[0][2]=0;
		 DHtrans[0][3]=params[1];
		 
		 DHtrans[1][0]=FastMath.sin(params[3])*FastMath.cos(params[0]);
		 DHtrans[1][1]=FastMath.cos(params[3])*FastMath.cos(params[0]);
		 DHtrans[1][2]=-FastMath.sin(params[0]);
		 DHtrans[1][3]=-FastMath.sin(params[0])*params[2];
		 
		 DHtrans[2][0]=FastMath.sin(params[3])*FastMath.sin(params[0]);
		 DHtrans[2][1]=FastMath.cos(params[3])*FastMath.sin(params[0]);
		 DHtrans[2][2]=FastMath.cos(params[0]);
		 DHtrans[2][3]=FastMath.cos(params[0])*params[2];
		 
		 DHtrans[3][0]=0;
		 DHtrans[3][1]=0;
		 DHtrans[3][2]=0;
		 DHtrans[3][3]=1;
		 
		 return DHtrans;
		
	}
	
	public static DerivativeStructure[][] dsTransform(int n, DerivativeStructure[] params){
		DerivativeStructure[][] DHtrans=new DerivativeStructure[4][4];
		 DHtrans[0][0]=params[3].cos();
		 DHtrans[0][1]=(params[3].sin()).negate();
		 DHtrans[0][2]=new DerivativeStructure(n,1,0);
		 DHtrans[0][3]=params[1];
		 
		 DHtrans[1][0]=(params[3].sin()).multiply(params[0].cos().getValue());
		 DHtrans[1][1]=(params[3].cos()).multiply(params[0].cos().getValue()); 
		 DHtrans[1][2]=(params[0].sin()).negate();
		 DHtrans[1][3]=(params[2].multiply(params[0].sin().getValue())).negate();
		 
		 DHtrans[2][0]=(params[3].sin()).multiply(params[0].sin().getValue());
		 DHtrans[2][1]=(params[3].cos()).multiply(params[0].sin().getValue());
		 DHtrans[2][2]=params[0].cos();//Math.cos(params[0]);
		 DHtrans[2][3]=params[2].multiply(params[0].cos().getValue());
		 
		 DHtrans[3][0]=new DerivativeStructure(n,1,0);
		 DHtrans[3][1]=new DerivativeStructure(n,1,0);
		 DHtrans[3][2]=new DerivativeStructure(n,1,0);
		 DHtrans[3][3]=new DerivativeStructure(n,1,1);
		 
		 
		 
		return DHtrans;
		
	}

	public static DerivativeStructure[][] doubleToDS(int n, double[][] params){
		
		DerivativeStructure[][] ds=new DerivativeStructure[n][4];
		for(int i=0; i<ds.length; i++){
			for(int j=0; j<ds[i].length; j++){
				ds[i][j]=new DerivativeStructure(n,1,params[i][j]);
				
			}
	
		}
		
		return ds;
	}

	public static double[] numericValue(String[] typeConfig, double[][] linkParams, double[] x){

		
		
		for(int i=0;i<linkParams.length;i++){
			if(typeConfig[i].equals("R")){
				linkParams[i][3]=x[i];  //Var. si el param es de una Rev. 
				
			}
			
			else if(typeConfig[i].equals("P")){
				linkParams[i][2]=x[i];  //Var. si el param es una Prismatic
				
			}
			
			
		}
		double[] funciones=new double[3];
		double[][] TT=MatrixOps.identity(4);
		for(int i=0;i<linkParams.length;i++){
			double[][] Ti= numericTransform(linkParams[i]);
			TT=MatrixOps.multiply(TT, Ti);
		}
		funciones[0]=TT[0][3];
		funciones[1]=TT[1][3];
		funciones[2]=TT[2][3];


		//funciones=MatrixOps.column(dummy);
		return funciones;
	}

	public static DerivativeStructure[] dsValue(String[] typeConfig, double[][] linkParams, DerivativeStructure[] x){
		
		DerivativeStructure[][] lp = doubleToDS(x.length, linkParams);
		for(int i=0;i<lp.length;i++){
			if(typeConfig[i].equals("R")){
				lp[i][3]=x[i];  //Var. si el param es de una Rev. x[i]
				
				
			}
			
			else if(typeConfig[i].equals("P")){
				lp[i][2]=x[i];  //Var. si el param es una Prismatic x[i]
				
			}
			
			
		}
		
		DerivativeStructure[][] TT = dsTransform(x.length,lp[0]);

		
		DerivativeStructure[] funciones=new DerivativeStructure[3];
		for(int i=1;i<linkParams.length;i++){
			DerivativeStructure[][] Ti = dsTransform(x.length,lp[i]);

			TT=MatrixOps.multiply(TT, Ti); 
		}
		
		funciones[0]=TT[0][3];
		funciones[1]=TT[1][3];
		funciones[2]=TT[2][3];
		
		return funciones;
	}
	
	public static double[] deg2rad(double[] degrees){
		
		double[] radians = new double[degrees.length];
		for(int i = 0; i< degrees.length; i++){
			
			radians[i] = FastMath.toRadians(degrees[i]);
			
		}
		
		return radians;
	}
	
public static double[][] rotEuler(double[] Angles) {
		
		double[][] RotEuler = new double[3][3];
		
		RotEuler[0][0] = FastMath.cos(Angles[0])*FastMath.cos(Angles[1])*FastMath.cos(Angles[2]) - FastMath.sin(Angles[0])*FastMath.sin(Angles[2]);
		RotEuler[0][1] = -FastMath.cos(Angles[0])*FastMath.cos(Angles[1])*FastMath.sin(Angles[2]) - FastMath.sin(Angles[0])*FastMath.cos(Angles[2]);
		RotEuler[0][2] = FastMath.cos(Angles[0])*FastMath.sin(Angles[1]);
		
		RotEuler[1][0] = FastMath.sin(Angles[0])*FastMath.cos(Angles[1])*FastMath.cos(Angles[2]) + FastMath.cos(Angles[0])*FastMath.sin(Angles[2]);
		RotEuler[1][1] = -FastMath.sin(Angles[0])*FastMath.cos(Angles[1])*FastMath.sin(Angles[2]) + FastMath.cos(Angles[0])*FastMath.cos(Angles[2]);
		RotEuler[1][2] = FastMath.sin(Angles[0])*FastMath.sin(Angles[1]);
		
		RotEuler[2][0] = -FastMath.sin(Angles[1])*FastMath.cos(Angles[2]);
		RotEuler[2][1] = FastMath.sin(Angles[1])*FastMath.sin(Angles[2]);
		RotEuler[2][2] = FastMath.cos(Angles[1]);
		
		return RotEuler;
	}

public static double[] tipCoords(double[][] TipConfig){
		
		double[] tipCoords = new double[2];
		
		tipCoords = MatrixOps.multiply(TipConfig[1], rotEuler(deg2rad(TipConfig[0])));
		
		
		return tipCoords;
	}
		
}

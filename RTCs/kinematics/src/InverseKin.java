

import java.io.IOException;

import org.apache.commons.math3.analysis.differentiation.DerivativeStructure;
import org.apache.commons.math3.analysis.differentiation.JacobianFunction;
import org.apache.commons.math3.analysis.differentiation.MultivariateDifferentiableVectorFunction;
import org.apache.commons.math3.exception.MathIllegalArgumentException;
import org.apache.commons.math3.linear.ArrayRealVector;
import org.apache.commons.math3.linear.RealVector;
import org.apache.commons.math3.util.FastMath;



public class InverseKin {

	/**
	 * @param args
	 * @throws IOException 
	 */

	
	public static double[] InverseKinematicSolver(double[] t0) throws IOException{
		
		InputData id = new InputData("{\"DOF\":7,\"MATRIX_CONFIG\":[[[0.0,0.0,0.0],[1.0,0.0,0.0],[0.0,0.0,1.0]],[[0.0,0.4,0.0],[0.0,1.0,0.0],[0.0,0.0,1.0]],[[0.0,0.4,0.3],[1.0,0.0,0.0],[0.0,-1.0,0.0]],[[0.0,0.4,0.3],[0.0,-1.0,0.0],[0.0,0.0,1.0]],[[0.0,-0.1,0.3],[0.0,-1.0,0.0],[0.0,0.0,1.0]],[[0.0,-0.1,0.3],[1.0,0.0,0.0],[0.0,0.0,1.0]],[[0.0,-0.1,0.3],[0.0,-1.0,0.0],[0.0,0.0,1.0]]],\"TYPE_CONFIG\":[\"R\",\"R\",\"R\",\"R\",\"R\",\"R\",\"R\"]}");
		InputData inputs = id.DataJson;
		
		int DOF = inputs.DOF;	//Get amount of Degrees of Freedom in the system
		
		double[][][] matrixConfig = inputs.MATRIX_CONFIG; //Get system geometric configuration

		final String[] typeConfig = inputs.TYPE_CONFIG; //Get system joint type configuration
		
		final double[][] linkParams = ForwardKin.linkParamsChart(DOF, typeConfig, matrixConfig);
		//StdArrayIO.print(linkParams);
		
		MultivariateDifferentiableVectorFunction PositionVector= new MultivariateDifferentiableVectorFunction(){

			@Override
			public double[] value(double[] x)
					throws IllegalArgumentException {
				// TODO Auto-generated method stub
				
				double[] func = ForwardKin.numericValue(typeConfig, linkParams, x);
				return func;
			}

			@Override
			public DerivativeStructure[] value(DerivativeStructure[] x)
					throws MathIllegalArgumentException {
				// TODO Auto-generated method stub
				DerivativeStructure[] func = ForwardKin.dsValue(typeConfig, linkParams, x);
				return func;
			}
			
			
		}; //Fin de la interfaz
		
		
		double[] q0=MatrixOps.robotOrigin(DOF);
		RealVector Q0 = new ArrayRealVector(q0);
		double e=0.001;
		double error;
		double[] results = null;

		
		JacobianFunction jacobian=new JacobianFunction(PositionVector);
		
		do{
			
			RealVector DT=new ArrayRealVector((new ArrayRealVector(t0)).subtract(new ArrayRealVector(PositionVector.value(q0))));
			double[] dt = DT.toArray();

			
			double[][] jinv=MatrixOps.pinv(jacobian.value(q0));

	 		double[] lol = MatrixOps.multiply(jinv, dt);
			
			RealVector LOL= new ArrayRealVector(lol);
			RealVector Q1= new ArrayRealVector((new ArrayRealVector(q0)).add(LOL));
			error=(Q1.subtract(Q0)).getNorm();
			Q0=Q1;
			q0 = Q0.toArray();
			
			 if(error<e){
				 StdOut.println("Joint values: ");
				 	results=Q1.toArray();
				 	//StdArrayIO.print(results); 
			 }
			
			
		}while(error>e);
		
		results = domain(results);
		return results;
	}
	
	public static double[] domain(double[] x){
	
	for(int i=0; i<x.length; i++){
		if(x[i]<-FastMath.PI){
			x[i]%=-2*FastMath.PI;
			
			if(x[i]<-FastMath.PI){
				x[i]+= 2*FastMath.PI;
			}
			
			else{
				
			}
			
		}
		
		else if(x[i]>FastMath.PI){
			x[i]%=2*FastMath.PI;
			
			if(x[i]>FastMath.PI){
				x[i]-= 2*FastMath.PI;
			}
			
			else{
				
			}
			
		}
	}
		
		
		
		return x;
		
	}

}

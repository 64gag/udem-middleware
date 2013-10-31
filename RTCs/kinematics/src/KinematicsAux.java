

import java.io.IOException;

import com.google.gson.Gson;



public class KinematicsAux {

	/**
	 * @param args
	 * @throws IOException 
	 */
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub

		OutputData out = new OutputData();
		out.JOINTS = KinematicModule();
		Gson gson = new Gson();
		StdOut.print(gson.toJson(out));

	}
	
	public static double[] KinematicModule() throws IOException{
		StdOut.print("Input destination coordinates: ");
		double[] target = StdArrayIO.readDouble(3);
		double[] jointValues = InverseKin.InverseKinematicSolver(target);
		StdArrayIO.print(jointValues);
		return jointValues;
		
	}

}



import com.google.gson.*;

public class InputData {
       
        public int DOF;
        public double[][][] MATRIX_CONFIG;
        public String[] TYPE_CONFIG;
		public InputData DataJson;
 
        public InputData(String DataJson) {
                Gson gson = new Gson();
                this.DataJson = gson.fromJson(DataJson, InputData.class);
        }      
}
// -*- Java -*-
/*!
 * @file  KinematicsImpl.java
 * @brief Kinematics RTC
 * @date  $Date$
 *
 * $Id$
 */

import RTC.TimedLong;
import RTC.TimedString;
import jp.go.aist.rtm.RTC.DataFlowComponentBase;
import jp.go.aist.rtm.RTC.Manager;
import jp.go.aist.rtm.RTC.port.InPort;
import jp.go.aist.rtm.RTC.port.OutPort;
import jp.go.aist.rtm.RTC.util.DataRef;
import jp.go.aist.rtm.RTC.util.StringHolder;
import RTC.ReturnCode_t;

import com.google.gson.Gson;

public class KinematicsImpl extends DataFlowComponentBase {

	public KinematicsImpl(Manager manager) {  
        super(manager);
        m_p_target_val = new TimedString();
        m_p_target = new DataRef<TimedString>(m_p_target_val);
        m_TargetIn = new InPort<TimedString>("Target", m_p_target);
        
        m_p_status_val = new TimedLong();
        m_p_status = new DataRef<TimedLong>(m_p_status_val);
        m_StatusOut = new OutPort<TimedLong>("Status", m_p_status);
        
        m_p_result_val = new TimedString();
        m_p_result = new DataRef<TimedString>(m_p_result_val);
        m_ResultOut = new OutPort<TimedString>("Result", m_p_result);
    }

    @Override
    protected ReturnCode_t onInitialize() {
        addInPort("Target", m_TargetIn);
        
        addOutPort("Status", m_StatusOut);
        addOutPort("Result", m_ResultOut);

        bindParameter("robot_config", m_robot_config, "{\"dof\" : 7, \"matrix_config\" : [[[0.0,0.0,0.0],[1.0,0.0,0.0],[0.0,0.0,1.0]],[[0.0,0.4,0.0],[0.0,1.0,0.0],[0.0,0.0,1.0]],[[0.0,0.4,0.3],[1.0,0.0,0.0],[0.0,-1.0,0.0]],[[0.0,0.4,0.3],[0.0,-1.0,0.0],[0.0,0.0,1.0]],[[0.0,-0.1,0.3],[0.0,-1.0,0.0],[0.0,0.0,1.0]],[[0.0,-0.1,0.3],[1.0,0.0,0.0],[0.0,0.0,1.0]],[[0.0,-0.1,0.3],[0.0,-1.0,0.0],[0.0,0.0,1.0]]], \"type_config\" : [\"R\",\"R\",\"R\",\"R\",\"R\",\"R\",\"R\"] }");
        return super.onInitialize();
    }

    @Override
    protected ReturnCode_t onFinalize() {
        return super.onFinalize();
    }

    @Override
    protected ReturnCode_t onActivated(int ec_id) {
        return super.onActivated(ec_id);
    }

    @Override
    protected ReturnCode_t onDeactivated(int ec_id) {
        return super.onDeactivated(ec_id);
    }

    @Override
    protected ReturnCode_t onExecute(int ec_id) {

        if( m_TargetIn.isNew() ) {
        	m_TargetIn.read();

    		Gson in_gson = new Gson();
    		InputData in = new InputData();
    		String in_json = m_p_target.v.data;
    		in = in_gson.fromJson(in_json, InputData.class);
    		double[] target = in.target_coords;
    		double[] jointValues = InverseKin.InverseKinematicSolver(target, m_robot_config.toString());
    		
    		OutputData out = new OutputData();
    		out.joints = jointValues;
    		Gson out_gson = new Gson();
    		String out_json = new String(out_gson.toJson(out));
    		m_p_result_val.data = new String(out_json);
			m_p_result_val.tm = new RTC.Time(0,0);
		  	m_ResultOut.write();
			/*		  	
			m_p_status_val.data = 10;
		  	m_p_status_val.tm = new RTC.Time(0, 0);

		  	m_StatusOut.write();
		  	*/
          }
	  	
        return super.onExecute(ec_id);
    }

    protected StringHolder m_robot_config = new StringHolder();

    protected TimedString m_p_target_val;
    protected DataRef<TimedString> m_p_target;
    protected InPort<TimedString> m_TargetIn;

    protected TimedLong m_p_status_val;
    protected DataRef<TimedLong> m_p_status;
    protected OutPort<TimedLong> m_StatusOut;

    protected TimedString m_p_result_val;
    protected DataRef<TimedString> m_p_result;
    protected OutPort<TimedString> m_ResultOut;


}

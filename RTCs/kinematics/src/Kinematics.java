import jp.go.aist.rtm.RTC.Manager;
import jp.go.aist.rtm.RTC.RTObject_impl;
import jp.go.aist.rtm.RTC.RtcDeleteFunc;
import jp.go.aist.rtm.RTC.RtcNewFunc;
import jp.go.aist.rtm.RTC.RegisterModuleFunc;
import jp.go.aist.rtm.RTC.util.Properties;

public class Kinematics implements RtcNewFunc, RtcDeleteFunc, RegisterModuleFunc {

    public static String component_conf[] = {
    	    "implementation_id", "Kinematics",
    	    "type_name",         "Kinematics",
    	    "description",       "Kinematics RTC",
    	    "version",           "0.0.1",
    	    "vendor",            "UDEM",
    	    "category",          "Mechanical",
    	    "activity_type",     "STATIC",
    	    "max_instance",      "1",
    	    "language",          "Java",
    	    "lang_type",         "compile",
            "conf.default.robot_config", "{ \"dof\" : 6, \"matrix_config\" : [[[0.0, 0.0, 0.0],[1.0, 0.0, 0.0],[0.0, 0.0, 1.0]], [[0.0, 0.4, 0.0],[0.0, 1.0, 0.0],[0.0, 0.0, 1.0]], [[0.0,0.4,0.3],[1.0,0.0,0.0],[0.0,-1.0,0.0]], [[0.0,-0.1,0.3],[0.0,-1.0,0.0],[0.0,0.0,1.0]], [[0.0,-0.1,0.3],[1.0,0.0,0.0],[0.0,0.0,1.0]], [[0.0,-0.1,0.3],[0.0,-1.0,0.0],[0.0,0.0,1.0]]], \"type_config\" : [\"R\",\"R\",\"R\",\"R\",\"R\",\"R\"] }",
            "conf.__widget__.robot_config", "text",
    	    ""
            };

    public RTObject_impl createRtc(Manager mgr) {
        return new KinematicsImpl(mgr);
    }

    public void deleteRtc(RTObject_impl rtcBase) {
        rtcBase = null;
    }
    public void registerModule() {
        Properties prop = new Properties(component_conf);
        final Manager manager = Manager.instance();
        manager.registerFactory(prop, new Kinematics(), new Kinematics());
    }
}

import jp.go.aist.rtm.RTC.Manager;
import jp.go.aist.rtm.RTC.RTObject_impl;
import jp.go.aist.rtm.RTC.RtcDeleteFunc;
import jp.go.aist.rtm.RTC.RtcNewFunc;
import jp.go.aist.rtm.RTC.RegisterModuleFunc;
import jp.go.aist.rtm.RTC.util.Properties;

/*!
 * @class Kinematics
 * @brief Kinematics RTC-
 */
public class Kinematics implements RtcNewFunc, RtcDeleteFunc, RegisterModuleFunc {

//  Module specification
//  <rtc-template block="module_spec">
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
            "conf.default.robot_config", "{\"type_config\" : \"RRRRR\"," +
            		"\"matrix_config\" : [[[1,2,3], [4,5,6], [7,8,9]],[[1,2,3], [4,5,6], [7,8,9]]], "+
            		"\"dof\" : 7 }",
            "conf.__widget__.robot_config", "text",
    	    ""
            };
//  </rtc-template>

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

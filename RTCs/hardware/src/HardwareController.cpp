#include <vector>
#include <string>
#include <sstream>
#include <json/json.h>
#include "HardwareController.h"
#include "HardwareAux.h"

unsigned int HardwareController::haveCurrent(void)
{
	return angles_current.size();
}

unsigned int HardwareController::haveTarget(void)
{
	return angles_target.size();
}

void HardwareController::setValues(std::vector<float> v, unsigned short int t)
{
	switch(t){
	case V_SLOPES:
		slopes = v;
		break;
	case V_CURRENT:
		angles_current = v;
		break;
	case V_TARGET:
		angles_target = v;
		break;
	}
}

void HardwareController::setSlopes(std::vector<float> v){
	setValues(v, V_SLOPES);
}

void HardwareController::setCurrent(std::vector<float> v){
	setValues(v, V_CURRENT);
}

void HardwareController::setTarget(std::vector<float> v){
	setValues(v, V_TARGET);
}

unsigned int HardwareController::doUpdate(void)
{
	unsigned int ret = 0;
	
	if(!haveCurrent() || !haveTarget())
		return ret;
	
	for(int i=0;i<joints_count;i++) {
		if (angles_current[i] != angles_target[i]) {
			ret |= (1 << i);
			float smaller_current = (((float)(angles_current[i]<angles_target[i]))-0.5f)*2.0f;	//Ugly way to get -1 or 1
			float diff = (angles_target[i]-angles_current[i])*smaller_current;
			angles_current[i] += (diff>slopes[i] ? slopes[i]: diff)*smaller_current;
		}
	}

	return ret;
}

HardwareController::HardwareController(int j, std::vector<float> s)
{
	utid = 1;
	joints_count = j;
	slopes = s;
}

HardwareController::~HardwareController(void)
{
}

std::string HardwareController::getJSON(std::string format)
{
	std::ostringstream out;
	std::vector<std::string> format_pieces = split(format, '%');

	unsigned int i;
	for(i=0; i<format_pieces.size(); i++) {
		out << format_pieces[i];
		if(i+1 < format_pieces.size()) {
			out << angles_current[i];
		}
	}
	Json::Value toRobot;
	toRobot["ns"] = "org.jwebsocket.plugins.system";
	toRobot["type"] = "broadcast";
	toRobot["data"] = out.str();
	toRobot["responseRequested"] = true;
	toRobot["utid"] = utid++;

 return toRobot.toStyledString();
}

enum {
        HW_CURRENT=0,
        HW_TARGET,
        HW_COUNT
};

enum {
	V_SLOPES=0,
	V_CURRENT,
	V_TARGET
};

class HardwareController {
 private:
	int joints_count;
	unsigned int utid;
	std::vector<float> slopes;
	std::vector<float> angles_current;
	std::vector<float> angles_target;
 public:
	HardwareController(int, std::vector<float>);
	~HardwareController(void);
	void setValues(std::vector<float>, unsigned short int);
	void setSlopes(std::vector<float>);
	void setCurrent(std::vector<float>);
	void setTarget(std::vector<float>);
	unsigned int doUpdate(void);
	std::string getJSON(std::string);
	unsigned int haveCurrent();
	unsigned int haveTarget();
};

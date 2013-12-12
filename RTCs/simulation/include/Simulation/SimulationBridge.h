#ifndef SIMULATIONBRIDGE
#define SIMULATIONBRIDGE

extern "C" {

int ws_rosbridge_open(char *host, int port);
int ws_rosbridge_service(const char *a);
void ws_rosbridge_close(void);
void simRosSetJointState(int size, int *handles, int *setModes, float *values);
void simRosSetObjectPose(int handle, int relativeToObjectHandle, float *pose);

}

#endif

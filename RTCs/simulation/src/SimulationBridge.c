#include <libwebsockets.h>
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <stdint.h>

#define DEBUG

struct lws_context_creation_info *info;
struct libwebsocket_context *context;
struct libwebsocket *wsi;
char msg[2048];

int connected;
int done;

enum demo_protocols {
	PROTOCOL_ROS_SIMULATION,
	DEMO_PROTOCOL_COUNT
};

static int callback_rosbridge_simulation(struct libwebsocket_context *thisctx, struct libwebsocket *wsi, enum libwebsocket_callback_reasons reason, void *user, void *in, size_t len)
{
	unsigned char buf[LWS_SEND_BUFFER_PRE_PADDING + 4096 + LWS_SEND_BUFFER_POST_PADDING];
	int l = 0;
	int n;
	switch (reason) {
	case LWS_CALLBACK_CLIENT_ESTABLISHED:
		connected = 1;
		break;
	case LWS_CALLBACK_CLOSED:
		connected = 0;
		done = 1;
		break;
	case LWS_CALLBACK_CLIENT_RECEIVE:
		((char *)in)[len] = '\0';
		printf("%s\n", (char *)in);
		done = 1;
		break;
	case LWS_CALLBACK_CLIENT_WRITEABLE:
		//"{ \"op\": \"call_service\", \"service\": \"/vrep/simRosSetJointState\", \"args\": %s }"
		l += sprintf((char *)&buf[LWS_SEND_BUFFER_PRE_PADDING + l], "%s", msg);
		n = libwebsocket_write(wsi, &buf[LWS_SEND_BUFFER_PRE_PADDING], l, LWS_WRITE_TEXT);

		if (n < 0 || n < l)
			return -1;

		break;
	default:
		break;
	}

	return 0;
}

static struct libwebsocket_protocols protocols[] = {
	{
		"rosbridge",
		callback_rosbridge_simulation,
		0,
		25000000,
	},
	{ NULL, NULL, 0, 0 }
};

int ws_rosbridge_open(char *host, int port)
{
	connected = 0;

	lws_set_log_level(0, NULL);

	info = (struct lws_context_creation_info *)calloc(1, sizeof(struct lws_context_creation_info));
	if(info == NULL){
		return -1;
	}

	info->port = CONTEXT_PORT_NO_LISTEN;
	info->protocols = protocols;
	info->gid = -1;
	info->uid = -1;

	context = libwebsocket_create_context(info);
	if (context == NULL) {
		free(info);
		info = NULL;
		return -2;
	}
	
	wsi = libwebsocket_client_connect(context, host, port, 0, "/", host, host, protocols[PROTOCOL_ROS_SIMULATION].name, -1);

	if (wsi == NULL) {
		libwebsocket_context_destroy(context);
		free(info);
		info = NULL;
		return -3;
	}

	while(!connected)
		libwebsocket_service(context, 10);

	return 0;
}

int ws_rosbridge_service(const char *m)
{
	strcpy(msg, m);

	if (connected) {
		libwebsocket_callback_on_writable(context, wsi);
		done = 0;
		while(!done)
			libwebsocket_service(context, 10);
	}

	return 0;
}

void ws_rosbridge_close(void)
{
	libwebsocket_context_destroy(context);
	free(info);
	info = NULL;
}

void simRosSetJointState(int size, int *handles, int *setModes, float *values)
{
	char msg[512], handles_str[128], setModes_str[128], values_str[256];
	int i;
	sprintf(handles_str, "%d", handles[0]);
	sprintf(setModes_str, "%d", setModes[0]);
	sprintf(values_str, "%f", values[0]);
	for(i=1; i<size; i++) {
		sprintf(handles_str, "%s, %d", handles_str, handles[i]);
		sprintf(setModes_str, "%s, %d", setModes_str, setModes[i]);
		sprintf(values_str, "%s, %f", values_str, values[i]);
	}
	sprintf(msg, "{\"op\" : \"call_service\", \"service\" : \"/vrep/simRosSetJointState\", \"args\" : {\"handles\" : [%s], \"setModes\" : [%s], \"values\" : [%s]}}", handles_str, setModes_str, values_str);
#ifdef DEBUG
	printf("%s\n", msg);
#endif
	ws_rosbridge_service(msg);
}

void simRosSetObjectPose(int handle, int relativeToObjectHandle, float *pose){

	char msg[512];
	sprintf(msg, "{\"op\" : \"call_service\", \"service\" : \"/vrep/simRosSetObjectPose\", \"args\" : {\"handle\" : %d, \"relativeToObjectHandle\" : %d, \"pose\" : {\"position\" : {\"x\" : %f, \"y\" : %f, \"z\" : %f}, \"orientation\" : {\"x\" : %f, \"y\" : %f, \"z\" : %f,  \"w\" : %f}}}}", handle, relativeToObjectHandle, pose[0], pose[1], pose[2], pose[3], pose[4], pose[5], pose[6]);
#ifdef DEBUG
	printf("%s\n", msg);
#endif
	ws_rosbridge_service(msg);
}




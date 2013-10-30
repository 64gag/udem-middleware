#include <libwebsockets.h>
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <stdint.h>

extern unsigned char *cam_data;

char topic[128];
int was_closed = 0;
int force_exit = 0;
int step = 0;

enum demo_protocols {
	PROTOCOL_ROS_IMAGE,
	DEMO_PROTOCOL_COUNT
};

static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

static char *decoding_table = NULL;

void build_decoding_table() {
	decoding_table = (char *)malloc(256);
	int i;
	for (i = 0; i < 64; i++)
		decoding_table[(unsigned char) encoding_table[i]] = i;
}

void base64_cleanup() {
	free(decoding_table);
	decoding_table = NULL;
}

unsigned char *base64_decode(const char *data, size_t input_length, size_t *output_length) {

	if (decoding_table == NULL) build_decoding_table();
	if (input_length % 4 != 0){
		return NULL;
	}

	*output_length = input_length / 4 * 3;
	if (data[input_length - 1] == '=') (*output_length)--;
	if (data[input_length - 2] == '=') (*output_length)--;

//	unsigned char *decoded_data = (unsigned char *)malloc(*output_length);
	unsigned char *decoded_data = cam_data;
	if (decoded_data == NULL){
		return NULL;
	}
	unsigned int i, j;
	for (i = 0, j = 0; i < input_length;) {
		uint32_t sextet_a = data[i] == '=' ? 0 & i++ : decoding_table[(unsigned char)data[i++]];
		uint32_t sextet_b = data[i] == '=' ? 0 & i++ : decoding_table[(unsigned char)data[i++]];
		uint32_t sextet_c = data[i] == '=' ? 0 & i++ : decoding_table[(unsigned char)data[i++]];
		uint32_t sextet_d = data[i] == '=' ? 0 & i++ : decoding_table[(unsigned char)data[i++]];

		uint32_t triple = (sextet_a << 3 * 6)
		+ (sextet_b << 2 * 6)
		+ (sextet_c << 1 * 6)
		+ (sextet_d << 0 * 6);

		if (j < *output_length) decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
		if (j < *output_length) decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
		if (j < *output_length) decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
	}

	return decoded_data;
}


static int callback_ros_image(struct libwebsocket_context *thisctx, struct libwebsocket *wsi, enum libwebsocket_callback_reasons reason, void *user, void *in, size_t len)
{
	unsigned char buf[LWS_SEND_BUFFER_PRE_PADDING + 4096 + LWS_SEND_BUFFER_POST_PADDING];
	int l = 0, n;
	switch (reason) {
		case LWS_CALLBACK_CLOSED:
			was_closed = 1;
			break;
		case LWS_CALLBACK_CLIENT_RECEIVE:
			((char *)in)[len] = '\0';
			{
				char * data, *data_end;
				data = strstr ((char *)in, "data");
				data += 8; /* Move past 'data" : "' */
				data_end = strstr(((char *)in)+len-100, "\""); /* Search from the end, because it is faster */
				*data_end = '\0';
				size_t ol;
				cam_data = base64_decode(data, data_end-data, &ol);
			}
			libwebsocket_callback_on_writable(thisctx, wsi);
			break;
		case LWS_CALLBACK_CLIENT_ESTABLISHED:
			libwebsocket_callback_on_writable(thisctx, wsi);
			break;
		case LWS_CALLBACK_CLIENT_WRITEABLE:
			if(step == 0){
				l += sprintf((char *)&buf[LWS_SEND_BUFFER_PRE_PADDING + l],
				"{ \"op\": \"subscribe\", \"topic\": \"%s\", \"type\": \"sensor_msgs/Image\" }", topic);

				n = libwebsocket_write(wsi, &buf[LWS_SEND_BUFFER_PRE_PADDING], l, LWS_WRITE_TEXT);

				if (n < 0)
					return -1;
				if (n < l) {
					return -1;
				}
				step++;
			}else{
				l += sprintf((char *)&buf[LWS_SEND_BUFFER_PRE_PADDING + l],
				"{ \"op\": \"unsubscribe\", \"topic\": \"%s\" }", topic);

				n = libwebsocket_write(wsi, &buf[LWS_SEND_BUFFER_PRE_PADDING], l, LWS_WRITE_TEXT);

				if (n < 0)
					return -1;
				if (n < l) {
					return -1;
				}

				force_exit = 1;
				step = 0;
			}
			break;
		default:
			break;
	}

	return 0;
}

static struct libwebsocket_protocols protocols[] = {
	{
		"ros-image",
		callback_ros_image,
		0,
		25000000,
	},
	{ NULL, NULL, 0, 0 } /* end */
};

int getImageRaw(const char * host, int port, const char * target_topic)
{
	int n = 0, use_ssl = 0;
	struct libwebsocket_context *context;
	const char *address;
	struct libwebsocket *wsi;
	int ietf_version = -1;
	struct lws_context_creation_info info;
	force_exit = 0; was_closed = 0;
	memset(&info, 0, sizeof info);
	address = host;
	info.port = CONTEXT_PORT_NO_LISTEN;
	info.protocols = protocols;
	info.gid = -1; info.uid = -1;

	lws_set_log_level(0, NULL);

	strcpy(topic, target_topic);
	context = libwebsocket_create_context(&info);
	if (context == NULL) {
		return 1;
	}

	wsi = libwebsocket_client_connect(context, address, port, use_ssl, "/", host, host, protocols[PROTOCOL_ROS_IMAGE].name, ietf_version);

	if (wsi == NULL) {
		libwebsocket_context_destroy(context);
		return 1;
	}

	n = 0;
	while (n >= 0 && !was_closed && !force_exit)
	{
		n = libwebsocket_service(context, 10);
		if (n < 0)
			continue;
	}

	libwebsocket_context_destroy(context);
	return 0;
}


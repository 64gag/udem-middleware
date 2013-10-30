extern "C" {

	void build_decoding_table();
	void base64_cleanup();
	unsigned char *base64_decode(const char *data, size_t input_length, size_t *output_length);
	int getImageRaw(const char * host, int port, const char * topic);

}

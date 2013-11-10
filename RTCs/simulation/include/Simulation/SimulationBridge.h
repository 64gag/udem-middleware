extern "C" {

int ws_vrep_open(char *host, int port);
int ws_vrep_service(const char *a);
void ws_vrep_close(void);

}

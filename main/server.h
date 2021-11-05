#include <esp_system.h>
#include "esp_err.h"
#include "esp_netif.h"

static const char *HTTP_TAG = "server";

esp_err_t hello_get_handler(httpd_req_t *req);
esp_err_t http_404_error_handler(httpd_req_t *req, httpd_err_code_t err);
httpd_handle_t start_webserver(void);
void stop_webserver(httpd_handle_t server);
void disconnect_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);
void connect_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data);

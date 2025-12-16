#ifndef C2RN_WEB_H
#define C2RN_WEB_H
#include <openssl/ssl.h>
#include <openssl/err.h>
void remove_newlines(char *str);
void initialize_ssl(); 
SSL_CTX* create_ssl_context();
void ww_dial(const char* host, char* message, char *response, size_t message_size, size_t response_size);
void ww_get_self_ip(
    const char* message, 
    char* ip, 
    size_t response_size, 
    size_t message_size
);
void ww_get_json(
    const char* chat_id, 
    const char* text, 
    const char* TOKEN, 
    const char* message, 
    char* json, 
    size_t response_size, 
    size_t message_size
);
void ww_call(
    const char* TOKEN, 
    char *response, 
    size_t response_size
);
#endif
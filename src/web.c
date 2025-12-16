#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define PORT 443

void remove_newlines(char *str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != '\n') {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

void initialize_ssl() {
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
}

SSL_CTX* create_ssl_context() {
    const SSL_METHOD *method;
    SSL_CTX *ctx;

    method = TLS_client_method();
    ctx = SSL_CTX_new(method);
    if (!ctx) {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    return ctx;
}

void ww_dial(
    const char* host,
    char* message,
    char *response,
    size_t message_size,
    size_t response_size
) {
    int sockfd;
    struct hostent *server;
    struct sockaddr_in serv_addr;
    initialize_ssl();
    SSL_CTX *ctx = create_ssl_context();
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        fprintf(stderr,"ERROR opening socket\n");
        exit(1);
    }
    server = gethostbyname(host);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(1);
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        fprintf(stderr,"ERROR connecting");
        exit(1);
    }
    SSL *ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sockfd);
    if (SSL_connect(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(1);
    }
    int bytes = SSL_write(ssl, message, strlen(message));
    if (bytes <= 0) {
        ERR_print_errors_fp(stderr);
        exit(1);
    }
    int total_bytes = 0;
    while (total_bytes < (int)response_size - 1) {
        bytes = SSL_read(ssl, response + total_bytes, response_size - total_bytes - 1);
        if (bytes <= 0) break;
        total_bytes += bytes;
    }
    if (total_bytes > 0) {
        response[total_bytes] = '\0';
    }
    SSL_free(ssl);
    close(sockfd);
    SSL_CTX_free(ctx);
}
void ww_get_self_ip(
    const char* message, 
    char* ip, 
    size_t response_size, 
    size_t message_size
) {
    char response[8192];
    const char* host = "ifconfig.me";
    sprintf(
        message,
        "GET /ip "
        "HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n",
        host
    );
    ww_dial(host,message,response,message_size,response_size);
    regex_t regex;
    if (regcomp(&regex, "([0-9]{1,3}\\.){3}[0-9]{1,3}", REG_EXTENDED)) {
        printf("Could not compile regex");
    }
    regmatch_t match;
    int result = regexec(&regex, response, 1, &match, 0);
    strncpy(ip, response + match.rm_so, match.rm_eo - match.rm_so);
    ip[match.rm_eo - match.rm_so] = '\0'; // Terminator
    regfree(&regex);
}
void ww_get_json(
    const char* chat_id, 
    const char* text, 
    const char* TOKEN, 
    const char* message, 
    char* json, 
    size_t response_size, 
    size_t message_size
) {
    char response[8192];
    const char* host = "api.telegram.org";
    sprintf(message,
	"GET /bot%s/sendMessage?chat_id=%s&text=%s "
    "HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", TOKEN, 
        chat_id, 
        text, 
        host);
    ww_dial(host,message,response,message_size,response_size);
    regex_t regex;
    remove_newlines(response);
    if (regcomp(&regex, "\\{.*\\}", REG_EXTENDED)) {
        printf("Could not compile regex");
    }
    regmatch_t match;
    regexec(&regex, response, 1, &match, 0);
    strncpy(json, response + match.rm_so, match.rm_eo - match.rm_so);
    json[match.rm_eo - match.rm_so] = '\0'; // Terminator
    regfree(&regex);
}
void ww_call(
    const char* TOKEN, 
    char *response, 
    size_t response_size
) {
    const char* host = "api.telegram.org";
    const char message[1024];
    sprintf(
        message,
        "GET /bot%s/getUpdates "
        "HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n",
        TOKEN, 
        host
    );
    ww_dial(host, message, response, 1024, response_size);
    host = "ifconfig.me";
    sprintf(
        message,
        "GET /ip "
        "HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n",
        host
    );
    ww_dial(host, message, response, 1024, response_size);
}

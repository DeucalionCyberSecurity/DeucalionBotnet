#include <arpa/inet.h>
#include <netdb.h>

int main() {
    const char *domain = "shit.d3vsoft.com";
    struct addrinfo hints, *res, *p;
    struct sockaddr_in *ipv4;
    char ipstr[INET_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET; // Use AF_INET for IPv4
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(domain, NULL, &hints, &res);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return 1;
    }

    printf("IP addresses for %s:\n", domain);

    for (p = res; p != NULL; p = p->ai_next) {
        ipv4 = (struct sockaddr_in *)p->ai_addr;
        inet_ntop(p->ai_family, &(ipv4->sin_addr), ipstr, sizeof ipstr);
        printf("  %s\n", ipstr);
    }

    freeaddrinfo(res);
    return 0;
}
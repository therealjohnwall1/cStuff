#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "client.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>


// testing shit out

int main(void) {

    char* pageName = "ebay.com";  // Corrected to use double quotes for string

    struct hostent *server;
    server = gethostbyname(pageName);  // Corrected function name

    if (server == NULL) {
        fprintf(stderr, "Error: %s\n", hstrerror(h_errno));
        exit(1);
    }

    printf("Official name: %s\n", server->h_name);

    printf("Aliases:\n");
    for (char **alias = server->h_aliases; *alias != NULL; alias++) {
        printf("\t%s\n", *alias);
    }

    printf("Address type: %d\n", server->h_addrtype);
    printf("Address length: %d\n", server->h_length);

    printf("Addresses:\n");
    for(int i = 0; i < server->h_length; i++) {
        printf("%s\n",server->h_addr_list[i]);
    }

    return 0;

}

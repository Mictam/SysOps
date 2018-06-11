#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>

#define SOCKET_NAME "/tmp/aaaa"

int main(){
    int fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    unlink(SOCKET_NAME);
    struct sockaddr_un name;
    memset(&name, 0, sizeof(struct sockaddr_un));
    name.sun_family = AF_UNIX;
    strncpy(name.sun_path, SOCKET_NAME, sizeof(name.sun_path) - 1);
    bind(fd, (const struct sockaddr *) &name, sizeof(struct sockaddr_un));
    char buf[100];
    while(1){
        int a = read(fd, buf, 100);
        printf("%s\n", buf);
    }
}

client.c
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>

#define SOCKET_NAME "/tmp/aaaa"

int main(){
    int fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    struct sockaddr_un name;
    memset(&name, 0, sizeof(struct sockaddr_un));
    name.sun_family = AF_UNIX;
    strncpy(name.sun_path, SOCKET_NAME, sizeof(name.sun_path) - 1);
    bind(fd, (const struct sockaddr *) &name, sizeof(struct sockaddr_un));
    connect(fd, (const struct sockaddr *) &name, sizeof(struct sockaddr_un));
    char buf[100];
    sprintf(buf, "HELLO to proces: %d", getpid());
    write(fd, buf, sizeof(buf));
}

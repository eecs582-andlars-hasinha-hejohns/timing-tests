#define _GNU_SOURCE
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cassert>

#include <unistd.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <sstream>
#include <deque>

#define FFUSE_SHMEM_SIZE (1<<12)

struct client_handle{
};

static std::deque<client_handle> m;

int main(){
    for(const auto& x : m){
    }
    int ffuse_server_fd;
    if((ffuse_server_fd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0){
        perror("socket");
        return EXIT_FAILURE;
    }
    struct sockaddr_un ffuse_server_addr;
    ffuse_server_addr.sun_family = AF_UNIX;
    char ffuse_server_addr_path[sizeof(ffuse_server_addr.sun_path)];
    memset(ffuse_server_addr.sun_path, 0, sizeof(ffuse_server_addr_path));
    char path[] = "\0/ffuse/server.sock";
    memcpy(ffuse_server_addr.sun_path, path, sizeof(path));
    if(bind(ffuse_server_fd, (struct sockaddr *)&ffuse_server_addr, sizeof(ffuse_server_addr))){
        perror("bind");
        return EXIT_FAILURE;
    }
    sleep(5);
    union {
        struct cmsghdr cmsg;
        char control_buf[CMSG_SPACE(sizeof(int))];
    } cmsg_buf;
    struct msghdr msg;
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_control = cmsg_buf.control_buf;
    msg.msg_controllen = sizeof(cmsg_buf.control_buf);
    recvmsg(ffuse_server_fd, &msg, 0);
    struct cmsghdr *cmsg = CMSG_FIRSTHDR(&msg);
    int ffuse_fd;
    memcpy(&ffuse_fd, CMSG_DATA(cmsg), sizeof(ffuse_fd));
    void *ffuse_shmem;
    if((ffuse_shmem = mmap(NULL, FFUSE_SHMEM_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, ffuse_fd, 0)) == (void *)-1){
        perror("mmap");
        return EXIT_FAILURE;
    }
    if(mlock(ffuse_shmem, FFUSE_SHMEM_SIZE)){
        perror("mlock");
        return EXIT_FAILURE;
    }
    printf("%s\n", ffuse_shmem);
    return EXIT_SUCCESS;
}

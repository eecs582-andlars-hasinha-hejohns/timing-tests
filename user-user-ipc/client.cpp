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

#define FFUSE_SHMEM_SIZE (1<<12)

int main(){
    int ffuse_fd;
    if((ffuse_fd = memfd_create("ffuse", MFD_ALLOW_SEALING)) == -1){
        perror("memfd_create");
        return EXIT_FAILURE;
    }
    if(ftruncate(ffuse_fd, FFUSE_SHMEM_SIZE)){
        perror("ftruncate");
        return EXIT_FAILURE;
    }
    void *ffuse_shmem;
    if((ffuse_shmem = mmap(NULL, FFUSE_SHMEM_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, ffuse_fd, 0)) == (void *)-1){
        perror("mmap");
        return EXIT_FAILURE;
    }
    if(mlock(ffuse_shmem, FFUSE_SHMEM_SIZE)){
        perror("mlock");
        return EXIT_FAILURE;
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
    if(connect(ffuse_server_fd, (struct sockaddr *)&ffuse_server_addr, sizeof(ffuse_server_addr))){
        perror("connect");
        return EXIT_FAILURE;
    }
    union {
        struct cmsghdr cmsg;
        char control_buf[CMSG_SPACE(sizeof(int))];
    } cmsg_buf;
    struct msghdr msg;
    msg.msg_control = cmsg_buf.control_buf;
    msg.msg_controllen = sizeof(cmsg_buf.control_buf);
    struct cmsghdr *cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_len = CMSG_LEN(sizeof(int));
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    memcpy(CMSG_DATA(cmsg), &ffuse_fd, sizeof(int));
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    sendmsg(ffuse_server_fd, &msg, 0);
    sprintf((char *)ffuse_shmem, "Hello World!");
    sleep(10);
    return EXIT_SUCCESS;
}

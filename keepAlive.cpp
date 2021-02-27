//
// Created by wy on 2021/2/27.
//

#include "keepAlive.h"
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <sys/select.h>
#include <netinet/tcp.h>
using namespace std;

#define LISTENNUM 5

int main()
{
    int skfd;
    if ((skfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("");
        exit(-1);
    }

    struct sockaddr_in saddr;
    bzero(&saddr, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    saddr.sin_addr.s_addr = inet_addr("115.29.109.198");

    if (bind(skfd, (struct sockaddr*)&saddr, sizeof(saddr)) < 0) {
        perror("");
        exit(-1);
    }

    if (listen(skfd, LISTENNUM) < 0) {
        perror("");
        exit(-1);
    }

    int clifd;
    if ((clifd = accept(skfd, NULL, NULL)) < 0) {
        perror("");
        exit(-1);
    }
    cout << "有新连接" << endl;

    //setsockopt
    int tcp_keepalive_intvl = 5;   //保活探测消息的发送频率。默认值为75s
    int tcp_keepalive_probes = 5;  //TCP发送保活探测消息以确定连接是否已断开的次数。默认值为9次
    int tcp_keepalive_time = 5;    //允许的持续空闲时间。默认值为7200s（2h）
    int tcp_keepalive_on = 1;

    if (setsockopt(clifd, SOL_TCP, TCP_KEEPINTVL,
                   &tcp_keepalive_intvl, sizeof(tcp_keepalive_intvl)) < 0) {
        perror("");
        exit(-1);
    }

    if (setsockopt(clifd, SOL_TCP, TCP_KEEPCNT,
                   &tcp_keepalive_probes, sizeof(tcp_keepalive_probes)) < 0) {
        perror("");
        exit(-1);
    }

    if (setsockopt(clifd, SOL_TCP, TCP_KEEPIDLE,
                   &tcp_keepalive_time, sizeof(tcp_keepalive_time)) < 0) {
        perror("");
        exit(-1);
    }

    if (setsockopt(clifd, SOL_SOCKET, SO_KEEPALIVE,
                   &tcp_keepalive_on, sizeof(tcp_keepalive_on))) {
        perror("");
        exit(-1);
    }

    char buf[1025];
    int r;
    int maxfd;
    fd_set rset;
    FD_ZERO(&rset);
    sleep(5);
    while (1) {
        FD_SET(clifd, &rset);
        maxfd = clifd + 1;
        if (select(maxfd, &rset, NULL, NULL, NULL) < 0) {
            perror("");
            exit(-1);
        }

        if (FD_ISSET(clifd, &rset)) {
            r = read(clifd, buf, sizeof(buf));
            if (r == 0) {
                cout << "接收到FIN" << endl;
                close(clifd);
                break;
            }
            else if (r == -1) {
                if (errno == EINTR) {
                    cout << "errno: EINTR" << endl;
                    continue;
                }

                if (errno == ECONNRESET) {
                    cout << "errno: ECONNRESET" << endl;
                    cout << "对端已崩溃且已重新启动" << endl;
                    close(clifd);
                    break;
                }

                if (errno == ETIMEDOUT) {
                    cout << "errno: ETIMEDOUT" << endl;
                    cout << "对端主机崩溃" << endl;
                    close(clifd);
                    break;
                }

                if (errno == EHOSTUNREACH) {
                    cout << "errno: EHOSTUNREACH" << endl;
                    cout << "对端主机不可达" << endl;
                    close(clifd);
                    break;
                }
            }
        }
    }

    close(skfd);
    return 0;
}

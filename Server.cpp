#include "BinarTree.h"
#include "DataBase.h"
#include <iostream>
#include "BTree.h"



#pragma comment(lib, "Ws2_32.lib")
#pragma warning(suppress : 4996)
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORT    5555
#define BUFLEN  4096

int   readFromClient(int fd, char* buf);
void  writeToClient(int fd, char* buf);

int main(void)
{
    std::string loadFile = "test.txt";
    DataBase dataBase;

    dataBase.LoadData(loadFile);
    //vector<Student> studlist = dataBase.tree.Find(4.21, 4.21);
    //cout << endl;
    //dataBase.tree.Delete(dataBase.studentList[1]);
    //dataBase.Show();
    //for (int i = 0; i < studlist.size(); ++i) cout << studlist[i].rating << endl;
    //dataBase.btree.traverse();
    //vector<Student> studs;
    //studs = dataBase.btree.FindFrom("I");
    //for (int i = 0; i < studs.size(); ++i)
    //{
    //    cout << studs[i].lastName << endl;
    //}
    //vector<Student> v = dataBase.hashSet.Find("A", 203, 211, 4, 5);

    //dataBase.tree.Obhod();
    //int i;
    //for (i = 0; i < 13; ++i) dataBase.tree.Delete(dataBase.studentList[i]);
    //while (1)
    //{
    //    i = 0;
    //    cin >> i;
    //    dataBase.tree.Delete(dataBase.studentList[i]);

    int     i, err, opt = 1;
    int     sock, new_sock;
    fd_set  active_set, read_set;
    struct  sockaddr_in  addr;
    struct  sockaddr_in  client;
    char    buf[BUFLEN];
    char    otvet[BUFLEN];
    socklen_t  size;

    printf("http SERVER\n");

    // Инициализация windows sockets
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("WSAStartup failed\n");
        return 1;
    }

    // Создаем TCP сокет для приема запросов на соединение
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("Server: cannot create socket");
        exit(EXIT_FAILURE);
    }
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    // Заполняем адресную структуру и
    // связываем сокет с любым адресом
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    err = bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    if (err < 0)
    {
        perror("Server: cannot bind socket");
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Создаем очередь на 3 входящих запроса соединения
    err = listen(sock, 3);
    if (err < 0)
    {
        perror("Server: listen queue failure");
        WSACleanup();
        exit(EXIT_FAILURE);
    }


    FD_ZERO(&active_set);
    FD_SET(sock, &active_set);


    while (true)
    {

        read_set = active_set;
        if (select(FD_SETSIZE, &read_set, NULL, NULL, NULL) < 0)
        {
            perror("Server: select  failure");
            WSACleanup();
            exit(EXIT_FAILURE);
        }
        
        for (int j = 0; j < read_set.fd_count; j++)
        {
            i = read_set.fd_array[j];
            if (FD_ISSET(i, &read_set))
            {
                if (i == sock)
                {
                    size = sizeof(client);
                    new_sock = accept(sock, (struct sockaddr*)&client, &size);
                    if (new_sock < 0)
                    {
                        perror("accept");
                        WSACleanup();
                        exit(EXIT_FAILURE);
                    }
                    fprintf(stdout, "Server: connect from host %s, port %hu.\n",
                        inet_ntoa(client.sin_addr),
                        ntohs(client.sin_port));
                    FD_SET(new_sock, &active_set);
                    fprintf(stdout, "new socket = %d\n", new_sock);
                }
                else
                {
                    fprintf(stdout, "socket = %d\n", i);
                    
                    err = readFromClient(i, buf);
                    if (err < 0)
                    {
                        closesocket(i);
                        FD_CLR(i, &active_set);
                        fprintf(stdout, "close socket = %d\n", i);
                    }
                    else
                    {
                        
                        if (strstr(buf, "stop"))
                        {
                            closesocket(i);
                            FD_CLR(i, &active_set);
                            dataBase.SaveData(loadFile);
                            fprintf(stdout, "close socket = %d\n", i);
                        }
                        else
                        {
                            strcpy_s(otvet, dataBase.ReadLine(buf).c_str());
                            writeToClient(i, otvet);
                            //closesocket(i);
                            //FD_CLR(i, &active_set);
                        }
                    }
                }
            }
        }
    }
    WSACleanup();

    std::string str;
    while (1)
    {
        std::getline(std::cin, str);
        std::cout << dataBase.ReadLine(str) << std::endl;
    }
    


}


int  readFromClient(int fd, char* buf)
{
    int  nbytes;

    nbytes = recv(fd, buf, BUFLEN, 0);
    fprintf(stdout, "reading %d bytes from socket %d\n", nbytes, fd);
    if (nbytes < 0)
    {
        // ошибка чтения
        perror("Server: read failure");
        return -1;
    }
    else if (nbytes == 0)
    {
        // больше нет данных
        return -1;
    }
    else
    {
        // есть данные
        fprintf(stdout, "Server got message: %s\n", buf);
        return 0;
    }
}


void  writeToClient(int fd, char* buf)
{
    int  nbytes;
    nbytes = send(fd, buf, strlen(buf) + 1, 0);
    fprintf(stdout, "Write back: %s\nnbytes=%d\n", buf, nbytes);

    if (nbytes < 0)
    {
        perror("Server: write failure");
    }
}
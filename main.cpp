//Questao 2 - Prova 3 de LPII
// Felipe Melo
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include "Fila.h"
#include "Pilha.h"

#define ADDR_SIZE 16
#define QTD_CLIENTES 6
#define SERVER_PORT 8600
#define TAM_MSG 100


using namespace std;

int contClient = 0;

//Verifica palindromo com um TAD de Pilha e Fila usando o buffer como parametro a ser analisado
int verificaPalindromo(char* buffer){
  int aux = 0;
  Fila fila;
  Pilha pilha;
  int contador = 0;

    for (int i = 0; buffer[i] != '\0'; i++){
      if (buffer[i] != ' '){
        pilha.inserir(buffer[i]);
        fila.inserir(buffer[i]);
        contador++;
      }
    }


  for (int i = 0; i < contador; i++){
    if(pilha.remover() != fila.remover()){
     aux = 1;
    }
  }

  if (aux == 1){
    return 0;
  }
  return 1;
}


void *handle_client(void *p)
{
    int my_client_fd = (int)p;
    char *welcome_msg = "BEMVINDO\n";//Para cada thread
    write(my_client_fd, welcome_msg, strlen(welcome_msg));
    while (true){
        char buffer[TAM_MSG];
        char msg_to_client[TAM_MSG];
        char* token;
        int read_size;
        srand(time(NULL));
        read_size = read(my_client_fd, buffer, TAM_MSG);

        if (read_size > 0){
            buffer[strcspn(buffer, "\n")] = 0;
            cout << "Client:" <<  buffer << endl;
            
            //Finaliza se receber a palavra SHUTDOWN
            if (strcmp("SHUTDOWN", buffer, 8) == 0){
              close(my_client_fd);
              contClient--;
              pthread_exit(NULL);
            }

            //Diz se eh palindromo ou nao
            if (verificaPalindromo(buffer)){
                cout << "Eh Palindromo!" << endl;
             }else{
                cout << "Nao eh Palindromo!" << endl;
             }
            }

        sprintf(msg_to_client, "Contador clientes: %d\n", contClient);

        write(my_client_fd, msg_to_client, strlen(msg_to_client));
    }
}

int main(void)
{
    
    int server_fd;
    int client_fd[QTD_CLIENTES];
    int client_info_len[QTD_CLIENTES];
    int client_index = 0;

    unsigned int server_port = 0;
    struct sockaddr_in server_info;
    struct sockaddr_in client_info[QTD_CLIENTES];
    pthread_t client_thread[QTD_CLIENTES];

    cout << "Porta do server :" << SERVER_PORT << endl;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        cout << "Problemas na criacao do socket!" << endl;
        exit(0);
    }
    else
    {
        bzero(&server_info, sizeof(server_info));

        for (int i = 0; i < QTD_CLIENTES; i++)
        {
            bzero(&client_info[i], sizeof(client_info[i]));
        }

        server_info.sin_family = AF_INET;
        server_info.sin_addr.s_addr = htonl(INADDR_ANY);
        server_info.sin_port = htons(SERVER_PORT);

        if ((bind(server_fd, (const struct sockaddr *)&server_info, sizeof(server_info))) != 0)
        {
            cout << "Problemas no bind()" << endl;
            exit(0);
        }
        else
        {
            cout << "Aguardando conexoes na porta" << SERVER_PORT << endl;

            if (listen(server_fd, QTD_CLIENTES) != 0)
            {
                cout << endl << "Erro ao invocar funcao listen()" << endl;
                exit(0);
            }
            else
            {
                cout << "..." << endl;
                char addr_buf[ADDR_SIZE + 1];

                while (client_fd[client_index] = accept(server_fd, (struct sockaddr *)&client_info[client_index].sin_addr, &client_info_len[client_index]))
                {
                    char *client_ip_addr = inet_ntoa(client_info[client_index].sin_addr);
                    cout << "[" << client_index << "]"  << "Recebi conexao de " << client_ip_addr << endl;

                    pthread_create(&client_thread[client_index], NULL, handle_client, (void *)client_fd[client_index]);

                    contClient++;
                    client_index++;
                    client_index = client_index % 10;

                    cout << "Total de clientes conectados: " << contClient << endl;
                }
            }
        }
    }
    return 0;
}

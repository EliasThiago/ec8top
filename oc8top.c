#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"
#include "versaoso.h"
#include "numprocessos.h"
#include "infomemoria.h"
#include "bateria.h"

#define tamanho_buffer 10000

static int segmento_inicial(char *b, size_t s) {//snprintf substitui o valor no buffer, se usá-lo irá substituir os dados do buffer
    snprintf(b,s, "<h1>Monitorador de recursos %lu</h1><hr>", random() % 100);
    return 1;
}

static int segmento_sobre(char *b, size_t s) {//strncat concatena informações ao buffer, por isso é bom usá-lo somente
    strncat(b, "<hr><center><h4><i>Feito pela turma 2011 da Unipac Lafaiete - &copy; Todos os direitos reservados</i></h4></center>", s);
    return 1;
}

static int ev_handler(struct mg_connection *conn, 
                      enum mg_event ev) { //funcao que abriga os codigos html da pagina
  char buffer[tamanho_buffer];
  buffer[0] = '\x0';
  switch (ev) {
    case MG_AUTH: return MG_TRUE;
    case MG_REQUEST:
      mg_send_header(conn, "Content-Type", "text/html");
	//inicio da pagina      
	strncpy(buffer, 
        "<doctype html>\n"
	"<html>\n"
        "<header>"
        "<title>EC8</title>"
        "</header>\n"
        "<body>\n", sizeof(buffer)); 
	
      //acrescenta informacoes iniciais da pagina 
      segmento_inicial(buffer, sizeof(buffer));
      
      /* a partir daqui serao colodas as funcoes que irao compor a pagina: */

      //acrescenta as informações de versão do SO
      versaoso(buffer, sizeof(buffer));

      //informações sobre quantidade de processos e tempo de atividade
      infomemoria(buffer, sizeof(buffer));

      //informações sobre memoria RAM
      numprocessos(buffer, sizeof(buffer));
      
      
      //acrescenta as informações da bateria
      bateria(buffer, sizeof(buffer));

      /* ultimo segmento com informacoes de rodape */	
      segmento_sobre(buffer, sizeof(buffer));
      strncat(buffer, 
        "</body>\n"
        "</html>", sizeof(buffer));

      mg_printf_data(conn, buffer);
      return MG_TRUE;
    default: return MG_FALSE;
  }
}

int main(void) {
  struct mg_server *server;

  // Create and configure the server
  server = mg_create_server(NULL, ev_handler);
  mg_set_option(server, "listening_port", "8080");  //porta usada e a porta 8080

  // Serve request. Hit Ctrl-C to terminate the program
  printf("Starting on port %s\n", mg_get_option(server, "listening_port"));
  for (;;) {
    mg_poll_server(server, 1000);
  }

  // Cleanup, and free server instance
  mg_destroy_server(&server);

  return 0;
}


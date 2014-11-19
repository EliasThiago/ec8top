#include <stdio.h>
#include <string.h>
#include <sys/sysinfo.h> //biblioteca que permite obter info dos sistema
#include "infomemoria.h"

int infomemoria(char *b, size_t s) {//Função que que mostra status da memoria Ram do sistema

	/* Conversoes para uso de medidas */
	const double megabyte = 1024 * 1024; // definindo a constante megabyte

	/* Obtendo informacoes do sistema  */
	struct sysinfo si; // estruturou uma "variavel" com as definicoes do sysinfo
	sysinfo (&si);// sysinfo: retorna uma serie de informacoes do sistema como uptime, memoria disponivel, entre outros
    
	char buffer[500]; // setando buffer que contera o texto de tamanho 500
	buffer[0] = '\x0'; // o \x e responsavel pela sequencia de escape unicode (e semelhante ao \u, exceto pela definicao de comprimento de variavel)
	
	/*impressao das informacoes*/
	snprintf(buffer,500, "Total de Mem&oacuteria RAM: %5.1f MB<br>Total de Mem&oacuteria RAM livre: %5.1f MB<br>Total de Mem&oacuteria 			RAM em uso: %5.1f MB<br>",
       		si.totalram / megabyte,si.freeram / megabyte , (si.totalram - si.freeram) / megabyte); // imprimindo o que foi requisitado no projeto
	strncat(b, "<h4>Informa&ccedil&otildees sobre a Mem&oacuteria RAM: </h4>", s);
	strncat(b, buffer, s); // anexa caracteres de uma string em outra, strncat(destino, origem, nr_caracteres)

  
	return 1;
}




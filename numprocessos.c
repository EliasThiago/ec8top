#include <stdio.h>
#include <string.h>
#include <sys/sysinfo.h> //biblioteca que permite obter info dos sistema
#include "numprocessos.h"

int numprocessos(char *b, size_t s) {//Função que que mostra quantos processos estao executando na maquina

	/* Conversoes para uso de medidas */
	const long minuto = 60; // definindo a constante minuto  
	const long hora = minuto * 60; // definindo a constante hora
	const long dia = hora * 24; // definindo a constante dia

	/* Obtendo informacoes do sistema  */
	struct sysinfo si; // estruturou uma "variavel" com as definicoes do sysinfo
	sysinfo (&si); // sysinfo: retorna uma serie de informacoes do sistema como uptime, memoria disponivel, entre outros 
    
	char buffer[500]; // setando buffer que contera o texto de tamanho 500
	buffer[0] = '\x0'; // \x e responsavel pela sequencia de escape unicode (e semelhante ao \u, exceto pela definicao de comprimento de variavel)
	
	/*impressao das informacoes*/
	snprintf(buffer,500, "Tempo de funcionamento do sistema: %ld dias, %ld:%02ld:%02ld h <br> Quantidade de processo em 			execu&ccedil&atildeo:  %d Procesos<br>",
       		si.uptime / dia , (si.uptime % dia) / hora,(si.uptime % hora) / minuto , si.uptime % minuto , si.procs); // imprimindo o que foi requisitado no projeto
	strncat(b, "<h4>Atividade da M&aacutequina e Processos: </h4>", s);
	strncat(b, buffer, s); // anexa caracteres de uma string em outra, strncat(destino, origem, nr_caracteres)
  
	return 1;
}




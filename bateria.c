#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bateria.h"


#define TAMBUFF 500 //definindo a constante TAMBUFF com valor 500
 

int bateria(char *b, size_t s){
    //buffer que conterá o texto
    char buffer[TAMBUFF]; //setando buffer que contera o texto de tamanho 500
    buffer[0] = '\x0'; // o \x e responsavel pela sequencia de escape unicode (e semelhante ao \u, exceto pela definicao de comprimento de variavel)
    
    //leitor de arquivos
    FILE *arquivo;
    
    char *linha;
    char buff[TAMBUFF];
    buff[0] = '\x0';
    
    //valor da porcentagem da bateria
    float valor; // setando a variavel valor (responsavel pela porcentagem de bateria)
    
    //setando o nivel total de bateria
    arquivo = fopen("/sys/class/power_supply/BAT0/charge_full", "r"); // fopen: abre o arquivo , "r": define que o arquivo de texto e somente para leitura
    if (arquivo == 0)
      arquivo = fopen("/sys/class/power_supply/BAT0/energy_full", "r");
    if (arquivo == 0)
      return -1;
      //O nível da bateria não pôde ser lido
      
    //atribuindo o total da bateria a um float
    while (!feof(arquivo)){
	linha = fgets(buff, TAMBUFF, arquivo);
	if (linha != 0){
	    valor = atoi(linha); // atoi: converte strings em numeros inteiros
	}
    }
    fclose(arquivo); // fechando o arquivo 

    //setando o nivel atual de bateria
    arquivo = fopen("/sys/class/power_supply/BAT0/charge_now", "r");
    if (arquivo == 0)
      arquivo = fopen("/sys/class/power_supply/BAT0/energy_now", "r");
    if (arquivo == 0)
      return -1;
     //O nível da bateria não pôde ser lido    
      
    //atribuindo a carga total ao float
    while (!feof(arquivo)){
	linha = fgets(buff, TAMBUFF, arquivo);
	if (linha != 0){
	    //calculando a porcentagem
	    valor = atoi(linha)/valor*100;
	}
    }
    fclose(arquivo);
    
    
    snprintf(buffer,TAMBUFF, "Porcentagem da bateria: %.0f%%", valor); // a funcao snprintf tem a mesma funcionalidade da funcao sprintf (a saida resultante  respeita o tamanho maximo, indicado iquantidade)
    // apos a execucao dos formatos, sera colocado na variavel indicada por endereçoString
    strncat(b, buffer, s);     

    //retorna sucesso
    return 1;
}

//============================================================================
// Name        : Proj1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string.h>
using namespace std;
#include "vetor.h"

int main() {
	vetor* vec = vetor_novo();

	FILE *wordlist = fopen("wordlist.txt", "r");
	if(!wordlist)
	{
		cout << "erro ao abrir ficheiro com lista de palavras\n";
		return 2;
	}

	cout << "Going through the data please wait..."<< endl;

	char line[100];
	while (fgets(line, sizeof(line), wordlist)) {
		if(line[strlen(line)-1] == '\n')
			line[strlen(line)-1]  = ',';

		char * word;
		word = strtok (line," ,.-;'");
		while (word != NULL)
		{

			if(vetor_pesquisa(vec, word) == -1)
				vetor_insere(vec, word, vec->tamanho);

			word = strtok (NULL," ,.-;'");
		}
	}

	fclose(wordlist);
	vetor_ordena(vec);
	char currentChar = ',';
	for(int i = 0; i < vec->tamanho; i++){

		if(vetor_elemento(vec, i)[0] != currentChar){
			currentChar = vetor_elemento(vec, i)[0];
			cout << currentChar<< endl;

		}
		cout << vetor_elemento(vec, i) << endl;
	}

	vetor_apaga(vec);
	return 0;
}












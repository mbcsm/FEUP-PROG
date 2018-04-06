//============================================================================
// Name        : Proj1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string.h>
#include "vetor.h"
#include <iostream>
#include <fstream>
using namespace std;

int 	numberWords = 0,
		numberNonDuplicates = 0;

int main() {


	vetor* vec = vetor_novo();

	FILE *wordlist = fopen("wordlist.txt", "r");
	if(!wordlist)
	{
		cout << "Error: Could Not Open File\n";
		return 2;
	}

	cout << "Going through the data please wait..."<< endl;

	char line[100];
	while (fgets(line, sizeof(line), wordlist)) {
		if(line[strlen(line)-1] == '\n')
			line[strlen(line)-1]  = ',';

		char * word;
		word = strtok (line," ,.-;'");

		numberWords++;

		while (word != NULL)
		{
			if(vetor_pesquisa(vec, word) == -1){
				vetor_insere(vec, word, vec->tamanho);
				numberNonDuplicates++;
			}


			word = strtok (NULL," ,.-;'");
		}
	}

	fclose(wordlist);

	cout << endl << "Sorting Words . . . " << endl;
	vetor_ordena(vec);
	char currentChar = ',';
	int totalLetter = 0;
	for(int i = 0; i < vec->tamanho; i++){

		totalLetter++;
		if(vetor_elemento(vec, i)[0] != currentChar){
			currentChar = vetor_elemento(vec, i)[0];
			cout << endl << vetor_elemento(vec, i) << endl;
			totalLetter = 0;

		}else if(totalLetter % 100 == 0)
				cout << ".";

		if(totalLetter % 1000 == 0 && totalLetter != 0)
						cout << endl;
	}

	cout << endl << endl << "Number Of simple Words: " << numberWords << endl;
	cout << endl << "Number Of Non Duplicate Words: " << numberNonDuplicates << endl;

	cout << endl << "Saving to File Vec.txt..." << endl;
	if(vetor_guarda_ficheiro(vec, "vec.txt") == 0)
		cout << endl << "Save Successful" << endl;


	vetor_apaga(vec);
	return 0;
}












#include "Dictionary.h"

Dictionary::Dictionary() 
{
	wordlist = {};
}

vector<string> Dictionary::getWordFromFile(string filename)
{
	ifstream dicionario;
	dicionario.open(filename);
	string linha;
	vector<string> texto;

	if (dicionario.fail())
	{
		cerr << "Inexistent file \n";
		exit(1);
	}


	while (!dicionario.eof())
	{
		getline(dicionario, linha);
		if (linha.size() == 0)
		{
			continue;
		}
		else if (!isalpha(linha.at(0)))
		{
			continue;
		}
		else
		{
			stringstream linestream(linha);
			string Word;
			string data;
			linestream >> Word;
			Word.erase(Word.size() - 1, 1);
			getline(linestream, data, ':');  // read up-to the first : (discards :)
			texto.push_back(Word);
			wordlist.push_back(Word);

		}

	}
	dicionario.close();
	texto.erase(unique(texto.begin(), texto.end()), texto.end());
	return texto;
}

bool Dictionary::FoundWord(string palavra)
{
	for (unsigned int i = 0; i < wordlist.size(); i++)
	{
		if (palavra == wordlist.at(i))
			return true;
		else continue;
	}
	return false;
}
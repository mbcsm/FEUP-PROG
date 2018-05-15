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
		if (palavra == wordlist.at(i) || palavra == "X")
			return true;
		else continue;
	}
	return false;
}


string Dictionary::showSynonym(string palavra)
{
	transform(palavra.begin(), palavra.end(), palavra.begin(), ::tolower);
	transform(palavra.begin(), palavra.begin()+1, palavra.begin(), ::toupper);
	string synonymWord;
	if (FoundWord(palavra) == false)
	{
		cout << "The word isn´t in the dictionay ";
		return 0;
	}

	ifstream dicionario;
	dicionario.open("dicionario.txt");
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
			string data,data2;
			

			linestream >> Word;

			Word.erase(Word.size() - 1, 1);
			getline(linestream, data, ':');  // read up-to the first : (discards :)
			
			if (Word == palavra)
			{
				stringstream linestream2(linha);
				getline(linestream2, data2, ':');
				linestream2 >> synonymWord;
				synonymWord.erase(synonymWord.size() - 1, 1);
				break;


			}

		}

	}
	dicionario.close();
	texto.erase(unique(texto.begin(), texto.end()), texto.end());
	return synonymWord;
}
		

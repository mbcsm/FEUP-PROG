#include "Board.h"

Board::Board()
{
	xSize = 0;
	ySize = 0;
}

int Board::getxSize()
{
	return xSize;
}

int Board::getySize()
{
	return ySize;
}

vector<vector<string>> Board::getwordVec()
{
	vector<vector<string>> words;
	for (unsigned int i = 0; i < wordVec.size(); i++)
	{
		vector<string> inf;
		inf.push_back(wordVec.at(i).getWord());
		inf.push_back(to_string(wordVec.at(i).getX()));
		inf.push_back(to_string(wordVec.at(i).getY()));
		words.push_back(inf);
	}
	return words;
}

Board::Board(int xSize, int ySize)
{
	this->xSize = xSize;
	this->ySize = ySize;
}

bool Board::operator== (Board b)
{
	vector<vector<string>> words2 = b.getwordVec();
	vector<vector<string>> words;
	for (unsigned int i = 0; i < wordVec.size(); i++)
	{
		vector<string> inf;
		inf.push_back(wordVec.at(i).getWord());
		inf.push_back(to_string(wordVec.at(i).getX()));
		inf.push_back(to_string(wordVec.at(i).getY()));
		words.push_back(inf);
	}
	sort(words.begin(), words.end());
	sort(words2.begin(), words2.end());
	return words == words2;
}
void Board::DrawBoard()
{

	char** BoardArray = CreateBoardMatrix();

	cout << " ";
	int asciiValue = 97;
	for (int i = 0; i < xSize; i++) {

		cout << " " << char(asciiValue);
		asciiValue++;
	}

	cout << endl;
	asciiValue = 65;
	for (int i = 0; i < ySize; i++) {
		cout << char(asciiValue);
		asciiValue++;
		for (int j = 0; j < xSize; j++) {
			cout << " " << BoardArray[i][j]; //TODO: Replace with array of the board
		}
		cout << endl;
	}

}



void Board::InsertWord(int x, int y, char Direction, string word, bool showWords)
{
	transform(word.begin(), word.end(), word.begin(), ::tolower);
	transform(word.begin(), word.begin()+1, word.begin(), ::toupper);
	int horientation = -1;
	if (Direction == 'V' || Direction == 'v')
		horientation = 0;
	else if (Direction == 'H' || Direction == 'h')
		horientation = 1;
	else
	{
		cout << " The direction is incorrect! " << endl;
		return;
	}


	Dictionary a;
	a.getWordFromFile("dicionario.txt");
	if (a.FoundWord(word) == false) {
		cout << " The word isn't in the dictionary" << endl;
		return;
	}
	if (WordExistsInBoard(word) == 1) {
		cout << " Word Already Played" << endl;
		return;
	}
	if (WordFits(x, y, horientation, word) == 1) {
		cout << " Word Doesn't Fit" << endl;
		return;
	}

	if (WordMatchesWithOtherLetters(x, y, horientation, word) == 1) {
		cout << " Word Doesn't Match With Other Letters" << endl;
		return;
	}
	for (auto & c : word) c = toupper(c);
	Word newWord = Word(wordVec.size(), x, y, horientation, word, showWords);
	wordVec.push_back(newWord);


}


int Board::WordExistsInBoard(string word) {

	for (std::vector<int>::size_type i = 0; i != wordVec.size(); i++)
		if (wordVec[i].getWord() == word && wordVec[i].getWord() != "X" && !wordVec[i].isHidden())
			return 1;

	return 0;
}

int Board::WordFits(int x, int y, int horientation, string word) {
	if (x >= xSize || y >= ySize)
		return 1;

	if (horientation == 0)
		if (x + word.size() > xSize)
			return 1;
	if (horientation == 1)
		if (y + word.size() > ySize)
			return 1;

	return 0;
}


int Board::WordMatchesWithOtherLetters(int x, int y, int horientation, string word) {
	char** BoardArray = CreateBoardMatrix();

	for (unsigned int i = 0; i < word.size(); i++)
	{
		char a = word.at(i);
		if (horientation == 0 && (BoardArray[x + i][y] != '*' && BoardArray[x + i][y] != toupper(a)))
			return 1;
		else if (horientation == 1 && (BoardArray[x][y + i] != '*' && BoardArray[x][y + i] != toupper(a)))
			return 1;


	}

	return 0;
}

int Board::WordBlackCells(char** BoardArray) {
	for (std::vector<int>::size_type i = 0; i != wordVec.size(); i++) {
		if (wordVec[i].getHorientation() == 0) {
			if (BoardArray[wordVec[i].getX()][wordVec[i].getY() - 1] == '*')
				return 0;
		}
		else if (wordVec[i].getHorientation() == 1) {
			for (unsigned int j = 0; j < wordVec[i].getWord().size(); j++)
			{
				char a = wordVec[i].getWord().at(j);
				BoardArray[wordVec[i].getX()][j + wordVec[i].getY()] = a;
			}
		}
	}

	return 0;
}


char** Board::CreateBoardMatrix() {

	char** BoardArray = 0;
	BoardArray = new char*[xSize];

	for (int h = 0; h < ySize; h++)
	{
		BoardArray[h] = new char[ySize];

		for (int w = 0; w < ySize; w++)
		{
			BoardArray[h][w] = '*';
		}
	}

	for (std::vector<int>::size_type i = 0; i != wordVec.size(); i++) {
		if (wordVec[i].getHorientation() == 0) {
			if(!wordVec[i].isHidden())
			for (unsigned int j = 0; j < wordVec[i].getWord().size(); j++)
			{
				char a = wordVec[i].getWord().at(j);
				if(!wordVec[i].isHidden())
					BoardArray[j + wordVec[i].getX()][wordVec[i].getY()] = a;
			}

			if (wordVec[i].getX() != 0)
				if (BoardArray[wordVec[i].getX() - 1][wordVec[i].getY()] == '*')
					BoardArray[wordVec[i].getX() - 1][wordVec[i].getY()] = '#';
			if (wordVec[i].getX() + wordVec[i].getWord().size() != ySize)
				if (BoardArray[wordVec[i].getX() + wordVec[i].getWord().size()][wordVec[i].getY()] == '*')
					BoardArray[wordVec[i].getX() + wordVec[i].getWord().size()][wordVec[i].getY()] = '#';

		}
		else if (wordVec[i].getHorientation() == 1) {
			if(!wordVec[i].isHidden())
			for (unsigned int j = 0; j < wordVec[i].getWord().size(); j++)
			{
				char a = wordVec[i].getWord().at(j);
				BoardArray[wordVec[i].getX()][j + wordVec[i].getY()] = a;
			}

			if (wordVec[i].getY() != 0)
				if (BoardArray[wordVec[i].getX()][wordVec[i].getY() - 1] == '*')
					BoardArray[wordVec[i].getX()][wordVec[i].getY() - 1] = '#';
			if (wordVec[i].getY() + wordVec[i].getWord().size() != xSize)
				if (BoardArray[wordVec[i].getX()][wordVec[i].getY() + wordVec[i].getWord().size()] == '*')
					BoardArray[wordVec[i].getX()][wordVec[i].getY() + wordVec[i].getWord().size()] = '#';

		}
	}

	return BoardArray;
}


int Board::CheckEndGame() {
	char** BoardArray = CreateBoardMatrix();
	for (int h = 0; h < xSize; h++)
	{
		for (int w = 0; w < ySize; w++)
		{
			if (BoardArray[h][w] == '*')
				return 1;
		}
	}

	endGame = 1;
	return 0;
}


int Board::getEndGame() {
	return endGame;
}




vector<string> Board::WordsThatFit(int x, int y, int horientation)
{
	Dictionary a;

	vector<string> words = a.getWordFromFile("dicionario.txt");
	vector<string> wordsViable;
	for (unsigned int i = 0; i < words.size(); i++)
	{

		if (WordExistsInBoard(words.at(i)) == 1)
			continue;

		else if (WordFits(x, y, horientation, words.at(i)) == 1)
			continue;

		else if (WordMatchesWithOtherLetters(x, y, horientation, words.at(i)) == 1)
			continue;

		wordsViable.push_back(words.at(i));

	}
	return wordsViable;
}


void Board::SaveToFile(string outputfile, vector<string> position)
{
	ofstream file;
	file.open(outputfile);

	file << xSize << ";" << ySize << endl;
	for (unsigned int i = 0; i < wordVec.size(); i++)
		file << position.at(i) << ";" << wordVec.at(i).getWord() << endl;
		
	

}

void Board::removeWord(string word)
{
	transform(word.begin(), word.end(), word.begin(), ::toupper);
	for (unsigned int i = 0; i < wordVec.size(); i++)
		if (word == wordVec.at(i).getWord() && !wordVec.at(i).isHidden())
			wordVec.erase(wordVec.begin()+i);
}

void Board::loadBoard(string filename, bool showWords)
{
	playerMode = !showWords;
	ifstream file;
	file.open(filename);
	if (!file.is_open())
	{
		cout << " The file could not be open. ";
		return;
	}
	int id = 0;
	string line;
	int linecounter = 0, xSiz = 0, ySiz = 0;
	string posi = ""; string wordname = ""; string position = "";

	
	while (!file.eof())
	{
		getline(file, line);

		string data;
		id++;
		if (line.size() == 0)
			continue;
		if (linecounter == 0)
		{
			stringstream linestream(line);
			linestream >> xSiz;
			getline(linestream, data, ';');  // read up-to the first ; (discard ;).
			linestream >> ySiz;
		
			xSize = xSiz;
			ySize = ySiz;
		}
		else {
			stringstream linestream(line);

			linestream >> posi;
			
			string::size_type pos = posi.find(';');
			if (posi.npos != pos) {
				wordname = posi.substr(pos + 1);
				 position = posi.substr(0, pos);
			}
			int x = position.at(0)-65;
			int y = position.at(1)-97;
			char horientation = position.at(2);


	
			InsertWord(x,y, horientation, wordname, showWords);
		}
		linecounter++;
	} 

}

void Board::showClues()
{
	cout << "________________ Clues Table ________________\n";
	Dictionary a;
	char ori;
	vector<int> horizontal;
	vector<int> vertical;
	a.getWordFromFile("dicionario.txt");
	cout << "\n\n";
	for (unsigned int i = 0; i < wordVec.size(); i++)
	{
		if (wordVec.at(i).getHorientation() == 0) {
			ori = 'V';
			vertical.push_back(i);
		}
		else if (wordVec.at(i).getHorientation() == 1) {
			ori = 'H';
			horizontal.push_back(i);
		}	
	}
	cout << "\n Horizontal:\n\n";
	if (horizontal.size() > 0) {
		for (unsigned int i = 0; i < wordVec.size(); i++)
		{
			if (i == horizontal.at(i))
				if(wordVec.at(i).isHidden())
					cout << " Synonym: " << a.showSynonym(wordVec.at(i).getWord()) << "   Xpos: " << char(wordVec.at(i).getX() + 65) << "   Ypos: " << char(wordVec.at(i).getY() + 97) << endl;
			else continue;
		}
	}
	cout << "\n Vertical: \n\n";
	if (vertical.size() > 0) {
		for (unsigned int i = 0; i < wordVec.size(); i++)
		{

			if (i == vertical.at(i))
				if(wordVec.at(i).isHidden())
					cout << " Synonym: " << a.showSynonym(wordVec.at(i).getWord()) << "   Xpos: " << char(wordVec.at(i).getX() + 65) << "   Ypos: " << char(wordVec.at(i).getY() + 97) << endl;
			else continue;
		}
	}

}

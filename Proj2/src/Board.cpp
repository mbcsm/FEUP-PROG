#include "Board.h"

Board::Board()
{
	xSize = 0;
	ySize = 0;
}

Board::Board(int xSize, int ySize)
{
	this->xSize = xSize;
	this->ySize = ySize;
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



void Board::InsertWord(int x, int y, char Direction, string word) 
{
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
	if(WordExistsInBoard(word) == 1){
		cout << " Word Already Played" << endl;
		return;
	}
	if(WordFits(x, y, horientation, word) == 1){
		cout << " Word Doesn't Fit" << endl;
		return;
	}

	if(WordMatchesWithOtherLetters(x, y, horientation, word) == 1){
		cout << " Word Doesn't Match With Other Letters" << endl;
		return;
	}
	for (auto & c: word) c = toupper(c);
	Word newWord = Word(wordVec.size(), x, y, horientation, word);
	wordVec.push_back(newWord);

}


int Board::WordExistsInBoard(string word){
	for(std::vector<int>::size_type i = 0; i != wordVec.size(); i++)
		if(wordVec[i].getWord() == word)
			return 1;

	return 0;
}

int Board::WordFits(int x, int y, int horientation, string word){
	if(x >= xSize || y >= ySize)
		return 1;

	if(horientation == 0)
		if(x + word.size() > xSize)
			return 1;
	if(horientation == 1)
		if(y + word.size() > ySize)
			return 1;

	return 0;
}


int Board::WordMatchesWithOtherLetters(int x, int y, int horientation, string word){
	char** BoardArray = CreateBoardMatrix();

	for (unsigned int i = 0; i < word.size(); i++)
	{
		char a = word.at(i);
		if(horientation == 0 && (BoardArray[x + i][y] != '*' && BoardArray[x + i][y] != toupper(a)))
			return 1;
		else if(horientation == 1 && (BoardArray[x][y + i] != '*' && BoardArray[x][y + i] != toupper(a)))
			return 1;


	}

	return 0;
}


char** Board::CreateBoardMatrix(){

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

	for(std::vector<int>::size_type i = 0; i != wordVec.size(); i++){
		if (wordVec[i].getHorientation() == 0){
			for (unsigned int j = 0; j < wordVec[i].getWord().size(); j++)
			{
				char a = wordVec[i].getWord().at(j);
				BoardArray[j + wordVec[i].getX()][wordVec[i].getY()] = a;
			}
		}
		else if (wordVec[i].getHorientation() == 1){
			for (unsigned int j = 0; j < wordVec[i].getWord().size(); j++)
			{
				char a = wordVec[i].getWord().at(j);
				BoardArray[wordVec[i].getX()][j + wordVec[i].getY()] = a;
			}
		}
	}

   return BoardArray;
 }


int Board::CheckEndGame(char** BoardArray){

	for (int h = 0; h < ySize; h++)
	{
		for (int w = 0; w < ySize; w++)
		{
			if(BoardArray[h][w] == '*')
				return 1;
		}
	}

	endGame = 1;
	return 0;
 }


int Board::getEndGame(){
   return endGame;
 }















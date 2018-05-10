#include <iostream>
#include "Proj.h"
#include "Board.h"
#include "Dictionary.h"
using namespace std;

int main()
{
	string filename;
	cout << "Insert the file name (dicionario.txt) : ";
	cin >> filename;

	int lines, columns;
	cout << "board size (lines columns) ? ";
	cin >> lines;
	cin >> columns;

	Board a = Board(lines, columns);
	a.DrawBoard();

	while(a.getEndGame() == 0){
		int lineInput, columnInput, orientationInput;
		string untreatedInput, word;
		cout << "Position (LCD / CTR-Z = Stop) ? ";
		cin >> untreatedInput;

		cout << "Word (- = remove / ? = help) ? ";
		cin >> word;

		lineInput = (int)untreatedInput[0] - 65;
		columnInput = (int)untreatedInput[1] - 97;

		a.InsertWord(lineInput,columnInput,untreatedInput[2], word);
		a.DrawBoard();
	}

	cout << "VICTORY - Board Filled";
	system("pause");
	return 0;
}

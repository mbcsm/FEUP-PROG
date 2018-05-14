#include <iostream>
#include "Proj.h"
#include "Board.h"
#include "Dictionary.h"
using namespace std;
int Create_Puzzle();

int main()
{
	
	_tsetlocale(LC_ALL, _T("portuguese")); //correcta utilização dos acentos 
	int op;

	do
	{
		system("cls");

		cout << "\n\n   WORD GAMES - Menu: \n\n\n" << endl;

		cout << "   1- Create a Puzzle \n" << endl;
		cout << "   2- Load a Puzzle \n\n" << endl;

		cout << "   0- Exit \n\n\n" << endl;
		cout << "   Select an option: "; cin >> op;
		switch (op)
		{
		case 0:
			exit(0);
			break;
		case 1:
			Create_Puzzle();
			break;
		case 2:
			/////////////////////////
			break;
		default:

			main();
			break;
		}

	} while (op != 0);

	return 0;
}






int Create_Puzzle()
{
	system("cls");
	string filename;
	cout << "Insert the file name (dicionario.txt) : ";
	cin >> filename;

	int lines, columns;
	cout << "board size (lines columns) ? ";
	cin >> lines;
	cin >> columns;

	Board a = Board(lines, columns);
	a.DrawBoard();

	while (a.getEndGame() == 0) {
		int lineInput, columnInput, orientationInput;
		string untreatedInput, word;
		cout << "Position (LCD / CTR-Z = Stop) ? ";
		cin >> untreatedInput;

		if (untreatedInput == "Z")
		{
			string outputfile;
			char option;
			cout << "Do you want to save the crossword ? (y/n) ";
			cin >> option;
			if (option == 'y' || option == 'Y')
			{
				cout << "Enter file name: "; cin >> outputfile;
				a.SaveToFile(outputfile);
				return 0;
			}
			else if (option == 'n' || option == 'N')
			{
				cout << " Ok. Bye\n";
				system("pause");
				return 0;
			}
			else
				continue;
		}


		lineInput = (int)untreatedInput[0] - 65;
		columnInput = (int)untreatedInput[1] - 97;

		int horientation = -1;

		if (untreatedInput[2] == 'V' || untreatedInput[2] == 'v')
				horientation = 0;
		else if (untreatedInput[2] == 'H' || untreatedInput[2] == 'h')
			horientation = 1;
		else{
			cout << "Invalid Direction" << endl;
			continue;
		}

		if(islower(untreatedInput.at(0)) || isupper(untreatedInput.at(1))){
			cout << "Invalid Position, Make sure the (Line) is Uppercase and the (Column) Lowercase" << endl;
			continue;
		}
		if(lineInput > lines || columnInput > columns){
			cout << "Invalid Position" << endl;
			continue;
		}

		cout << "Word (- = remove / ? = help) ? ";
		cin >> word;


		if (word == "?")
		{
			vector<string> words = a.WordsThatFit(lineInput, columnInput, horientation);
			for (unsigned int i = 0; i < words.size(); i++)
				cout << words.at(i) << endl;
		
		}
		else if (word.at(0) == '-')
		{
			word.erase(word.begin());
			a.removeWord(word);
			a.DrawBoard();
		}

		else
		{
			a.InsertWord(lineInput, columnInput, horientation, word);
			a.DrawBoard();
		}


		a.CheckEndGame();
		if (a.getEndGame() == 1)
		{
			cout << "VICTORY - Board Filled\n";
			string outputfile;
			char option;
			cout << "Do you want to save the crossword ? (y/n) ";
			cin >> option;
			if (option == 'y' || option == 'Y')
			{
				cout << "Enter file name: "; cin >> outputfile;
				a.SaveToFile(outputfile);
				return 0;
			}
			else if (option == 'n' || option == 'N')
			{
				cout << " Ok. Bye\n";
				system("pause");
				return 0;
			}
			else
				continue;
		}
	}



	system("pause");
	return 0;
}


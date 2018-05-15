#include <iostream>
#include "Proj.h"
#include "Board.h"
#include "Dictionary.h"
#include "Player.h"
using namespace std;
int Create_Puzzle();
int Resume_Puzzle();
int Load_Puzzle();
int Load_Player();
int main()
{
	
	_tsetlocale(LC_ALL, _T("portuguese")); //correcta utilização dos acentos 
	int op;

	do
	{
		system("cls");

		cout << "\n\n   WORD GAMES - Menu: \n\n\n" << endl;

		cout << "   1- Create a Puzzle \n" << endl;
		cout << "   2- Resume a Puzzle \n" << endl;
		cout << "   3- Load Puzzle \n\n" << endl;
		cout << "   4- Player \n\n" << endl;

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
			Resume_Puzzle();
			break;
		case 3:
			Load_Puzzle();
			break;
		case 4:
			Load_Player();
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
	vector<string> guardpositions;
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
		guardpositions.push_back(untreatedInput);

		if (untreatedInput == "Z")
		{
			string outputfile;
			char option;
			cout << "Do you want to save the crossword ? (y/n) ";
			cin >> option;
			if (option == 'y' || option == 'Y')
			{
				cout << "Enter file name: "; cin >> outputfile;
				a.SaveToFile(outputfile,guardpositions);
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
			a.InsertWord(lineInput, columnInput, untreatedInput[2], word, false);
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
				a.SaveToFile(outputfile, guardpositions);
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

int Resume_Puzzle()
{
	system("cls");
	string filename, boardname;
	cout << "Insert the file name (dicionario.txt) : ";
	cin >> filename;
	cout << "Insert the file name where the board was guarded : ";
	cin >> boardname;
	Board a;
	a.loadBoard(boardname, false);

	a.DrawBoard();
	vector<string> guardpositions;

	a.CheckEndGame();

	if (a.getEndGame() == 1) {
		cout << " The board is already completed. \n";
		system("pause");
		return 0;
	}

	while (a.getEndGame() == 0) {
		int lineInput, columnInput, orientationInput;
		string untreatedInput, word;
		cout << "Position (LCD / CTR-Z = Stop) ? ";
		cin >> untreatedInput;
		guardpositions.push_back(untreatedInput);

		if (untreatedInput == "Z")
		{
			string outputfile;
			char option;
			cout << "Do you want to save the crossword ? (y/n) ";
			cin >> option;
			if (option == 'y' || option == 'Y')
			{
				cout << "Enter file name: "; cin >> outputfile;
				a.SaveToFile(outputfile, guardpositions);
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


		cout << "Word (- = remove / ? = help) ? ";
		cin >> word;

		lineInput = (int)untreatedInput[0] - 65;
		columnInput = (int)untreatedInput[1] - 97;



		if (word == "?")
		{
			vector<string> words = a.WordsThatFit(lineInput, columnInput, untreatedInput[2]);
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
			a.InsertWord(lineInput, columnInput, untreatedInput[2], word, false);
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
				a.SaveToFile(outputfile, guardpositions);
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

int Load_Puzzle()
{
	system("cls");
	string filename, boardname;
	cout << "Insert the file name (dicionario.txt) : ";
	cin >> filename;
	cout << "Insert the file name where the board was guarded : ";
	cin >> boardname;
	Board b;
	b.loadBoard(boardname, false);
	b.CheckEndGame();
	int lines = b.getxSize();
	int columns = b.getySize();
	if (b.getEndGame() == 0) {
		cout << " The board you loaded isn't completed. \n";
		system("pause");
		return 0;
	}
	b.showClues();

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
			cout << "Do you want to give up ? (y/n) ";
			cin >> option;
			if (option == 'y' || option == 'Y')
			{
				cout << " Ok. Bye\n";
				system("pause");
				return 0;
			}
			else if (option == 'n' || option == 'N')
			{
				cout << "\n Let´s get back on track \n";
				continue;
			}
			else
				continue;
		}


		cout << "Word (- = remove / ? = help) ? ";
		cin >> word;

		lineInput = (int)untreatedInput[0] - 65;
		columnInput = (int)untreatedInput[1] - 97;



		if (word == "?")
		{
			vector<string> words = a.WordsThatFit(lineInput, columnInput, untreatedInput[2]);
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
			a.InsertWord(lineInput, columnInput, untreatedInput[2], word, false);
			a.DrawBoard();
		}


		a.CheckEndGame();
		if (a.getEndGame() == 1 && a == b)
		{
			cout << "VICTORY - Board Filled correctely\n";
			string outputfile;
			char option;
			cout << "Do you want to save your information? (y/n) ";
			cin >> option;
			if (option == 'y' || option == 'Y')
			{
				cout << "Enter file name: "; cin >> outputfile;

				return 0;
			}
			else if (option == 'n' || option == 'N')
			{
				cout << " Ok. Bye\n";
				system("pause");
				return 0;
			}
			else
			{
				system("pause");
				return 0;
			};
		}
		else if (a.getEndGame() == 1 ) {
			cout << " The answer was incorrect.Goodbye \n";
		}
	}

	system("pause");
	return 0;
}


int Load_Player(){

	system("cls");
	string filename, boardname;
	cout << "Insert the file name (dicionario.txt) : ";
	cin >> filename;
	cout << "Insert the file name where the board was guarded : ";
	cin >> boardname;
	Board a;
	a.loadBoard(boardname, true);

	a.showClues();

	a.DrawBoard();
	vector<string> guardpositions;


	while (a.getEndGame() == 0) {
		int lineInput, columnInput, orientationInput;
		string untreatedInput, word;
		cout << "Position (LCD / CTR-Z = Stop) ? ";
		cin >> untreatedInput;
		guardpositions.push_back(untreatedInput);

		if (untreatedInput == "Z")
		{
			string outputfile;
			char option;
			cout << "Do you want to save the crossword ? (y/n) ";
			cin >> option;
			if (option == 'y' || option == 'Y')
			{
				cout << "Enter file name: "; cin >> outputfile;
				a.SaveToFile(outputfile, guardpositions);
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
		if(lineInput > a.getxSize() || columnInput > a.getySize()){
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
			a.InsertWord(lineInput, columnInput, untreatedInput[2], word, false);
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
				a.SaveToFile(outputfile, guardpositions);
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

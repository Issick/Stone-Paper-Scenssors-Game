#include <iostream>
#include <time.h>
using namespace std;

enum enGameChoices { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundResults
{
	enGameChoices PlayerChoice;
	enGameChoices ComputerChoice;
	enWinner Winner;
	string WinnerName = "";
};

struct stGameResults
{
	stRoundResults Round[10];
	short GameRounds = 1;
	short PlayerWinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner Winner;
	string WinnerName = "";

};

short ReadRoundsNumber()
{
	short Number = 1;

	do
	{
		cout << "How many rounds do you want to play? 1-10?\n";
		cin >> Number;
	}

	while (Number < 1 || Number>10);

	return Number;
}

enGameChoices GetPlayerChoice(short RoundOrder)
{
	short Choice = 1;

	cout << "Round [" << RoundOrder + 1 << "] begains :\n\n";
	cout << "Your choice : [1] Stone, [2] Paper, [3] Scissors ?";
	cin >> Choice;
	cout << endl;

	return enGameChoices(Choice);
}

int RandomNumber(int From, int To)
{
	int randNum = rand() % (To - From + 1) + From;

	return randNum;
}

enGameChoices ComputerChoiceMake()
{
	return enGameChoices(RandomNumber(1, 3));
}

enWinner GetWinner(enGameChoices PlayerChoice, enGameChoices ComputerChoice)
{
	if (PlayerChoice == ComputerChoice)
		return enWinner::Draw;

	else
	{
		switch (PlayerChoice)
		{
		case enGameChoices::Stone:
			if (ComputerChoice == enGameChoices::Paper)
				return enWinner::Computer;
			break;

		case enGameChoices::Paper:
			if (ComputerChoice == enGameChoices::Scissors)
				return enWinner::Computer;
			break;

		case enGameChoices::Scissors:
			if (ComputerChoice == enGameChoices::Stone)
				return enWinner::Computer;
			break;
		}

		return enWinner::Player;
	}
}

string GetWinnerName(enWinner Winner)
{
	string WinnerName[3] = { "Player","Computer","No one" };

	return WinnerName[Winner - 1];
}

string GetChoiceText(enGameChoices GameChoice)
{
	string TextChoice[3] = { "Stone","Paper","Scissors" };

	return TextChoice[GameChoice - 1];
}

void PrintRoundResult(stRoundResults RoundResult, short RoundOrder)
{
	cout << "-----------Round [" << RoundOrder + 1 << "]---------------\n\n";
	cout << "Player Choice    : " << GetChoiceText(RoundResult.PlayerChoice) << endl;
	cout << "Computer Choice  : " << GetChoiceText(RoundResult.ComputerChoice) << endl;
	cout << "Round Winner     : [" << RoundResult.WinnerName << "]" << endl;
	cout << "-----------------------------------\n\n";
}

void SumWins(stGameResults& GameResults, enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player:
		GameResults.PlayerWinTimes++;
		break;

	case enWinner::Computer:
		GameResults.ComputerWinTimes++;
		break;

	case enWinner::Draw:
		GameResults.DrawTimes++;
		break;
	}
}


stGameResults PlayGame(short RoundsNumber)
{
	stGameResults GameResults;
	GameResults.GameRounds = RoundsNumber;

	for (short RoundOrder = 0; RoundOrder < RoundsNumber; RoundOrder++)
	{
		GameResults.Round[RoundOrder].PlayerChoice = GetPlayerChoice(RoundOrder);
		GameResults.Round[RoundOrder].ComputerChoice = ComputerChoiceMake();
		GameResults.Round[RoundOrder].Winner = GetWinner(GameResults.Round[RoundOrder].PlayerChoice, GameResults.Round[RoundOrder].ComputerChoice);
		GameResults.Round[RoundOrder].WinnerName = GetWinnerName(GameResults.Round[RoundOrder].Winner);

		PrintRoundResult(GameResults.Round[RoundOrder], RoundOrder);
		SumWins(GameResults, GameResults.Round[RoundOrder].Winner);
	}

	if (GameResults.PlayerWinTimes == GameResults.ComputerWinTimes)
		GameResults.Winner = enWinner::Draw;
	else if (GameResults.PlayerWinTimes > GameResults.ComputerWinTimes)
		GameResults.Winner = enWinner::Player;
	else
		GameResults.Winner = enWinner::Computer;

	GameResults.WinnerName = GetWinnerName(GameResults.Winner);

	return GameResults;
}

string Tabs(short Number)
{
	string t = "";

	for (int i = 0; i < Number; i++)
	{
		t += "\t";
	}

	return t;
}

void PrintGameResults(stGameResults GameResults)
{
	cout << Tabs(2) << "__________________________________________________________\n\n";
	cout << Tabs(2) << "                 +++ G a m e  O v e r +++\n";
	cout << Tabs(2) << "__________________________________________________________\n\n";
	cout << Tabs(2) << "_____________________ [Game Results ]_____________________\n\n";
	cout << Tabs(2) << "Game Rounds        : " << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player1 won times  : " << GameResults.PlayerWinTimes << endl;
	cout << Tabs(2) << "Computer won times : " << GameResults.ComputerWinTimes << endl;
	cout << Tabs(2) << "Draw times         : " << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner       : " << GameResults.WinnerName << endl;
	cout << Tabs(2) << "___________________________________________________________\n";
}

void StartGame()
{
	char PlayAgain = 'y';

	do
	{
		stGameResults GameResults = PlayGame(ReadRoundsNumber());
		PrintGameResults(GameResults);

		cout << Tabs(2) << "Do you want to play again? Y/N?";
		cin >> PlayAgain;
	}

	while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}

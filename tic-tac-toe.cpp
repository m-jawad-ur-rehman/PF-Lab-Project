#include <iostream>
#include <ctime>
using namespace std;

void menu();
void drawBoard(char *);
void compMove(char *, char);
void plyrMove(char *, char);
bool isBoardFull(char *);
bool checkWinner(char *, char);

int main()
{
  srand(time(NULL));
  menu();

  char *moves = new char[9]{'1', '2', '3', '4', '5', '6', '7', '8', '9'};
  drawBoard(moves);

  for (int i = 0; i < 9; i++)
  {
    moves[i] = ' ';
  }

  char playerMove = 'X';
  char computerMove = 'O';
  int i = 0;

  do
  {
    plyrMove(moves, playerMove);
    drawBoard(moves);

    if (checkWinner(moves, playerMove))
    {
      cout << "You Won >>>" << endl;
      break;
    }

    compMove(moves, computerMove);
    drawBoard(moves);

    if (checkWinner(moves, computerMove))
    {
      cout << "Computer Won >>>" << endl;
      break;
    }

    i++;
  } while (i < 9);

  return 0;
}

void menu()
{
      cout << endl;
      cout << endl;

    cout << "\t\t==        ==        == == == ==      =       ==        ==       =       == ==\n";
    cout << "\t\t== =    = ==              ==       == ==     ==        ==     == ==     == == ==\n";
    cout << "\t\t==  =  =  ==              ==     ==     ==   ==   ==   ==   ==     ==   ==     ==\n";
    cout << "\t\t==   ==   ==              ==    == == == ==  ==  =  =  ==  == == == ==  ==     ==\n";
    cout << "\t\t==        ==        ==    ==    ==       ==  == =    = ==  ==       ==  == == ==\n";
    cout << "\t\t==        ==        ========    ==       ==  ==        ==  ==       ==  == ==\n";

    cout << endl;
    cout << endl;

    cout << "\t\t========================================================\n";
    cout << "\t\t|-------------------- TIC-TAC-TOE ---------------------|\n";
    cout << "\t\t========================================================\n";

    cout << endl;
    cout << endl;

    cout << "\t =========================================\n";
    cout << "\t|---------------- WELCOME ----------------|\n";
    cout << "\t =========================================\n";

    cout << endl;
}

void drawBoard(char *moves)
{

  cout << "       |       |       " << endl;
  cout << "   " << moves[0] << "   |   " << moves[1] << "   |   " << moves[2] << "   " << endl;
  cout << "_______|_______|______" << endl;
  cout << "       |       |       " << endl;
  cout << "   " << moves[3] << "   |   " << moves[4] << "   |   " << moves[5] << "   " << endl;
  cout << "_______|_______|_______" << endl;
  cout << "       |       |       " << endl;
  cout << "   " << moves[6] << "   |   " << moves[7] << "   |   " << moves[8] << "   " << endl;
  cout << "       |       |       " << endl;
  cout << endl;
}

void compMove(char *moves, char move)
{
  int n = 0;
  do
  {
    n = rand() % 9;
  } while (moves[n] != ' ');
  moves[n] = move;
}

void plyrMove(char *moves, char move)
{
  int n = 0;
  do
  {
    cout << "Enter Any Box Between 1 to 9 => ";
    cin >> n;
    if (n < 1 || n > 9 || moves[n - 1] != ' ')
    {
      cout << "Invalid Move... \n " << endl;
    }
  } while (n < 1 || n > 9 || moves[n - 1] != ' ');

  moves[n - 1] = move;
}

bool isBoardFull(char *moves)
{
  for (int i = 0; i < 9; i++)
  {
    if (moves[i] == ' ')
    {
      return false;
    }
  }
  return true;
}

bool checkWinner(char *moves, char move)
{
  for (int i = 0; i < 9; i += 3)
  {
    if (moves[i] == move && moves[i + 1] == move && moves[i + 2] == move)
    {
      return true;
    }
  }

  for (int i = 0; i < 3; i++)
  {
    if (moves[i] == move && moves[i + 3] == move && moves[i + 6] == move)
    {
      return true;
    }
  }

  if ((moves[0] == move && moves[4] == move && moves[8] == move) ||
      (moves[2] == move && moves[4] == move && moves[6] == move))
  {
    return true;
  }

  return false;
}
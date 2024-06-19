#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

void intro();
void allocateMoves(char **&, int, int);
void deallocateMoves(char **&, int);
void drawBoard(char **);
void setBoard(char **, int, int);
char getPlyrMarker();
void getCompMove(char **, char);
void getPlyrMove(char **, char);
bool isBoardFull(char **, int, int);
bool checkWinner(char **, char, int);
void resetStats(const char *, int, int, int);
void updateStats(const char *, char);
void showStats(const char *);
void p2pGame(char **, int, int, char, const char *);
void p2cGame(char **, int, int, char, const char *);
void menu(char **, char, char, const char *p2pSF = "p2p-Stats", const char *p2cSF = "p2c-Stats");
void ticTacToe();

int main()
{
  srand(time(NULL));
  intro();
  ticTacToe();

  return 0;
}

void intro()
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
  cout << "\t\t\t========================================================\n";
  cout << "\t\t\t|----------------------- WELCOME ----------------------|\n";
  cout << "\t\t\t========================================================\n";
  cout << endl;
  cout << endl;
  cout << "== == ==  ==  == == ==    == == ==    ==     == == ==   == == ==   = == =   == == ==" << endl;
  cout << "   ==     ==  ==             ==     ==  ==   ==            ==     ==    ==  ==      " << endl;
  cout << "   ==     ==  ==             ==    == == ==  ==            ==     ==    ==  == = =  " << endl;
  cout << "   ==     ==  ==             ==    ==    ==  ==            ==     ==    ==  ==      " << endl;
  cout << "   ==     ==  == == ==       ==    ==    ==  == == ==      ==      = == =   == == ==" << endl;
  cout << endl;
  cout << endl;
  cout << endl;
}

void allocateMoves(char **&moves, int rows, int cols)
{
  moves = new char *[rows];

  for (int i = 0; i < rows; i++)
  {
    moves[i] = new char[cols];
  }
}

void deallocateMoves(char **&moves, int rows)
{
  for (int i = 0; i < rows; i++)
  {
    delete[] moves[i];
  }
  delete[] moves;
  moves = nullptr;
}

void drawBoard(char **moves)
{

  cout << "       |       |       " << endl;
  cout << "   " << moves[0][0] << "   |   " << moves[0][1] << "   |   " << moves[0][2] << "   " << endl;
  cout << "_______|_______|______" << endl;
  cout << "       |       |       " << endl;
  cout << "   " << moves[1][0] << "   |   " << moves[1][1] << "   |   " << moves[1][2] << "   " << endl;
  cout << "_______|_______|_______" << endl;
  cout << "       |       |       " << endl;
  cout << "   " << moves[2][0] << "   |   " << moves[2][1] << "   |   " << moves[2][2] << "   " << endl;
  cout << "       |       |       " << endl;
  cout << endl;
}

void setBoard(char **moves, int r, int c)
{
  for (int i = 0; i < r; i++)
  {
    for (int j = 0; j < c; j++)
    {
      moves[i][j] = ' ';
    }
  }
}

char getPlyrMarker()
{
  char marker = '\0';
  do
  {
    cout << "Enter Your Marker Style Either \"X\" or \"O\" => ";
    cin >> marker;
  } while (marker != 'X' && marker != 'O');
  return marker;
}

void getCompMove(char **moves, char move)
{
  int row = 0;
  int col = 0;
  do
  {
    row = rand() % 3;
    col = rand() % 3;
  } while (moves[row][col] != ' ');
  moves[row][col] = move;
}

void getPlyrMove(char **moves, char move)
{
  int row = 0;
  int col = 0;
  do
  {
    cout << "Enter Row No. (1, 2 or 3) => ";
    cin >> row;
    if (row < 1 || row > 3)
    {
      cout << "Invalid Move... Out of Range" << endl;
    }
    else if (moves[row - 1][0] != ' ' && moves[row - 1][1] != ' ' && moves[row - 1][2] != ' ')
    {
      cout << "Invalid Move... This Row is Allocated" << endl;
    }
  } while ((row < 1 || row > 3) || (moves[row - 1][0] != ' ' && moves[row - 1][1] != ' ' && moves[row - 1][2] != ' '));

  do
  {
    cout << "Enter Column No. (1, 2 or 3) => ";
    cin >> col;
    if (col < 1 || col > 3)
    {
      cout << "Invalid Move... Out of Range \n ";
    }
    else if (moves[row - 1][col - 1] != ' ')
    {
      cout << "Invalid Move... \n Location Already Occupied \n " << endl;
    }
  } while ((col < 1 || col > 3) || (moves[row - 1][col - 1] != ' '));

  moves[row - 1][col - 1] = move;
}

bool isBoardFull(char **moves, int r, int c)
{
  for (int i = 0; i < r; i++)
  {
    for (int j = 0; j < c; j++)
    {
      if (moves[i][j] == ' ')
        return false;
    }
  }
  return true;
}

bool checkWinner(char **moves, char move, int s)
{
  for (int i = 0; i < s; i++)
  {
    if ((moves[i][0] == move && moves[i][1] == move && moves[i][2] == move) ||
        (moves[0][i] == move && moves[1][i] == move && moves[2][i] == move))
    {
      return true;
    }
  }

  if ((moves[0][0] == move && moves[1][1] == move && moves[2][2] == move) ||
      (moves[0][2] == move && moves[1][1] == move && moves[2][0] == move))
  {
    return true;
  }

  return false;
}

void resetStats(const char *sF, int p1, int p2, int d)
{
  ofstream out(sF);
  out << p1 << " " << p2 << " " << d;
  out.close();
}

void updateStats(const char *sF, char p1Result)
{
  ifstream in(sF);

  int p1Wins = 0;
  int p2Wins = 0;
  int draws = 0;

  if (in.is_open())
  {
    in >> p1Wins >> p2Wins >> draws;
    if (p1Result == 'W')
    {
      p1Wins++;
    }

    else if (p1Result == 'L')
    {
      p2Wins++;
    }

    else if (p1Result == 'D')
    {
      draws++;
    }
  }
  in.close();

  resetStats(sF, p1Wins, p2Wins, draws);
}

void showStats(const char *sF)
{
  ifstream in(sF);

  int p1Wins = 0;
  int p2Wins = 0;
  int draws = 0;

  if (in.is_open())
  {
    in >> p1Wins >> p2Wins >> draws;
  }
  in.close();

  cout << "\t\t TIC TAC TOE \n " << endl;

  if (sF[2] == 'p')
  {
    cout << "\tPlayer 1 Wins => " << p1Wins << endl;
    cout << "\tPlayer 2 Wins => " << p2Wins << endl;
  }

  else
  {
    cout << "\tYour Wins     => " << p1Wins << endl;
    cout << "\tComputer Wins => " << p2Wins << endl;
  }

  cout << "\tDraws         => " << draws << endl;
  cout << "\n " << endl;
}

void p2pGame(char **moves, int rows, int cols, char play, const char *sF)
{
  do
  {
    setBoard(moves, rows, cols);
    drawBoard(moves);

    cout << "Player 1 => " << endl;
    cout << "\t\t";
    char plyr1Marker = getPlyrMarker();
    char plyr2Marker = plyr1Marker == 'X' ? 'O' : 'X';
    cout << "Player 2 Marker => \"O\"" << endl;

    do
    {
      cout << "Player 1 Move: \n";
      getPlyrMove(moves, plyr1Marker);
      drawBoard(moves);

      if (checkWinner(moves, plyr1Marker, rows))
      {
        cout << "Player 1 Won >>>" << endl;
        updateStats(sF, 'W');
        break;
      }
      if (isBoardFull(moves, rows, cols))
      {
        cout << "This Game is a Draw >>> " << endl;
        updateStats(sF, 'D');
        break;
      }

      cout << "Player 2 Move: \n";
      getPlyrMove(moves, plyr2Marker);
      drawBoard(moves);

      if (checkWinner(moves, plyr2Marker, rows))
      {
        cout << "Player 2 Won >>>" << endl;
        updateStats(sF, 'L');
        break;
      }
      if (isBoardFull(moves, rows, cols))
      {
        cout << "This Game is a Draw >>> " << endl;
        updateStats(sF, 'D');
        break;
      }
    } while (true);

    cout << "Do you Want to Play Again ...\n " << endl;
    cout << "\t=> Enter \"P\" to Play Again" << endl;
    cout << "\t=> Enter \"M\" to Go to Menu" << endl;
    cout << "\t=> Enter \"Q\" to Quit" << endl;
    cin >> play;
  } while (play == 'P' || play == 'p');

  if (play == 'M' || play == 'm')
  {
    menu(moves, rows, cols);
  }
  else
  {
    char reset = '\0';
    cout << "Do you want to Reset Stats (y/n) => ";
    cin >> reset;

    if (reset == 'y')
      resetStats(sF, 0, 0, 0);
  }
}

void p2cGame(char **moves, int rows, int cols, char play, const char *sF)
{
  do
  {
    setBoard(moves, rows, cols);
    drawBoard(moves);

    char plyrMarker = getPlyrMarker();
    char compMarker = plyrMarker == 'X' ? 'O' : 'X';

    do
    {
      cout << "Player Move: \n";
      getPlyrMove(moves, plyrMarker);
      drawBoard(moves);

      if (checkWinner(moves, plyrMarker, rows))
      {
        cout << "You Won >>>" << endl;
        updateStats(sF, 'W');
        break;
      }
      if (isBoardFull(moves, rows, cols))
      {
        cout << "This Game is a Draw >>> " << endl;
        updateStats(sF, 'D');
        break;
      }

      getCompMove(moves, compMarker);
      drawBoard(moves);

      if (checkWinner(moves, compMarker, rows))
      {
        cout << "Computer Won >>>" << endl;
        updateStats(sF, 'L');
        break;
      }
      if (isBoardFull(moves, rows, cols))
      {
        cout << "This Game is a Draw >>> " << endl;
        updateStats(sF, 'D');
        break;
      }
    } while (true);

    cout << "Do you Want to Play Again ...\n " << endl;
    cout << "\t=> Enter \"P\" to Play Again" << endl;
    cout << "\t=> Enter \"M\" to Go to Menu" << endl;
    cout << "\t=> Enter \"Q\" to Quit" << endl;
    cin >> play;
  } while (play == 'P' || play == 'p');

  if (play == 'M' || play == 'm')
  {
    menu(moves, rows, cols);
  }
  else
  {
    char reset = '\0';
    cout << "Do you want to Reset Stats (y/n) => ";
    cin >> reset;

    if (reset == 'y')
      resetStats(sF, 0, 0, 0);
  }
}

void menu(char **moves, char rows, char cols, const char *p2pSF, const char *p2cSF)
{
  char play = '\0';
  char slct = '\0';
  char mode = '\0';

  cout << "1: Game Mode Selection -> Enter \"M\"" << endl;
  cout << "2: Game Stats          -> Enter \"S\"" << endl;
  cout << "3: New Game            -> Enter \"G\"" << endl;
  cout << "\t => ";

  do
  {
    cin >> slct;
    if (slct != 'M' && slct != 'S' && slct != 'G')
    {
      cout << "Invalid Input... Re Enter Your Choice >>>" << endl;
    }
  } while (slct != 'M' && slct != 'S' && slct != 'G');

  switch (slct)
  {
  case 'M':
    cout << "ENTER GAME MODE => " << endl;
    cout << "For Player vs Player   -> Enter \"P\"" << endl;
    cout << "For Player vs Computer -> Enter \"C\"" << endl;
    do
    {
      cin >> mode;
      if (mode != 'P' && mode != 'C')
      {
        cout << "Invalid Input... Re Enter Your Choice >>>" << endl;
      }
    } while (mode != 'P' && mode != 'C');

    switch (mode)
    {
    case 'P':
      p2pGame(moves, rows, cols, play, p2pSF);
      break;
    case 'C':
      p2cGame(moves, rows, cols, play, p2cSF);
      break;
    }
    break;
  case 'S':
    cout << "P2P STATS >>>" << endl;
    showStats(p2pSF);
    cout << "P2C STATS >>>" << endl;
    showStats(p2cSF);
    cout << "\n " << endl;
    menu(moves, rows, cols);
    break;
  case 'G':
    cout << "Creating New P2C Game =>\n " << endl;
    p2cGame(moves, rows, cols, play, p2cSF);
    break;
  }
}

void ticTacToe()
{
  int rows = 3;
  int cols = 3;

  char **moves = nullptr;
  allocateMoves(moves, rows, cols);

  char *p2pStatsFile = new char[10]{"p2p-Stats"};
  resetStats(p2pStatsFile, 0, 0, 0);

  char *p2cStatsFile = new char[10]{"p2c-Stats"};
  resetStats(p2cStatsFile, 0, 0, 0);

  menu(moves, rows, cols);

  deallocateMoves(moves, rows);
  delete[] p2pStatsFile;
  delete[] p2cStatsFile;
}
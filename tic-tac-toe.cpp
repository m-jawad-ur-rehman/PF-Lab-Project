#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

void intro();
void allocateMoves(char **&, int, int);
void drawBoard(char **);
void setBoard(char **, int, int);
char getPlyrMarker();
void getCompMove(char **, char);
void getPlyrMove(char **, char);
bool isBoardFull(char **, int, int);
bool checkWinner(char **, char, int, int);
void createStats(char *, int, int, int);
void updateStats(char *, char);
void showStats(char *);
void p2pGame(char **, int, int, char, char *);
void p2cGame(char **, int, int, char, char *);
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
    cout << "Enter Row No. (Any No. Between 1 to 3) => ";
    cin >> row;
    if (row < 1 || row > 3)
    {
      cout << "Invalid Move... Out of Range" << endl;
    }
    else if (moves[row - 1][0] != ' ' && moves[row - 1][1] != ' ' && moves[row - 1][2] != ' ')
    {
      cout << "Invalid Move... This Row is Allocated" << endl;
    }
  } while (row < 1 || row > 3 || (moves[row - 1][0] != ' ' && moves[row - 1][1] != ' ' && moves[row - 1][0] != ' '));

  do
  {
    cout << "Enter Column No. (Any No. Between 1 to 3) => ";
    cin >> col;
    if (col < 1 || col > 3)
    {
      cout << "Invalid Move... Out of Range \n ";
    }
    else if (moves[row - 1][col - 1] != ' ')
    {
      cout << "Invalid Move... \n Location Already Occupied \n " << endl;
    }
  } while (col < 1 || col > 3 || moves[row - 1][col - 1] != ' ');

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

bool checkWinner(char **moves, char move, int r, int c)
{
  for (int i = 0; i < r; i++)
  {
    if (moves[i][0] == move && moves[i][1] == move && moves[i][2] == move)
    {
      return true;
    }
  }

  for (int i = 0; i < c; i++)
  {
    if (moves[0][i] == move && moves[1][i] == move && moves[2][i] == move)
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

void createStats(char *sF, int p1, int p2, int d)
{
  ofstream out(sF);
  out << p1 << " " << p2 << " " << d;
  out.close();
}

void updateStats(char *sF, char p1Result)
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

  createStats(sF, p1Wins, p2Wins, draws);
}

void showStats(char *sF)
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
}

void p2pGame(char **moves, int rows, int cols, char play, char *sF)
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

      if (checkWinner(moves, plyr1Marker, rows, cols))
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

      if (checkWinner(moves, plyr2Marker, rows, cols))
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

    cout << "Do you Want to Play Again ..." << endl;
    cout << "\t=> Enter \"P\" to Play Again" << endl;
    cout << "\t=> Enter \"Q\" to Quit" << endl;
    cin >> play;

  } while (play != 'Q' && play != 'q');
}

void p2cGame(char **moves, int rows, int cols, char play, char *sF)
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

      if (checkWinner(moves, plyrMarker, rows, cols))
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

      if (checkWinner(moves, compMarker, rows, cols))
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

    cout << "Do you Want to Play Again ..." << endl;
    cout << "\t=> Enter \"P\" to Play Again" << endl;
    cout << "\t=> Enter \"Q\" to Quit" << endl;
    cin >> play;
  } while (play != 'Q' && play != 'q');
}

void ticTacToe()
{
  int rows = 3;
  int cols = 3;
  char play = '\0';

  char **moves = nullptr;
  allocateMoves(moves, rows, cols);

  char *p2pStatsFile = new char[15]{"p2p-Game-Stats"};
  createStats(p2pStatsFile, 0, 0, 0);

  char *p2cStatsFile = new char[15]{"p2c-Game-Stats"};
  createStats(p2cStatsFile, 0, 0, 0);

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
      p2pGame(moves, rows, cols, play, p2pStatsFile);
      break;
    case 'C':
      cout << "Enter GAME DIFFICULTY LEVEL => " << endl;
      cout << "For Easy   -> Enter \"E\"" << endl;
      cout << "For Medium -> Enter \"M\"" << endl;
      cout << "For Hard   -> Enter \"H\"" << endl;
      p2cGame(moves, rows, cols, play, p2cStatsFile);
      break;
    }
    break;
  case 'S':
    cout << "P2P STATS >>>" << endl;
    showStats(p2pStatsFile);
    cout << "P2C STATS >>>" << endl;
    showStats(p2cStatsFile);
    break;
  case 'G':
    cout << "Creating New P2C Game =>\n " << endl;
    p2cGame(moves, rows, cols, play, p2cStatsFile);
    break;
  }
}
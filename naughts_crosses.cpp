// Naughts and Crosses!!!
// plays against a human opponent.


//Include nescicary functions
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <ctime>

//set STL namespace
using namespace std;

//set global constants
const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';

//function prototypes
void instructions();
bool askYesNo(string question);
int askNumber(string question, int high, int low = 0);
char humanPiece();
char opponent(char piece);
void displayBoard(const vector<char>& board);
char winner(const vector<char>& board);
bool isLegal(const vector<char>& board, int move);
int humanMove(const vector<char>& board, char human);
int computerMove(vector<char> board, char computer);
void announceWinner(char winner, char computer, char human);
void game();

int main()
{
    instructions();
    while (!askYesNo("Quit"))
        game();
    return 0; 
}

void game()
{
int move;
const int NUM_SQUARES = 9;
vector<char> board(NUM_SQUARES, EMPTY);

char human = humanPiece();
char computer = opponent(human);
char turn = X;
displayBoard(board);

while (winner(board) == NO_ONE)
{
if (turn == human)
{
move = humanMove(board, human);
board[move] = human;
}
else
{
move = computerMove(board, computer);
board[move] = computer;
}
displayBoard(board);
turn = opponent(turn);
}

/*
for(;;)
{
system("cls");
displayBoard(board);
announceWinner(winner(board), computer, human);
int counter = time();
cout << counter;
cout << "Type 'Quit' to quit.";
cin >> move;
}*/

announceWinner(winner(board), computer, human);
}

void instructions()
{
cout << "Welcome to NAUGHTS AND CROSSES\n";
cout << "Stand by to hear THE INSTRUCTIONS\n\n";

cout << "Make your move by entering a number 1 - 9.\n";
cout << "Positions are illustrated below:\n\n";

cout << " 7 | 8 | 9\n";
cout << " ---------\n";
cout << " 4 | 5 | 6\n";
cout << " ---------\n";
cout << " 1 | 2 | 3\n";

cout << "\n\nBE PRE-PAIIIIIIRED!!\n\n";
}

bool askYesNo(string question = "")
{
char response;
while (response != 'y' && response != 'n'
       && response != '0' && response != '1')
{
cout << question << " (y/n): ";
cin >> response;
}
if (response == 'y' || response == '1')
    return true;
if (response == 'n' || response == '0')
    return false;
}

int askNumber(string question, int high, int low)
{


const int NUM_PAD[] = {7, 8, 9, 4, 5, 6, 1, 2, 3};
int number = low-1;
while (number > high+1 || number < low+1)
{
cout << question << " (" << low+1 << " - " << high+1 << "): ";
cin >> number;
}
return NUM_PAD[number-1];
}

char humanPiece()
{
if (askYesNo("Would you like to go first"))
{
cout << "\nPlayer goes first!! GOOD LUCK!\n";
return X;
} 
else
{
cout << "\nComputer goes first!! GOOD LUCK!\n";
return O;
}
}

char opponent(char piece)
{
if (piece == X)
return O;
else
return X;
}

void displayBoard(const vector<char>& board)
{
cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
cout << "\n\t---------"; 
cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
cout << "\n\t---------"; 
cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
cout << "\n\n";
}

char winner(const vector<char>& board)
{
const int TOTAL_ROWS = 8;
const int WINNING_ROWS[TOTAL_ROWS][3] = { {0, 1, 2},
{3, 4, 5},
/***************/ {6, 7, 8},
/* 0 | 1 | 2 */ 
/* --------- */ {0, 3, 6},
/* 3 | 4 | 5 */ {1, 4, 7},
/* --------- */ {2, 5, 8},
/* 6 | 7 | 8 */
/***************/ {0, 4, 8},
{2, 4, 6} };

// if any winning row has three values that are the same (and not empty)
// then that value (X or O) IS THE WINNER!!!
for (int row = 0; row < TOTAL_ROWS; ++row)
{
if( (board[WINNING_ROWS[row][0]] != EMPTY) &&
(board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) &&
(board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]]) )
{
return board[WINNING_ROWS[row][0]];
}
}

//If it's gotten to here, then no one's won. Either someone's still got
//turns left, or it's a tie. If there's no empty qsuares - it's a tie!
if ( !count(board.begin(), board.end(), EMPTY) )// count counts how many
// EMPTY's there are in the
// entirety of the board.
// if it returns 0 (false)
// then we return a tie
return TIE;
//otherwise, if no one's won, and there are empty spaces, the game is
//still on!!
return NO_ONE ;
}

inline bool isLegal(int move, const vector<char>& board)
{
return (board[move] == EMPTY);
}

int humanMove(const vector<char>& board, char human)
{
int move = askNumber( "Where will you move?", (board.size()-1) ) - 1;
while (!isLegal(move, board))
{
cout << "\nThat square is already occupied. DUMMY!\n";
move = askNumber( "Where will you move?", (board.size()-1) ) - 1;
}
cout << "Righteo!\n";
return move;
}

int computerMove(vector<char> board, char computer)
{
system("cls");

//If computer can win now, do that!
for (int move = 0; move < board.size(); ++move) // for every possible square...
{
if (isLegal(move, board))//check wether the square is empty
{
board[move] = computer; // place the computer piece there
if (winner(board) == computer) // if it wins for the computer
{
return move;
}
//if it doesn't, remove the piece, and try again. 
board[move] = EMPTY;
}
}

//If human can win on next turn, block them!
char human = opponent(computer); //create a human dummy
for (int move = 0; move < board.size(); ++move) // check this all by each position
{
if (isLegal(move, board))//if the square is empty...
{
board[move] = human; // put a human pawn there
if (winner(board) == human) // if the human would win
{
return move;
}
board[move] = EMPTY; // if not, try on the next pos.
}
}

/*
//I can't win now, and the human's not about to win next, so lets pick the
//most desirable square.
const int BEST_MOVES[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};//Middle, corners, others.
for (int i = 0; i < board.size(); ++i)
{
int move = BEST_MOVES[i]; // check by each square, in order.
if(isLegal(move, board))
{
cout << move+1 << endl; // it if's legal, take it!
return move;
}
}

*/ // I don't like that method becase going first and playing 1, 9, 7, 8
// will always win. Too predictable.
srand(time(0));
for (;;)
{
int move = rand()%9;
if(isLegal(move, board))
{
return move; 
}
}
}

void announceWinner(char winner, char computer, char human)
{
if (winner == computer)
cout << winner << "'s won!\nCOMPUTER WINS!\n";
else if (winner == human)
cout << winner << "'s won!\nCongrats, you won!\n";
else
cout << "It's a tie. HURRAY!\n";
} 

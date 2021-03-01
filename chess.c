#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Methods
int translateColumnChar(char);
int translateRowToRealNum(int);
void printWelcomeMessage();
void printChessBoard();
int isPawn(int, char);
int usePawn(int, char, int, char, int);
int readInt();
int promotePawnFirstPlayer();
int promotePawnSecondPlayer();
int isKnight(int, char);
int useKnight(int, char, int, char, int);
int isRook(int, char);
int useRook(int, char, int, char, int);
int isBishop(int, char);
int useBishop(int, char, int, char, int);
int isQueen(int, char);
int useQueen(int, char, int, char, int);
int isKing(int, char);
int useKing(int, char, int, char, int);
void kingIsInCheck();
void userInteraction();

//Global Variables
int chessBoard[8][8] = {
							{-4, -2, -3, -5, -6, -3, -2, -4},
							{-1, -1, -1, -1, -1, -1, -1, -1},
							{0, 0, 0, 0, 0, 0, 0, 0},
							{0, 0, 0, 0, 0, 0, 0, 0},
							{0, 0, 0, 0, 0, 0, 0, 0},
							{0, 0, 0, 0, 0, 0, 0, 0},
							{1, 1, 1, 1, 1, 1, 1, 1},
							{4, 2, 3, 5, 6, 3, 2, 4}
						};
char footer[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
int footerNum[8] =  {0, 1, 2, 3, 4, 5, 6, 7}; //numerical values of footer characters regarding the chessboard coordinates

//Checks if each player had a first turn yet, for purposes of the pawns
int playerOneFirstTurnWasPlayed = 0;
int playerTwoFirstTurnWasPlayed = 0;

int main(){

	userInteraction();

	return 0;
}

void printWelcomeMessage(){
	//Welcome message to user and explaining format of game
	printf("\nWelcome to the Chess Game\n\n");
	printf("The legend: Absolute values of each number means\n");
	printf("0 = Empty\n1 = Pawn\n2 = Knight\n3 = Rook\n4 = Queen\n5 = King\n");

	//Who plays what
	printf("\nPlayer One has the positive numbered pieces\nPlayer Two has the negative nunbered pieces\n\n");

	//Commands
	printf("Commands: \n");
	printf("\t-'mv (currentRow, currentColumn)(newRow, newColumn)' means to move the current piece to a new location\n\t(ie. mv (2/a)(3/a) moves the piece at 2/a to 3/a)\n");
	printf("\t-'cp (currentRow, currentColumn)(newRow, newColumn)' means to capture the opponent's piece in the new location\n\t(ie. cp (3/a)(4/b) allows you to capture the piece at 4/b)\n");
	printf("\t-'show' means to display the contents of the chess board\n\n");
}

void printChessBoard(){
	//Printing out chess board
	int i;
	int k;
	int j;
	printf("  ---------------------------------\n");
	for(i = 0, k = 8; k > 0; i++, k--){
		printf("%d |", k);
		for(j = 0; j < 8; j++){
			if (chessBoard[i][j] >= 0)
			{
				printf(" %d, ", chessBoard[i][j]);
			} else {
				printf("%d, ", chessBoard[i][j]);
			}	
		}
		printf("| \n");
	}

	//Printing the bottom portion
	printf("  ---------------------------------\n");
	printf(" ");
	for(int r = 0; r < 8; r++){
		printf("   %c", footer[r]);
	}
	printf("\n");
}

//Turns char into a number to be used to access two-dim array
int translateColumnChar(char letter){
	for(int i = 0; i < 8; i++){
		if(footer[i] == letter){
			return footerNum[i];
		}
	}
	return -1;
}

int translateRowToRealNum(int num){
	return 8 - num;
}

//Handles the user interface
void userInteraction(){
	//Player one values
	int playerOneCurrentRow;
	char playerOneCurrentCol;
	char tempPlayerOneCurrentRow[2];
	int playerOneNewRow;
	char playerOneNewCol;
	char tempPlayerOneNewRow[2];

	//Player two values
	int playerTwoCurrentRow;
	char playerTwoCurrentCol;
	char tempPlayerTwoCurrentRow[2];
	int playerTwoNewRow;
	char playerTwoNewCol;
	char tempPlayerTwoNewRow[2];

	//Total command
	char command[25];

	printWelcomeMessage();
	printChessBoard();

	//Runs as long as the user doesn't enter "quit"
	while(command[0] != 'q' && command[1] != 'u' && command[2] != 'i' && command[3] != 't'){
		//Player One Goes
		playerOne:
		printf("Player One, your turn\n Command: ");
		fgets(command, 25, stdin);

		// Assigning values from command
		memcpy(tempPlayerOneCurrentRow, &command[4], 1);
		tempPlayerOneCurrentRow[1] = '\0';
		playerOneCurrentRow = atoi(tempPlayerOneCurrentRow);
		playerOneCurrentCol = command[6];
		memcpy(tempPlayerOneNewRow, &command[9], 1);
		tempPlayerOneNewRow[1] = '\0';
		playerOneNewRow = atoi(tempPlayerOneNewRow);
		playerOneNewCol = command[11];


		if(command[0] == 'q' && command[1] == 'u' && command[2] == 'i' && command[3] == 't'){ //Breaks the loop if a player enters "quit"
			printf("Player Two wins!\n");
			return;
		} else if ((command[0] == 'm' && command[1] == 'v') || ((command[0] == 'c' && command[1] == 'p'))){
			if(isPawn(playerOneCurrentRow, playerOneCurrentCol)){ //Case for pawn
				if(usePawn(playerOneCurrentRow, playerOneCurrentCol, playerOneNewRow, playerOneNewCol, 1) == 1){
					;
				} else {
					printf("\n**That is an illegal move, please try again**\n");
					goto playerOne;
				}
			} else if(isKnight(playerOneCurrentRow, playerOneCurrentCol)){ //Case for knight
				if(useKnight(playerOneCurrentRow, playerOneCurrentCol, playerOneNewRow, playerOneNewCol, 1) == 1){
					;
				} else {
					printf("\n**That is an illegal move, please try again**\n");
					goto playerOne;
				} 
			} else if(isRook(playerOneCurrentRow, playerOneCurrentCol)){ //Case for rook
				if(useRook(playerOneCurrentRow, playerOneCurrentCol, playerOneNewRow, playerOneNewCol, 1) == 1){
					;
				} else {
					printf("\n**That is an illegal move, please try again**\n");
					goto playerOne;
				}
			} else if(isBishop(playerOneCurrentRow, playerOneCurrentCol)){ //Case for bishop
				if(useBishop(playerOneCurrentRow, playerOneCurrentCol, playerOneNewRow, playerOneNewCol, 1) == 1){
					;
				} else {
					printf("\n**That is an illegal move, please try again**\n");
					goto playerOne;
				}
			} else if(isQueen(playerOneCurrentRow, playerOneCurrentCol)){ //Case for queen
				if(useQueen(playerOneCurrentRow, playerOneCurrentCol, playerOneNewRow, playerOneNewCol, 1) == 1){
					;
				} else {
					printf("\n**That is an illegal move, please try again**\n");
					goto playerOne;
				}
			} else if(isKing(playerOneCurrentRow, playerOneCurrentCol)){ //Case for king
				if(useKing(playerOneCurrentRow, playerOneCurrentCol, playerOneNewRow, playerOneNewCol, 1) == 1){
					;
				} else {
					printf("\n**That is an illegal move, please try again**\n");
					goto playerOne;
				}
			} else { //Anything else if an illegal move
				printf("\n**That is an illegal move, please try again**\n");
				goto playerOne;
			}
			playerOneFirstTurnWasPlayed = 1; //Makes sure playerOne doesn't move up two spaces again with pawn after first move
		} else if(command[0] == 's' && command[1] == 'h' && command[2] == 'o' && command[3] == 'w'){ //'show' command for showing chessboard
			printChessBoard();
			goto playerOne;
		} else {
			printf("Invalid Entry, try again\n");
			goto playerOne;
		}
		kingIsInCheck();

		//Player Two Goes
		playerTwo:
		printf("Player Two, your turn\n Command: ");
		fgets(command, 25, stdin);

		// Assigning values from command
		memcpy(tempPlayerTwoCurrentRow, &command[4], 1);
		tempPlayerTwoCurrentRow[1] = '\0';
		playerTwoCurrentRow = atoi(tempPlayerTwoCurrentRow);
		playerTwoCurrentCol = command[6];
		memcpy(tempPlayerTwoNewRow, &command[9], 1);
		tempPlayerTwoNewRow[1] = '\0';
		playerTwoNewRow = atoi(tempPlayerTwoNewRow);
		playerTwoNewCol = command[11];

		if(command[0] == 'q' && command[1] == 'u' && command[2] == 'i' && command[3] == 't'){ //breaks the loop if playerTwo enters "quit"
			printf("Player One wins!\n");
			return;
		} else if((command[0] == 'm' && command[1] == 'v') || ((command[0] == 'c' && command[1] == 'p'))){
			if(isPawn(playerTwoCurrentRow, playerTwoCurrentCol)){ //Case for Pawn
				if(usePawn(playerTwoCurrentRow, playerTwoCurrentCol, playerTwoNewRow, playerTwoNewCol, -1) == 1){
					;
				} else {
					printf("\n**That is an illegal move, please try again**\n");
					goto playerTwo;
				}
			} else if(isKnight(playerTwoCurrentRow, playerTwoCurrentCol)){ //Case for knight
				if(useKnight(playerTwoCurrentRow, playerTwoCurrentCol, playerTwoNewRow, playerTwoNewCol, -1) == 1){
					;
				} else {
					printf("\n**That is an illegal move, please try again**\n");
					goto playerTwo;
				}
			}  else if(isRook(playerTwoCurrentRow, playerTwoCurrentCol)){ //Case for rook
				if(useRook(playerTwoCurrentRow, playerTwoCurrentCol, playerTwoNewRow, playerTwoNewCol, -1) == 1){
					;
				} else {
					printf("\n**That is an illegal move, please try again**\n");
					goto playerTwo;
				}
			} else if(isBishop(playerTwoCurrentRow, playerTwoCurrentCol)){ //Case for bishop
				if(useBishop(playerTwoCurrentRow, playerTwoCurrentCol, playerTwoNewRow, playerTwoNewCol, -1) == 1){
					;
				} else {
					printf("\n**That is an illegal move, please try again**\n");
					goto playerTwo;
				}
			} else if(isQueen(playerTwoCurrentRow, playerTwoCurrentCol)){ //Case for queen
				if(useQueen(playerTwoCurrentRow, playerTwoCurrentCol, playerTwoNewRow, playerTwoNewCol, -1) == 1){
					;
				} else {
					printf("\n**That is an illegal move, please try again**\n");
					goto playerTwo;
				}
			} else if(isKing(playerTwoCurrentRow, playerTwoCurrentCol)){ //Case for king
				if(useKing(playerTwoCurrentRow, playerTwoCurrentCol, playerTwoNewRow, playerTwoNewCol, -1) == 1){
					;
				} else {
					printf("\n**That is an illegal move, please try again**\n");
					goto playerTwo;
				}
			}
			else { //Anything else is an illegal move
				printf("\n**That is an illegal move, please try again**\n");
				goto playerTwo;
			}
			playerTwoFirstTurnWasPlayed = 1; //Makes sure that player two doesn't go two spaces ahead with pawn after first turn
		} else if(command[0] == 's' && command[1] == 'h' && command[2] == 'o' && command[3] == 'w'){
			printChessBoard();
			goto playerTwo;
		} else {
			printf("Invalid Entry, try again\n");
			goto playerTwo;
		}
	}
	kingIsInCheck();
	
}

//Checks if user entered the coordinates for a pawn
int isPawn(int row, char col){
	int realRowNum;
	int realCharNum;

	realRowNum = translateRowToRealNum(row);
	realCharNum = translateColumnChar(col);
	
	if(chessBoard[realRowNum][realCharNum] == 1 || chessBoard[realRowNum][realCharNum] == -1){
		return 1;
	}
	return 0;
}

int usePawn(int row1, char col1, int row2, char col2, int playerSign){
	int originalRow;
	int originalCol;
	int originalCoordinateValue;
	int newRow;
	char newColChar;
	int newColNum;
	int newCoordinateValue;

	originalRow = translateRowToRealNum(row1);
	originalCol = translateColumnChar(col1);
	originalCoordinateValue = chessBoard[originalRow][originalCol];
	newRow = translateRowToRealNum(row2);
	newColNum = translateColumnChar(col2);
	newCoordinateValue = chessBoard[newRow][newColNum];

	//Checking if user entered a value greater than or less than allowed
	if(newRow > 7 || newRow < 0 || newColNum > 7 || newColNum < 0){
		printf("\n**A value you entered was greater than 8, greater than h, less than 1, or less than a. Please try again\n\n");
		return 0;
	}

	//Checking if a player is trying to play an opponent's piece
	if(playerSign == 1 && originalCoordinateValue < 0){
		return -1;
	} else if(playerSign == -1 && originalCoordinateValue > 0){
		return -1;
	}

	//Checking if player is trying to illegally move diagonally
	if(playerSign == 1){
		if((originalCol - newColNum == 1 && originalRow - newRow == 1) && newCoordinateValue == 0){
			return -1;
		} else if((newColNum - originalCol == 1 && originalRow - newRow == 1) && newCoordinateValue == 0){
			return -1;
		}
	} else if(playerSign == -1){
		if((originalCol - newColNum == 1 && newRow - originalRow == 1) && newCoordinateValue == 0){
			return -1;
		} else if((newColNum - originalCol == 1 && newRow - originalRow == 1) && newCoordinateValue == 0){
			return -1;
		}
	}

	//player one first turn
	if(!playerOneFirstTurnWasPlayed){
		if((newCoordinateValue <= 0 && originalRow - newRow <=2)){
			chessBoard[newRow][newColNum] = chessBoard[originalRow][originalCol];
			chessBoard[originalRow][originalCol] = 0;
			printChessBoard();
			return 1;
		} else if((((originalRow - newRow == 1) && (newColNum - originalCol == 1)) || ((originalRow - newRow == 1) && (originalCol - newColNum == 1)))){
			if(newCoordinateValue < 0){
				chessBoard[newRow][newColNum] = chessBoard[originalRow][originalCol];
				chessBoard[originalRow][originalCol] = 0;
				printChessBoard();
				return 1;
			}
		} else {
			return -1;
		}
	} else if(!playerTwoFirstTurnWasPlayed){ //player two first turn
		if((newCoordinateValue >= 0 && newRow - originalRow <=2)){
			chessBoard[newRow][newColNum] = chessBoard[originalRow][originalCol];
			chessBoard[originalRow][originalCol] = 0;
			printChessBoard();
			return 1;
		} else if((((newRow - originalRow == 1) && (newColNum - originalCol == 1)) || ((newRow - originalRow == 1) && (originalCol - newColNum == 1)))){
			if(newCoordinateValue < 0){
				chessBoard[newRow][newColNum] = chessBoard[originalRow][originalCol];
				chessBoard[originalRow][originalCol] = 0;
				printChessBoard();
				return 1;
			}
		} else {
			return -1;
		}
	} else {
		if(playerOneFirstTurnWasPlayed){ //player one regular turn
			if((newCoordinateValue <= 0 && originalRow - newRow <=1)){
				chessBoard[newRow][newColNum] = chessBoard[originalRow][originalCol];
				chessBoard[originalRow][originalCol] = 0;
				printChessBoard();
				return 1;
		} else if((((originalRow - newRow == 1) && (newColNum - originalCol == 1)) || ((originalRow - newRow == 1) && (originalCol - newColNum == 1)))){
			if(newCoordinateValue < 0){
				chessBoard[newRow][newColNum] = chessBoard[originalRow][originalCol];
				chessBoard[originalRow][originalCol] = 0;
				printChessBoard();
				return 1;
			}
		} else {
			return -1;
		}
		} if(playerTwoFirstTurnWasPlayed){ //player two regular turn
			if((newCoordinateValue >= 0 && newRow - originalRow <=1)){
				chessBoard[newRow][newColNum] = chessBoard[originalRow][originalCol];
				chessBoard[originalRow][originalCol] = 0;
				printChessBoard();
				return 1;
			} else if((((newRow - originalRow == 1) && (newColNum - originalCol == 1)) || ((newRow - originalRow == 1) && (originalCol - newColNum == 1)))){
				if(newCoordinateValue < 0){
					chessBoard[newRow][newColNum] = chessBoard[originalRow][originalCol];
					chessBoard[originalRow][originalCol] = 0;
					printChessBoard();
					return 1;
				}
			} else {
				return -1;
			}
		}
	}
	return 0;

}

//Checks if the coordinate selected is a knight
int isKnight(int row, char col){
	int realRow; //real row number for index
	int realCol; //real row number for index
	int coordinateValue;

	//turns row and column to real indexes
	realRow = translateRowToRealNum(row);
	realCol = translateColumnChar(col);
	coordinateValue = chessBoard[realRow][realCol];

	//returns true if the piece in the coordinate is a knight
	if(coordinateValue == 2 || coordinateValue == -2){
		return 1;
	}
	return 0;
}

int useKnight(int row1, char col1, int row2, char col2, int playerSign){
	int originalRow;
	int originalCol;
	int originalCoordinateValue;
	int newCoordinateValue;
	int newRow;
	char newColChar;
	int newColNum;

	originalRow = translateRowToRealNum(row1);
	originalCol = translateColumnChar(col1);
	originalCoordinateValue = chessBoard[originalRow][originalCol];
	newRow = translateRowToRealNum(row2);
	newColNum = translateColumnChar(col2);
	newCoordinateValue = chessBoard[newRow][newColNum];

	//Checking if user entered a value greater than or less than allowed
	if(newRow > 7 || newRow < 0 || newColNum > 7 || newColNum < 0 || 
	   originalRow > 7 || originalRow < 0 || originalCol > 7 || originalCol < 0){
		return -1;
	}

	//Checks if player is playing opponent's piece
	if(playerSign == 1 && originalCoordinateValue < 0){
		return -1;
	} else if(playerSign == -1 && originalCoordinateValue > 0){
		return -1;
	}

	//Cases where it works
	if ((newRow == (originalRow - 2) && newColNum == (originalCol + 1)) ||
	    (newRow == (originalRow - 2) && newColNum == (originalCol - 1)) ||
	    (newRow == (originalRow + 2) && newColNum == (originalCol - 1)) ||
	    (newRow == (originalRow + 2) && newColNum == (originalCol + 1)) ||
	    (newRow == (originalRow - 1) && newColNum == (originalCol - 2)) ||
	    (newRow == (originalRow + 1) && newColNum == (originalCol - 2)) ||
	    (newRow == (originalRow - 1) && newColNum == (originalCol + 2)) ||
	    (newRow == (originalRow + 1) && newColNum == (originalCol + 2))){

		//Case where it works
		if (!((originalCoordinateValue > 0 && newCoordinateValue > 0) ||
			(originalCoordinateValue < 0 && newCoordinateValue < 0))){
			chessBoard[newRow][newColNum] = chessBoard[originalRow][originalCol];
			chessBoard[originalRow][originalCol] = 0;
			printChessBoard();
			return 1;
		} else { //Case that doesn't work
			return -1;
		}
	} else { //Case that doesn't work
		return -1;
	}
	return -1;
}

int isRook(int row, char col){
	int realRow; 
	int realCol;
	int coordinateValue;

	realRow = translateRowToRealNum(row);
	realCol = translateColumnChar(col);
	coordinateValue = chessBoard[realRow][realCol];

	if(coordinateValue == 4 || coordinateValue == -4){
		return 1;
	}
	return 0;
}

int useRook(int row1, char col1, int row2, char col2, int playerSign){
	int originalRow; //real row number for index
	int originalCol; //real row number for index
	int originalCoordinateValue; //value at original coordinates
	int newCoordinateValue; //value at new coordinates
	int newRow; //real index number of new row parameter
	char newColChar; //new char for col
	int newColNum; //real index of new col

	originalRow = translateRowToRealNum(row1);
	originalCol = translateColumnChar(col1);
	originalCoordinateValue = chessBoard[originalRow][originalCol];
	newRow = translateRowToRealNum(row2);
	newColNum = translateColumnChar(col2);
	newCoordinateValue = chessBoard[newRow][newColNum];

	//Checking if user entered a value greater than or less than allowed
	if(newRow > 7 || newRow < 0 || newColNum > 7 || newColNum < 0){
		return -1;
	}

	//Checks if player is playing the opponent's piece
	if(playerSign == 1 && originalCoordinateValue < 0){
		return -1;
	} else if(playerSign == -1 && originalCoordinateValue > 0){
		return -1;
	}

	//Game logic, first if statement starts with legal moves and checks rules until allowed to move
	if ((newRow <= originalRow && newColNum == originalCol) || //up
		((newRow - originalRow) <= 7) && newColNum == originalCol || //down
		(newRow == originalRow && (newColNum - originalCol) <= 7) || //right
		(newRow == originalRow && newColNum <= originalCol)) { //left

		int isNegative = originalCoordinateValue < 0; //if the currentPlayer is playing the negative pieces
		int isPositive = originalCoordinateValue > 0; //if the currentPlayer is playing the positive pieces

		//Checking if there is a piece in the path that the user wants: downward row
		for(int i = originalRow + 1; i < (newRow - originalRow); i++){
			if(isPositive){
				if(chessBoard[i][originalCol] >= 1){
					printf("\n**That path has one of your own pieces in the way**\n\n");
					return -1;
				} else if(chessBoard[i][originalCol] < 0){
					printf("\n**Before that spot, there is an opponent piece you could take over**\n\n");
					return -1;
				}
			} else if(isNegative){
				if(chessBoard[i][originalCol] <= -1){
					printf("\n**That spot has one of your own pieces in the way**\n\n");
					return -1;
				} else if(chessBoard[i][originalCol] > 0){
					printf("\n**Before that spot, there is an opponent piece you could take over**\n\n");
					return -1;
				}
			}
		}

		//Checking if there is a piece in the path that the user wants: upward row
		for(int i = originalRow - 1; i > newRow; i--){
			if(isPositive){
				if(chessBoard[i][originalCol] >= 1){
					printf("\n**That path has one of your own pieces in the way**\n\n");
					return -1;
				} else if(chessBoard[i][originalCol] < 0){
					printf("\n**Before that spot, there is an opponent piece you could take over**\n\n");
					return -1;
				}
			} else if(isNegative){
				if(chessBoard[i][originalCol] <= -1){
					printf("\n**That spot has one of your own pieces in the way**\n\n");
					return -1;
				} else if(chessBoard[i][originalCol] > 0){
					printf("\n**Before that spot, there is an opponent piece you could take over**\n\n");
					return -1;
				}
			}
		}

		//Checking if there is a piece in the path the user wants: right
		for(int i = originalCol + 1; i <= (newColNum - originalCol); i++){
			if(isPositive){
				if(chessBoard[originalRow][i] >= 1){
					printf("\n**That path has one of your own pieces in the way**\n\n");
					return -1;
				} else if(chessBoard[originalRow][i] < 0){
					printf("\n**Before that spot, there is an opponent piece you could take over**\n\n");
					return -1;
				}
			} else if(isNegative){
				if(chessBoard[originalRow][i] <= -1){
					printf("\n**That spot has one of your own pieces in the way**\n\n");
					return -1;
				} else if(chessBoard[originalRow][i] > 0){
					printf("\n**Before that spot, there is an opponent piece you could take over**\n\n");
					return -1;
				}
			}
		}

		//Checking if there is a piece in the path the user wants: left
		for(int i = originalCol - 1; i >= newColNum; i--){
			if(isPositive){
				if(chessBoard[originalRow][i] >= 1){
					printf("\n**That path has one of your own pieces in the way**\n\n");
					return -1;
				} else if(chessBoard[originalRow][i] < 0){
					printf("\n**Before that spot, there is an opponent piece you could take over**\n\n");
					return -1;
				}
			} else if(isNegative){
				if(chessBoard[originalRow][i] >= -1){
					printf("\n**That spot has one of your own pieces in the way**\n\n");
					return -1;
				} else if(chessBoard[originalCol][i] > 0){
					printf("\n**Before that spot, there is an opponent piece you could take over**\n\n");
					return -1;
				}
			}
		}

		//If made to this point, then the move can be made legally
		chessBoard[newRow][newColNum] = chessBoard[originalRow][originalCol];
		chessBoard[originalRow][originalCol] = 0;
		printChessBoard();
		return 1;
	}
	return -1; 
}

int isBishop(int row, char col){
	int realRow;
	int realCol;
	int coordinateValue;

	realRow = translateRowToRealNum(row);
	realCol = translateColumnChar(col);
	coordinateValue = chessBoard[realRow][realCol];

	if(coordinateValue == 3 || coordinateValue == -3){
		return 1;
	}
	return 0;
}

int useBishop(int row1, char col1, int row2, char col2, int playerSign){
	int originalRow; //real row number for index
	int originalCol; //real row number for index
	int originalCoordinateValue; //value at original coordinates
	int newCoordinateValue; //value at new coordinates
	int newRow; //real index number of new row parameter
	char newColChar; //new char for col
	int newColNum; //real index of new col

	originalRow = translateRowToRealNum(row1);
	originalCol = translateColumnChar(col1);
	originalCoordinateValue = chessBoard[originalRow][originalCol];
	newRow = translateRowToRealNum(row2);
	newColNum = translateColumnChar(col2);
	newCoordinateValue = chessBoard[newRow][newColNum];

	//Checking if user entered a value greater than or less than allowed
	if(newRow > 7 || newRow < 0 || newColNum > 7 || newColNum < 0){
		printf("\n**A value you entered was greater than 8, greater than h, less than 1, or less than a\n\n");
		return -1;
	}

	//Checks if player is playing the opponent's piece
	if(playerSign == 1 && originalCoordinateValue < 0){
		return -1;
	} else if(playerSign == -1 && originalCoordinateValue > 0){
		return -1;
	}

	//Entering condition for legal move
	if(abs(newColNum - originalCol) == abs(newRow - originalRow)){
		int isPositive = originalCoordinateValue > 0; //if the currentPlayer is playing the positive pieces
		int isNegative = originalCoordinateValue < 0; //if the currentPlayer is playing the negative pieces

		//Checking if a piece is in the path
		for(int i = 1, j = 1; i < abs(originalRow - newRow); i++, j++){ //upper right
			if(isPositive){
				//upper right
				if((newRow < originalRow) && (newColNum > originalCol)){
					if(chessBoard[originalRow - i][originalCol + j] > 0){
						printf("\n**That path has one of your own pieces in the way**\n\n");
						return -1;
					} else if(chessBoard[originalRow - i][originalCol + j] < 0){
						printf("\n**Before that spot, there is an opponent piece you could take over**\n\n");
						return -1;
					}
				}
				//upper left
				else if((newRow < originalRow) && (newColNum < originalCol)){
					if(chessBoard[originalRow - i][originalCol - j] > 0){
						printf("\n**That path has one of your own pieces in the way**\n\n");
						return -1;
					} else if(chessBoard[originalRow - i][originalCol - j] < 0){
						printf("\n**Before that spot, there is an opponent piece you could take over**\n\n");
						return -1;
					}
				}
				//lower right
				else if((newRow > originalRow) && (newColNum > originalCol)){
					if(chessBoard[originalRow + i][originalCol + j] > 0){
						printf("\n**That path has one of your own pieces in the way**\n\n");
						return -1;
					} else if(chessBoard[originalRow + i][originalCol + j] < 0){
						printf("\n**Before that spot, there is an opponent piece you could take over**\n\n");
						return -1;
					}
				}
				//lower left
				else if((newRow > originalRow) && (newColNum < originalCol)){
					if(chessBoard[originalRow + i][originalCol - j] > 0){
						printf("\n**That path has one of your own pieces in the way**\n\n");
						return -1;
					} else if(chessBoard[originalRow + i][originalCol - j] < 0){
						printf("\n**Before that spot, there is an opponent piece you could take over**\n\n");
						return -1;
					}
				}
			} else if(isNegative){
				//upper right
				if((newRow < originalRow) && (newColNum > originalCol)){
					if(chessBoard[originalRow - i][originalCol + j] < 0){
						printf("\n**That path has one of your own pieces in the way**\n\n");
						return -1;
					} else if(chessBoard[originalRow - i][originalCol + j] > 0){
						printf("\n**Before that spot, there is an opponent piece you could take over**\n\n");
						return -1;
					}
				}
				//upper left
				else if((newRow < originalRow) && (newColNum < originalCol)){
					if(chessBoard[originalRow - i][originalCol - j] < 0){
						printf("\n**That path has one of your own pieces in the way**\n\n");
						return -1;
					} else if(chessBoard[originalRow - i][originalCol - j] > 0){
						printf("\n**Before that spot, there is an opponent piece you could take over**\n\n");
						return -1;
					}
				}
				//lower right
				else if((newRow > originalRow) && (newColNum > originalCol)){
					if(chessBoard[originalRow + i][originalCol + j] < 0){
						printf("\n**That path has one of your own pieces in the way**\n\n");
						return -1;
					} else if(chessBoard[originalRow + i][originalCol + j] > 0){
						printf("\n**Before that spot, there is an opponent piece you could take over**\n\n");
						return -1;
					}
				}
				//lower left
				else if((newRow > originalRow) && (newColNum < originalCol)){
					if(chessBoard[originalRow + i][originalCol - j] < 0){
						printf("\n**That path has one of your own pieces in the way**\n\n");
						return -1;
					} else if(chessBoard[originalRow + i][originalCol - j] > 0){
						printf("\n**Before that spot, there is an opponent piece you could take over**\n\n");
						return -1;
					}
				}
			}
		}

		//If made to this point, then the move can be made legally
		chessBoard[newRow][newColNum] = chessBoard[originalRow][originalCol];
		chessBoard[originalRow][originalCol] = 0;
		printChessBoard();
		return 1;
	}
	return 0; 
}

int isQueen(int row, char col){
	int realRow;
	int realCol;
	int coordinateValue;

	realRow = translateRowToRealNum(row);
	realCol = translateColumnChar(col);
	coordinateValue = chessBoard[realRow][realCol];

	if(coordinateValue == 5){
		return 1;
	}
	return 0;
}

int useQueen(int row1, char col1, int row2, char col2, int playerSign){
	int originalRow; //real row number for index
	int originalCol; //real row number for index
	int originalCoordinateValue; //value at original coordinates
	int newCoordinateValue; //value at new coordinates
	int newRow; //real index number of new row parameter
	char newColChar; //new char for col
	int newColNum; //real index of new col

	originalRow = translateRowToRealNum(row1);
	originalCol = translateColumnChar(col1);
	originalCoordinateValue = chessBoard[originalRow][originalCol];
	newRow = translateRowToRealNum(row2);
	newColNum = translateColumnChar(col2);
	newCoordinateValue = chessBoard[newRow][newColNum];

	//Checking if user entered a value greater than or less than allowed
	if(newRow > 7 || newRow < 0 || newColNum > 7 || newColNum < 0){
		printf("\n**A value you entered was greater than 8, greater than h, less than 1, or less than a\n\n");
		return -1;
	}

	//Checks if player is playing the opponent's piece
	if(playerSign == 1 && originalCoordinateValue < 0){
		return -1;
	} else if(playerSign == -1 && originalCoordinateValue > 0){
		return -1;
	}

	//Uses bishop function for diagnal movements
	if((newRow != originalRow) && (newColNum != originalCol)){
		if(useBishop(row1, col1, row2, col2, playerSign) == 1){
			;
		} else {
			return -1;
		}
	} else if((newRow != originalRow) || (newColNum != originalCol)){ //Uses rook for vertical or horizontal movements
		if(useRook(row1, col1, row2, col2, playerSign) == 1){
			;
		} else {
			return -1;
		}
	} else {
		printf("\n**That is an illegal move, please try again**\n\n");
		return -1;
	}
	return 0;
}

int isKing(int row, char col){
	int realRow;
	int realCol;
	int coordinateValue;

	realRow = translateRowToRealNum(row);
	realCol = translateColumnChar(col);
	coordinateValue = chessBoard[realRow][realCol];

	if(coordinateValue == 6){
		return 1;
	}
	return 0;
}

int useKing(int row1, char col1, int row2, char col2, int playerSign){
	int originalRow; //real row number for index
	int originalCol; //real row number for index
	int originalCoordinateValue; //value at original coordinates
	int newCoordinateValue; //value at new coordinates
	int newRow; //real index number of new row parameter
	char newColChar; //new char for col
	int newColNum; //real index of new col

	originalRow = translateRowToRealNum(row1);
	originalCol = translateColumnChar(col1);
	originalCoordinateValue = chessBoard[originalRow][originalCol];
	newRow = translateRowToRealNum(row2);
	newColNum = translateColumnChar(col2);
	newCoordinateValue = chessBoard[newRow][newColNum];

	//Checking if user entered a value greater than or less than allowed
	if(newRow > 7 || newRow < 0 || newColNum > 7 || newColNum < 0){
		printf("\n**A value you entered was greater than 8, greater than h, less than 1, or less than a\n\n");
		return -1;
	}

	//Checks if player is playing the opponent's piece
	if(playerSign == 1 && originalCoordinateValue < 0){
		return -1;
	} else if(playerSign == -1 && originalCoordinateValue > 0){
		return -1;
	}

	//Case where you can use king
	if ((newRow == originalRow + 1 && newColNum == originalCol) ||
	    (newRow == originalRow - 1 && newColNum == originalCol) ||
	    (newColNum == originalCol + 1 && newRow == originalRow) ||
	    (newColNum == originalCol - 1 && newRow == originalRow)){

		int isPositive = originalCoordinateValue > 0; //if the currentPlayer is playing the positive pieces
		int isNegative = originalCoordinateValue < 0; //if the currentPlayer is playing the negative pieces

		if(isPositive){
			if(newCoordinateValue > 0){
				printf("\n**That path has one of your own pieces in the way**\n\n");
				return -1;
			} 
		} else if(isNegative){
			if(newCoordinateValue < 0){
				printf("\n**That path has one of your own pieces in the way**\n\n");
				return -1;
			}
		}

		//If made to this point, then the move can be made legally
		chessBoard[newRow][newColNum] = chessBoard[originalRow][originalCol];
		chessBoard[originalRow][originalCol] = 0;
		printChessBoard();
		return 1;
	} 
	return 0;
}

void kingIsInCheck(){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(chessBoard[i][j] == 6){ //For player one's king
				if(chessBoard[i][j - 1] < 0){ //to the left
					printf("\n**Player One's King is in 'check'**\n\n");
					return;
				} else if(chessBoard[i][j + 1] < 0){ //to the right
					printf("\n**Player One's King is in 'check'**\n\n");
					return;
				} else if(chessBoard[i - 1][j] < 0){ //to up
					printf("\n**Player One's King is in 'check'**\n\n");
					return;
				} else if(chessBoard[i - 1][j-1] < 0){ //to upper left
					printf("\n**Player One's King is in 'check'**\n\n");
					return;
				} else if(chessBoard[i - 1][j + 1] < 0){ //to upper right
					printf("\n**Player One's King is in 'check'**\n\n");
					return;
				}
			} else if(chessBoard[i][j] == -6){
				if(chessBoard[i][j - 1] > 0){ //to the left
					printf("\n**Player Two's King is in 'check'\n");
					return;
				} else if(chessBoard[i][j + 1] > 0){ //to the right
					printf("\n**Player Two's King is in 'check'\n");
					return;
				} else if(chessBoard[i + 1][j] > 0){ //to up
					printf("\n**Player Two's King is in 'check'\n");
					return;
				} else if (chessBoard[i + 1][j + 1] > 0){ //to lower right
					printf("\n**Player Two's King is in 'check'\n");
					return;
				} else if(chessBoard[i + 1][j - 1] > 0){ //to lower left
					printf("\n**Player Two's King is in 'check'\n");
					return;
				}
			}
		}
	}
}


















































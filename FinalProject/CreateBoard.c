#include <stdbool.h>
#include <stdio.h>
#define Maxsize 8
char NextStep(char Ps2data, char Key);
char SearchBomb(char board[8][8], char BoardStatus[8][8], int row, int col);
void SearchZero(char board[8][8], char BoardStatus[8][8], int row, int col);
bool CheckValidity(char board[8][8], char BoardStatus[8][8], int row, int col,
                   char nextstep);
void WhetherStart(char Ps2data);
bool GameEnd(char board[8][8], char BoardStatus[8][8], char ChoseData);
void GameOverAnime();


int main() {
  char Ps2data = ' ';  // Uncover Flag
  char Key = ' ';      // Up Down Right Left
  // input Ps2data and Keydata here, how?
  char ChoseData;
  char nextstep = ' ';
  int posX = 0;
  int posY = 0;
  bool End = false; // End or not
  char OriginalBoard[8][8] = {{'B', '0', '0', '0', 'B', '0', '0', '0', 'B'},
                              {'0', '0', '0', '0', '0', '0', '0', '0', '0'},
                              {'B', '0', '0', '0', 'B', '0', '0', '0', '0'},
                              {'B', '0', '0', '0', '0', '0', 'B', '0', 'B'},
                              {'B', '0', 'B', '0', '0', '0', '0', '0', '0'},
                              {'B', '0', '0', '0', '0', '0', '0', '0', '0'},
                              {'0', '0', 'B', '0', 'B', '0', '0', '0', '0'},
                              {'B', '0', '0', '0', '0', '0', '0', '0', '0'},
                              {'0', '0', '0', '0', 'B', '0', '0', '0', '0'}};

  char BoardStatus[8][8] = {{'0', '0', '0', '0', '0', '0', '0', '0', '0'},
                            {'0', '0', '0', '0', '0', '0', '0', '0', '0'},
                            {'0', '0', '0', '0', '0', '0', '0', '0', '0'},
                            {'0', '0', '0', '0', '0', '0', '0', '0', '0'},
                            {'0', '0', '0', '0', '0', '0', '0', '0', '0'},
                            {'0', '0', '0', '0', '0', '0', '0', '0', '0'},
                            {'0', '0', '0', '0', '0', '0', '0', '0', '0'},
                            {'0', '0', '0', '0', '0', '0', '0', '0', '0'},
                            {'0', '0', '0', '0', '0', '0', '0', '0', '0'}}; //Have Status Flag F, Bomb B, Empty around E, 1,2,3,4 Bombs and 0 is cover status
  WhetherStart(Ps2data);  // send start request
  while (!End) {
    nextstep = NextStep(Ps2data, Key);  // need reset?
    if (CheckValidity(OriginalBoard[8][8], BoardStatus[8][8], posX, posY,
                      nextstep)) {
      if (nextstep == "Up") {
        posX--;
      }
      if (nextstep == "Down") {
        posX++;
      }
      if (nextstep == "Left") {
        posY--;
      }
      if (nextstep == "Right") {
        posY++;
      }
      if (nextstep == "Uncover") {
        ChoseData = SearchBomb(OriginalBoard, BoardStatus, posX, posY);
        BoardStatus[posX][posY] = ChoseData;
        if (ChoseData != 'B') {
          if(ChoseData == 'E'){
            SearchZero(OriginalBoard, BoardStatus, posX, posY);
          }else{
            BoardStatus[posX][posY] = ChoseData;
          }
        }
      }
      if (nextstep == "Flag") {
        if (BoardStatus[posX][posY] == '0') {
          BoardStatus[posX][posY] = 'F'; 
        } else {
          BoardStatus[posX][posY] == '0';
        }
      }
    }
    End = GameEnd(OriginalBoard[8][8],BoardStatus[8][8], ChoseData);
  }

  return 0;
}

void WhetherStart(char Ps2data) {
  // Ps2data = Keyboard input
  bool start = false;
  while (!start) {
    if (Ps2data == "Space") {
      start = true;
    }
  }
  return;
}
char NextStep(char Ps2data, char Key) {
  char next = ' ';
  if (Ps2data == "Space") {
    next = "Uncover";
  }
  if (Ps2data == 'Enter') {
    next = "Flag";
  }
  if (Key == "Up" || Key == "Down" || Key == "Left" || Key == "Right") {
    next = Key;
  }
  return next;
}
bool CheckValidity(char board[8][8], char BoardStatus[8][8], int row, int col,
                   char nextstep) {
  bool move = false;
  if (nextstep == "Up") {
    row--;
    move = true;
  }
  if (nextstep == "Down") {
    row++;
    move = true;
  }
  if (nextstep == "Left") {
    col--;
    move = true;
  }
  if (nextstep == "Right") {
    col++;
    move = true;
  }
  if (row < 0 || row > 8 || col < 0 || col > 8) {
    // false judgement
    return false;
  } else if (move) {
    return true;
  }
  if (nextstep == "Uncover") {
    if (BoardStatus[row][col] == '0') {
      return true;
    } else {
      return false;
    }
  }
  if (nextstep == "Flag") {
    if (BoardStatus[row][col] == '0' || BoardStatus[row][col] == 'F') {
      return true;
    } else {
      return false;
    }
  }
  return false;
}
char SearchBomb(char board[8][8], char BoardStatus[8][8], int row, int col) {
  char Num = '0';
  int Row = 0;
  int Col = 0;
  if (board[row][col] == 'B') {
    return 'B';
  }
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      Row = row + i;
      Col = col + j;
      if (Row < 0 || Row > 8 || Col < 0 || Col > 8) {
        continue;
      } else if (board[Row][Col] == 'B') {
        Num++;
      }
    }
  }
  if(Num == '0'){
    return 'E';
  }
  return Num;
}
void SearchZero(char board[8][8], char BoardStatus[8][8], int row, int col){
  if(row < 0 || row > 8 || col < 0 || col > 8){
    return;
  }
  int Row = 0;
  int Col = 0;
    for(int i = -1; i <= 1; i++){
      for(int j = -1; j <= 1; j++){
        Row = row + i;
        Col = col + i;
        if (Row < 0 || Row > 8 || Col < 0 || Col > 8) {
        continue;
      } else if (board[Row][Col] == 'B') {
        return;
      }
      }
    }
    for(int i = -1; i <= 1; i++){
      for(int j = -1; j <= 1; j++){
        SearchZero(board[8][8], BoardStatus[8][8], row + i, col + j);
      }
      }
      BoardStatus[row][col] = 'E'; //Empty bomb in the Vicinity
      return;

}
bool GameEnd(char board[8][8], char BoardStatus[8][8], char ChoseData) {
    int BombLEFT = 0;
    int BombNum = 0;
    if(ChoseData == 'B'){
      return true;
    }
    for(int i = 0; i <= 8; i++){
      for(int j = 0; j <= 8; j++){
          if(BoardStatus[i][j] == '0' || BoardStatus[i][j] == 'F'){
            BombLEFT++;
          }
          if(board[i][j] == 'B'){
            BombNum++;
          }

      }
    }
    if(BombNum == BombLEFT){
      return true;
    }else{
      return false;
    }
}
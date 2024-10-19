#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define Maxsize 8
char* NextStep(char* Ps2data, char* Key);
char SearchBomb(char board[][9], char BoardStatus[][9], int row, int col);
void SearchZero(char board[][9], char BoardStatus[][9], int row, int col);
bool CheckValidity(char board[][9], char BoardStatus[][9], int row, int col,
                   char* nextstep);
void WhetherStart(char* Ps2data);
bool GameEnd(char board[][9], char BoardStatus[][9], char ChoseData);
void GameOverAnime();

int main() {
  char* Ps2data = "Space";  // Uncover Flag
  char* Key = "";           // Up Down Right Left
  // input Ps2data and Keydata here, how?
  char ChoseData;
  char* nextstep = "";
  int posX = 0;
  int posY = 0;
  bool End = false;  // End or not
  char OriginalBoard[9][9] = {{'B', '0', '0', '0', 'B', '0', '0', '0', 'B'},
                              {'0', '0', '0', '0', '0', '0', '0', '0', '0'},
                              {'B', '0', '0', '0', 'B', '0', '0', '0', '0'},
                              {'B', '0', '0', '0', '0', '0', 'B', '0', 'B'},
                              {'B', '0', 'B', '0', '0', '0', '0', '0', '0'},
                              {'B', '0', '0', '0', '0', '0', '0', '0', '0'},
                              {'0', '0', 'B', '0', 'B', '0', '0', '0', '0'},
                              {'B', '0', '0', '0', '0', '0', '0', '0', '0'},
                              {'0', '0', '0', '0', 'B', '0', '0', '0', '0'}};

  char BoardStatus[9][9] = {{'0', '0', '0', '0', '0', '0', '0', '0', '0'},
                            {'0', '0', '0', '0', '0', '0', '0', '0', '0'},
                            {'0', '0', '0', '0', '0', '0', '0', '0', '0'},
                            {'0', '0', '0', '0', '0', '0', '0', '0', '0'},
                            {'0', '0', '0', '0', '0', '0', '0', '0', '0'},
                            {'0', '0', '0', '0', '0', '0', '0', '0', '0'},
                            {'0', '0', '0', '0', '0', '0', '0', '0', '0'},
                            {'0', '0', '0', '0', '0', '0', '0', '0', '0'},
                            {'0', '0', '0', '0', '0', '0', '0', '0',
                             '0'}};  // Have Status Flag F, Bomb B, Empty around
                                     // E, 1,2,3,4 Bombs and 0 is cover status
  WhetherStart(Ps2data);             // send start request
  while (!End) {
    nextstep = NextStep(Ps2data, Key);  // need reset?
    if (CheckValidity(OriginalBoard, BoardStatus, posX, posY, nextstep)) {
      if (strcmp(nextstep, "Up") == 0) {
        posX--;
      }
      if (strcmp(nextstep, "Down") == 0) {
        posX++;
      }
      if (strcmp(nextstep, "Left") == 0) {
        posY--;
      }
      if (strcmp(nextstep, "Right") == 0) {
        posY++;
      }
      if (strcmp(nextstep, "Uncover") == 0) {
        ChoseData = SearchBomb(OriginalBoard, BoardStatus, posX, posY);
        BoardStatus[posX][posY] = ChoseData;
        if (ChoseData != 'B') {
          if (ChoseData == 'E') {
            SearchZero(OriginalBoard, BoardStatus, posX, posY);
          } else {
            BoardStatus[posX][posY] = ChoseData;
          }
        }
      }
      if (strcmp(nextstep, "Flag") == 0) {
        if (BoardStatus[posX][posY] == '0') {
          BoardStatus[posX][posY] = 'F';
        } else {
          BoardStatus[posX][posY] = '0';
        }
      }
    }
    End = GameEnd(OriginalBoard, BoardStatus, ChoseData);
    // printf("Hello");
  }

  return 0;
}

void WhetherStart(char* Ps2data) {
  // Ps2data = Keyboard input
  bool start = false;
  while (!start) {
    if (strcmp(Ps2data, "Space") == 0) {
      start = true;
    }
  }
  return;
}
char* NextStep(char* Ps2data, char* Key) {
  char* next = "";
  if (strcmp(Ps2data, "Space") == 0) {
    next = "Uncover";
  }
  if (strcmp(Ps2data, "Enter") == 0) {
    next = "Flag";
  }
  if (strcmp(Key, "Up") == 0 || strcmp(Key, "Down") == 0 ||
      strcmp(Key, "Left") == 0 || strcmp(Key, "Right") == 0) {
    next = Key;
  }
  return next;
}
bool CheckValidity(char board[][9], char BoardStatus[][9], int row, int col,
                   char* nextstep) {
  bool move = false;
  if (strcmp(nextstep, "Up") == 0) {
    row--;
    move = true;
  }
  if (strcmp(nextstep, "Down") == 0) {
    row++;
    move = true;
  }
  if (strcmp(nextstep, "Left") == 0) {
    col--;
    move = true;
  }
  if (strcmp(nextstep, "Right") == 0) {
    col++;
    move = true;
  }
  if (row < 0 || row > 8 || col < 0 || col > 8) {
    // false judgement
    return false;
  } else if (move) {
    return true;
  }
  if (strcmp(nextstep, "Uncover") == 0) {
    if (BoardStatus[row][col] == '0') {
      return true;
    } else {
      return false;
    }
  }
  if (strcmp(nextstep, "Flag") == 0) {
    if (BoardStatus[row][col] == '0' || BoardStatus[row][col] == 'F') {
      return true;
    } else {
      return false;
    }
  }
  return false;
}
char SearchBomb(char board[][9], char BoardStatus[][9], int row, int col) {
  char Num = '0';
  int Row = 0;
  int Col = 0;
  if (board[row][col] == 'B') {
    return 'B';
  }
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      Row = row + i;
      Col = col + i;
      if (Row < 0 || Row > 8 || Col < 0 || Col > 8) {
        continue;
      } else if (board[Row][Col] == 'B') {
        Num++;
      }
    }
  }
  if (Num == '0') {
    return 'E';
  }
  return Num;
}
void SearchZero(char board[][9], char BoardStatus[][9], int row, int col) {
  if (row < 0 || row > 8 || col < 0 || col > 8) {
    return;
  }
  int Row = 0;
  int Col = 0;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      Row = row + i;
      Col = col + i;
      if (Row < 0 || Row > 8 || Col < 0 || Col > 8) {
        continue;
      } else if (board[Row][Col] == 'B') {
        return;
      }
    }
  }
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i != 0 || j != 0) {
        SearchZero(board, BoardStatus, row + i, col + j);
      }
    }
  }
  BoardStatus[row][col] = 'E';  // Empty bomb in the Vicinity
  return;
}
bool GameEnd(char board[][9], char BoardStatus[][9], char ChoseData) {
  int BombLEFT = 0;
  int BombNum = 0;
  if (ChoseData == 'B') {
    return true;
  }
  for (int i = 0; i <= 8; i++) {
    for (int j = 0; j <= 8; j++) {
      if (BoardStatus[i][j] == '0' || BoardStatus[i][j] == 'F') {
        BombLEFT++;
      }
      if (board[i][j] == 'B') {
        BombNum++;
      }
    }
  }
  if (BombNum == BombLEFT) {
    return true;
  } else {
    return false;
  }
}
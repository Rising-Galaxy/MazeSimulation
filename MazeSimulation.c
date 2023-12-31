#include <stdio.h>
#include <stdlib.h>
#define uint unsigned int
#define uchar unsigned char

uint RealMap[17][17] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 0
  1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, // 1
  1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, // 2
  1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, // 3
  1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, // 4
  1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, // 5
  1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, // 6
  1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, // 7
  1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, // 8
  1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, // 9
  1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, // 10
  1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, // 11
  1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, // 12
  1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, // 13
  1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, // 14
  1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, // 15
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 // 16
};
// posX和posY表示实际格子的坐标，换算至RealMap只需pos*2+1
int RealPosX = 7, RealPosY = 0, RealCar = 1; // 车的位置和车的朝向
char SymbolWall = '#', SymbolUp = 'U', SymbolRight = 'R', SymbolDown = 'D', SymbolLeft = 'L', SymbolSpace = ' ';
void GoForwardV() {
  uchar flag = 1;
  switch (RealCar) {
    case 0: if (RealMap[RealPosX * 2][RealPosY * 2 + 1] == 0) {
        RealPosX--;
        flag = 0;
      }
      break;
    case 1: if (RealMap[RealPosX * 2 + 1][RealPosY * 2 + 2] == 0) {
        RealPosY++;
        flag = 0;
      }
      break;
    case 2: if (RealMap[RealPosX * 2 + 2][RealPosY * 2 + 1] == 0) {
        RealPosX++;
        flag = 0;
      }
      break;
    case 3: if (RealMap[RealPosX * 2 + 1][RealPosY * 2] == 0) {
        RealPosY--;
        flag = 0;
      }
      break;
    default: break;
  }
  if (flag) {
    printf("[Error] You hit the wall!\n");
    exit(0);
  }
}
void TurnLeftV() {
  RealCar = (RealCar + 3) % 4;
}
void TurnRightV() {
  RealCar = (RealCar + 1) % 4;
}
void TurnBackV() {
  RealCar = (RealCar + 2) % 4;
}
void ChangeSymbol(char wall, char up, char right, char down, char left, char space) {
  SymbolWall = wall;
  SymbolUp = up;
  SymbolRight = right;
  SymbolDown = down;
  SymbolLeft = left;
  SymbolSpace = space;
}
void ChangeStartPos(int x, int y) {
  RealPosX = x;
  RealPosY = y;
}
void ChangeStartDirection(int dir) {
  RealCar = dir;
}
/**
 * 获取车的dir方向的红外传感器的值
 * @param  dir 方向 | 0 - 前 | 1 - 右 | 2 - 后 | 3 - 左
 * @return     红外传感器的值 0 - 无障碍物 1 - 有障碍物
 */
uchar getIR(uchar dir) {
  switch ((dir + RealCar) % 4) {
    case 0: return RealMap[RealPosX * 2][RealPosY * 2 + 1];
    case 1: return RealMap[RealPosX * 2 + 1][RealPosY * 2 + 2];
    case 2: return RealMap[RealPosX * 2 + 2][RealPosY * 2 + 1];
    case 3: return RealMap[RealPosX * 2 + 1][RealPosY * 2];
    default: return 1;
  }
}
/**
 * 打印地图
 */
void printMap() {
  RealMap[RealPosX * 2 + 1][RealPosY * 2 + 1] = 2; // 将车的位置标记为2
  // 打印地图
  for (int i = 0; i < 17; i++) {
    for (int j = 0; j < 17; j++) {
      if (RealMap[i][j] == 1) printf("%c", SymbolWall);
      else if (RealMap[i][j] == 2) {
        switch (RealCar) {
          case 0: printf("%c", SymbolUp);
            break;
          case 1: printf("%c", SymbolRight);
            break;
          case 2: printf("%c", SymbolDown);
            break;
          case 3: printf("%c", SymbolLeft);
            break;
        }
      }
      else printf("%c", SymbolSpace);
    }
    printf("\n");
  }
  printf("\n");
  RealMap[RealPosX * 2 + 1][RealPosY * 2 + 1] = 0; // 将车的位置标记为0
}

int main() {
  printMap();
  return 0;
}

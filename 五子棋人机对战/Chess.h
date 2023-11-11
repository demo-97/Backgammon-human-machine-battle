#pragma once
#include <graphics.h>//easyx图形库的头文件
#include <vector>
using namespace std;

//表示落子位置
struct ChessPos {
	int row;
	int col;
	ChessPos(int r = 0, int c = 0) : row(r), col(c) {}
};

typedef enum {
	CHESS_WHITE = -1,//白棋
	CHESS_BLACK = 1 //黑棋
}chess_kind_t;

class Chess
{
public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize);
	void init();
	bool clickBoard(int x, int y, ChessPos* pos);
	void chessDown(ChessPos *pos, chess_kind_t kind);
	int getGradeSize();//获取棋盘大小（13，15，19）

	//获取指定位置是黑棋白棋or空白
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);
	bool checkOver();//检查棋局是否结束

private:
	IMAGE chessBlackImg;//黑棋棋子
	IMAGE chessWhiteImg;//白棋棋子
	int gradeSize;//棋盘大小
	int margin_x;//棋盘左侧边界
	int margin_y;//棋盘顶部边界
	float chessSize;//棋子大小（棋盘小方格大小）

	//存储当前棋局分布数据 0：空白 1：黑子 -1：白子
	vector<vector<int>> chessMap;

	//现在该谁下棋
	bool playerFlag;//true：该黑走 false：该白走

	void updateGameMap(ChessPos *pos);

	bool checkWin();

	ChessPos lastPos;//最近落子点位置
};



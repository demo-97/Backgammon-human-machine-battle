#pragma once
#include <graphics.h>//easyxͼ�ο��ͷ�ļ�
#include <vector>
using namespace std;

//��ʾ����λ��
struct ChessPos {
	int row;
	int col;
	ChessPos(int r = 0, int c = 0) : row(r), col(c) {}
};

typedef enum {
	CHESS_WHITE = -1,//����
	CHESS_BLACK = 1 //����
}chess_kind_t;

class Chess
{
public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize);
	void init();
	bool clickBoard(int x, int y, ChessPos* pos);
	void chessDown(ChessPos *pos, chess_kind_t kind);
	int getGradeSize();//��ȡ���̴�С��13��15��19��

	//��ȡָ��λ���Ǻ������or�հ�
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);
	bool checkOver();//�������Ƿ����

private:
	IMAGE chessBlackImg;//��������
	IMAGE chessWhiteImg;//��������
	int gradeSize;//���̴�С
	int margin_x;//�������߽�
	int margin_y;//���̶����߽�
	float chessSize;//���Ӵ�С������С�����С��

	//�洢��ǰ��ֲַ����� 0���հ� 1������ -1������
	vector<vector<int>> chessMap;

	//���ڸ�˭����
	bool playerFlag;//true���ú��� false���ð���

	void updateGameMap(ChessPos *pos);

	bool checkWin();

	ChessPos lastPos;//������ӵ�λ��
};



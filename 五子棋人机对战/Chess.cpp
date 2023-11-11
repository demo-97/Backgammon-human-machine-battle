#include "Chess.h"
#include <math.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include <conio.h>

//easyx2018��֧��PNG��ʽ��ͼƬ����������ע�͵��ˣ�������JPG��ʽ��ͼƬ

//void putimagePNG(int x, int y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
//{
//	// ������ʼ��
//	DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
//	DWORD* draw = GetImageBuffer();
//	DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
//	int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
//	int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
//	int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
//	int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
//	int dstX = 0;    //���Դ������صĽǱ�
//
//	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
//	for (int iy = 0; iy < picture_height; iy++)
//	{
//		for (int ix = 0; ix < picture_width; ix++)
//		{
//			int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
//			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
//			int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
//			int sg = ((src[srcX] & 0xff00) >> 8);   //G
//			int sb = src[srcX] & 0xff;              //B
//			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
//			{
//				dstX = (ix + x) + (iy + y) * graphWidth; //���Դ������صĽǱ�
//				int dr = ((dst[dstX] & 0xff0000) >> 16);
//				int dg = ((dst[dstX] & 0xff00) >> 8);
//				int db = dst[dstX] & 0xff;
//				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
//					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
//					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
//			}
//		}
//	}
//}
Chess::Chess(int gradeSize, int marginX, int marginY, float chessSize)
{
	this->gradeSize = gradeSize;
	this->margin_x = marginX;
	this->margin_y = marginY;
	this->chessSize = chessSize;
	playerFlag = CHESS_BLACK;
	vector<int> row(gradeSize, 0);
	for (int i = 0; i < gradeSize; i++) chessMap.push_back(row);
}

void Chess::init()
{
	//������Ϸ����
	initgraph(897, 895);
	//initgraph(897, 895, SHOWCONSOLE);//��ʾ����̨

	//��ʾ����ͼƬ
	loadimage(0, L"res/����2.jpg");

	//���ſ�ʼ��ʾ��
	mciSendString(L"play res/start.wav", 0, 0, 0);

	//���غ���Ͱ������ӵ�ͼƬ
	loadimage(&chessBlackImg, L"res/black.jpg", chessSize, chessSize, true);//true�ȱ�����
	loadimage(&chessWhiteImg, L"res/white.jpg", chessSize, chessSize, true);


	//��������
	for (int i = 0; i < gradeSize; i++) {
		for (int j = 0; j < gradeSize; j++) {
			chessMap[i][j] = 0;
		}
	}
	playerFlag = true;
}

bool Chess::clickBoard(int x, int y, ChessPos * pos)
{	
	int col = (x - margin_x) / chessSize;
	int row = (y - margin_y) / chessSize;
	int leftTopPosX = margin_x + chessSize * col;
	int leftTopPosY = margin_y + chessSize * row;
	int offset = chessSize * 0.4;

	int len;
	//���Ͻ�
	len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
	if (len < offset) {
		pos->row = row;
		pos->col = col;
		if (chessMap[pos->row][pos->col] == 0) {
			return true;
		}
		else return false;
	}
	//���Ͻ�
	len = sqrt((leftTopPosX + chessSize - x) * (leftTopPosX + chessSize - x) +
		(y - leftTopPosY) * (y - leftTopPosY));
	if (len < offset) {
		pos->row = row;
		pos->col = col + 1;
		if (chessMap[pos->row][pos->col] == 0) {
			return true;
		}
		else return false;
	}
	//���½�
	len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + 
		(leftTopPosY + chessSize - y) * (leftTopPosY + chessSize - y));
	if (len < offset) {
		pos->row = row + 1;
		pos->col = col;
		if (chessMap[pos->row][pos->col] == 0) {
			return true;
		}
		else return false;
	}
	//���½�
	len = sqrt((leftTopPosX + chessSize - x) * (leftTopPosX + chessSize - x) +
		(leftTopPosY + chessSize - y) * (leftTopPosY + chessSize - y));
	if (len < offset) {
		pos->row = row + 1;
		pos->col = col + 1;
		if (chessMap[pos->row][pos->col] == 0) {
			return true;
		}
		else return false;
	}
	return false;
}

void Chess::chessDown(ChessPos * pos, chess_kind_t kind)
{
	mciSendString(L"play res/down8.WAV", 0, 0, 0);
	int x = margin_x + chessSize * pos->col - 0.5 * chessSize;
	int y = margin_y + chessSize * pos->row - 0.5 * chessSize;
	if (kind == CHESS_WHITE) {
		//printf("%d,%d,white\n", pos->row, pos->col);
		putimage(x, y, &chessWhiteImg);
	}
	else {
		//printf("%d,%d,black\n", pos->row, pos->col);
		putimage(x, y, &chessBlackImg);
	}
	updateGameMap(pos);
}

int Chess::getGradeSize()
{
	return gradeSize;
}

int Chess::getChessData(ChessPos * pos)
{
	return chessMap[pos->row][pos->col];
}

int Chess::getChessData(int row, int col)
{
	return chessMap[row][col];
}

bool Chess::checkOver()
{
	if (checkWin()) {
		//
		Sleep(1500);
		if (playerFlag == false) {
			mciSendString(L"play res/����.mp3", 0, 0, 0);
			loadimage(0, L"res/ʤ��.jpg");
		}
		else {
			mciSendString(L"play res/ʧ��.mp3", 0, 0, 0);
			loadimage(0, L"res/ʧ��.jpg");
		}
		_getch();//��ͣ
		return true;
	}
	return false;
}

void Chess::updateGameMap(ChessPos * pos)
{
	lastPos = *pos;
	chessMap[pos->row][pos->col] = playerFlag ? CHESS_BLACK : CHESS_WHITE;
	playerFlag = !playerFlag;
}

bool Chess::checkWin()
{
	int row = lastPos.row;
	int col = lastPos.col;
	//for (int i = -1; i < )

	//ˮƽ����
	for (int i = 0; i < 5; i++) {
		//���ڵ�i��
		if (col - i >= 0 && col - i + 4 < gradeSize &&
			chessMap[row][col - i] == chessMap[row][col - i + 1] &&
			chessMap[row][col - i] == chessMap[row][col - i + 2] && 
			chessMap[row][col - i] == chessMap[row][col - i + 3] && 
			chessMap[row][col - i] == chessMap[row][col - i + 4]) {
			return true;
		}
	}

	//��ֱ����
	for (int i = 0; i < 5; i++) {
		//���ڵ�i��
		if (row - i >= 0 && row - i + 4 < gradeSize &&
			chessMap[row - i][col] == chessMap[row - i + 1][col] &&
			chessMap[row - i][col] == chessMap[row - i + 2][col] &&
			chessMap[row - i][col] == chessMap[row - i + 3][col] &&
			chessMap[row - i][col] == chessMap[row - i + 4][col]) {
			return true;
		}
	}

	//�������Ϸ���
	for (int i = 0; i < 5; i++) {
		//���ڵ�i��
		if (row + i - 4 >= 0 && row + i < gradeSize &&
			col - i >= 0 && col - i + 4 < gradeSize &&
			chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1] &&
			chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2] &&
			chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3] &&
			chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4]) {
			return true;
		}
	}
	//�������·���
	for (int i = 0; i < 5; i++) {
		//���ڵ�i��
		if (row - i >= 0 && row - i + 4 < gradeSize &&
			col - i >= 0 && col - i + 4 < gradeSize &&
			chessMap[row - i][col - i] == chessMap[row - i + 1][col - i + 1] &&
			chessMap[row - i][col - i] == chessMap[row - i + 2][col - i + 2] &&
			chessMap[row - i][col - i] == chessMap[row - i + 3][col - i + 3] &&
			chessMap[row - i][col - i] == chessMap[row - i + 4][col - i + 4]) {
			return true;
		}
	}
	return false;
}



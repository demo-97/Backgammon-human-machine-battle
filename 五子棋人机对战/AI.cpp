#include "AI.h"

void AI::init(Chess * chess)
{
	this->chess = chess;
	int size = chess->getGradeSize();
	vector<int> row(size, 0);
	for (int i = 0; i < size; i++) {
		scoreMap.push_back(row);
	}
}

void AI::go()
{
	ChessPos pos = think();
	Sleep(1000);//��װ˼��
	chess->chessDown(&pos, CHESS_WHITE);
}

void AI::calculateScore()
{
	int personNum = 0;//���ַ������壩�ж��ٸ���������
	int aiNum = 0;//ai�������壩�ж��ٸ���������
	int emptyNum = 0;
	//������������
	for (int i = 0; i < scoreMap.size(); i++) {
		for (int j = 0; j < scoreMap[i].size(); j++) {
			scoreMap[i][j] = 0;
		}
	}

	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			//��ÿ�������
			if (chess->getChessData(row, col)) continue;
	
			for (int y = -1; y <= 0; y++) {
				for (int x = -1; x <= 1; x++) {
					//if (y == 0 && x == 0) continue;
					if (y == 0 && x != 1) continue;
					personNum = 0;
					aiNum = 0;
					emptyNum = 0;
					//��������ڸ�λ�����ӣ��ṹ��ʲô����
					for (int i = 1; i <= 4; i++) {
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size) {
							if (chess->getChessData(curRow, curCol) == 1) personNum++;
							else if (chess->getChessData(curRow, curCol) == 0) {
								emptyNum++;
								break;
							}
							else break;
						}
						else break;
					}
					//�������
					for (int i = 1; i <= 4; i++) {
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size) {
							if (chess->getChessData(curRow, curCol) == 1) personNum++;
							else if (chess->getChessData(curRow, curCol) == 0) {
								emptyNum++;
								break;
							}
							else break;
						}
						else break;
					}

					if (personNum == 1) {//��2
						scoreMap[row][col] += 10;
					}
					else if (personNum == 2) {
						if (personNum == 1) {
							scoreMap[row][col] += 30;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 40;
						}
					}
					else if (personNum == 3) {
						if (emptyNum == 1) {
							scoreMap[row][col] += 60;
						}
						else if (emptyNum == 2) {
							scoreMap[row][col] += 200;
						}
					}
					else if (personNum == 4) {
						scoreMap[row][col] += 20000;
					}

					//��������ڸ�λ�����ӣ��ṹ��ʲôģ��
					emptyNum = 0;
					for (int i = 1; i <= 4; i++) {
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size) {
							if (chess->getChessData(curRow, curCol) == -1) aiNum++;
							else if (chess->getChessData(curRow, curCol) == 0) {
								emptyNum++;
								break;
							}
							else break;
						}
						else break;
					}
					//�������
					for (int i = 1; i <= 4; i++) {
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size) {
							if (chess->getChessData(curRow, curCol) == -1) aiNum++;
							else if (chess->getChessData(curRow, curCol) == 0) {
								emptyNum++;
								break;
							}
							else break;
						}
						else break;
					}

					if (aiNum == 0) {
						scoreMap[row][col] += 5;
					}
					else if (aiNum == 1) {
						scoreMap[row][col] += 10;
					}
					else if (aiNum == 2) {
						if (emptyNum == 1) scoreMap[row][col] += 25;
						else if (emptyNum == 2) scoreMap[row][col] += 50;
					}
					else if (aiNum == 3) {
						if (emptyNum == 1) scoreMap[row][col] += 55;
						else if (emptyNum == 2) scoreMap[row][col] += 10000;
					}
					else if (aiNum >= 4) {
						scoreMap[row][col] += 30000;
					}
				}
			}
		}
	}
}

ChessPos AI::think()
{
	calculateScore();

	vector<ChessPos> maxPoints;
	int maxScore = 0;
	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			if (chess->getChessData(row, col) == 0) {
				if (scoreMap[row][col] > maxScore) {
					maxScore = scoreMap[row][col];
					maxPoints.clear();
					maxPoints.push_back(ChessPos(row, col));
				}
				else if (scoreMap[row][col] == maxScore) {
					maxPoints.push_back(ChessPos(row, col));
				}
			}
		} 
	}
	int index = rand() % maxPoints.size();
	return maxPoints[index];
}

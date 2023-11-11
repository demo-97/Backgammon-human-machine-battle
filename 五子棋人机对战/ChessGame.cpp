#include "ChessGame.h"

ChessGame::ChessGame(Man * man, AI * ai, Chess * chess) :man(man), ai(ai), chess(chess)
{
	man->init(chess);
	ai->init(chess);
}

//开始
void ChessGame::play()
{
	chess->init();
	while (1) {
		//棋手先走
		man->go();
		if (chess->checkOver()) {
			chess->init();
			continue;
		}
		//AI走
		ai->go();
		if (chess->checkOver()) {
			chess->init();
			continue;
		}
	}
}

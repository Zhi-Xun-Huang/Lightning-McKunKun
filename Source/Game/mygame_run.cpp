#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <iostream>


using namespace game_framework;

int mckun = 0; // state of mckunkun
int linear = 0;  
bool forcestop = false;
int keepmove = 0;
int bg_linear = 0;
bool bg_en = true;
bool w_pressed = false;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{	


	if (keepmove == 1) {
		int top = character[mckun].Top();
		top -= linear;
		if (forcestop == false && linear <= 30)linear += 3;
		character[mckun].SetTopLeft(character[mckun].Left(), top);
	}

	if (keepmove == 2) {
		int left = character[mckun].Left();
		left -= linear;
		if (forcestop == false && linear <= 30)linear += 3;
		character[mckun].SetTopLeft(left, character[mckun].Top());
	}

	if (keepmove == 3) {
		int top = character[mckun].Top();
		top += linear;
		if (forcestop == false && linear <= 30)linear += 3;
		character[mckun].SetTopLeft(character[mckun].Left(), top);
	}

	if (keepmove == 4) {
		int left = character[mckun].Left();
		left += linear;
		if (forcestop == false && linear <= 30)linear += 3;
		character[mckun].SetTopLeft(left, character[mckun].Top());
	}

	if (forcestop == true) {
		if (linear == 0){ 
			forcestop = false;
			keepmove = 0;
		}
		if (linear != 0) linear -= 1;
	}

	if (w_pressed == true) {
		bg_en = false;
		if (bg_linear >= 10) bg_linear -= 1;
	}

	if (w_pressed == false) {
		if (bg_linear >= 500) bg_en = true;
		else bg_linear += 5;
	}

	background[0].SetAnimation(bg_linear, bg_en);

}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	background[0].LoadBitmapByString({
		"resources/start/start000.bmp", "resources/start/start001.bmp",
		"resources/start/start002.bmp", "resources/start/start003.bmp",
		"resources/start/start004.bmp", "resources/start/start005.bmp",
		"resources/start/start006.bmp", "resources/start/start007.bmp",
		"resources/start/start008.bmp", "resources/start/start009.bmp",
		"resources/start/start010.bmp", "resources/start/start011.bmp",
		"resources/start/start012.bmp", "resources/start/start013.bmp",
		"resources/start/start014.bmp", "resources/start/start015.bmp",
		"resources/start/start016.bmp", "resources/start/start017.bmp",
		"resources/start/start018.bmp", "resources/start/start019.bmp",
		"resources/start/start020.bmp", "resources/start/start021.bmp",
		"resources/start/start022.bmp", "resources/start/start023.bmp",
		"resources/start/start024.bmp", "resources/start/start025.bmp",
		"resources/start/start026.bmp", "resources/start/start027.bmp",
		"resources/start/start028.bmp", "resources/start/start029.bmp",
		"resources/start/start030.bmp", "resources/start/start031.bmp",
		"resources/start/start032.bmp", "resources/start/start033.bmp",
		"resources/start/start034.bmp", "resources/start/start035.bmp",
		"resources/start/start036.bmp", "resources/start/start037.bmp",
		"resources/start/start038.bmp", "resources/start/start039.bmp",
		"resources/start/start040.bmp", "resources/start/start041.bmp",
		"resources/start/start042.bmp", "resources/start/start043.bmp",
		"resources/start/start044.bmp", "resources/start/start045.bmp",
		"resources/start/start046.bmp", "resources/start/start047.bmp",
		"resources/start/start048.bmp", "resources/start/start049.bmp",
		"resources/start/start050.bmp", "resources/start/start051.bmp",
		"resources/start/start052.bmp", "resources/start/start053.bmp",
		"resources/start/start054.bmp", "resources/start/start055.bmp",
		"resources/start/start056.bmp", "resources/start/start057.bmp",
		"resources/start/start058.bmp", "resources/start/start059.bmp",
		"resources/start/start060.bmp", "resources/start/start061.bmp",
		"resources/start/start062.bmp", "resources/start/start063.bmp",
		"resources/start/start064.bmp", "resources/start/start065.bmp",
		"resources/start/start066.bmp", "resources/start/start067.bmp",
		"resources/start/start068.bmp", "resources/start/start069.bmp",
		"resources/start/start070.bmp", "resources/start/start071.bmp",
		"resources/start/start072.bmp", "resources/start/start073.bmp",
		"resources/start/start074.bmp", "resources/start/start075.bmp",
		"resources/start/start076.bmp", "resources/start/start077.bmp",
		"resources/start/start078.bmp", "resources/start/start079.bmp",
	});
	background[0].SetTopLeft(-1000, 0);
	

	character[0].LoadBitmapByString({ 
		"resources/KUN00die.bmp",
		"resources/KUN01die.bmp",
		"resources/KUN02die.bmp",
		"resources/KUN03die.bmp",
		"resources/KUN04die.bmp",
		"resources/KUN05die.bmp",
		"resources/KUN06die.bmp",
		"resources/KUN07die.bmp",
		"resources/KUN08die.bmp",
		"resources/KUN09die.bmp",
		"resources/KUN10die.bmp",
		"resources/KUN11die.bmp",
		"resources/KUN12die.bmp",
		"resources/KUN13die.bmp",
		"resources/KUN14die.bmp",
		"resources/KUN15die.bmp",
		"resources/KUN16die.bmp",
		"resources/KUN17die.bmp",
		"resources/KUN18die.bmp",
		"resources/KUN19die.bmp",
		"resources/KUN20die.bmp",
		"resources/KUN21die.bmp",
		"resources/KUN22die.bmp",
		"resources/KUN23die.bmp"
		},RGB(255, 255, 255)
	);

	character[1].LoadBitmapByString({
		"resources/KUN24bb.bmp",
		"resources/KUN25bb.bmp",
		"resources/KUN26bb.bmp",
		"resources/KUN27bb.bmp",
		"resources/KUN28bb.bmp",
		"resources/KUN29bb.bmp",
		"resources/KUN30bb.bmp",
		"resources/KUN31bb.bmp",
		"resources/KUN32bb.bmp",
		"resources/KUN33bb.bmp",
		"resources/KUN34bb.bmp",
		"resources/KUN35bb.bmp"
		}, RGB(255, 255, 255)
	);

	character[2].LoadBitmapByString({
		"resources/KUN36run.bmp",
		"resources/KUN37run.bmp",
		"resources/KUN38run.bmp",
		"resources/KUN39run.bmp",
		"resources/KUN40run.bmp",
		"resources/KUN41run.bmp"
		}, RGB(255, 255, 255)
	);


	for (int i = 0; i < 3; i++) {
		character[i].SetTopLeft(750, 265);
		character[i].SetAnimation(100, false);
	}


}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{	


	if (nChar == 0x45) {
		if (mckun == 2) mckun = 0;
		else mckun += 1;
	}

	if (nChar == 0x57) {
		//keepmove = 1;
		w_pressed = true;
		bg_linear = 500;
		//linear = 0;
	}

	if (nChar == 0x41) {
		keepmove = 2;
		//linear = 0;
	}
		

	if (nChar == 0x53) {
		keepmove = 3;
		//linear = 0;
	}

	if (nChar == 0x44) {
		keepmove = 4;
		//linear = 0;
	}

	/*
	if (nChar == 0x57) { //W_up
		int top = character[mckun].Top();
		top -= 20;
		character[mckun].SetTopLeft(character[mckun].Left(), top);
	}

	if (nChar == 0x41) { //A_left
		int left = character[mckun].Left();
		left -= 20;
		character[mckun].SetTopLeft(left, character[mckun].Top());
	}

	if (nChar == 0x53) { //S_down
		int top = character[mckun].Top();
		top += 20;
		character[mckun].SetTopLeft(character[mckun].Left(), top);
	}

	if (nChar == 0x44) { //D_right
		int left = character[mckun].Left();
		left += 20;
		character[mckun].SetTopLeft(left, character[mckun].Top());
	}
	*/
	

}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 0x57 || nChar == 0x41 || nChar == 0x53 || nChar == 0x44) {
		forcestop = true;
		w_pressed = false;
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作53
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	background[0].ShowBitmap();
	character[mckun].ShowBitmap();
}
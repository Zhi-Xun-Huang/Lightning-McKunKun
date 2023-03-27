#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"


using namespace game_framework;

int mckun = 0; // state of mckunkun
int linear = 0;
bool forcestop = false;

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

	ball.SetTopLeft(ball.Left() + 1, character[mckun].Top());

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
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	background.LoadBitmapByString({ 
		"resources/phase11_background.bmp", 
		"resources/phase12_background.bmp", 
		"resources/phase21_background.bmp", 
		"resources/phase22_background.bmp", 
		"resources/phase31_background.bmp", 
		"resources/phase32_background.bmp",
		"resources/phase41_background.bmp",
		"resources/phase42_background.bmp",
		"resources/phase51_background.bmp",
		"resources/phase52_background.bmp",
		"resources/phase61_background.bmp",
		"resources/phase62_background.bmp",
	});
	background.SetTopLeft(0, 0);

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
		character[i].SetTopLeft(150, 265);
		character[i].SetAnimation(100, false);
	}

	chest_and_key.LoadBitmapByString({ "resources/chest.bmp", "resources/chest_ignore.bmp" }, RGB(255, 255, 255));
	chest_and_key.SetTopLeft(150, 430);

	bee.LoadBitmapByString({ "resources/bee_1.bmp", "resources/bee_2.bmp" });
	bee.SetTopLeft(462, 265);

	ball.LoadBitmapByString({ "resources/Basketball.bmp" }, RGB(255, 255, 255));
	ball.SetTopLeft(0, 0);

	for (int i = 0; i < 3; i++) {
		door[i].LoadBitmapByString({ "resources/door_close.bmp", "resources/door_open.bmp" }, RGB(255, 255, 255));
		door[i].SetTopLeft(462 - 100 * i, 265);
	}

}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{	

	if (nChar == 0x46) {
		//ball.SetTopLeft(character[mckun].Top(), character[mckun].Left());
		ball.ShowBitmap();
	}

	if (nChar == 0x45) {
		if (mckun == 2) mckun = 0;
		else mckun += 1;
	}

	if (nChar == 0x57) {
		keepmove = 1;
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
	background.ShowBitmap();
	character[mckun].ShowBitmap();
}


void CGameStateRun::show_text_by_phase() {
	CDC *pDC = CDDraw::GetBackCDC();
	CFont* fp;

	CTextDraw::ChangeFontLog(pDC, fp, 21, "微軟正黑體", RGB(0, 0, 0), 800);

	if (phase == 1 && sub_phase == 1) {
		CTextDraw::Print(pDC, 237, 128, "Current Speed:");
		CTextDraw::Print(pDC, 55, 163, "將灰色方格換成 resources 內的 giraffe.bmp 圖樣！");
		CTextDraw::Print(pDC, 373, 537, "按下 Enter 鍵來驗證");
	} else if (phase == 2 && sub_phase == 1) {
		CTextDraw::Print(pDC, 26, 128, "下一個階段，讓長頸鹿能夠透過上下左右移動到這個位置！");
		CTextDraw::Print(pDC, 373, 537, "按下 Enter 鍵來驗證");
	} else if (phase == 3 && sub_phase == 1) {
		CTextDraw::Print(pDC, 205, 128, "幫你準備了一個寶箱");
		CTextDraw::Print(pDC, 68, 162, "設計程式讓長頸鹿摸到寶箱後，將寶箱消失！");
		CTextDraw::Print(pDC, 68, 196, "記得寶箱要去背，使用 RGB(255, 255, 255)");
		CTextDraw::Print(pDC, 373, 537, "按下 Enter 鍵來驗證");
	} else if (phase == 4 && sub_phase == 1) {
		CTextDraw::Print(pDC, 173, 128, "幫你準備了一個蜜蜂好朋友");
		CTextDraw::Print(pDC, 89, 162, "已經幫它做了兩幀的動畫，讓它可以上下移動");
		CTextDraw::Print(pDC, 110, 196, "寫個程式來讓你的蜜蜂好朋友擁有動畫！");
		CTextDraw::Print(pDC, 373, 537, "按下 Enter 鍵來驗證");
	} else if (phase == 5 && sub_phase == 1) {
		CTextDraw::Print(pDC, 173, 128, "幫你準備了三扇門");
		CTextDraw::Print(pDC, 89, 162, "設計程式讓長頸鹿摸到門之後，門會打開");
		CTextDraw::Print(pDC, 373, 537, "按下 Enter 鍵來驗證");
	} else if (phase == 6 && sub_phase == 1) {
		CTextDraw::Print(pDC, 173, 128, "幫你準備了一顆會倒數的球");
		CTextDraw::Print(pDC, 89, 162, "設計程式讓球倒數，然後顯示 OK 後停止動畫");
		CTextDraw::Print(pDC, 373, 537, "按下 Enter 鍵來驗證");
	} else if (sub_phase == 2) {
		CTextDraw::Print(pDC, 268, 128, "完成！");
	}

	CDDraw::ReleaseBackCDC();
}
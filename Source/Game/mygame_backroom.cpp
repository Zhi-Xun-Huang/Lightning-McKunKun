#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>
#include <random>
#include <windows.h>

using namespace game_framework;
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateBackroom::CGameStateBackroom(CGame* g) : CGameState(g)
{

}

void CGameStateBackroom::OnMove() {

}
void CGameStateBackroom::OnInit()
{

	backroom.LoadBitmapByString({
		"resources/backroom.bmp"
	});

	for (int m = 0; m < 5; m++) {
		obunga[m].LoadBitmapByString({
			"resources/obunga/Obunga00.bmp",
			"resources/obunga/Obunga01.bmp",
			"resources/obunga/Obunga02.bmp",
			"resources/obunga/Obunga03.bmp",
			"resources/obunga/Obunga04.bmp",
			"resources/obunga/Obunga05.bmp",
			"resources/obunga/Obunga06.bmp",
			"resources/obunga/Obunga07.bmp",
			"resources/obunga/Obunga08.bmp",
			"resources/obunga/Obunga09.bmp",
			"resources/obunga/Obunga10.bmp",
			"resources/obunga/Obunga11.bmp",
			"resources/obunga/Obunga12.bmp",
			"resources/obunga/Obunga13.bmp",
			"resources/obunga/Obunga14.bmp",
			"resources/obunga/Obunga15.bmp",
			"resources/obunga/Obunga16.bmp",
			"resources/obunga/Obunga17.bmp",
			"resources/obunga/Obunga18.bmp",
			"resources/obunga/Obunga19.bmp",
			"resources/obunga/Obunga20.bmp",
			"resources/obunga/Obunga21.bmp",
			"resources/obunga/Obunga22.bmp",
			"resources/obunga/Obunga23.bmp",
			"resources/obunga/Obunga24.bmp",
			"resources/obunga/Obunga25.bmp",
			"resources/obunga/Obunga26.bmp",
			"resources/obunga/Obunga27.bmp",
			"resources/obunga/Obunga28.bmp",
			"resources/obunga/Obunga29.bmp",
			"resources/obunga/Obunga30.bmp" }, RGB(0, 0, 0));

		obunga[m].SetAnimation(50, false);
	}
}

void CGameStateBackroom::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作53
{
	GetCursorPos(&p);
	HWND hwnd = FindWindowA(NULL, "LMKK");
	ScreenToClient(hwnd, &p);
	Xmouse = p.x;
	Ymouse = p.y;

}

void CGameStateBackroom::OnBeginState()
{

}

void CGameStateBackroom::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateBackroom::OnLButtonDown(UINT nFlags, CPoint point)
{
}

void CGameStateBackroom::OnShow()
{
CAudio* audio = CAudio::Instance();
	if (sleep) {
		Sleep(3500);
		sleep = false;
	}
	backroom.ShowBitmap();
	if (musicflag) {
		audio->Pause();
		audio->Play(6, true);
		musicflag = false;
	}
	CDC* pDC = CDDraw::GetBackCDC();
	CFont* fp;
	CTextDraw::ChangeFontLog(pDC, fp, 24, "Consolas", RGB(0, 0, 0), 800);
	CTextDraw::Print(pDC, 150, 50, "X:");
	CTextDraw::Print(pDC, 250, 50, to_string(Xmouse));
	CTextDraw::Print(pDC, 150, 80, "Y:");
	CTextDraw::Print(pDC, 250, 80, to_string(Ymouse));
	CDDraw::ReleaseBackCDC();
}
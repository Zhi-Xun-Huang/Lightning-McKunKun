#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>
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
	black.LoadBitmapByString({
	"resources/black.bmp"
	});

	backroom.LoadBitmapByString({
		"resources/backroom.bmp"
	});

	backroomend.LoadBitmapByString({
		"resources/backroomend.bmp"
	});

	kunkun.LoadBitmapByString({
		"resources/kunDie/KUN00die.bmp",
		"resources/kunDie/KUN01die.bmp",
		"resources/kunDie/KUN02die.bmp",
		"resources/kunDie/KUN03die.bmp",
		"resources/kunDie/KUN04die.bmp",
		"resources/kunDie/KUN05die.bmp",
		"resources/kunDie/KUN06die.bmp",
		"resources/kunDie/KUN07die.bmp",
		"resources/kunDie/KUN08die.bmp",
		"resources/kunDie/KUN09die.bmp",
		"resources/kunDie/KUN10die.bmp",
		"resources/kunDie/KUN11die.bmp",
		"resources/kunDie/KUN12die.bmp",
		"resources/kunDie/KUN13die.bmp",
		"resources/kunDie/KUN14die.bmp",
		"resources/kunDie/KUN15die.bmp",
		"resources/kunDie/KUN16die.bmp",
		"resources/kunDie/KUN17die.bmp",
		"resources/kunDie/KUN18die.bmp",
		"resources/kunDie/KUN19die.bmp",
		"resources/kunDie/KUN20die.bmp",
		"resources/kunDie/KUN21die.bmp",
		"resources/kunDie/KUN22die.bmp",
		"resources/kunDie/KUN23die.bmp"
		}, RGB(255, 255, 255)
	);
	kunkun.SetTopLeft(300, 400);
	kunkun.SetAnimation(70, false);
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
		black.ShowBitmap();
		audio->Pause();
		audio->Play(5, true);
		Sleep(3500);
		sleep = false;
	}
	else {
		if (finalflag) {
			sprintf(msg, "Game fatal error:\n\n%s\n\nFile: %s\n\nLine: %d"
				"\n\n(PRESS RETRY TO DO NOTHING USEFUL, "
				"YOU CAN'T SAVE HIM.)"
				"\n(PRESS CANCEL WILL DO NOTHING AS WELL.)",
				"KUNKUN WILL NEVER COME BACK.","NONONONONONONONONONONONONONONONONONONONONO", 0000);
			id = AfxMessageBox(msg, MB_RETRYCANCEL);
			finalflag = false;
		}
		backroom.ShowBitmap();
		if (musicflag) {
			for (int i = 0; i < 5; i++) audio->Stop(i);
			audio->Play(6, true);
			musicflag = false;
		}
		if (kunkun.GetSelectShowBitmap() == 0 && countflag) {
			destroycount += 1;
			countflag = false;
		}
		if (kunkun.GetSelectShowBitmap() == 11) {
			countflag = true;
		}
		if (destroycount >= 10) {
			backroomend.ShowBitmap();
		}
		if (destroycount == 15) {
			PostQuitMessage(0);
		}
		kunkun.ShowBitmap();
	}
	
}
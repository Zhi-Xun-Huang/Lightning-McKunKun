#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
	
}

void CGameStateInit::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(0, "Start Initialize...");	// 一開始的loading進度為0%
	Sleep(200);

	load_background();

	for (int i = 1; i < 100; i += 5) {
		ShowInitProgress(i, "Loading .");
		ShowInitProgress(i, "Loading ..");
		ShowInitProgress(i, "Loading ...");
		ShowInitProgress(i, "Loading ....");
		ShowInitProgress(i, "Loading .....");
	}
	
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//

	CAudio* audio = CAudio::Instance();
	audio->Load(0, "resources/audio/JNTM.wav");
	audio->Load(1, "resources/audio/NGM.wav");
	audio->Load(2, "resources/audio/Rrrrr.wav");
	audio->Load(3, "resources/audio/NMson.wav");
	audio->Load(4, "resources/audio/UCHMJ.wav");
	audio->Load(5, "resources/audio/Freeze.wav");
	audio->Load(6, "resources/audio/Backroom.wav");
	audio->Load(7, "resources/audio/NiceBall.wav");
	audio->Load(8, "resources/audio/Story.wav");
	audio->Load(9, "resources/audio/+1.wav");
	audio->Load(10, "resources/audio/Phase.wav");
}

void CGameStateInit::OnBeginState()
{
	
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{	
	flag = true;
}


void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
}

void CGameStateInit::OnShow()
{
	CAudio* audio = CAudio::Instance();
	if (flag) {
		if (count == 0) audio->Play(8, false);
		if (count < 1200) story.SelectShowBitmap(0);
		story.ShowBitmap();
		count++;
	}
	else background.ShowBitmap();
	if (count >= 1200) {
		story.SelectShowBitmap(1);
	}
	if (count > 2000) {
		count = 0;
		audio->Pause();
		GotoGameState(GAME_STATE_RUN);       // 切換至GAME_STATE_RUN
	}
}

void CGameStateInit::load_background() {
	story.LoadBitmapByString({ "resources/story.bmp", "resources/info.bmp" });
	story.SetTopLeft(0, 0);
	background.LoadBitmapByString({ "resources/LMKK1.bmp", "resources/LMKK2.bmp" });
	background.SetTopLeft(0, 0);
	background.SetAnimation(1000, false);
}
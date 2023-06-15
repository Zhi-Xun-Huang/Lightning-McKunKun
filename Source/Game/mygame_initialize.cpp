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
		ShowInitProgress(i, "Loading.");
		ShowInitProgress(i, "Loading..");
		ShowInitProgress(i, "Loading...");
		ShowInitProgress(i, "Loading....");
		ShowInitProgress(i, "Loading.....");
	}
	
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//

	CAudio* audio = CAudio::Instance();
	audio->Load(0, "resources/JNTM.wav");
	audio->Load(1, "resources/NGM.wav");
	audio->Load(2, "resources/Rrrrr.wav");
	audio->Load(3, "resources/NMson.wav");
	audio->Load(4, "resources/UCHMJ.wav");
	audio->Load(5, "resources/Freeze.wav");
	audio->Load(6, "resources/Backroom.wav");
	audio->Load(7, "resources/NiceBall.wav");
	audio->Load(8, "resources/Story.wav");
}

void CGameStateInit::OnBeginState()
{
	
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{	
	CAudio* audio = CAudio::Instance();
	flag = true;
	if (count >= 1200) { 
		count = 0;
		GotoGameState(GAME_STATE_RUN);       // 切換至GAME_STATE_RUN
	}		
}


void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
}

void CGameStateInit::OnShow()
{
	CAudio* audio = CAudio::Instance();
	if (flag) {
		if (count == 0) audio->Play(8, false);
		story.ShowBitmap();
		count++;
	}
	else background.ShowBitmap();
}

void CGameStateInit::load_background() {
	story.LoadBitmapByString({ "resources/story.bmp" });
	story.SetTopLeft(0, 0);
	background.LoadBitmapByString({ "resources/LMKK1.bmp", "resources/LMKK2.bmp" });
	background.SetTopLeft(0, 0);
	background.SetAnimation(1000, false);
}
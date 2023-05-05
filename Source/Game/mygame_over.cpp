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
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g): CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	
}

void CGameStateOver::OnBeginState()
{
}

void CGameStateOver::OnInit()
{
	background.LoadBitmapByString({ "resources/gameover.bmp" });
	background.SetTopLeft(0, 0);
	character.LoadBitmapByString({
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
	character.SetTopLeft(20, 400);
	character.SetAnimation(100, false);
}

void CGameStateOver::OnShow()
{
	background.ShowBitmap();
	character.ShowBitmap();
	
}

void CGameStateOver::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 0x0D) {
		GotoGameState(GAME_STATE_RUN);
		CAudio* audio = CAudio::Instance();
		audio->Stop(1);
		audio->Play(0, true);
	}
}


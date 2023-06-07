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
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
	
}

void CGameStateInit::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(0, "Start Initialize...");	// �@�}�l��loading�i�׬�0%
	Sleep(200);

	load_background();

	ShowInitProgress(66, "Initialize...");
	Sleep(200);
	//
	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
	//

	CAudio* audio = CAudio::Instance();
	audio->Load(0, "resources/JNTM.wav");
	audio->Load(1, "resources/NGM.wav");
	audio->Load(2, "resources/Rrrrr.wav");
	audio->Load(3, "resources/NMson.wav");
	audio->Load(4, "resources/UCHMJ.wav");
	audio->Load(5, "resources/Backroom.wav");
	audio->Load(6, "resources/Freeze.wav");
	audio->Load(7, "resources/NiceBall.wav");
}

void CGameStateInit::OnBeginState()
{
	
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
	CAudio* audio = CAudio::Instance();
	audio->Play(0, true);
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
}

void CGameStateInit::OnShow()
{
	background.ShowBitmap();
}

void CGameStateInit::load_background() {
	background.LoadBitmapByString({ "resources/LMKK1.bmp", "resources/LMKK2.bmp" });
	background.SetTopLeft(0, 0);
	background.SetAnimation(1000, false);
}
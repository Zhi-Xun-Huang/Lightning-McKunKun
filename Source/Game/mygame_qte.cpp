#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <string>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <random>

using namespace std;
using namespace game_framework;
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

int Random(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> range(min, max);
	return range(gen);
}

CGameStateQte::CGameStateQte(CGame* g) : CGameState(g)
{

}

void CGameStateQte::OnInit()
{
	qte[0].LoadBitmapByString({ "resources/qte/qte_bg.bmp" });
	qte[1].LoadBitmapByString({ "resources/qte/qte_po.bmp" });
	qte[2].LoadBitmapByString({ "resources/qte/qte_st.bmp" });
	background.LoadBitmapByString({ "resources/niceball/NiceBall00.bmp", "resources/niceball/NiceBall01.bmp", "resources/niceball/NiceBall02.bmp",
									"resources/niceball/NiceBall03.bmp", "resources/niceball/NiceBall04.bmp", "resources/niceball/NiceBall05.bmp",
									"resources/niceball/NiceBall06.bmp", "resources/niceball/NiceBall07.bmp", "resources/niceball/NiceBall08.bmp",
									"resources/niceball/NiceBall09.bmp", "resources/niceball/NiceBall10.bmp", "resources/niceball/NiceBall11.bmp",
									"resources/niceball/NiceBall12.bmp", "resources/niceball/NiceBall13.bmp", "resources/niceball/NiceBall14.bmp",
									"resources/niceball/NiceBall15.bmp", "resources/niceball/NiceBall16.bmp", "resources/niceball/NiceBall17.bmp",
									"resources/niceball/NiceBall18.bmp", "resources/niceball/NiceBall19.bmp", "resources/niceball/NiceBall20.bmp",
									"resources/niceball/NiceBall21.bmp", "resources/niceball/NiceBall22.bmp", "resources/niceball/NiceBall23.bmp",
									"resources/niceball/NiceBall24.bmp", "resources/niceball/NiceBall25.bmp", "resources/niceball/NiceBall26.bmp",
									"resources/niceball/NiceBall27.bmp", "resources/niceball/NiceBall28.bmp", "resources/niceball/NiceBall29.bmp",
									"resources/niceball/NiceBall29.bmp", "resources/niceball/NiceBall30.bmp", "resources/niceball/NiceBall31.bmp",
									"resources/niceball/NiceBall34.bmp", "resources/niceball/NiceBall33.bmp", "resources/niceball/NiceBall34.bmp",
									"resources/niceball/NiceBall35.bmp", "resources/niceball/NiceBall36.bmp", "resources/niceball/NiceBall37.bmp",
									"resources/niceball/NiceBall38.bmp", "resources/niceball/NiceBall39.bmp", "resources/niceball/NiceBall40.bmp",
									"resources/niceball/NiceBall41.bmp", "resources/niceball/NiceBall42.bmp", "resources/niceball/NiceBall43.bmp",
									"resources/niceball/NiceBall44.bmp", "resources/niceball/NiceBall45.bmp", "resources/niceball/NiceBall46.bmp",
									"resources/niceball/NiceBall47.bmp", "resources/niceball/NiceBall48.bmp", "resources/niceball/NiceBall49.bmp",
									"resources/niceball/NiceBall50.bmp", "resources/niceball/NiceBall51.bmp", "resources/niceball/NiceBall52.bmp",
									"resources/niceball/NiceBall53.bmp", "resources/niceball/NiceBall54.bmp", "resources/niceball/NiceBall55.bmp",
									"resources/niceball/NiceBall56.bmp", "resources/niceball/NiceBall57.bmp", "resources/niceball/NiceBall58.bmp",
									"resources/niceball/NiceBall59.bmp", "resources/niceball/NiceBall60.bmp", "resources/niceball/NiceBall61.bmp",
									"resources/niceball/NiceBall62.bmp", "resources/niceball/NiceBall63.bmp", "resources/niceball/NiceBall64.bmp",
									"resources/niceball/NiceBall65.bmp", "resources/niceball/NiceBall66.bmp", "resources/niceball/NiceBall67.bmp",
									"resources/niceball/NiceBall68.bmp", "resources/niceball/NiceBall69.bmp", "resources/niceball/NiceBall70.bmp" 
									}, RGB(0, 0, 0));
	background.SetTopLeft(0, 0);
	background.SetAnimation(33, true);
}

void CGameStateQte::OnBeginState()
{
	background.ToggleAnimation();
}

void CGameStateQte::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateQte::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CAudio* audio = CAudio::Instance();

	if (nChar == 0x20) {
		if (background.GetSelectShowBitmap() >= 40 && background.GetSelectShowBitmap() <= 50) {  // SpaceBar
			GotoGameState(GAME_STATE_RUN);
			audio->Stop(7);
			audio->Play(2, false);
		}
		else {
			if (Random(1, 100) == 10) {
				sprintf(msg, "Game fatal error:\n\n%s\n\nFile: %s\n\nLine: %d"
					"\n\n(Press Retry to debug the application, "
					"if it is executed in debug mode.)"
					"\n(Press Cancel otherwise.)",
					"A bitmap must be loaded before SetTopLeft() is called !!!", __FILE__, __LINE__);
				id = AfxMessageBox(msg, MB_RETRYCANCEL);
				GotoGameState(GAME_STATE_BACKROOM);
			}
			else {
				GotoGameState(GAME_STATE_OVER);
				audio->Pause();
				audio->Play(1, true);
				audio->Play(3, false);
			}
		}
	}
	
}

void CGameStateQte::OnLButtonDown(UINT nFlags, CPoint point)
{
}

void CGameStateQte::OnShow()
{	
	CAudio* audio = CAudio::Instance();
	if (background.GetSelectShowBitmap() != 71) background.ShowBitmap();
	else if (background.GetSelectShowBitmap() == 71) {
		if (true) {
			sprintf(msg, "Game fatal error:\n\n%s\n\nFile: %s\n\nLine: %d"
				"\n\n(Press Retry to debug the application, "
				"if it is executed in debug mode.)"
				"\n(Press Cancel otherwise.)",
				"A bitmap must be loaded before SetTopLeft() is called !!!", __FILE__, __LINE__);
			id = AfxMessageBox(msg, MB_RETRYCANCEL);
			GotoGameState(GAME_STATE_BACKROOM);
		}
		else {
			GotoGameState(GAME_STATE_OVER);
			audio->Pause();
			audio->Play(1, true);
			audio->Play(3, false);
		}
	}

	CDC* pDC = CDDraw::GetBackCDC();
	CFont* fp;
	CTextDraw::ChangeFontLog(pDC, fp, 24, "Consolas", RGB(255, 255, 255), 800);
	CTextDraw::Print(pDC, 50, 50, "Press SpaceBar on RED:");
	CTextDraw::Print(pDC, 530, 50, to_string(background.GetSelectShowBitmap()));
	CDDraw::ReleaseBackCDC();

	qte[0].SetTopLeft(450, 48);
	qte[1].SetTopLeft(610, 48);
	qte[2].SetTopLeft(450 + 4 * (background.GetSelectShowBitmap()), 38);
	for (int i = 0; i < 3; i++) qte[i].ShowBitmap();
}

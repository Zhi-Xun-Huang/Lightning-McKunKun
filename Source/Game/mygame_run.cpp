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

using namespace std;
using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////
int random(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> range(min, max);
	return range(gen);
}

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
	CAudio* audio = CAudio::Instance();
	if (!BackroomJump) {
		for (int i = 0; i < 3; i++) {

			if ((armstrong[i].Left() + 410 >= character[0].Left() && armstrong[i].Left() + 370 <= character[0].Left()) && armstrong[i].GetSelectShowBitmap() >= 58) {
				int tmp = random(2, 4);
				if (armstrong[i].GetSelectShowBitmap() == 60) {
					for (int i = 2; i < 5; i++) audio->Stop(i);
					audio->Play(tmp, false);
				}
			
			}

			if ((armstrong[i].Left() + 410 >= character[0].Left() && armstrong[i].Left() + 370 <= character[0].Left()) && armstrong[i].GetSelectShowBitmap() == 61) {
				if (BBCount > 0) {
					if (BBOne) {
						GotoGameState(GAME_STATE_QTE);
						//audio->Pause();
						audio->Play(7, false);
						BBCount -= 1;
						BBOne = false;
						KKID = 1;
					}
				}
				else {
					GotoGameState(GAME_STATE_OVER);
					audio->Pause();
					audio->Play(1, true);
					for (int i = 0; i < 3; i++) {
						armstrong[i].SelectShowBitmap(0);
						ArmstrongShow = false;
						background[0].SelectShowBitmap(0);
						BGEnable = true;
					}
				}
			}

			if (armstrong[i].GetSelectShowBitmap() == 15) {
				BBOne = true;
			}

			if (armstrong[i].GetSelectShowBitmap() == 0 && ArmstrongShow == true) {
				armstrong[i].SetTopLeft(random(-2000, 2000), armstrong[i].Top());
				armstrong[i].SetAnimation(random(10, 30), false);
			}

			if (character[KKID].Left() < armstrong[i].Left() + 400) armstrong[i].SetTopLeft(armstrong[i].Left() - 10, armstrong[i].Top());
			if (character[KKID].Left() > armstrong[i].Left() + 400) armstrong[i].SetTopLeft(armstrong[i].Left() + 10, armstrong[i].Top());
		}

		if (background[0].Left() >= -40) {
			background[0].SetTopLeft(-40, background[0].Top());
			int cleft = character[KKID].Left();
			if (cleft >= -80) {
				cleft -= Linear;
				character[KKID].SetTopLeft(cleft, character[KKID].Top());
			}

			/*if (random(1, 250) == 37) {

				audio->Pause();
				audio->Play(6, true);
				Sleep(2000);
				sprintf(msg, "Game fatal error:\n\n%s\n\nFile: %s\n\nLine: %d"
					"\n\n(Press Retry to debug the application, "
					"if it is executed in debug mode.)"
					"\n(Press Cancel otherwise.)",
					"A bitmap must be loaded before SetTopLeft() is called !!!", __FILE__, __LINE__);
				id = AfxMessageBox(msg, MB_RETRYCANCEL);
				audio->Pause();
				audio->Play(6, true);
				BackroomJump = true;
			}*/

		}

		if (background[0].Left() <= -1920) {
			background[0].SetTopLeft(-1920, background[0].Top());
			int cleft = character[KKID].Left();
			if (cleft <= 1200) {
				cleft += Linear;
				character[KKID].SetTopLeft(cleft, character[KKID].Top());
			}

			/*if (random(1, 250) == 37) { //1 250

				audio->Pause();
				audio->Play(6, true);
				Sleep(2000);
				sprintf(msg, "Game fatal error:\n\n%s\n\nFile: %s\n\nLine: %d"
					"\n\n(Press Retry to debug the application, "
					"if it is executed in debug mode.)"
					"\n(Press Cancel otherwise.)",
					"A bitmap must be loaded before SetTopLeft() is called !!!", __FILE__, __LINE__);
				id = AfxMessageBox(msg, MB_RETRYCANCEL);
				audio->Pause();
				audio->Play(6, true);
				BackroomJump = true;

			}*/


		}

		if (ADPressed == false && Linear <= 30) Linear += 1;

		if (TurnLR == 1) {
			background[0].SetTopLeft(background[0].Left() + Linear, background[0].Top());
			if (character[KKID].Left() >= -80) {
				for (int i = 0; i < 3; i++) armstrong[i].SetTopLeft(armstrong[i].Left() + Linear, armstrong[i].Top());
				basketball.SetTopLeft(basketball.Left() + Linear, basketball.Top());
			}
			if ((character[KKID].Left() >= 660 || character[KKID].Left() <= 630) && character[KKID].Left() >= -80) character[KKID].SetTopLeft(character[KKID].Left() - Linear, character[KKID].Top());
		}

		if (TurnLR == 2) {
			background[0].SetTopLeft(background[0].Left() - Linear, background[0].Top());
			if (character[KKID].Left() <= 1200) {
				for (int i = 0; i < 3; i++) armstrong[i].SetTopLeft(armstrong[i].Left() - Linear, armstrong[i].Top());
				basketball.SetTopLeft(basketball.Left() - Linear, basketball.Top());
			}
			if ((character[KKID].Left() >= 660 || character[KKID].Left() <= 630) && character[KKID].Left() <= 1200) character[KKID].SetTopLeft(character[KKID].Left() + Linear, character[KKID].Top());
		}

		if (ADPressed == true) {
			if (Linear == 0) {
				ADPressed = true;
				TurnLR = 0;
			}
			if (Linear != 0) Linear -= 1;
		}

		if (WPressed == true) {
			BGEnable = false;
			if (BGLinear >= 10) BGLinear -= 5;
		}

		if (SpacePressed == true) {
			if (BGLinear >= 500) BGEnable = true;
			else BGLinear += 5;
		}

		if ((basketball.Left() - 250 <= character[0].Left() && basketball.Left() + 250 >= character[0].Left()) && basketball.GetSelectShowBitmap() == 25) {
			if (BBAdd) {
				BBCount += 1;
				BBAdd = false;
			}
		}

		if (basketball.GetSelectShowBitmap() == 10) {
			BBAdd = true;
		}
		background[0].SetAnimation(BGLinear, BGEnable);

		character[1].SetTopLeft(character[0].Left(), character[0].Top());
	}
	else {
		if (MusicFlag) {
			audio->Pause();
			audio->Play(5, true);
			MusicFlag = false;
		}

	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	background[0].LoadBitmapByString({
		"resources/start/start000.bmp", "resources/start/start001.bmp",
		"resources/start/start002.bmp", "resources/start/start003.bmp",
		"resources/start/start004.bmp", "resources/start/start005.bmp",
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
		"resources/start/start058.bmp", "resources/start/start059.bmp"
		});

	background[0].SetTopLeft(-1000, 0);
	background[1].LoadBitmapByString({ "resources/black.bmp" });
	background[2].LoadBitmapByString({ "resources/backroom.bmp" });

	character[1].LoadBitmapByString({
		"resources/kunBB/KUN24bb.bmp",
		"resources/kunBB/KUN25bb.bmp",
		"resources/kunBB/KUN26bb.bmp",
		"resources/kunBB/KUN27bb.bmp",
		"resources/kunBB/KUN28bb.bmp",
		"resources/kunBB/KUN29bb.bmp",
		"resources/kunBB/KUN30bb.bmp",
		"resources/kunBB/KUN31bb.bmp",
		"resources/kunBB/KUN32bb.bmp",
		"resources/kunBB/KUN33bb.bmp",
		"resources/kunBB/KUN34bb.bmp",
		"resources/kunBB/KUN35bb.bmp"
		}, RGB(255, 255, 255)
	);

	character[0].LoadBitmapByString({
		"resources/kunRun/KUN36run.bmp",
		"resources/kunRun/KUN37run.bmp",
		"resources/kunRun/KUN38run.bmp",
		"resources/kunRun/KUN39run.bmp",
		"resources/kunRun/KUN40run.bmp",
		"resources/kunRun/KUN41run.bmp"
		}, RGB(255, 255, 255)
	);
	
	for (int i = 0; i < 3; i++) {
		armstrong[i].LoadBitmapByString({
		"resources/armstrong/armstrong00.bmp", "resources/armstrong/armstrong01.bmp", "resources/armstrong/armstrong02.bmp",
		"resources/armstrong/armstrong03.bmp", "resources/armstrong/armstrong04.bmp", "resources/armstrong/armstrong05.bmp",
		"resources/armstrong/armstrong06.bmp", "resources/armstrong/armstrong07.bmp", "resources/armstrong/armstrong08.bmp",
		"resources/armstrong/armstrong09.bmp", "resources/armstrong/armstrong10.bmp", "resources/armstrong/armstrong11.bmp",
		"resources/armstrong/armstrong12.bmp", "resources/armstrong/armstrong13.bmp", "resources/armstrong/armstrong14.bmp",
		"resources/armstrong/armstrong15.bmp", "resources/armstrong/armstrong16.bmp", "resources/armstrong/armstrong17.bmp",
		"resources/armstrong/armstrong18.bmp", "resources/armstrong/armstrong19.bmp", "resources/armstrong/armstrong20.bmp",
		"resources/armstrong/armstrong21.bmp", "resources/armstrong/armstrong22.bmp", "resources/armstrong/armstrong23.bmp",
		"resources/armstrong/armstrong24.bmp", "resources/armstrong/armstrong25.bmp", "resources/armstrong/armstrong26.bmp",
		"resources/armstrong/armstrong27.bmp", "resources/armstrong/armstrong28.bmp", "resources/armstrong/armstrong29.bmp",
		"resources/armstrong/armstrong30.bmp", "resources/armstrong/armstrong31.bmp", "resources/armstrong/armstrong32.bmp",
		"resources/armstrong/armstrong33.bmp", "resources/armstrong/armstrong34.bmp", "resources/armstrong/armstrong35.bmp",
		"resources/armstrong/armstrong36.bmp", "resources/armstrong/armstrong37.bmp", "resources/armstrong/armstrong38.bmp",
		"resources/armstrong/armstrong39.bmp", "resources/armstrong/armstrong40.bmp", "resources/armstrong/armstrong41.bmp",
		"resources/armstrong/armstrong42.bmp", "resources/armstrong/armstrong43.bmp", "resources/armstrong/armstrong44.bmp",
		"resources/armstrong/armstrong45.bmp", "resources/armstrong/armstrong46.bmp", "resources/armstrong/armstrong47.bmp",
		"resources/armstrong/armstrong48.bmp", "resources/armstrong/armstrong49.bmp", "resources/armstrong/armstrong50.bmp",
		"resources/armstrong/armstrong51.bmp", "resources/armstrong/armstrong52.bmp", "resources/armstrong/armstrong53.bmp",
		"resources/armstrong/armstrong54.bmp", "resources/armstrong/armstrong55.bmp", "resources/armstrong/armstrong56.bmp",
		"resources/armstrong/armstrong57.bmp", "resources/armstrong/armstrong58.bmp", "resources/armstrong/armstrong59.bmp",
		"resources/armstrong/armstrong60.bmp", "resources/armstrong/armstrong61.bmp", "resources/armstrong/armstrong62.bmp"
			}, RGB(255, 255, 255)
		);
		armstrong[i].SetTopLeft(random(-2000, 2000), 270);
	}
	

	for (int i = 0; i < 2; i++) {
		character[i].SetTopLeft(640, 400);
		character[i].SetAnimation(50, false);
	}

	basketball.LoadBitmapByString({
		"resources/basketball/basketball00.bmp",
		"resources/basketball/basketball01.bmp",
		"resources/basketball/basketball02.bmp",
		"resources/basketball/basketball03.bmp",
		"resources/basketball/basketball04.bmp",
		"resources/basketball/basketball05.bmp",
		"resources/basketball/basketball06.bmp",
		"resources/basketball/basketball07.bmp",
		"resources/basketball/basketball08.bmp",
		"resources/basketball/basketball09.bmp",
		"resources/basketball/basketball10.bmp",
		"resources/basketball/basketball11.bmp",
		"resources/basketball/basketball12.bmp",
		"resources/basketball/basketball13.bmp",
		"resources/basketball/basketball14.bmp",
		"resources/basketball/basketball15.bmp",
		"resources/basketball/basketball16.bmp",
		"resources/basketball/basketball17.bmp",
		"resources/basketball/basketball18.bmp",
		"resources/basketball/basketball19.bmp",
		"resources/basketball/basketball20.bmp",
		"resources/basketball/basketball21.bmp",
		"resources/basketball/basketball22.bmp",
		"resources/basketball/basketball23.bmp",
		"resources/basketball/basketball24.bmp",
		"resources/basketball/basketball25.bmp"
		}, RGB(255, 255, 255)
	);
	basketball.SetAnimation(50, false);

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
			"resources/obunga/Obunga30.bmp",
			}, RGB(0, 0, 0)
			);
		obunga[m].SetAnimation(50, false);
	}

	bbx = random(-500, 500);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	if (debug == false && nChar == 0x51) {
		debug = true;  // QKey detection.(debug platform)
		BBCount = 10;
	}

	/*if (nChar == 0x20) {  // SpaceBar detection.(handbrake)
		WPressed = false;
		SpacePressed = true;
	}

	if (nChar == 0x45) {  // EKey detection.(KunKun Status Change)
		if (KKID == 1) KKID = 0;
		else KKID += 1;
	}*/

	if (nChar == 0x57) {  // WKey detection.(accelerator)
		WPressed = true;
		ArmstrongShow = true;
	}

	if (nChar == 0x41) {  // AKey detection.(turn left)
		ADPressed = false;
		TurnLR = 1;
		KKID = 0;
	}

	if (nChar == 0x44) {  // DKey detection(turn right)
		ADPressed = false;
		TurnLR = 2;
		KKID = 0;
	}

}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (debug == true && nChar == 0x51) debug = false;

	if (nChar == 0x57 || nChar == 0x41 || nChar == 0x53 || nChar == 0x44) ADPressed = true;

	if (nChar == 0x20) SpacePressed = false;
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作53
{
	GetCursorPos(&p);
	HWND hwnd = FindWindowA(NULL, "LMKK");
	ScreenToClient(hwnd, &p);
	Xmouse = p.x;
	Ymouse = p.y;
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	
}


void CGameStateRun::OnShow()
{
	for (int m = 0; m < 5; m++) {
		ObungaMove[m] = true;
	}
	if (!BackroomJump) {
		background[0].ShowBitmap();
		if (ArmstrongShow == true) {
			for (int i = 0; i < 3; i++) armstrong[i].ShowBitmap();
		}
		if (basketball.GetSelectShowBitmap() == 0) {
			basketball.SetTopLeft(bbx, 450);
			basketball.ShowBitmap();
		}
		else {
			basketball.ShowBitmap();
		}
		if (basketball.GetSelectShowBitmap() == 10) {
			bbx = random(-5000, 5000);
		}
		character[KKID].ShowBitmap();
	}
	else {
		if (BlackFlag) {
			background[1].ShowBitmap();
			BlackFlag = false;
		}
		else {
			if (ff) {
				Sleep(3500);
				MusicFlag = true;
				ff = false;
				for (int m = 0; m < 5; m++) {
					obunga[m].SetTopLeft(random(0, 1180), random(0, 485));
				}
			}
			background[2].ShowBitmap();
			for (int m = 0; m < 5; m++) {
				obunga[m].ShowBitmap();
				if (obunga[m].GetSelectShowBitmap() == 0 && ObungaMove[m] == true) {
					obunga[m].SetTopLeft(random(0, 1320), random(0, 625));
					ObungaMove[m] = false;
				}
				if (obunga[m].GetSelectShowBitmap() == 15) {
					ObungaMove[m] = true;
				}
			}
		}
	}


	CDC *pDC = CDDraw::GetBackCDC();
	CFont* fp;
	CTextDraw::ChangeFontLog(pDC, fp, 24, "Consolas", RGB(0, 0, 0), 800);
	string speed = to_string(500-BGLinear);
	if (!BackroomJump) {
		CTextDraw::Print(pDC, 1230, 50, "Speed:");
		CTextDraw::Print(pDC, 1370, 50, speed);
		CTextDraw::Print(pDC, 1400, 50, " KM/s");
		CTextDraw::Print(pDC, 1230, 70, "Basketball Remain:");
		string m = to_string(BBCount);
		CTextDraw::Print(pDC, 1530, 70, m);
	}


	if (debug == true) {
		CTextDraw::Print(pDC, 80, 80, "KK_Left:");
		CTextDraw::Print(pDC, 250, 80, to_string(character[KKID].Left()));
		CTextDraw::Print(pDC, 80, 50, "BG_Left:");
		CTextDraw::Print(pDC, 250, 50, to_string(background[0].Left()));
		CTextDraw::Print(pDC, 80, 110, "AS_Left:");
		CTextDraw::Print(pDC, 250, 110, to_string(armstrong[0].Left()));
		CTextDraw::Print(pDC, 80, 140, "BB_Left:");
		CTextDraw::Print(pDC, 250, 140, to_string(basketball.Left()));
		CTextDraw::Print(pDC, 150, 170, "X:");
		CTextDraw::Print(pDC, 250, 170, to_string(Xmouse));
		CTextDraw::Print(pDC, 150, 200, "Y:");
		CTextDraw::Print(pDC, 250, 200, to_string(Ymouse));
	}

	CDDraw::ReleaseBackCDC();
}


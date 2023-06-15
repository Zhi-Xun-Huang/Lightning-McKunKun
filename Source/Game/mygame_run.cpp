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
#include <random>

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
	basketball.ToggleAnimation();
	CAudio* audio = CAudio::Instance();
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	CAudio* audio = CAudio::Instance();
	if (BBCount >= VictoryCodition[3]) {
		end = true;
	}
	if (!end) {
		if (BBCount >= VictoryCodition[PHASE]) {
				PHASEEnable = false;
				start = false;
				BBCount = 0;
				if (PHASE < 3) PHASE += 1;
				ArmstrongEnable = false;
				WPressed = false;
		}
	}
	
	

	if (PHASEEnable) {

		for (int i = 0; i < ArmstrongAmount[PHASE]; i++) {

			if ((armstrong[i].Left() + 430 >= character[0].Left() && armstrong[i].Left() + 390 <= character[0].Left()) && armstrong[i].GetSelectShowBitmap() >= 58) { // Armstrong Sound Effect
				int tmp = random(2, 4);
				if (armstrong[i].GetSelectShowBitmap() == 60) {
					for (int i = 2; i < 5; i++) audio->Stop(i);
					audio->Play(tmp, false);
				}

			}

			if ((armstrong[i].Left() + 410 >= character[0].Left() && armstrong[i].Left() + 370 <= character[0].Left()) && armstrong[i].GetSelectShowBitmap() == 61) {  // Armstrong Beat KunKun Detection
				if (BBCount > 0) {
					if (BBOne) {
						GotoGameState(GAME_STATE_QTE);
						for (int i = 0; i < 3; i++) {
							armstrong[i].SelectShowBitmap(0);
							//ArmstrongEnable = false;
							background.SelectShowBitmap(0);
							BGEnable = true;
						}
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
						ArmstrongEnable = false;
						background.SelectShowBitmap(0);
						BGEnable = true;
					}
				}
			}

			if (armstrong[i].GetSelectShowBitmap() == 15) BBOne = true;

			if (character[KKID].Left() < armstrong[i].Left() + 400) armstrong[i].SetTopLeft(armstrong[i].Left() - 10, armstrong[i].Top());
			if (character[KKID].Left() > armstrong[i].Left() + 400) armstrong[i].SetTopLeft(armstrong[i].Left() + 10, armstrong[i].Top());

			if (armstrong[i].GetSelectShowBitmap() == 0 && ArmstrongEnable) {
				armstrong[i].SetTopLeft(random(-2000, 2000), 270);
				armstrong[i].SetAnimation(random(10, 30), false);
			}
		}

		if (background.Left() >= -40) {
			background.SetTopLeft(-40, background.Top());
			int cleft = character[KKID].Left();
			if (cleft >= -80) {
				cleft -= Linear;
				character[KKID].SetTopLeft(cleft, character[KKID].Top());
			}
		}

		if (background.Left() <= -1920) {
			background.SetTopLeft(-1920, background.Top());
			int cleft = character[KKID].Left();
			if (cleft <= 1200) {
				cleft += Linear;
				character[KKID].SetTopLeft(cleft, character[KKID].Top());
			}
		}

		if (TurnLR == 1) {
			background.SetTopLeft(background.Left() + Linear, background.Top());
			if (character[KKID].Left() >= -80) {
				for (int i = 0; i < 3; i++) armstrong[i].SetTopLeft(armstrong[i].Left() + Linear, armstrong[i].Top());
				basketball.SetTopLeft(basketball.Left() + Linear, basketball.Top());
			}
			if ((character[KKID].Left() >= 660 || character[KKID].Left() <= 630) && character[KKID].Left() >= -80) character[KKID].SetTopLeft(character[KKID].Left() - Linear, character[KKID].Top());
		}

		if (TurnLR == 2) {
			background.SetTopLeft(background.Left() - Linear, background.Top());
			if (character[KKID].Left() <= 1200) {
				for (int i = 0; i < 3; i++) armstrong[i].SetTopLeft(armstrong[i].Left() - Linear, armstrong[i].Top());
				basketball.SetTopLeft(basketball.Left() - Linear, basketball.Top());
			}
			if ((character[KKID].Left() >= 660 || character[KKID].Left() <= 630) && character[KKID].Left() <= 1200) character[KKID].SetTopLeft(character[KKID].Left() + Linear, character[KKID].Top());
		}

		if (ADPressed == false && Linear <= 30) Linear += 1;

		if (ADPressed == true) {
			if (Linear == 0) {
				ADPressed = true;
				TurnLR = 0;
			}
			if (Linear != 0) Linear -= 1;
		}

		if (WPressed == true) {
			BGEnable = true;
			if (BGLinear >= 10) BGLinear -= 5;
		}

		if ((basketball.Left() - 250 <= character[KKID].Left() && basketball.Left() + 250 >= character[KKID].Left()) && basketball.GetSelectShowBitmap() == 30) {
			if (BBAdd) {
				audio->Play(9, false);
				BBCount += 1;
				BBAdd = false;
			}
		}

		if (basketball.GetSelectShowBitmap() == 10) BBAdd = true;

		character[1].SetTopLeft(character[0].Left(), character[0].Top());

		background.SetAnimation(BGLinear, true);
	}
	else {



		blank.ShowBitmap();
		for (int i = 0; i < 7; i++) alphabet[i].ShowBitmap();
		
		alphabet[0].SetTopLeft(640, 400);
		alphabet[1].SetTopLeft(680, 400);
		alphabet[2].SetTopLeft(720, 400);
		alphabet[3].SetTopLeft(760, 400);
		alphabet[4].SetTopLeft(800, 400);
		alphabet[5].SetTopLeft(840, 400);
		alphabet[6].SetTopLeft(880, 400);

		if (!start) for (int i = 0; i < 7; i++) alphabet[i].SetAnimation(50, false);
		if (start) {
			audio->Stop(5);
			if(count == 0) audio->Play(1, false);
			if (count > 100) alphabet[0].SelectShowBitmap(21); //L
			if (count > 150) alphabet[1].SelectShowBitmap(14); //E
			if (count > 200) alphabet[2].SelectShowBitmap(31); //V
			if (count > 250) alphabet[3].SelectShowBitmap(14); //E
			if (count > 300) alphabet[4].SelectShowBitmap(21); //L
			if (count > 350) alphabet[5].SelectShowBitmap(0);  //0
			if (count > 400) alphabet[6].SelectShowBitmap(PHASE); //PHASE
			if (count > 600) {
				count = 0;
				audio->Play(0, true);
				PHASEEnable = true;
			}
			count++;
		}
	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	background.LoadBitmapByString({
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
		"resources/start/start058.bmp", "resources/start/start059.bmp"
		});

	background.SetTopLeft(-1000, 0);

	blank.LoadBitmapByString({ "resources/blank.bmp" });
	blank.SetTopLeft(0, 0);

	dashboard.LoadBitmapByString({
		"resources/dashboard.bmp"
	}, RGB(255, 255, 255));

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
		}, RGB(255, 255, 255));

	character[0].LoadBitmapByString({
		"resources/kunRun/KUN36run.bmp",
		"resources/kunRun/KUN37run.bmp",
		"resources/kunRun/KUN38run.bmp",
		"resources/kunRun/KUN39run.bmp",
		"resources/kunRun/KUN40run.bmp",
		"resources/kunRun/KUN41run.bmp"
		}, RGB(255, 255, 255));

	for (int i = 0; i < 2; i++) {
		character[i].SetTopLeft(640, 400);
		character[i].SetAnimation(50, false);
	}
	
	for (int i = 0; i < 9; i++) {
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
			}, RGB(255, 255, 255));
		armstrong[i].SetTopLeft(random(-2000, 2000), 270);
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
		"resources/basketball/basketball25.bmp",
		"resources/basketball/basketball26.bmp",
		"resources/basketball/basketball27.bmp",
		"resources/basketball/basketball28.bmp",
		"resources/basketball/basketball29.bmp",
		"resources/basketball/basketball30.bmp"
		}, RGB(0, 0, 0));
	
	basketball.SetTopLeft(random(-2000, 2000), 450);
	basketball.SetAnimation(30, true);

	for (int i = 0; i < 21; i++) {
		alphabet[i].LoadBitmapByString({ 
			"resources/alphabet/0.bmp",
			"resources/alphabet/1.bmp",
			"resources/alphabet/2.bmp",
			"resources/alphabet/3.bmp",
			"resources/alphabet/4.bmp",
			"resources/alphabet/5.bmp",
			"resources/alphabet/6.bmp",
			"resources/alphabet/7.bmp",
			"resources/alphabet/8.bmp",
			"resources/alphabet/9.bmp",
			"resources/alphabet/A.bmp",
			"resources/alphabet/B.bmp",
			"resources/alphabet/C.bmp",
			"resources/alphabet/D.bmp",
			"resources/alphabet/E.bmp",
			"resources/alphabet/F.bmp",
			"resources/alphabet/G.bmp",
			"resources/alphabet/H.bmp",
			"resources/alphabet/I.bmp",
			"resources/alphabet/J.bmp",
			"resources/alphabet/K.bmp",
			"resources/alphabet/L.bmp",
			"resources/alphabet/M.bmp",
			"resources/alphabet/N.bmp",
			"resources/alphabet/O.bmp",
			"resources/alphabet/P.bmp",
			"resources/alphabet/Q.bmp",
			"resources/alphabet/R.bmp",
			"resources/alphabet/S.bmp",
			"resources/alphabet/T.bmp",
			"resources/alphabet/U.bmp",
			"resources/alphabet/V.bmp",
			"resources/alphabet/W.bmp",
			"resources/alphabet/X.bmp",
			"resources/alphabet/Y.bmp",
			"resources/alphabet/Z.bmp"
			}, RGB(255, 255, 255));
	}
	everest.LoadBitmapByString({ "resources/everest.bmp" });

	for (int i = 0; i < 5; i++) {
		kunfamily[i].LoadBitmapByString({
			"resources/kunRun/KUN36run.bmp",
			"resources/kunRun/KUN37run.bmp",
			"resources/kunRun/KUN38run.bmp",
			"resources/kunRun/KUN39run.bmp",
			"resources/kunRun/KUN40run.bmp",
			"resources/kunRun/KUN41run.bmp"
			}, RGB(255, 255, 255));
	}
	for (int i = 0; i < 5; i++) {
		kunfamily[i].SetTopLeft(200 + 200 * i, 200);
		kunfamily[i].SetAnimation(50, false);
	}
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	start = true;

	if (PHASEEnable) {
		if (!debug && nChar == 0x51) {
			debug = true;  // QKey detection.(debug platform)
			BBCount += 5;
		}

		if (nChar == 0x57) {  // WKey detection.(accelerator)
			WPressed = true;
			background.ToggleAnimation();
			ArmstrongEnable = true;
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
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (debug == true && nChar == 0x51) debug = false;

	if (nChar == 0x57 || nChar == 0x41 || nChar == 0x44) ADPressed = true;

	//if (nChar == 0x20) SpacePressed = false;
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
	if (end) {
		everest.ShowBitmap();
		for (int i = 0; i < 5; i++) {
			kunfamily[i].ShowBitmap();
		}
	}
	else {
		if (PHASEEnable) {

			if (background.GetSelectShowBitmap() == 59 && BGEnable) {
				background.ToggleAnimation();
			}
			else if (background.GetSelectShowBitmap() != 59) background.ShowBitmap();

			if (basketball.GetSelectShowBitmap() != 30) {
				basketball.ShowBitmap();
			}
			else if (basketball.GetSelectShowBitmap() == 30) {
				basketball.SetTopLeft(random(-2000, 2000), 450);
				basketball.ToggleAnimation();
			}

			if (ArmstrongEnable) for (int i = 0; i < ArmstrongAmount[PHASE]; i++) armstrong[i].ShowBitmap();

			character[KKID].ShowBitmap();

			dashboard.SetTopLeft(1145, 0);
			dashboard.ShowBitmap();

			CDC* pDC = CDDraw::GetBackCDC();
			CFont* fp;
			CTextDraw::ChangeFontLog(pDC, fp, 24, "Consolas", RGB(0, 0, 0), 800);

			if (debug) {
				CTextDraw::Print(pDC, 80, 80, "KK_Left:");
				CTextDraw::Print(pDC, 250, 80, to_string(character[KKID].Left()));
				CTextDraw::Print(pDC, 80, 50, "BG_Left:");
				CTextDraw::Print(pDC, 250, 50, to_string(background.Left()));
				CTextDraw::Print(pDC, 80, 110, "AS_Left:");
				CTextDraw::Print(pDC, 250, 110, to_string(armstrong[0].Left() + 390));
				CTextDraw::Print(pDC, 80, 140, "BB_Left:");
				CTextDraw::Print(pDC, 250, 140, to_string(basketball.Left()));
				CTextDraw::Print(pDC, 80, 170, "Phase:");
				CTextDraw::Print(pDC, 250, 170, to_string(PHASE));
				CTextDraw::Print(pDC, 80, 200, "AS_Amount:");
				CTextDraw::Print(pDC, 250, 200, to_string(ArmstrongAmount[PHASE]));
				CTextDraw::Print(pDC, 80, 230, "VK_Codition:");
				CTextDraw::Print(pDC, 250, 230, to_string(VictoryCodition[PHASE]));
			}

			CDDraw::ReleaseBackCDC();

			for (int i = 0; i < 21; i++) alphabet[i].ShowBitmap(0.6);

			/////////////////////////////////////
			alphabet[0].SelectShowBitmap(28); //S
			alphabet[0].SetTopLeft(1250, 50);
			alphabet[1].SelectShowBitmap(25); //P
			alphabet[1].SetTopLeft(1270, 50);
			alphabet[2].SelectShowBitmap(14); //E
			alphabet[2].SetTopLeft(1290, 50);
			alphabet[3].SelectShowBitmap(14); //E
			alphabet[3].SetTopLeft(1310, 50);
			alphabet[4].SelectShowBitmap(13); //D
			alphabet[4].SetTopLeft(1330, 50);
			int tmp0 = 500 - BGLinear;
			int a = 0, b = 0, c = 0;
			while (tmp0 >= 100) { tmp0 -= 100; a++; }
			alphabet[5].SelectShowBitmap(a);  //100
			alphabet[5].SetTopLeft(1470, 50);
			while (tmp0 >= 10) { tmp0 -= 10; b++; }
			alphabet[6].SelectShowBitmap(b);  //010 
			alphabet[6].SetTopLeft(1490, 50);
			if (tmp0 == 10) c = 0;
			else c = tmp0;
			alphabet[7].SelectShowBitmap(c);  //001
			alphabet[7].SetTopLeft(1510, 50);

			//////////////////////////////////////
			alphabet[8].SelectShowBitmap(11);  //B
			alphabet[8].SetTopLeft(1250, 110);
			alphabet[9].SelectShowBitmap(10);  //A
			alphabet[9].SetTopLeft(1270, 110);
			alphabet[10].SelectShowBitmap(28); //S
			alphabet[10].SetTopLeft(1290, 110);
			alphabet[11].SelectShowBitmap(20); //K
			alphabet[11].SetTopLeft(1310, 110);
			alphabet[12].SelectShowBitmap(14); //E
			alphabet[12].SetTopLeft(1330, 110);
			alphabet[13].SelectShowBitmap(29); //T
			alphabet[13].SetTopLeft(1350, 110);
			alphabet[14].SelectShowBitmap(11); //B
			alphabet[14].SetTopLeft(1370, 110);
			alphabet[15].SelectShowBitmap(10); //A
			alphabet[15].SetTopLeft(1390, 110);
			alphabet[16].SelectShowBitmap(21); //L
			alphabet[16].SetTopLeft(1410, 110);
			alphabet[17].SelectShowBitmap(21); //L
			alphabet[17].SetTopLeft(1430, 110);
			int tmp1 = BBCount;
			int d = 0, e = 0, f = 0;
			while (tmp1 >= 100) { tmp1 -= 100; d++; }
			alphabet[18].SelectShowBitmap(d);  //100
			alphabet[18].SetTopLeft(1470, 110);
			while (tmp1 >= 10) { tmp1 -= 10; e++; }
			alphabet[19].SelectShowBitmap(e);  //010 
			alphabet[19].SetTopLeft(1490, 110);
			if (tmp1 == 10) f = 0;
			else f = tmp1;
			alphabet[20].SelectShowBitmap(f);  //001
			alphabet[20].SetTopLeft(1510, 110);
		}
	}
}
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

using namespace std;
using namespace game_framework;
 
int KKID = 0;               // State of KunKun
int BGID = 0;               // State of background
int Linear = 0;             // Linear turn left & right
int TurnLR = 0;             // Turn left or right or not
int BGLinear = 500;         // Background latency
bool ADPressed = true;     // Akey or DKey pressed
bool BGEnable = true;       // Background animation enable
bool WPressed = false;      // State of WKey
bool SpacePressed = false;  // State of SpaceBar
bool ArmstrongShow = false; // Armstrong be shown or not

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
	if ((armstrong.Left() + 420 >= character[0].Left() && armstrong.Left() + 380 <= character[0].Left()) && armstrong.GetSelectShowBitmap() == 62) {
		GotoGameState(GAME_STATE_OVER);
	}

	if (armstrong.GetSelectShowBitmap() == 0) {
		armstrong.SetTopLeft(character[KKID].Left() - 400, armstrong.Top());
	}

	if (background[0].Left() >= -40) {
		background[0].SetTopLeft(-40, background[0].Top());
		int cleft = character[KKID].Left();
		if (cleft >= -80) {
			cleft -= Linear;
			character[KKID].SetTopLeft(cleft, character[KKID].Top());
		}
	} 

	if (background[0].Left() <= -1920) {
		background[0].SetTopLeft(-1920, background[0].Top());
		int cleft = character[KKID].Left();
		if (cleft <= 1200) {
			cleft += Linear;
			character[KKID].SetTopLeft(cleft, character[KKID].Top());
		}
	}

	if (character[KKID].Left() < armstrong.Left() + 400) armstrong.SetTopLeft(armstrong.Left() - 20, armstrong.Top());
	if (character[KKID].Left() > armstrong.Left() + 400) armstrong.SetTopLeft(armstrong.Left() + 20, armstrong.Top());

	if (ADPressed == false && Linear <= 30) Linear += 1;

	if (TurnLR == 1) {
		background[0].SetTopLeft(background[0].Left() + Linear, background[0].Top());
		if (character[KKID].Left() >= -80) armstrong.SetTopLeft(armstrong.Left() + Linear, armstrong.Top());
		if ((character[KKID].Left() >= 660 || character[KKID].Left() <= 630) && character[KKID].Left() >= -80) character[KKID].SetTopLeft(character[KKID].Left() - Linear, character[KKID].Top());
	}

	if (TurnLR == 2) {
		background[0].SetTopLeft(background[0].Left() - Linear, background[0].Top());
		if (character[KKID].Left() <= 1200) armstrong.SetTopLeft(armstrong.Left() - Linear, armstrong.Top());
		if ((character[KKID].Left() >= 660 || character[KKID].Left() <= 630) && character[KKID].Left() <= 1200) character[KKID].SetTopLeft(character[KKID].Left() + Linear, character[KKID].Top());
	}

	if (ADPressed == true) {
		if (Linear == 0){ 
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

	background[0].SetAnimation(BGLinear, BGEnable);
	armstrong.SetAnimation(30, false);

}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	background[0].LoadBitmapByString({
		"resources/start/start000.bmp"/*, "resources/start/start001.bmp",
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
		"resources/start/start058.bmp", "resources/start/start059.bmp",
		"resources/start/start060.bmp", "resources/start/start061.bmp",
		"resources/start/start062.bmp", "resources/start/start063.bmp",
		"resources/start/start064.bmp", "resources/start/start065.bmp",
		"resources/start/start066.bmp", "resources/start/start067.bmp",
		"resources/start/start068.bmp", "resources/start/start069.bmp",
		"resources/start/start070.bmp", "resources/start/start071.bmp",
		"resources/start/start072.bmp", "resources/start/start073.bmp",
		"resources/start/start074.bmp", "resources/start/start075.bmp",
		"resources/start/start076.bmp", "resources/start/start077.bmp",
		"resources/start/start078.bmp", "resources/start/start079.bmp",
		"resources/start/start080.bmp", "resources/start/start081.bmp",
		"resources/start/start082.bmp", "resources/start/start083.bmp",
		"resources/start/start084.bmp", "resources/start/start085.bmp",
		"resources/start/start086.bmp", "resources/start/start087.bmp",
		"resources/start/start088.bmp", "resources/start/start089.bmp",
		"resources/start/start090.bmp", "resources/start/start091.bmp",
		"resources/start/start092.bmp", "resources/start/start093.bmp",
		"resources/start/start094.bmp", "resources/start/start095.bmp",
		"resources/start/start096.bmp", "resources/start/start097.bmp",
		"resources/start/start098.bmp", "resources/start/start099.bmp"*/
	});


	background[0].SetTopLeft(-1000, 0);

	background[1].LoadBitmapByString({ "resources/gameover.bmp" });
	background[1].SetTopLeft(0, 0);
	

	character[2].LoadBitmapByString({ 
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
		},RGB(255, 255, 255)
	);

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

	armstrong.LoadBitmapByString({
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

	armstrong.SetTopLeft(60, 270);

	for (int i = 0; i < 3; i++) {
		character[i].SetTopLeft(640, 400);
		character[i].SetAnimation(100, false);
	}

}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{	
	if (nChar == 0x20) {  // SpaceBar detection.(handbrake)
		WPressed = false;
		SpacePressed = true;
	}

	if (nChar == 0x45) {  // EKey detection.(KunKun Status Change)
		if (KKID == 2) KKID = 0;
		else KKID += 1;
	}

	if (nChar == 0x57) {  // WKey detection.(accelerator)
		WPressed = true;
		ArmstrongShow = true;
	}

	if (nChar == 0x41) {  // AKey detection.(turn left)
		ADPressed = false;
		TurnLR = 1;
	}

	if (nChar == 0x44) {  // DKey detection(turn right)
		ADPressed = false;
		TurnLR = 2;
	}

}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
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
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{	
	background[BGID].ShowBitmap();
	if (ArmstrongShow == true) armstrong.ShowBitmap();
	character[KKID].ShowBitmap();
	CDC *pDC = CDDraw::GetBackCDC();
	CFont* fp;
	CTextDraw::ChangeFontLog(pDC, fp, 24, "Arial", RGB(0, 0, 0), 800);
	string speed = to_string(Linear);
	CTextDraw::Print(pDC, 1230, 50, "Speed:");
	CTextDraw::Print(pDC, 1350, 50, speed);
	CTextDraw::Print(pDC, 1400, 50, " KM/s");
	CTextDraw::Print(pDC, 80, 80, "KK_Left:");
	string x = to_string(character[KKID].Left());
	CTextDraw::Print(pDC, 250, 80, x);
	CTextDraw::Print(pDC, 80, 50, "BG_Left:");
	string y = to_string(background[BGID].Left());
	CTextDraw::Print(pDC, 250, 50, y);
	CTextDraw::Print(pDC, 80, 110, "AS_Left:");
	string z = to_string(armstrong.Left());
	CTextDraw::Print(pDC, 250, 110, z);
	CDDraw::ReleaseBackCDC();

}


#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"


using namespace game_framework;

int mckun = 0; // state of mckunkun
int linear = 0;
bool forcestop = false;

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
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

void CGameStateRun::OnMove()							// ���ʹC������
{	

	ball.SetTopLeft(ball.Left() + 1, character[mckun].Top());

	if (keepmove == 1) {
		int top = character[mckun].Top();
		top -= linear;
		if (forcestop == false && linear <= 30)linear += 3;
		character[mckun].SetTopLeft(character[mckun].Left(), top);
	}

	if (keepmove == 2) {
		int left = character[mckun].Left();
		left -= linear;
		if (forcestop == false && linear <= 30)linear += 3;
		character[mckun].SetTopLeft(left, character[mckun].Top());
	}

	if (keepmove == 3) {
		int top = character[mckun].Top();
		top += linear;
		if (forcestop == false && linear <= 30)linear += 3;
		character[mckun].SetTopLeft(character[mckun].Left(), top);
	}

	if (keepmove == 4) {
		int left = character[mckun].Left();
		left += linear;
		if (forcestop == false && linear <= 30)linear += 3;
		character[mckun].SetTopLeft(left, character[mckun].Top());
	}
	if (forcestop == true) {
		if (linear == 0){ 
			forcestop = false;
			keepmove = 0;
		}
		if (linear != 0) linear -= 1;
	}
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	background.LoadBitmapByString({ 
		"resources/phase11_background.bmp", 
		"resources/phase12_background.bmp", 
		"resources/phase21_background.bmp", 
		"resources/phase22_background.bmp", 
		"resources/phase31_background.bmp", 
		"resources/phase32_background.bmp",
		"resources/phase41_background.bmp",
		"resources/phase42_background.bmp",
		"resources/phase51_background.bmp",
		"resources/phase52_background.bmp",
		"resources/phase61_background.bmp",
		"resources/phase62_background.bmp",
	});
	background.SetTopLeft(0, 0);

	character[0].LoadBitmapByString({ 
		"resources/KUN00die.bmp",
		"resources/KUN01die.bmp",
		"resources/KUN02die.bmp",
		"resources/KUN03die.bmp",
		"resources/KUN04die.bmp",
		"resources/KUN05die.bmp",
		"resources/KUN06die.bmp",
		"resources/KUN07die.bmp",
		"resources/KUN08die.bmp",
		"resources/KUN09die.bmp",
		"resources/KUN10die.bmp",
		"resources/KUN11die.bmp",
		"resources/KUN12die.bmp",
		"resources/KUN13die.bmp",
		"resources/KUN14die.bmp",
		"resources/KUN15die.bmp",
		"resources/KUN16die.bmp",
		"resources/KUN17die.bmp",
		"resources/KUN18die.bmp",
		"resources/KUN19die.bmp",
		"resources/KUN20die.bmp",
		"resources/KUN21die.bmp",
		"resources/KUN22die.bmp",
		"resources/KUN23die.bmp"
		},RGB(255, 255, 255)
	);

	character[1].LoadBitmapByString({
		"resources/KUN24bb.bmp",
		"resources/KUN25bb.bmp",
		"resources/KUN26bb.bmp",
		"resources/KUN27bb.bmp",
		"resources/KUN28bb.bmp",
		"resources/KUN29bb.bmp",
		"resources/KUN30bb.bmp",
		"resources/KUN31bb.bmp",
		"resources/KUN32bb.bmp",
		"resources/KUN33bb.bmp",
		"resources/KUN34bb.bmp",
		"resources/KUN35bb.bmp"
		}, RGB(255, 255, 255)
	);

	character[2].LoadBitmapByString({
		"resources/KUN36run.bmp",
		"resources/KUN37run.bmp",
		"resources/KUN38run.bmp",
		"resources/KUN39run.bmp",
		"resources/KUN40run.bmp",
		"resources/KUN41run.bmp"
		}, RGB(255, 255, 255)
	);

	for (int i = 0; i < 3; i++) {
		character[i].SetTopLeft(150, 265);
		character[i].SetAnimation(100, false);
	}

	chest_and_key.LoadBitmapByString({ "resources/chest.bmp", "resources/chest_ignore.bmp" }, RGB(255, 255, 255));
	chest_and_key.SetTopLeft(150, 430);

	bee.LoadBitmapByString({ "resources/bee_1.bmp", "resources/bee_2.bmp" });
	bee.SetTopLeft(462, 265);

	ball.LoadBitmapByString({ "resources/Basketball.bmp" }, RGB(255, 255, 255));
	ball.SetTopLeft(0, 0);

	for (int i = 0; i < 3; i++) {
		door[i].LoadBitmapByString({ "resources/door_close.bmp", "resources/door_open.bmp" }, RGB(255, 255, 255));
		door[i].SetTopLeft(462 - 100 * i, 265);
	}

}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{	

	if (nChar == 0x46) {
		//ball.SetTopLeft(character[mckun].Top(), character[mckun].Left());
		ball.ShowBitmap();
	}

	if (nChar == 0x45) {
		if (mckun == 2) mckun = 0;
		else mckun += 1;
	}

	if (nChar == 0x57) {
		keepmove = 1;
		//linear = 0;
	}

	if (nChar == 0x41) {
		keepmove = 2;
		//linear = 0;
	}
		

	if (nChar == 0x53) {
		keepmove = 3;
		//linear = 0;
	}

	if (nChar == 0x44) {
		keepmove = 4;
		//linear = 0;
	}

	/*
	if (nChar == 0x57) { //W_up
		int top = character[mckun].Top();
		top -= 20;
		character[mckun].SetTopLeft(character[mckun].Left(), top);
	}

	if (nChar == 0x41) { //A_left
		int left = character[mckun].Left();
		left -= 20;
		character[mckun].SetTopLeft(left, character[mckun].Top());
	}

	if (nChar == 0x53) { //S_down
		int top = character[mckun].Top();
		top += 20;
		character[mckun].SetTopLeft(character[mckun].Left(), top);
	}

	if (nChar == 0x44) { //D_right
		int left = character[mckun].Left();
		left += 20;
		character[mckun].SetTopLeft(left, character[mckun].Top());
	}
	*/
	

}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 0x57 || nChar == 0x41 || nChar == 0x53 || nChar == 0x44) {
		forcestop = true;
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@53
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnShow()
{
	background.ShowBitmap();
	character[mckun].ShowBitmap();
}


void CGameStateRun::show_text_by_phase() {
	CDC *pDC = CDDraw::GetBackCDC();
	CFont* fp;

	CTextDraw::ChangeFontLog(pDC, fp, 21, "�L�n������", RGB(0, 0, 0), 800);

	if (phase == 1 && sub_phase == 1) {
		CTextDraw::Print(pDC, 237, 128, "Current Speed:");
		CTextDraw::Print(pDC, 55, 163, "�N�Ǧ��洫�� resources ���� giraffe.bmp �ϼˡI");
		CTextDraw::Print(pDC, 373, 537, "���U Enter �������");
	} else if (phase == 2 && sub_phase == 1) {
		CTextDraw::Print(pDC, 26, 128, "�U�@�Ӷ��q�A�����V������z�L�W�U���k���ʨ�o�Ӧ�m�I");
		CTextDraw::Print(pDC, 373, 537, "���U Enter �������");
	} else if (phase == 3 && sub_phase == 1) {
		CTextDraw::Print(pDC, 205, 128, "���A�ǳƤF�@���_�c");
		CTextDraw::Print(pDC, 68, 162, "�]�p�{�������V���N���_�c��A�N�_�c�����I");
		CTextDraw::Print(pDC, 68, 196, "�O�o�_�c�n�h�I�A�ϥ� RGB(255, 255, 255)");
		CTextDraw::Print(pDC, 373, 537, "���U Enter �������");
	} else if (phase == 4 && sub_phase == 1) {
		CTextDraw::Print(pDC, 173, 128, "���A�ǳƤF�@�ӻe���n�B��");
		CTextDraw::Print(pDC, 89, 162, "�w�g�������F��V���ʵe�A�����i�H�W�U����");
		CTextDraw::Print(pDC, 110, 196, "�g�ӵ{�������A���e���n�B�;֦��ʵe�I");
		CTextDraw::Print(pDC, 373, 537, "���U Enter �������");
	} else if (phase == 5 && sub_phase == 1) {
		CTextDraw::Print(pDC, 173, 128, "���A�ǳƤF�T����");
		CTextDraw::Print(pDC, 89, 162, "�]�p�{�������V���N�������A���|���}");
		CTextDraw::Print(pDC, 373, 537, "���U Enter �������");
	} else if (phase == 6 && sub_phase == 1) {
		CTextDraw::Print(pDC, 173, 128, "���A�ǳƤF�@���|�˼ƪ��y");
		CTextDraw::Print(pDC, 89, 162, "�]�p�{�����y�˼ơA�M����� OK �ᰱ��ʵe");
		CTextDraw::Print(pDC, 373, 537, "���U Enter �������");
	} else if (sub_phase == 2) {
		CTextDraw::Print(pDC, 268, 128, "�����I");
	}

	CDDraw::ReleaseBackCDC();
}
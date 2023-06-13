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

CGameStateBackroom::CGameStateBackroom(CGame* g) : CGameState(g)
{

}

void CGameStateBackroom::OnInit()
{
	/*for (int i = 0; i < 5; i++) {
		obunga[i].LoadBitmapByString({
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
			"resources/obunga/Obunga30.bmp"
			}, RGB(0, 0, 0));
		obunga[i].SetAnimation(50, false);
		obunga[i].SetTopLeft(0, 0);
	}*/
}

void CGameStateBackroom::OnBeginState()
{

}

void CGameStateBackroom::OnMove()
{
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

void CGameStateBackroom::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateBackroom::OnLButtonDown(UINT nFlags, CPoint point)
{
}

void CGameStateBackroom::OnShow()
{

}


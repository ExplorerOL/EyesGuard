
/*********************************************************************
*                                                                    *
* EyesGuard - cares about youe vision during working on PC!                               *
* Site of program http://eyesguard.ru                                *
*                              					     *
*    © Dmitry Vorobjev (eyesguard@yandex.ru), 2011,                  *
*    © Mihail Buryakov   (mihail.buryakov@gmail.com), 2012,          *
*    © Dmitry Vorobjev (eyesguard@yandex.ru), 2018.                  *
*   This program is free software; you can redistribute it and/or    *
*   modify it under the terms of the GNU General Public License as   *
*   published by the Free Software Foundation; either version 2 of   *
*   the License, or at your option) any later version.               *
*                                                                    *
*   This program is distributed in the hope that it will be useful,  *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of   *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    *
*   GNU General Public License for more details.                     *
*                                                                    *
*   The official publication of the license GNU GPL you can          *
*   find here: http://www.gnu.org/licenses/gpl.html                  *
*                                                                    *
*********************************************************************/

//---------------------------------------------------------------------------

#ifndef MainWnd_UnitH
#define MainWnd_UnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "trayicon.h"
#include <ImgList.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include "BreakWnd_Unit.h"
#include "ProgramState.h"
#include <Graphics.hpp>

//---------------------------------------------------------------------------
class TMainWnd : public TForm
{
__published:	// IDE-managed Components
        TLabel *OptionsLabel;
        TEdit *TimeWorkEdit;
        TEdit *TimeBreakEdit;
        TButton *ButApply;
        TButton *ButExit;
        TTrayIcon *TrayIcon;
        TImageList *TrayImageList;
        TPopupMenu *PopupMenu;
        TMenuItem *PopupExit;
        TTimer *MainTimer;
        TCheckBox *CheckSound;
        TCheckBox *CheckOff;
        TMenuItem *PopupSet;
        TMenuItem *PopupOff;
        TMenuItem *PopupMakeBr;
        TLabel *InfoLabel;
        TMenuItem *PopupBreakLine;
        TMenuItem *PopupTimerReset;
        TImageList *PopupImageList;
        TImage *Image1;
        TButton *ButHide;
        TPanel *Panel1;
        TLabel *TimeWorkLabel;
        TLabel *TimeBreakLabel;
	TCheckBox *CheckActivity;
        void __fastcall ButHideClick(TObject *Sender);
        void __fastcall ButExitClick(TObject *Sender);
        void __fastcall ButApplyClick(TObject *Sender);
        void __fastcall MainTimerTimer(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall TrayIconClick(TObject *Sender);
        void __fastcall TimeWorkEditKeyPress(TObject *Sender, char &Key);
        void __fastcall TimeBreakEditKeyPress(TObject *Sender, char &Key);
        void __fastcall TimeWorkEditClick(TObject *Sender);
        void __fastcall TimeBreakEditClick(TObject *Sender);
        void __fastcall CheckSoundEnter(TObject *Sender);
        void __fastcall CheckOffEnter(TObject *Sender);
        void __fastcall PopupOffClick(TObject *Sender);
        void __fastcall PopupExitClick(TObject *Sender);
        void __fastcall PopupSetClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall PopupMakeBrClick(TObject *Sender);
        void __fastcall PopupTimerResetClick(TObject *Sender);
        void __fastcall TrayIconMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
	void __fastcall CheckActivityEnter(TObject *Sender);
        void __fastcall ShowHintMessage();
        void __fastcall HideHintMessage();

private:	// User declarations

public:		// User declarations
        
        __fastcall TMainWnd(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainWnd *MainWnd;


void updateWindow();
bool updateState();
void CloseWarningMsg();



//---------------------------------------------------------------------------


#endif

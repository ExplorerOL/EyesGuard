
/*********************************************************************
*                                                                    *
* EyesGuard - программа для тех, кто хочет сохранить свое зрение,    *
*             работая на компьютере.                                 *
* Сайт программы www.eyesguard.org                                   *
*    © Воробьев Дмитрий (eyesguard@yandex.ru), 2011,                 *
*    © Буряков Михаил   (mihail.buryakov@gmail.com), 2012.           *
*    Данная программа является свободным программным обеспечением.   *
* Вы вправе распространять ее и/или модифицировать в соответствии    *
* с условиями Генеральной Общественной Лицензии GNU в том виде,      *
* как она была опубликована Фондом Свободного ПО                     *
* (Free Software Foundation); либо версии                            *
* 2 Лицензии либо (по вашему желанию) любой более поздней версии.    *
*                                                                    *
* Программа распространяется в надежде, что она будет полезной,      *
* но БЕЗ КАКИХ БЫ ТО НИ БЫЛО ГАРАНТИЙНЫХ ОБЯЗАТЕЛЬСТВ; даже без      *
* косвенных гарантийных обязательств, связанных с ПОТРЕБИТЕЛЬСКИМИ   *
* СВОЙСТВАМИ и ПРИГОДНОСТЬЮ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Для получения    *
* более подробной информации ознакомьтесь с Генеральной              *
* Общественной Лицензией GNU (http://www.gnu.org/licenses/gpl.html). *
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
#include <Graphics.hpp>
#define TIMERMULT 60000
#define TIMEFIRSTWRN 1
//---------------------------------------------------------------------------
class TMainWnd : public TForm
{
__published:	// IDE-managed Components
        TLabel *OptionsLabel;
        TEdit *TimeWorkEdit;
        TEdit *TimeBreakEdit;
        TLabel *TimeWorkLabel;
        TLabel *TimeBreakLabel;
        TButton *ButCancel;
        TButton *ButApply;
        TButton *ButExit;
        TTrayIcon *TrayIcon;
        TImageList *TrayImageList;
        TPopupMenu *PopupMenu;
        TMenuItem *PopupExit;
        TTimer *Timer;
        TCheckBox *CheckSound;
        TCheckBox *CheckOff;
        TMenuItem *PopupSet;
        TMenuItem *PopupOff;
        TMenuItem *PopupMakeBr;
        TCheckBox *CheckEnMonOff;
        TLabel *InfoLabel;
        TMenuItem *PopupBreakLine;
        TMenuItem *PopupTimerReset;
        TImageList *PopupImageList;
        TImage *Image1;
        TButton *ButOK;
        void __fastcall ButExitClick(TObject *Sender);
        void __fastcall ButApplyClick(TObject *Sender);
        void __fastcall ButCancelClick(TObject *Sender);
        void __fastcall TimerTimer(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
     //   void __fastcall FormCreate(TObject *Sender);
        void __fastcall TrayIconClick(TObject *Sender);
        void __fastcall TimeWorkEditKeyPress(TObject *Sender, char &Key);
        void __fastcall TimeBreakEditKeyPress(TObject *Sender, char &Key);
        void __fastcall TimeWorkEditClick(TObject *Sender);
        void __fastcall TimeBreakEditClick(TObject *Sender);
        void __fastcall CheckEnMonOffEnter(TObject *Sender);
        void __fastcall CheckSoundEnter(TObject *Sender);
        void __fastcall CheckOffEnter(TObject *Sender);
        void __fastcall PopupOffClick(TObject *Sender);
        void __fastcall PopupExitClick(TObject *Sender);
        void __fastcall PopupSetClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall PopupMakeBrClick(TObject *Sender);
        void __fastcall PopupTimerResetClick(TObject *Sender);
        void __fastcall ButOKClick(TObject *Sender);

private:	// User declarations

public:		// User declarations

unsigned char TimeWork;
unsigned char TimeBreak;
bool EnMonOff;
bool Sound;
bool Off;



bool IsBreakNow;
bool IsWarningNow;
unsigned char Counter;

double* BreakWnd1;


        __fastcall TMainWnd(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainWnd *MainWnd;


//---------------------------------------------------------------------------


#endif

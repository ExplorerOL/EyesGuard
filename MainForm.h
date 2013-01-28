
/*********************************************************************
*                                                                    *
* EyesGuard - ��������� ��� ���, ��� ����� ��������� ���� ������,    *
*             ������� �� ����������.                                 *
* ���� ��������� www.eyesguard.org                                   *
*    � �������� ������� (eyesguard@yandex.ru), 2007.                 *
*    ������ ��������� �������� ��������� ����������� ������������.   *
* �� ������ �������������� �� �/��� �������������� � ������������    *
* � ��������� ����������� ������������ �������� GNU � ��� ����,      *
* ��� ��� ���� ������������ ������ ���������� ��                     *
* (Free Software Foundation); ���� ������                            *
* 2 �������� ���� (�� ������ �������) ����� ����� ������� ������.    *
*                                                                    *
* ��������� ���������������� � �������, ��� ��� ����� ��������,      *
* �� ��� ����� �� �� �� ���� ����������� ������������; ���� ���      *
* ��������� ����������� ������������, ��������� � ����������������   *
* ���������� � ������������ ��� ������������ �����. ��� ���������    *
* ����� ��������� ���������� ������������ � �����������              *
* ������������ ��������� GNU (http://www.gnu.org/licenses/gpl.html). *
*                                                                    *
*********************************************************************/

//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "trayicon.h"
#include <ImgList.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include "BreakForm.h"
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
        TButton *ButOK;
        TButton *ButApply;
        TButton *ButExit;
        TTrayIcon *TrayIcon;
        TImageList *ImageList;
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
        void __fastcall ButExitClick(TObject *Sender);
        void __fastcall ButApplyClick(TObject *Sender);
        void __fastcall ButOKClick(TObject *Sender);
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

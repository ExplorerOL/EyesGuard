
/*********************************************************************
*                                                                    *
* EyesGuard - ��������� ��� ���, ��� ����� ��������� ���� ������,    *
*             ������� �� ����������.                                 *
* ���� ��������� www.eyesguard.org                                   *
*    � �������� ������� (eyesguard@yandex.ru), 2011.                 *
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

#include <vcl.h>
#pragma hdrstop

#include "MainWnd_Unit.h"
#include "InputOutput.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
TMainWnd *MainWnd;
TBreakWnd *BreakWnd;

//---------------------------------------------------------------------------
__fastcall TMainWnd::TMainWnd(TComponent* Owner)
        : TForm(Owner)
{
  IsBreakNow = false;
  IsWarningNow = false;
  Counter = 0;

  EnMonOff = true;
  Sound = true;
  Off = false;

  ReadSettings();
  if (!(Off)) Timer->Interval = (MainWnd->TimeWork - TIMEFIRSTWRN)*TIMERMULT;
  Timer->Enabled = true;
  TrayIcon->Visible = false;
  TrayIcon->Visible = true;
  
 
}

//---------------------------------------------------------------------------
void __fastcall TMainWnd::ButExitClick(TObject *Sender)
{
 Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::ButApplyClick(TObject *Sender)
{
 WriteSettings();
 ButApply->Enabled = false;
 CloseWarningMsg();
 FlashWindow(Application->Handle,true);
}
//---------------------------------------------------------------------------
void __fastcall TMainWnd::ButOKClick(TObject *Sender)
{
 UpdateWndSet();
 ButApply->Enabled = false;
 Hide();
}
//---------------------------------------------------------------------------

void __fastcall TMainWnd::TimerTimer(TObject *Sender)
{
  if (IsBreakNow)

        if (IsWarningNow)
             { // ��������� ������ Work �� BreakWarning

               Counter = 0;
               if (EnMonOff) SendMessage(Handle,WM_SYSCOMMAND,SC_MONITORPOWER,-1);
               if (BreakWnd != NULL)
                        {
                         delete BreakWnd;
                         BreakWnd = NULL;
                        }
             //  BreakWnd->Close();
               IsWarningNow = false;
               IsBreakNow = false;
               Timer->Interval = (MainWnd->TimeWork - TIMEFIRSTWRN)*TIMERMULT;
               MainWnd->PopupTimerReset->Enabled = true;
              // Beep(2000,100);

             }
          else
             { // ��������� ������ BreakWarning �� Break

               Timer->Interval = 1000;

               if (Sound)
                { Beep(1000,500);
                  Sleep(1000);
                  Beep(1000,500);
                }

               Counter = 0;

               IsWarningNow = true;
               IsBreakNow = true;
             }


   else if (IsWarningNow)
             { // ��������� ������ Break �� WorkWarning

               if (Counter == 0)
                        {
                         if (BreakWnd == NULL)
                           {
                            BreakWnd = new TBreakWnd( Application );
                            BreakWnd->Cursor = crNone;
                            BreakWnd->SetFocus();
                           }
                         Timer->Interval = 5000;
                         MainWnd->PopupTimerReset->Enabled = false;
                         Counter++;
                         return;
                        }
               if (EnMonOff)
                 {
                  SendMessage(Handle,WM_SYSCOMMAND,SC_MONITORPOWER,1);
                 }

               IsWarningNow = false;
               IsBreakNow = true;
               Timer->Interval = MainWnd->TimeBreak*TIMERMULT;

               Counter = 0;

             }
          else
             { // ��������� ������ WorkWarning �� Work

                Counter++;


           if (Counter == 1) {  Timer->Interval = 3000;
                            MessageBox(NULL, "����� 1 ������ ����� �������!",
                            "EyesGuard !��������! ",MB_SYSTEMMODAL+MB_ICONWARNING);

                             }

           if (Counter == 2)  { CloseWarningMsg();
                            Timer->Interval = TIMERMULT; }
           if (Counter == 3) Timer->Interval = 1000;
           if (Counter == 4) MessageBox(NULL, "����� 10 ������ ����� �������!",
                           "EyesGuard !��������! ", MB_SYSTEMMODAL+MB_ICONWARNING);
           if (Counter == 7) CloseWarningMsg();
           if ((Counter == 10) && (Sound)) Beep(1000,100);
           if ((Counter == 11) && (Sound)) Beep(1000,100);
           if (Counter == 12) { Counter = 0;
                                if (Sound) Beep(1000,500);
                                IsWarningNow = true;
                                IsBreakNow = false; }
          
              }


}
//---------------------------------------------------------------------------

void __fastcall TMainWnd::FormClose(TObject *Sender, TCloseAction &Action)
{
 Action = caNone;
 UpdateWndSet();
 ButApply->Enabled = false;
 Hide();
}
//---------------------------------------------------------------------------

/* ����� ������� ������������� ��������� ���������
void __fastcall TMainWnd::FormCreate(TObject *Sender)
{

//��������� ������� ����������
HANDLE ProcessHandle;
HANDLE ThreadHandle;
DWORD ProcessID = GetCurrentProcessId();
ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS,false,ProcessID);
SetPriorityClass(ProcessHandle,IDLE_PRIORITY_CLASS);
ThreadHandle = GetCurrentThread();
SetThreadPriority(ThreadHandle,THREAD_PRIORITY_LOWEST);


}
*/
//---------------------------------------------------------------------------

void __fastcall TMainWnd::TrayIconClick(TObject *Sender)
{
 Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainWnd::TimeWorkEditKeyPress(TObject *Sender, char &Key)
{
    if  ( ((Key < '0') || (Key > '9')) && (Key != 8) ) Key = 0;
}
//---------------------------------------------------------------------------

void __fastcall TMainWnd::TimeBreakEditKeyPress(TObject *Sender, char &Key)
{
  if  ( ((Key < '0') || (Key > '9')) && (Key != 8) ) Key = 0;
}
//---------------------------------------------------------------------------

void __fastcall TMainWnd::TimeWorkEditClick(TObject *Sender)
{
 ButApply->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainWnd::TimeBreakEditClick(TObject *Sender)
{
  ButApply->Enabled = true;
}
//---------------------------------------------------------------------------


void __fastcall TMainWnd::CheckEnMonOffEnter(TObject *Sender)
{
 ButApply->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainWnd::CheckSoundEnter(TObject *Sender)
{
  ButApply->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainWnd::CheckOffEnter(TObject *Sender)
{
 ButApply->Enabled = true;
}

//---------------------------------------------------------------------------



//Begin Popup Menu---
void __fastcall TMainWnd::PopupExitClick(TObject *Sender)
{
 Application->Terminate();
}

//---------------------------------------------------------------------------

void __fastcall TMainWnd::PopupOffClick(TObject *Sender)
{
 if (BreakWnd != NULL)
        {
         delete BreakWnd;
         BreakWnd = NULL;
        } 


 CheckOff->Checked = !( CheckOff->Checked);
 MainWnd->ButApplyClick(PopupMenu);
}

//---------------------------------------------------------------------------

void __fastcall TMainWnd::PopupSetClick(TObject *Sender)
{
 if (BreakWnd == NULL) Show();
}

//---------------------------------------------------------------------------

void __fastcall TMainWnd::PopupMakeBrClick(TObject *Sender)
{
  Counter = 0;
  IsBreakNow = false;
  IsWarningNow = true;
  CloseWarningMsg();
  MainWnd->TimerTimer(PopupMakeBr);

}
//End Popup Menu---


//---------------------------------------------------------------------------
void __fastcall TMainWnd::FormShow(TObject *Sender)
{
 Left = Screen->Width - Width - 100;
 Top = Screen->Height - Height -100;
}

//---------------------------------------------------------------------------
void __fastcall TMainWnd::PopupTimerResetClick(TObject *Sender)
{
Timer->Enabled = false;

Counter = 0;
IsWarningNow = false;
IsBreakNow = false;
Timer->Interval = (MainWnd->TimeWork - TIMEFIRSTWRN)*TIMERMULT;

Timer->Enabled = true;
}
//---------------------------------------------------------------------------




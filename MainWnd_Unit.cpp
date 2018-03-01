
/*********************************************************************
*                                                                    *
* EyesGuard - ��������� ��� ���, ��� ����� ��������� ���� ������,    *
*             ������� �� ����������.                                 *
* ���� ���������                                                     *
*    � �������� ������� (eyesguard@yandex.ru), 2011,                 *
*    � ������� ������   (mihail.buryakov@gmail.com), 2012,           *
*    � �������� ������� (eyesguard@yandex.ru), 2018.                 *
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
//����������� �������� ����
__fastcall TMainWnd::TMainWnd(TComponent* Owner)
        : TForm(Owner)
{
//��� ������� ��������� ������������� ��������� �� ���������
  EnMonOff = true;
  Sound = true;
  Off = false;

//��������� ��������� �� �����, ���� ��� ���� ���������
  ReadSettings();
//���������� ������
  PopupTimerResetClick(MainWnd);


//�� �������, ������ ������� TrayIcon ������ ���� false, �� ����� �� ��������
  TrayIcon->Visible = false;
  TrayIcon->Visible = true;



}

//---------------------------------------------------------------------------
//������ ������ �����
void __fastcall TMainWnd::ButExitClick(TObject *Sender)
{
 Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TMainWnd::ButHideClick(TObject *Sender)
{
 UpdateWndSet();
 ButApply->Enabled = false;
 CloseWarningMsg();
 FlashWindow(Application->Handle,true);
 Hide();

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

void __fastcall TMainWnd::MainTimerTimer(TObject *Sender)
{
  if (IsBreakNow)

        if (IsWarningNow)
             { // ��������� ������ Work �� BreakWarning


               if (EnMonOff) SendMessage(Handle,WM_SYSCOMMAND,SC_MONITORPOWER,-1);
               if (BreakWnd != NULL)
                        {
                         delete BreakWnd;
                         BreakWnd = NULL;
                        }

               PopupTimerResetClick(Sender);
               MainWnd->PopupTimerReset->Enabled = true;
           

             }
          else
             { // ��������� ������ BreakWarning �� Break

               MainTimer->Interval = 1000;

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
                         MainTimer->Interval = 5000;
                         MainWnd->PopupTimerReset->Enabled = false;
                         Counter++;
                         return;
                        }
               if (EnMonOff)
                 {
                  SendMessage(Handle,WM_SYSCOMMAND,SC_MONITORPOWER,2);
                 }

               IsWarningNow = false;
               IsBreakNow = true;
               MainTimer->Interval = MainWnd->TimeBreak*TIMERMULT;

               Counter = 0;

             }
          else
             { // ��������� ������ WorkWarning �� Work

                Counter++;


           if (Counter == 1) {  MainTimer->Interval = 3000;
                            MessageBox(NULL, "����� 1 ������ ����� �������!",
                            "EyesGuard !��������! ",MB_SYSTEMMODAL+MB_ICONWARNING);

                             }

           if (Counter == 2)  { CloseWarningMsg();
                            MainTimer->Interval = TIMERMULT; }
           if (Counter == 3) MainTimer->Interval = 1000;
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
//������� �� ������ � ����
void __fastcall TMainWnd::TrayIconClick(TObject *Sender)
{
 Show();
}
//---------------------------------------------------------------------------
//�������� ����� ���� � ���� ������������ ��������
void __fastcall TMainWnd::TimeWorkEditKeyPress(TObject *Sender, char &Key)
{
    if  ( ((Key < '0') || (Key > '9')) && (Key != 8) ) Key = 0;
}
//---------------------------------------------------------------------------
//�������� ����� ���� � ���� ������� ����� ����������
void __fastcall TMainWnd::TimeBreakEditKeyPress(TObject *Sender, char &Key)
{
  if  ( ((Key < '0') || (Key > '9')) && (Key != 8) ) Key = 0;
}
//---------------------------------------------------------------------------
//������ �� ���� ����� ����� ����������
void __fastcall TMainWnd::TimeWorkEditClick(TObject *Sender)
{
 ButApply->Enabled = true;
}
//---------------------------------------------------------------------------
//������ �� ���� ������������ ��������
void __fastcall TMainWnd::TimeBreakEditClick(TObject *Sender)
{
  ButApply->Enabled = true;
}
//---------------------------------------------------------------------------
//��������� ��������� "��������� �������"

void __fastcall TMainWnd::CheckEnMonOffEnter(TObject *Sender)
{
 ButApply->Enabled = true;
}
//---------------------------------------------------------------------------
//��������� ��������� "�������� ����������"
void __fastcall TMainWnd::CheckSoundEnter(TObject *Sender)
{
  ButApply->Enabled = true;
}
//---------------------------------------------------------------------------
//��������� ��������� "���������"
void __fastcall TMainWnd::CheckOffEnter(TObject *Sender)
{
 ButApply->Enabled = true;
}

//---------------------------------------------------------------------------
//Begin Popup Menu---

//---------------------------------------------------------------------------
//������ ����� "�����" � ����������� ����
void __fastcall TMainWnd::PopupExitClick(TObject *Sender)
{
 Application->Terminate();
}

//---------------------------------------------------------------------------
//������ ����� "���������" � ����������� ����

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
//������ ����� "���������" � ������������ ���� -> �������� ������� ����

void __fastcall TMainWnd::PopupSetClick(TObject *Sender)
{
 if (BreakWnd == NULL) Show();
}

//---------------------------------------------------------------------------
//������ ����� "������� �������" � ������������ ����
void __fastcall TMainWnd::PopupMakeBrClick(TObject *Sender)
{
  Counter = 0;
  IsBreakNow = false;
  IsWarningNow = true;
  CloseWarningMsg();
  MainWnd->MainTimerTimer(PopupMakeBr);

}
//End Popup Menu---


//---------------------------------------------------------------------------
void __fastcall TMainWnd::FormShow(TObject *Sender)
{
 Left = Screen->Width - Width - 100;
 Top = Screen->Height - Height -100;
}

//---------------------------------------------------------------------------
//������ ����� "�������� ������" � ������������ ����
//BreakTime - ����� �� ��������
void __fastcall TMainWnd::PopupTimerResetClick(TObject *Sender)
{
MainTimer->Enabled = false;

Counter = 0;
IsWarningNow = false;
IsBreakNow = false;

  if (!(Off)) {
    MainTimer->Interval = (MainWnd->TimeWork - TIMEFIRSTWRN)*TIMERMULT;
    BreakTime = Now();
    BreakTime += MainWnd->TimeWork * TIMEMULT;
  }
MainTimer->Enabled = true;
}





//---------------------------------------------------------------------------
//������� ����������� ������� �� �������� ��� ��������� ���� �� ������ � ����
void __fastcall TMainWnd::HintTimerTimer(TObject *Sender)
{
  if (!Off) {
    MainWnd->TrayIcon->Hint = "Eyesguard\n�� �������� " + (BreakTime-Now()).FormatString("h:mm:ss");
  } else {
    MainWnd->TrayIcon->Hint = "Eyesguard\n���������";
  }
}
//---------------------------------------------------------------------------




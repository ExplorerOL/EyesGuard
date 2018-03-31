
/*********************************************************************
*                                                                    *
* EyesGuard - ��������� ��� ���, ��� ����� ��������� ���� ������,    *
*             ������� �� ����������.                                 *
* ���� ��������� http://eyesguard.ru                                 *
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


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"

TMainWnd *MainWnd;
extern TBreakWnd *BreakWnd;

THintWindow *hintMessage = NULL;




//---------------------------------------------------------------------------
//����������� �������� ����
__fastcall TMainWnd::TMainWnd(TComponent* Owner)
        : TForm(Owner)
{

  //��������� ���� ����� � ������������ ���� ����������� ����������
  updateWindow();

  //���������� � ��������� ������
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

 CloseWarningMsg();
 Hide();

}

//---------------------------------------------------------------------------
void __fastcall TMainWnd::ButApplyClick(TObject *Sender)
{
 if ( updateState() )
 {
 	ButApply->Enabled = false;
	CloseWarningMsg();
 }
}

//---------------------------------------------------------------------------
//��������� ������� �������
void __fastcall TMainWnd::MainTimerTimer(TObject *Sender)
{
	EGState.timerTick();

}
//---------------------------------------------------------------------------

void __fastcall TMainWnd::FormClose(TObject *Sender, TCloseAction &Action)
{
 Action = caNone;
 Hide();

}

//---------------------------------------------------------------------------
//������� ��� �� ������ � ����
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
  CloseWarningMsg();
  EGState.takeBreak();

}
//End Popup Menu---


//---------------------------------------------------------------------------
void __fastcall TMainWnd::FormShow(TObject *Sender)
{
 Left = Screen->Width - Width - 100;
 Top = Screen->Height - Height -100;

//��� ������ ����� ��������� ��������� ��������
 updateWindow();
 ButApply->Enabled = false;
}

//---------------------------------------------------------------------------
//������ ����� "�������� ������" � ������������ ����
//BreakTime - ����� �� ��������
void __fastcall TMainWnd::PopupTimerResetClick(TObject *Sender)
{
   EGState.resetCounterTimeWork();

}





//---------------------------------------------------------------------------
//������� ����������� ������� �� �������� ��� ��������� ���� �� ������ � ����

void __fastcall TMainWnd::TrayIconMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
   TDateTime timeWorkLeft;

   //1 = 24 ����. 1 ����� �� ���������� ������ � ������ (24*60*60) � �������� �� ���-�� ������
   timeWorkLeft = EGState.getTimeWorkLeft();
   MainWnd->TrayIcon->Hint = "EyesGuard\n�� �������� " + timeWorkLeft.FormatString("h:mm:ss");


}
//---------------------------------------------------------------------------



//���������� �������� � ����� ����� �������� ���� � ������������ �� ���������� ����������
void updateWindow()
{
	//�������� ������� ���������
	Settings currentSettings;
        currentSettings = EGState.getSettings();

	//������� ���������� ��������� � ������� ����
	MainWnd->TimeWorkEdit->Text = IntToStr(currentSettings.timeWork);
	MainWnd->TimeBreakEdit->Text = IntToStr(currentSettings.timeBreak);
        MainWnd->CheckActivity->Checked = currentSettings.monitorUserActivity;
	MainWnd->CheckSound->Checked = currentSettings.soundOn;
	MainWnd->CheckOff->Checked = currentSettings.programTurnedOff;

	if (currentSettings.programTurnedOff) MainWnd->PopupOff->Caption = "��������";
               else MainWnd->PopupOff->Caption = "���������";

       	if (currentSettings.programTurnedOff)
         {
          MainWnd->TrayIcon->IconIndex = 1;
          MainWnd->PopupMakeBr->Enabled = false;
          MainWnd->PopupTimerReset->Enabled = false;
          MainWnd->PopupOff->ImageIndex = 1;
         }
    else
         {
          MainWnd->TrayIcon->IconIndex = 0;
          MainWnd->PopupMakeBr->Enabled = true;
          MainWnd->PopupTimerReset->Enabled = true;
          MainWnd->PopupOff->ImageIndex = 2;
         } 

}


//������ ���������� �� ���� ����� � ���������� ��������� � ���� ��������
bool updateState()
{

	Settings currentSettings;
        
 	if ( (StrToInt(MainWnd->TimeWorkEdit->Text) < 5) || (StrToInt(MainWnd->TimeWorkEdit->Text) > 120) )
	     {
	       MessageBox(MainWnd->Handle, "����� ����� ���������� ������ ���� �� 5 �� 120 �����!", "��������!", MB_OK);
       	       return false;
             }
	currentSettings.timeWork = StrToInt(MainWnd->TimeWorkEdit->Text);


	if ( (StrToInt(MainWnd->TimeBreakEdit->Text) < 1) || (StrToInt(MainWnd->TimeBreakEdit->Text) > 30) )
	     {
       	       MessageBox(MainWnd->Handle, "����� �������� ������ ���� �� 1 �� 30 �����!", "��������!", MB_OK);
	       return false;
	     }
	currentSettings.timeBreak = StrToInt(MainWnd->TimeBreakEdit->Text);

        currentSettings.monitorUserActivity = MainWnd->CheckActivity->Checked;
  	currentSettings.soundOn = MainWnd->CheckSound->Checked;
	currentSettings.programTurnedOff = MainWnd->CheckOff->Checked;

	if (MainWnd->CheckOff->Checked) MainWnd->PopupOff->Caption = "��������";
               else MainWnd->PopupOff->Caption = "���������";


  if (MainWnd->CheckOff->Checked)
         {
           MainWnd->TrayIcon->IconIndex = 1;
           MainWnd->MainTimer->Interval = 0;
           MainWnd->PopupMakeBr->Enabled = false;
           MainWnd->PopupTimerReset->Enabled = false;
           MainWnd->PopupOff->ImageIndex = 1;
         }
    else
         {
           MainWnd->TrayIcon->IconIndex = 0;
           MainWnd->PopupTimerResetClick(MainWnd->ButApply);
           MainWnd->PopupMakeBr->Enabled = true;
           MainWnd->PopupTimerReset->Enabled = true;
           MainWnd->PopupOff->ImageIndex = 2;
         }


    EGState.setSettings(currentSettings);

  
return true;
}


//�������� ������������ ����
void CloseWarningMsg()
{
  HWND MesWndHandle = FindWindow(NULL, "EyesGuard !��������! ");
  if (MesWndHandle != NULL)  SendMessage(MesWndHandle, WM_CLOSE, 0,0);

}



void __fastcall TMainWnd::CheckActivityEnter(TObject *Sender)
{
  ButApply->Enabled = true;	
}
//---------------------------------------------------------------------------



//����������� ��������� � ������������ ������������ � ���� ������. ���������
void __fastcall TMainWnd::ShowHintMessage()
{


	if(hintMessage == NULL)
	  {
	    hintMessage=new THintWindow(this);
	    hintMessage->Brush->Color=clInfoBk;
	    hintMessage->Font->Color=clInfoText;
	    hintMessage->ParentWindow=Handle;


            hintMessage->Left = 0;
            hintMessage->Top = 0;
	    TPoint p(Screen->Width - 450 ,Screen->Height - 70);

	    TRect rc = hintMessage->CalcHintRect(400, "EyesGuard \n ������ ������� ������������� - ������������ �� �������!" ,NULL);
	    OffsetRect(&rc,p.x,p.y);
	    hintMessage->ActivateHint(rc, "EyesGuard \n ������ ������� ������������� - ������������ �� �������!");

          }

}

//������� ��������� � ������������ ������������ � ���� ������. ���������
void __fastcall TMainWnd::HideHintMessage()
{
   if (hintMessage != NULL)
        {
            hintMessage->ReleaseHandle();
            hintMessage = NULL;
        }

}


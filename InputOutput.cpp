
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
#pragma hdrstop
#include "InputOutput.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

#define setfilename "set.dat"
#define setfiledir  "."
#define setfile     setfiledir "\\" setfilename


//������ �������� �� �����

void ReadSettings()
{
   int fileHandle;
   unsigned char Value;

// �������� �����
if ((fileHandle = open(setfile, O_RDONLY | O_BINARY , S_IREAD)) != -1)
{


// ������ ��������� ������� ����� ����������
   if ( (read(fileHandle, &Value, 1)) == -1 )
    {
      MessageBox(MainWnd->Handle, "������ ��� ������ ����� " setfile "!", "��������!", MB_OK);
      MainWnd->TimeWork = 30;
    }

// ��������
   else if ( (Value >= 5) && (Value <= 120))
                     {
                      MainWnd->TimeWork = Value;
                     }
     else
      {
       MessageBox(MainWnd->Handle, "������������ ����� ����� ����������!", "��������!", MB_OK);
       MainWnd->TimeWork = 30;
      }


//  ������ ������������ ��������
   lseek(fileHandle, 2,SEEK_SET);
   if ( (read(fileHandle, &Value, 1)) == -1 )
    {
      MessageBox(MainWnd->Handle, "������ ��� ������ ����� " setfile "!", "��������!", MB_OK);
      MainWnd->TimeBreak = 10;
    }

// ��������
   else if ( (Value >= 1) && (Value <= 30) )
                     {
                      MainWnd->TimeBreak = Value;
                     }

     else
      {
       MessageBox(MainWnd->Handle, "������������ ����� ��������!", "��������!", MB_OK);
       MainWnd->TimeBreak = 10;
      }


//������ �������� ���������� ��������
   lseek(fileHandle, 4,SEEK_SET);
   if ( (read(fileHandle, &Value, 1)) == -1 )
    {
      MessageBox(MainWnd->Handle, "������ ��� ������ ����� " setfile "!", "��������!", MB_OK);
      MainWnd->EnMonOff = false;
    }
   else MainWnd->EnMonOff = Value;


//������ �������� ��������� ����������
   lseek(fileHandle, 6,SEEK_SET);
   if ( (read(fileHandle, &Value, 1)) == -1 )
    {
      MessageBox(MainWnd->Handle, "������ ��� ������ ����� " setfile "!", "��������!", MB_OK);
      MainWnd->Sound = true;
    }
   else MainWnd->Sound = Value;

//������ ��������� "���������"
   lseek(fileHandle, 8,SEEK_SET);
   if ( (read(fileHandle, &Value, 1)) == -1 )
    {
      MessageBox(MainWnd->Handle, "������ ��� ������ ����� " setfile "!", "��������!", MB_OK);
      MainWnd->Off = false;
    }
   else MainWnd->Off = Value;

   close(fileHandle);

}
else
{
//      MessageBox(MainWnd->Handle, "������ ��� ��������  �� ������ ����� " setfile "!", "��������!", MB_OK);
    // ��������� ���������� �� ���������
      MainWnd->TimeWork = 30;
      MainWnd->TimeBreak = 10;
      MainWnd->EnMonOff = false;
      MainWnd->Sound = true;
      MainWnd->Off = false;
}









   UpdateWndSet();
}


void WriteSettings()
{
   int fileHandle;

// �������� �����

   if (!DirectoryExists(setfiledir)) {
       CreateDir(setfiledir);
   }

   if ((fileHandle = open(setfile,
             O_WRONLY | O_CREAT  | O_BINARY, S_IWRITE)) == -1) //| O_TRUNC
    {


      MessageBox(MainWnd->Handle, "������ ��� �������� �� ������ ����� " setfile "!", "��������!", MB_OK);


      return;
    }

 if ( !(UpdateProgramSet()) ) return;


// ������ ��������� ������� ����� ����������
   if ( write(fileHandle, &(MainWnd->TimeWork), 1 ) != 1)
    {
      MessageBox(MainWnd->Handle, "������ ��� ������ � ���� set.dat", "��������!", MB_OK);
      return;
    }

// ������ ������������ ��������
   lseek(fileHandle, 2,SEEK_SET);
   if ( write(fileHandle, &(MainWnd->TimeBreak), 1 ) != 1)
    {
      MessageBox(MainWnd->Handle, "������ ��� ������ � ���� set.dat", "��������!", MB_OK);
      return;
    }

// ������ �������� ���������� ��������
   lseek(fileHandle, 4,SEEK_SET);
   if ( write(fileHandle, &(MainWnd->EnMonOff), 1 ) != 1)
    {
      MessageBox(MainWnd->Handle, "������ ��� ������ � ���� set.dat", "��������!", MB_OK);
      return;
    }

// ������ �������� ��������� ����������
   lseek(fileHandle, 6,SEEK_SET);
   if ( write(fileHandle, &(MainWnd->Sound), 1 ) != 1)
    {
      MessageBox(MainWnd->Handle, "������ ��� ������ � ���� set.dat", "��������!", MB_OK);
      return;
    }

// ������ ��������� "���������"
   lseek(fileHandle, 8,SEEK_SET);
   if ( write(fileHandle, &(MainWnd->Off), 1 ) != 1)
    {
      MessageBox(MainWnd->Handle, "������ ��� ������ � ���� set.dat", "��������!", MB_OK);
      return;
    }

   close(fileHandle);

}


//���������� �������� � ����� ����� �������� ���� � ������������ �� ���������� ����������
void UpdateWndSet()
{

  MainWnd->TimeWorkEdit->Text = IntToStr(MainWnd->TimeWork);
  MainWnd->TimeBreakEdit->Text = IntToStr(MainWnd->TimeBreak);
  MainWnd->CheckSound->Checked = MainWnd->Sound;
  MainWnd->CheckOff->Checked = MainWnd->Off;

  if (MainWnd->Off) MainWnd->PopupOff->Caption = "��������";
               else MainWnd->PopupOff->Caption = "���������";

  MainWnd->CheckEnMonOff->Checked = MainWnd->EnMonOff;
  if (MainWnd->Off)
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


//������ ���������� �� ���� ����� � ���������� ���������
bool UpdateProgramSet()
{
  MainWnd->Counter = 0;


  MainWnd->TimeBreak = StrToInt(MainWnd->TimeBreakEdit->Text);



  if ( (StrToInt(MainWnd->TimeWorkEdit->Text) < 5) ||
       (StrToInt(MainWnd->TimeWorkEdit->Text) > 120) )
     {
       MessageBox(MainWnd->Handle, "����� ����� ���������� ������ ���� �� 5 �� 120 �����!", "��������!", MB_OK);
       return false;
     }
  MainWnd->TimeWork = StrToInt(MainWnd->TimeWorkEdit->Text);


  if ( (StrToInt(MainWnd->TimeBreakEdit->Text) < 1) ||
       (StrToInt(MainWnd->TimeBreakEdit->Text) > 30) )
     {
       MessageBox(MainWnd->Handle, "����� �������� ������ ���� �� 1 �� 30 �����!", "��������!", MB_OK);
       return false;
     }
  MainWnd->TimeBreak = StrToInt(MainWnd->TimeBreakEdit->Text);


  MainWnd->Sound = MainWnd->CheckSound->Checked;
  MainWnd->Off = MainWnd->CheckOff->Checked;
  if (MainWnd->Off) MainWnd->PopupOff->Caption = "��������";
               else MainWnd->PopupOff->Caption = "���������";

  MainWnd->EnMonOff = MainWnd->CheckEnMonOff->Checked;
  if (MainWnd->Off)
         {
           MainWnd->TrayIcon->IconIndex = 1;
           MainWnd->Timer->Interval = 0;
           MainWnd->PopupMakeBr->Enabled = false;
           MainWnd->PopupTimerReset->Enabled = false;
           MainWnd->PopupOff->ImageIndex = 1;
         }
    else
         {
           MainWnd->TrayIcon->IconIndex = 0;
           //MainWnd->Timer->Interval = (MainWnd->TimeWork - TIMEFIRSTWRN)*TIMERMULT;
           MainWnd->PopupTimerResetClick(MainWnd->ButApply);
           MainWnd->PopupMakeBr->Enabled = true;
           MainWnd->PopupTimerReset->Enabled = true;
           MainWnd->PopupOff->ImageIndex = 2;
         }
  
return true;
}

void CloseWarningMsg()
{
  HWND MesWndHandle = FindWindow(NULL, "EyesGuard !��������! ");
  if (MesWndHandle != NULL)  SendMessage(MesWndHandle, WM_CLOSE, 0,0);

}



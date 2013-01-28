
/***************************************************************************
 *   Copyright (C) 2008 by Vorobyov Dmitry                                 *
 *   eyesguard@yandex.ru                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   The official publication of the license GNU GPL you can find here:    *
 *   http://www.gnu.org/licenses/gpl.html                                  *
 ***************************************************************************/

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
#include "InputOutput.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
TMainWnd *MainWnd;

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
  if (!(Off)) Timer->Interval = TimeWork*TIMERMULT;

 
}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TMainWnd::ButExitClick(TObject *Sender)
{
 Close();
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
             { // Установка режима Work

               Counter = 0;
               if (EnMonOff) SendMessage(Handle,WM_SYSCOMMAND,SC_MONITORPOWER,-1);
               delete BreakWnd;
               BreakWnd = NULL;
               IsBreakNow = !(IsBreakNow);
               Timer->Interval = (MainWnd->TimeWork - TIMEFIRSTWRN)*TIMERMULT;


             }
          else
             { // Установка режима BreakWarning

               Timer->Interval = 1000;
               if (!Sound) Counter = 50;
               while (Counter < 5)
                {
                 Counter++;
                 Beep(1000,100);
                 return;
                }
               Counter = 0;
               Beep(1000,500);
           

             }
   else if (IsWarningNow)
             { // Установка режима Break

               if (Counter == 0)
                        {
                         if (BreakWnd == NULL)
                           {
                            Application->CreateForm(__classid(TBreakWnd), &BreakWnd);
                            BreakWnd->Cursor = crNone;
                            BreakWnd->SetFocus();
                           }
                         Timer->Interval = 5000;
                         Counter++;
                         return;
                        }
               if (EnMonOff)
                 {
                  SendMessage(Handle,WM_SYSCOMMAND,SC_MONITORPOWER,1);
                 }
               IsBreakNow = !(IsBreakNow);

               Timer->Interval = MainWnd->TimeBreak*TIMERMULT;
               Counter = 0;
             }
          else
             { // Установка режима WorkWarning

              if (Counter == 0)
                         {
                           Counter++;
                           Timer->Interval = 3000;
                           MessageBox(NULL, "In 1 minute there will be a break!",
                           "EyesGuard !Warning! ",MB_SYSTEMMODAL+MB_ICONWARNING);
                           return;
                          }
              if (Counter == 1)
                         {
                           Counter++;
                           CloseWarningMsg();
                           Timer->Interval = TIMERMULT;
                           return;
                          }

              Timer->Interval = 1000;

              while (Counter < 11)
                {
                 Counter++;
                 if (Sound) Beep(1000,100);
                 if (Counter == 6)
                      {
                       CloseWarningMsg();
                      }
                 if (Counter == 3)
                        {
                           MessageBox(NULL, "In 10 seconds there will be a break!",
                           "EyesGuard !Warning! ", MB_SYSTEMMODAL+MB_ICONWARNING);
                        }
                 return;
                }

               Counter = 0;
               Beep(1000,500);
            }
IsWarningNow = !(IsWarningNow);
}
//---------------------------------------------------------------------------

void __fastcall TMainWnd::FormClose(TObject *Sender, TCloseAction &Action)
{
 if (TrayIcon->Visible) TrayIcon->Visible = false;
}
//---------------------------------------------------------------------------

/* Может вызвать заторможенное поведение программы
void __fastcall TMainWnd::FormCreate(TObject *Sender)
{

//Установка низкого приоритета
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
 Close();
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














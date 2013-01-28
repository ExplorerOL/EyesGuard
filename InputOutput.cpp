
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
#pragma hdrstop
#include "InputOutput.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

void ReadSettings()
{
   int fileHandle;
   unsigned char Value;

// Открытие файла
   if ((fileHandle = open("set.dat",
             O_RDONLY | O_BINARY , S_IREAD)) == -1)
    {
//      MessageBox(MainWnd->Handle, "Ошибка при открытии  на чтение файла set.dat", "Внимание!", MB_OK);
      return;
    }


// Чтение интервала времени между перерывами
   if ( (read(fileHandle, &Value, 1)) == -1 )
    {
      MessageBox(MainWnd->Handle, "Reading error (file set.dat)!", "Warning!", MB_OK);
      return;
    }


// Проверка
   if ( (Value >= 5) && (Value <= 120))
                     {
                      MainWnd->TimeWork = Value;
                     }
     else
      {
       MessageBox(MainWnd->Handle, "Work time is incorrect!", "Warning!", MB_OK);
       MainWnd->TimeWork = 30;
      }


//  Чтение длительности перерыва
   lseek(fileHandle, 2,SEEK_SET);
   if ( (read(fileHandle, &Value, 1)) == -1 )
    {
      MessageBox(MainWnd->Handle, "Reading error (file set.dat)!", "Warning!", MB_OK);
      return;
    }


// Проверка
   if ( (Value >= 1) && (Value <= 30) )
                     {
                      MainWnd->TimeBreak = Value;
                     }
     else
      {
       MessageBox(MainWnd->Handle, "Break time is incorrect!", "Warning!", MB_OK);
       MainWnd->TimeBreak = 10;
      }


//Чтение настроек отключения монитора
   lseek(fileHandle, 4,SEEK_SET);
   if ( (read(fileHandle, &Value, 1)) == -1 )
    {
      MessageBox(MainWnd->Handle, "Reading error (file set.dat)!", "Warning!", MB_OK);
      return;
    }
   MainWnd->EnMonOff = Value;


//Чтение настроек звукового оповещения
   lseek(fileHandle, 6,SEEK_SET);
   if ( (read(fileHandle, &Value, 1)) == -1 )
    {
      MessageBox(MainWnd->Handle, "Reading error (file set.dat)!", "Warning!", MB_OK);
      return;
    }
   MainWnd->Sound = Value;

//Чтение настройки "Выключить"
   lseek(fileHandle, 8,SEEK_SET);
   if ( (read(fileHandle, &Value, 1)) == -1 )
    {
      MessageBox(MainWnd->Handle, "Reading error (file set.dat)!", "Warning!", MB_OK);
      return;
    }
   MainWnd->Off = Value;

   
   close(fileHandle);
   UpdateWndSet();
}


void WriteSettings()
{
   int fileHandle;

// Открытие файла
   if ((fileHandle = open("set.dat",
             O_WRONLY | O_CREAT  | O_BINARY, S_IWRITE)) == -1) //| O_TRUNC
    {


      MessageBox(MainWnd->Handle, "Writing error (file set.dat)!", "Warning!", MB_OK);


      return;
    }

 if ( !(UpdateProgramSet()) ) return;


// Запись интервала времени между перерывами
   if ( write(fileHandle, &(MainWnd->TimeWork), 1 ) != 1)
    {
      MessageBox(MainWnd->Handle, "Writing error (file set.dat)", "Warning!", MB_OK);
      return;
    }

// Запись длительности перерыва
   lseek(fileHandle, 2,SEEK_SET);
   if ( write(fileHandle, &(MainWnd->TimeBreak), 1 ) != 1)
    {
      MessageBox(MainWnd->Handle, "Writing error (file set.dat)", "Warning!", MB_OK);
      return;
    }

// Запись настроек отключения монитора
   lseek(fileHandle, 4,SEEK_SET);
   if ( write(fileHandle, &(MainWnd->EnMonOff), 1 ) != 1)
    {
      MessageBox(MainWnd->Handle, "Writing error (file set.dat)", "Warning!", MB_OK);
      return;
    }

// Запись настроек звукового оповещения
   lseek(fileHandle, 6,SEEK_SET);
   if ( write(fileHandle, &(MainWnd->Sound), 1 ) != 1)
    {
      MessageBox(MainWnd->Handle, "Writing error (file set.dat)", "Warning!", MB_OK);
      return;
    }

// Запись настройки "Выключить"
   lseek(fileHandle, 8,SEEK_SET);
   if ( write(fileHandle, &(MainWnd->Off), 1 ) != 1)
    {
      MessageBox(MainWnd->Handle, "Writing error (file set.dat)", "Warning!", MB_OK);
      return;
    }

   close(fileHandle);

}



void UpdateWndSet()
{

  MainWnd->TimeWorkEdit->Text = IntToStr(MainWnd->TimeWork);
  MainWnd->TimeBreakEdit->Text = IntToStr(MainWnd->TimeBreak);
  MainWnd->CheckSound->Checked = MainWnd->Sound;
  MainWnd->CheckOff->Checked = MainWnd->Off;

  if (MainWnd->Off) MainWnd->PopupOff->Caption = "Switch on";
               else MainWnd->PopupOff->Caption = "Switch off";

  MainWnd->CheckEnMonOff->Checked = MainWnd->EnMonOff;
  if (MainWnd->Off)
         {
          MainWnd->TrayIcon->IconIndex = 1;
          MainWnd->PopupMakeBr->Enabled = false;
         }
    else
         {
          MainWnd->TrayIcon->IconIndex = 0;
          MainWnd->PopupMakeBr->Enabled = true;
         } 

}



bool UpdateProgramSet()
{
  MainWnd->Counter = 0;


  MainWnd->TimeBreak = StrToInt(MainWnd->TimeBreakEdit->Text);



  if ( (StrToInt(MainWnd->TimeWorkEdit->Text) < 5) ||
       (StrToInt(MainWnd->TimeWorkEdit->Text) > 120) )
     {
       MessageBox(MainWnd->Handle, "Work time should be in the interval from 5 to 120 minutes", "Warning!", MB_OK);
       return false;
     }
  MainWnd->TimeWork = StrToInt(MainWnd->TimeWorkEdit->Text);


  if ( (StrToInt(MainWnd->TimeBreakEdit->Text) < 1) ||
       (StrToInt(MainWnd->TimeBreakEdit->Text) > 30) )
     {
       MessageBox(MainWnd->Handle, "Break time should be in the interval from 1 to 30 minutes!", "Warning!", MB_OK);
       return false;
     }
  MainWnd->TimeBreak = StrToInt(MainWnd->TimeBreakEdit->Text);


  MainWnd->Sound = MainWnd->CheckSound->Checked;
  MainWnd->Off = MainWnd->CheckOff->Checked;
  if (MainWnd->Off) MainWnd->PopupOff->Caption = "Switch on";
               else MainWnd->PopupOff->Caption = "Switch off";

  MainWnd->EnMonOff = MainWnd->CheckEnMonOff->Checked;
  if (MainWnd->Off)
         {
           MainWnd->TrayIcon->IconIndex = 1;
           MainWnd->Timer->Interval = 0;
           MainWnd->PopupMakeBr->Enabled = false;
         }
    else
         {
           MainWnd->TrayIcon->IconIndex = 0;
           MainWnd->Timer->Interval = MainWnd->TimeWork*TIMERMULT;
           MainWnd->PopupMakeBr->Enabled = true;
         }

return true;
}

void CloseWarningMsg()
{
  HWND MesWndHandle = FindWindow(NULL, "EyesGuard !Warning! ");
  if (MesWndHandle != NULL)  SendMessage(MesWndHandle, WM_CLOSE, 0,0);

}




/*********************************************************************
*                                                                    *
* EyesGuard - программа для тех, кто хочет сохранить свое зрение,    *
*             работая на компьютере.                                 *
* Сайт программы                                                     *
*    © Воробьев Дмитрий (eyesguard@yandex.ru), 2011,                 *
*    © Буряков Михаил   (mihail.buryakov@gmail.com), 2012,           *
*    © Воробьев Дмитрий (eyesguard@yandex.ru), 2018.                 *
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
#pragma hdrstop
#include "InputOutput.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

#define setfilename "set.dat"
#define setfiledir  "."
#define setfile     setfiledir "\\" setfilename


//Чтение настроек из файла

void ReadSettings()
{
   int fileHandle;
   unsigned char Value;

// Открытие файла
if ((fileHandle = open(setfile, O_RDONLY | O_BINARY , S_IREAD)) != -1)
{


// Чтение интервала времени между перерывами
   if ( (read(fileHandle, &Value, 1)) == -1 )
    {
      MessageBox(MainWnd->Handle, "Ошибка при чтении файла " setfile "!", "Внимание!", MB_OK);
      MainWnd->TimeWork = 30;
    }

// Проверка
   else if ( (Value >= 5) && (Value <= 120))
                     {
                      MainWnd->TimeWork = Value;
                     }
     else
      {
       MessageBox(MainWnd->Handle, "Некорректное время между перерывами!", "Внимание!", MB_OK);
       MainWnd->TimeWork = 30;
      }


//  Чтение длительности перерыва
   lseek(fileHandle, 2,SEEK_SET);
   if ( (read(fileHandle, &Value, 1)) == -1 )
    {
      MessageBox(MainWnd->Handle, "Ошибка при чтении файла " setfile "!", "Внимание!", MB_OK);
      MainWnd->TimeBreak = 10;
    }

// Проверка
   else if ( (Value >= 1) && (Value <= 30) )
                     {
                      MainWnd->TimeBreak = Value;
                     }

     else
      {
       MessageBox(MainWnd->Handle, "Некорректное время перерыва!", "Внимание!", MB_OK);
       MainWnd->TimeBreak = 10;
      }


//Чтение настроек отключения монитора
   lseek(fileHandle, 4,SEEK_SET);
   if ( (read(fileHandle, &Value, 1)) == -1 )
    {
      MessageBox(MainWnd->Handle, "Ошибка при чтении файла " setfile "!", "Внимание!", MB_OK);
      MainWnd->EnMonOff = false;
    }
   else MainWnd->EnMonOff = Value;


//Чтение настроек звукового оповещения
   lseek(fileHandle, 6,SEEK_SET);
   if ( (read(fileHandle, &Value, 1)) == -1 )
    {
      MessageBox(MainWnd->Handle, "Ошибка при чтении файла " setfile "!", "Внимание!", MB_OK);
      MainWnd->Sound = true;
    }
   else MainWnd->Sound = Value;

//Чтение настройки "Выключить"
   lseek(fileHandle, 8,SEEK_SET);
   if ( (read(fileHandle, &Value, 1)) == -1 )
    {
      MessageBox(MainWnd->Handle, "Ошибка при чтении файла " setfile "!", "Внимание!", MB_OK);
      MainWnd->Off = false;
    }
   else MainWnd->Off = Value;

   close(fileHandle);

}
else
{
//      MessageBox(MainWnd->Handle, "Ошибка при открытии  на чтение файла " setfile "!", "Внимание!", MB_OK);
    // Заполнить значениями по умолчанию
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

// Открытие файла

   if (!DirectoryExists(setfiledir)) {
       CreateDir(setfiledir);
   }

   if ((fileHandle = open(setfile,
             O_WRONLY | O_CREAT  | O_BINARY, S_IWRITE)) == -1) //| O_TRUNC
    {


      MessageBox(MainWnd->Handle, "Ошибка при открытии на запись файла " setfile "!", "Внимание!", MB_OK);


      return;
    }

 if ( !(UpdateProgramSet()) ) return;


// Запись интервала времени между перерывами
   if ( write(fileHandle, &(MainWnd->TimeWork), 1 ) != 1)
    {
      MessageBox(MainWnd->Handle, "Ошибка при записи в файл set.dat", "Внимание!", MB_OK);
      return;
    }

// Запись длительности перерыва
   lseek(fileHandle, 2,SEEK_SET);
   if ( write(fileHandle, &(MainWnd->TimeBreak), 1 ) != 1)
    {
      MessageBox(MainWnd->Handle, "Ошибка при записи в файл set.dat", "Внимание!", MB_OK);
      return;
    }

// Запись настроек отключения монитора
   lseek(fileHandle, 4,SEEK_SET);
   if ( write(fileHandle, &(MainWnd->EnMonOff), 1 ) != 1)
    {
      MessageBox(MainWnd->Handle, "Ошибка при записи в файл set.dat", "Внимание!", MB_OK);
      return;
    }

// Запись настроек звукового оповещения
   lseek(fileHandle, 6,SEEK_SET);
   if ( write(fileHandle, &(MainWnd->Sound), 1 ) != 1)
    {
      MessageBox(MainWnd->Handle, "Ошибка при записи в файл set.dat", "Внимание!", MB_OK);
      return;
    }

// Запись настройки "Выключить"
   lseek(fileHandle, 8,SEEK_SET);
   if ( write(fileHandle, &(MainWnd->Off), 1 ) != 1)
    {
      MessageBox(MainWnd->Handle, "Ошибка при записи в файл set.dat", "Внимание!", MB_OK);
      return;
    }

   close(fileHandle);

}


//Обновление значений в полях формы главного окна в соответствии со значениями переменных
void UpdateWndSet()
{

  MainWnd->TimeWorkEdit->Text = IntToStr(MainWnd->TimeWork);
  MainWnd->TimeBreakEdit->Text = IntToStr(MainWnd->TimeBreak);
  MainWnd->CheckSound->Checked = MainWnd->Sound;
  MainWnd->CheckOff->Checked = MainWnd->Off;

  if (MainWnd->Off) MainWnd->PopupOff->Caption = "Включить";
               else MainWnd->PopupOff->Caption = "Выключить";

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


//Запись параметров из окна формы в переменные программы
bool UpdateProgramSet()
{
  MainWnd->Counter = 0;


  MainWnd->TimeBreak = StrToInt(MainWnd->TimeBreakEdit->Text);



  if ( (StrToInt(MainWnd->TimeWorkEdit->Text) < 5) ||
       (StrToInt(MainWnd->TimeWorkEdit->Text) > 120) )
     {
       MessageBox(MainWnd->Handle, "Время между перерывами должно быть от 5 до 120 минут!", "Внимание!", MB_OK);
       return false;
     }
  MainWnd->TimeWork = StrToInt(MainWnd->TimeWorkEdit->Text);


  if ( (StrToInt(MainWnd->TimeBreakEdit->Text) < 1) ||
       (StrToInt(MainWnd->TimeBreakEdit->Text) > 30) )
     {
       MessageBox(MainWnd->Handle, "Время перерыва должно быть от 1 до 30 минут!", "Внимание!", MB_OK);
       return false;
     }
  MainWnd->TimeBreak = StrToInt(MainWnd->TimeBreakEdit->Text);


  MainWnd->Sound = MainWnd->CheckSound->Checked;
  MainWnd->Off = MainWnd->CheckOff->Checked;
  if (MainWnd->Off) MainWnd->PopupOff->Caption = "Включить";
               else MainWnd->PopupOff->Caption = "Выключить";

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
  HWND MesWndHandle = FindWindow(NULL, "EyesGuard !Внимание! ");
  if (MesWndHandle != NULL)  SendMessage(MesWndHandle, WM_CLOSE, 0,0);

}



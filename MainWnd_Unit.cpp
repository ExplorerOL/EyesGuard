
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
//Конструктор главного окна
__fastcall TMainWnd::TMainWnd(TComponent* Owner)
        : TForm(Owner)
{
//При запуске программы устанавливаем настройки по умолчанию
  EnMonOff = true;
  Sound = true;
  Off = false;

//Считываем настройки из файла, если они были сохранены
  ReadSettings();
//Сбрасываем таймер
  PopupTimerResetClick(MainWnd);


//Не понятно, почему сначала TrayIcon должна быть false, но иначе не работает
  TrayIcon->Visible = false;
  TrayIcon->Visible = true;



}

//---------------------------------------------------------------------------
//Нажата кнопка выход
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
             { // Установка режима Work из BreakWarning


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
             { // Установка режима BreakWarning из Break

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
             { // Установка режима Break из WorkWarning

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
             { // Установка режима WorkWarning из Work

                Counter++;


           if (Counter == 1) {  MainTimer->Interval = 3000;
                            MessageBox(NULL, "Через 1 МИНУТУ будет перерыв!",
                            "EyesGuard !Внимание! ",MB_SYSTEMMODAL+MB_ICONWARNING);

                             }

           if (Counter == 2)  { CloseWarningMsg();
                            MainTimer->Interval = TIMERMULT; }
           if (Counter == 3) MainTimer->Interval = 1000;
           if (Counter == 4) MessageBox(NULL, "Через 10 СЕКУНД будет перерыв!",
                           "EyesGuard !Внимание! ", MB_SYSTEMMODAL+MB_ICONWARNING);
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
//Щелочок на иконке в трее
void __fastcall TMainWnd::TrayIconClick(TObject *Sender)
{
 Show();
}
//---------------------------------------------------------------------------
//Проверка ввода цифр в поле длительности перерыва
void __fastcall TMainWnd::TimeWorkEditKeyPress(TObject *Sender, char &Key)
{
    if  ( ((Key < '0') || (Key > '9')) && (Key != 8) ) Key = 0;
}
//---------------------------------------------------------------------------
//Проверка ввода цифр в поле времени между перерывами
void __fastcall TMainWnd::TimeBreakEditKeyPress(TObject *Sender, char &Key)
{
  if  ( ((Key < '0') || (Key > '9')) && (Key != 8) ) Key = 0;
}
//---------------------------------------------------------------------------
//Щелчок на поле время между перерывами
void __fastcall TMainWnd::TimeWorkEditClick(TObject *Sender)
{
 ButApply->Enabled = true;
}
//---------------------------------------------------------------------------
//Щелчок на поле длительности перерыва
void __fastcall TMainWnd::TimeBreakEditClick(TObject *Sender)
{
  ButApply->Enabled = true;
}
//---------------------------------------------------------------------------
//Изменение настройки "Выключать монитор"

void __fastcall TMainWnd::CheckEnMonOffEnter(TObject *Sender)
{
 ButApply->Enabled = true;
}
//---------------------------------------------------------------------------
//Изменение нестройки "Звуковое оповещение"
void __fastcall TMainWnd::CheckSoundEnter(TObject *Sender)
{
  ButApply->Enabled = true;
}
//---------------------------------------------------------------------------
//Изменение настройки "Выключить"
void __fastcall TMainWnd::CheckOffEnter(TObject *Sender)
{
 ButApply->Enabled = true;
}

//---------------------------------------------------------------------------
//Begin Popup Menu---

//---------------------------------------------------------------------------
//Выбран пункт "Выход" в контекстном меню
void __fastcall TMainWnd::PopupExitClick(TObject *Sender)
{
 Application->Terminate();
}

//---------------------------------------------------------------------------
//Выбран пункт "Выключить" в контекстном меню

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
//Выбран пункт "Настройки" в контектстном меню -> показать главное окно

void __fastcall TMainWnd::PopupSetClick(TObject *Sender)
{
 if (BreakWnd == NULL) Show();
}

//---------------------------------------------------------------------------
//Выбран пункт "Сделать перерыв" в контектстном меню
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
//Выбран пункт "Сбросить таймер" в контектстном меню
//BreakTime - время до перерыва
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
//Функция отображения времени до перерыва при наведении мыши на иконку в трее
void __fastcall TMainWnd::HintTimerTimer(TObject *Sender)
{
  if (!Off) {
    MainWnd->TrayIcon->Hint = "Eyesguard\nДо перерыва " + (BreakTime-Now()).FormatString("h:mm:ss");
  } else {
    MainWnd->TrayIcon->Hint = "Eyesguard\nВыключено";
  }
}
//---------------------------------------------------------------------------




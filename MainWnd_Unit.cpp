
/*********************************************************************
*                                                                    *
* EyesGuard - программа для тех, кто хочет сохранить свое зрение,    *
*             работая на компьютере.                                 *
* Сайт программы http://eyesguard.ru                                 *
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


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"

TMainWnd *MainWnd;
extern TBreakWnd *BreakWnd;

THintWindow *hintMessage = NULL;




//---------------------------------------------------------------------------
//Конструктор главного окна
__fastcall TMainWnd::TMainWnd(TComponent* Owner)
        : TForm(Owner)
{

  //Заполняем поля формы и контектсного меню актуальными значениями
  updateWindow();

  //Сбрасываем и запускаем таймер
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
//Обработка события таймера
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
//Щелочок ЛКМ на иконке в трее
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
  CloseWarningMsg();
  EGState.takeBreak();

}
//End Popup Menu---


//---------------------------------------------------------------------------
void __fastcall TMainWnd::FormShow(TObject *Sender)
{
 Left = Screen->Width - Width - 100;
 Top = Screen->Height - Height -100;

//При показе формы обновляем состояние настроек
 updateWindow();
 ButApply->Enabled = false;
}

//---------------------------------------------------------------------------
//Выбран пункт "Сбросить таймер" в контектстном меню
//BreakTime - время до перерыва
void __fastcall TMainWnd::PopupTimerResetClick(TObject *Sender)
{
   EGState.resetCounterTimeWork();

}





//---------------------------------------------------------------------------
//Функция отображения времени до перерыва при наведении мыши на иконку в трее

void __fastcall TMainWnd::TrayIconMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
   TDateTime timeWorkLeft;

   //1 = 24 часа. 1 делин на количество секунд в сутках (24*60*60) и умножаем на кол-во секунд
   timeWorkLeft = EGState.getTimeWorkLeft();
   MainWnd->TrayIcon->Hint = "EyesGuard\nДо перерыва " + timeWorkLeft.FormatString("h:mm:ss");


}
//---------------------------------------------------------------------------



//Обновление значений в полях формы главного окна в соответствии со значениями переменных
void updateWindow()
{
	//Получаем текущие настройки
	Settings currentSettings;
        currentSettings = EGState.getSettings();

	//Выводим полученные настройки в главное окно
	MainWnd->TimeWorkEdit->Text = IntToStr(currentSettings.timeWork);
	MainWnd->TimeBreakEdit->Text = IntToStr(currentSettings.timeBreak);
        MainWnd->CheckActivity->Checked = currentSettings.monitorUserActivity;
	MainWnd->CheckSound->Checked = currentSettings.soundOn;
	MainWnd->CheckOff->Checked = currentSettings.programTurnedOff;

	if (currentSettings.programTurnedOff) MainWnd->PopupOff->Caption = "Включить";
               else MainWnd->PopupOff->Caption = "Выключить";

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


//Запись параметров из окна формы в переменные программы и файл настроек
bool updateState()
{

	Settings currentSettings;
        
 	if ( (StrToInt(MainWnd->TimeWorkEdit->Text) < 5) || (StrToInt(MainWnd->TimeWorkEdit->Text) > 120) )
	     {
	       MessageBox(MainWnd->Handle, "Время между перерывами должно быть от 5 до 120 минут!", "Внимание!", MB_OK);
       	       return false;
             }
	currentSettings.timeWork = StrToInt(MainWnd->TimeWorkEdit->Text);


	if ( (StrToInt(MainWnd->TimeBreakEdit->Text) < 1) || (StrToInt(MainWnd->TimeBreakEdit->Text) > 30) )
	     {
       	       MessageBox(MainWnd->Handle, "Время перерыва должно быть от 1 до 30 минут!", "Внимание!", MB_OK);
	       return false;
	     }
	currentSettings.timeBreak = StrToInt(MainWnd->TimeBreakEdit->Text);

        currentSettings.monitorUserActivity = MainWnd->CheckActivity->Checked;
  	currentSettings.soundOn = MainWnd->CheckSound->Checked;
	currentSettings.programTurnedOff = MainWnd->CheckOff->Checked;

	if (MainWnd->CheckOff->Checked) MainWnd->PopupOff->Caption = "Включить";
               else MainWnd->PopupOff->Caption = "Выключить";


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


//Закрытие всплывающего окна
void CloseWarningMsg()
{
  HWND MesWndHandle = FindWindow(NULL, "EyesGuard !Внимание! ");
  if (MesWndHandle != NULL)  SendMessage(MesWndHandle, WM_CLOSE, 0,0);

}



void __fastcall TMainWnd::CheckActivityEnter(TObject *Sender)
{
  ButApply->Enabled = true;	
}
//---------------------------------------------------------------------------



//Отображение сообщения о неактивности пользователя в виде всплыв. подсказки
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

	    TRect rc = hintMessage->CalcHintRect(400, "EyesGuard \n Отсчет времени приостановлен - пользователь не активен!" ,NULL);
	    OffsetRect(&rc,p.x,p.y);
	    hintMessage->ActivateHint(rc, "EyesGuard \n Отсчет времени приостановлен - пользователь не активен!");

          }

}

//Скрытие сообщения о неактивности пользователя в виде всплыв. подсказки
void __fastcall TMainWnd::HideHintMessage()
{
   if (hintMessage != NULL)
        {
            hintMessage->ReleaseHandle();
            hintMessage = NULL;
        }

}



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


#pragma hdrstop

#include "ProgramState.h"
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <vcl.h>
#include "MainWnd_Unit.h"
#include "BreakWnd_Unit.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

extern TBreakWnd *BreakWnd;
ProgramState EGState;

//Public section

ProgramState::ProgramState()
{
 //При создании объекта заполняем настройками по умолчанию
 EGSettings.timeWork = 30;
 EGSettings.timeBreak = 5;
 EGSettings.monitorUserActivity = true;
 EGSettings.soundOn = true;
 EGSettings.programTurnedOff = false;

 //Если есть файл с настройками, то читаем настройки из файла
 readSettings();

 //Обнуляем значения счетчиков и состояний
 counterTimeWork = 0;
 counterTimeBreak = 0;
 breakInProgress = false;
 bUserActive = true;

}


Settings ProgramState::getSettings()
{
return EGSettings;
}

void ProgramState::setSettings(const Settings& newSettings)
{
	//Проверяем новые настройки на корректность, применяем и записываем в файл
	if (checkSettings(newSettings))
        {

           //Закрываем окно перерыва, если открыто

       	   if (BreakWnd != NULL)
        	{
	         delete BreakWnd;
	         BreakWnd = NULL;
        	}

           //Сбрасываем счетчики режимов
           counterTimeWork = 0;
           counterTimeBreak = 0;

           //Применяем и записываем в файл новые настройки
           EGSettings = newSettings;
           writeSettings();

         }
}


//Сделать перерыв сейчас
void ProgramState::takeBreak()
{
 counterTimeWork = EGSettings.timeWork*60;
 counterTimeBreak = 0;


}


void ProgramState::timerTick()
{
   //Если выбрана опция отслеживать активность пользователя  и нет перерыва, то проверить
   //когда была последняя активность
   if ( EGState.EGSettings.monitorUserActivity && (!breakInProgress) && (counterTimeWork > 15) )
     {

	//Определяем, активен ли пользователь. Если нет, то ничего не делаем
        DWORD dwTime;
        LASTINPUTINFO  liiStruct;
        liiStruct.cbSize = sizeof(liiStruct);


        GetLastInputInfo(&liiStruct);  //время последней активности
        dwTime = GetTickCount();       //время с момента работы оп. системы

        if (dwTime-liiStruct.dwTime > 120000)  //проверяем разницу
           {

         	bUserActive = false;
                MainWnd->ShowHintMessage();
           }
        else
           {
            bUserActive = true;
            MainWnd->HideHintMessage();
           }
     }

        //Если пользователь активен, то выполняем обработку события таймера
     if (!breakInProgress && bUserActive && !EGSettings.programTurnedOff) workTick();

     if (breakInProgress)  breakTick();


}


TDateTime ProgramState::getTimeWorkLeft()
{
return  TDateTime ( (EGSettings.timeWork*60 - counterTimeWork)/86400.0 );
}



void ProgramState::resetCounterTimeWork()
{
 counterTimeWork = 0;

}



TDateTime ProgramState::getTimeBreakLeft()
{
return  TDateTime ( (EGSettings.timeBreak*60 - counterTimeBreak)/86400.0);
}


void ProgramState::interruptBreak()
{
   counterTimeBreak = EGSettings.timeBreak*60;


}





//Private section  **************************************************************************

void ProgramState::readSettings()
{
	int fileHandle;
   	Settings settingsFromFile;

	// Открытие файла
	if ((fileHandle = open(setfilePath, O_RDONLY | O_BINARY , S_IREAD)) == -1)
             {
	        ShowMessage("Ошибка при открытии файла настроек  " setfilePath);
                return;
             }


        // Чтение интервала структуру с настройками
	if ( read(fileHandle, &settingsFromFile, sizeof(settingsFromFile)) == -1 )
    	     {
	       ShowMessage("Ошибка при чтении файла настроек  " setfilePath);
               return;
	     }



        //Проверяем считанные настройки и применяем
        if (checkSettings(settingsFromFile))
        	{
              	  EGSettings = settingsFromFile;
                }

 }

void ProgramState::writeSettings()
{
int fileHandle;


// Открытие файла

   if (!DirectoryExists(setfileDir)) {
       CreateDir(setfileDir);
   }

   //Открываем файл для записи
   if ((fileHandle = open(setfilePath,
             O_WRONLY | O_CREAT  | O_BINARY, S_IWRITE)) == -1)
    {
     ShowMessage("Ошибка при открытии файла настроек для записи  " setfilePath);
     return;
    }

// Запись настроек в файл
   if ( write(fileHandle, &EGSettings, sizeof(EGSettings)  ) !=  sizeof(EGSettings))
    {
      ShowMessage("Ошибка при записи файла настроек  " setfilePath);
      return;
    }



}

bool ProgramState::checkSettings(const Settings& settingsToCheck)
{
 if (  ( (settingsToCheck.timeWork >= 5) && (settingsToCheck.timeWork <= 120) ) &&

    ( (settingsToCheck.timeBreak >= 1) && (settingsToCheck.timeBreak <= 30) )  )

	return 1;

   else
    {
     ShowMessage("Некорректные настройки программы в файле   " setfilePath);
     return 0;
    }
}



//Отсчет времени между перерывами

void ProgramState::workTick()
{
     counterTimeWork++;

     //Предупреждение за 1 мин
     if (counterTimeWork == (EGSettings.timeWork*60-60) )
     	MessageBox(NULL, "Через 1 МИНУТУ будет перерыв!",
                            "EyesGuard !Внимание! ",MB_SYSTEMMODAL+MB_ICONWARNING);

     if (counterTimeWork == (EGSettings.timeWork*60-57) )
     	CloseWarningMsg();



     //Предупреждение за 10 сек
     if (counterTimeWork == (EGSettings.timeWork*60-10) )
     	MessageBox(NULL, "Через 10 СЕКУНД будет перерыв!",
                            "EyesGuard !Внимание! ",MB_SYSTEMMODAL+MB_ICONWARNING);

     if (counterTimeWork == (EGSettings.timeWork*60-7) )
       	CloseWarningMsg();



     //Три звуковых сигнала, затем открытие окна перерыва
     if (counterTimeWork == (EGSettings.timeWork*60-2) )
       	Beep(1000,100);
     if (counterTimeWork == (EGSettings.timeWork*60-1) )
       	Beep(1000,100);
     if (counterTimeWork >= (EGSettings.timeWork*60) )
       	{
        Beep(1000,500);
        if (BreakWnd == NULL)
     		{
	         BreakWnd = new TBreakWnd( Application );
        	 BreakWnd->Cursor = crNone;
	         BreakWnd->SetFocus();
        	}
        counterTimeWork = 0;
        breakInProgress = true;
        }

}



//Отсчет времени перерыва
void ProgramState::breakTick()
{
 counterTimeBreak++;




     //Три звуковых сигнала, затем открытие окна перерыва
     if (counterTimeBreak == (EGSettings.timeBreak*60-1) )
       	Beep(1000,500);

     if (counterTimeBreak >= (EGSettings.timeBreak*60) )
       	{
        Beep(1000,500);
        if (BreakWnd != NULL)
     		{
	         delete BreakWnd;
                 BreakWnd = NULL;
        	}
        counterTimeBreak = 0;
        breakInProgress = false;
        }

     if (BreakWnd != NULL)
     	{


                BreakWnd->LabelTimeBreakLeft->Caption = "До конца перерыва осталось " + EGState.getTimeBreakLeft().FormatString("h:mm:ss");
                BreakWnd->GaugeBreakProgress->Progress = counterTimeBreak*100.0/(EGSettings.timeBreak*60.0);
        }

}












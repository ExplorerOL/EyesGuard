
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

#ifndef ProgramStateH
#define ProgramStateH
#include "BreakWnd_Unit.h"
//---------------------------------------------------------------------------
#define setfileName "set.dat"
#define setfileDir  "."
#define setfilePath     setfileDir "\\" setfileName



//Структура, хранящая настройки программы
struct Settings{
unsigned char timeWork;
unsigned char timeBreak;
bool monitorUserActivity;
bool soundOn;
bool programTurnedOff;
};


//Класс, описыв-й состояние программы

class ProgramState {

public:
	ProgramState();
        Settings getSettings();
        void setSettings(const Settings& newSettings);
	void timerTick();
        void takeBreak();
        void resetCounterTimeWork();
        TDateTime getTimeWorkLeft();
        TDateTime getTimeBreakLeft();
        void interruptBreak();


private:
      	Settings EGSettings;
        unsigned counterTimeWork;
        unsigned counterTimeBreak;
        bool breakInProgress;
        bool bUserActive;


        void readSettings();
        void writeSettings();
	bool checkSettings(const Settings& settingsToCheck);

        void workTick();
        void breakTick();


};


extern ProgramState EGState;



#endif



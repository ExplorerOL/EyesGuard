
/*********************************************************************
*                                                                    *
* EyesGuard - cares about youe vision during working on PC!                               *
* Site of program http://eyesguard.ru                                *
*                              					     *
*    © Dmitry Vorobjev (eyesguard@yandex.ru), 2011,                  *
*    © Mihail Buryakov   (mihail.buryakov@gmail.com), 2012,          *
*    © Dmitry Vorobjev (eyesguard@yandex.ru), 2018.                  *
*   This program is free software; you can redistribute it and/or    *
*   modify it under the terms of the GNU General Public License as   *
*   published by the Free Software Foundation; either version 2 of   *
*   the License, or at your option) any later version.               *
*                                                                    *
*   This program is distributed in the hope that it will be useful,  *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of   *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    *
*   GNU General Public License for more details.                     *
*                                                                    *
*   The official publication of the license GNU GPL you can          *
*   find here: http://www.gnu.org/licenses/gpl.html                  *
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



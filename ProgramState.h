
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

#ifndef ProgramStateH
#define ProgramStateH
#include "BreakWnd_Unit.h"
//---------------------------------------------------------------------------
#define setfileName "set.dat"
#define setfileDir  "."
#define setfilePath     setfileDir "\\" setfileName



//���������, �������� ��������� ���������
struct Settings{
unsigned char timeWork;
unsigned char timeBreak;
bool monitorUserActivity;
bool soundOn;
bool programTurnedOff;
};


//�����, ������-� ��������� ���������

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



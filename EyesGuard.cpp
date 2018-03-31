
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

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("MainWnd_Unit.cpp", MainWnd);
USEFORM("BreakWnd_Unit.cpp", BreakWnd);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
         {


		HANDLE* EGMutex;
		*EGMutex = CreateMutex(NULL, true, "EGMutex");
		if (GetLastError()==ERROR_ALREADY_EXISTS)
    		    {
  		      ShowMessage("����� ������� ���������� ��� ��������!");
  		      Application->Terminate();
  		    }

                Application->Initialize();
                Application->ShowMainForm = false;
                Application->Title = "EyesGuard";
                Application->CreateForm(__classid(TMainWnd), &MainWnd);
		Application->Run();
         }


        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                        Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------

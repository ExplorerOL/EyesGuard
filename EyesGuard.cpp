
/*********************************************************************
*                                                                    *
* EyesGuard - cares about youe vision during working on PC!                               *
* Site of program http://eyesguard.ru                                *
*                              					     *
*    � Dmitry Vorobjev (eyesguard@yandex.ru), 2011,                  *
*    � Mihail Buryakov   (mihail.buryakov@gmail.com), 2012,          *
*    � Dmitry Vorobjev (eyesguard@yandex.ru), 2018.                  *
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
  		      ShowMessage("Can't start second copy of EyesGuard!");
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

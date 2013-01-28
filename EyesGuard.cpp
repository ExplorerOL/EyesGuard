
/*********************************************************************
*                                                                    *
* EyesGuard - программа для тех, кто хочет сохранить свое зрение,    *
*             работая на компьютере.                                 *
* Сайт программы www.eyesguard.org                                   *
*    © Воробьев Дмитрий (eyesguard@yandex.ru), 2007.                 *
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
//---------------------------------------------------------------------------
USEFORM("MainForm.cpp", MainWnd);
USEFORM("BreakForm.cpp", BreakWnd);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
         {


HANDLE* EGMutex;
*EGMutex = CreateMutex(NULL, true, "EGMutex");
if (GetLastError()==ERROR_ALREADY_EXISTS)
        {
        ShowMessage("Копия данного приложения уже запущена!");
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

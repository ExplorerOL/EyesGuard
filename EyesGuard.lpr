program EyesGuard;

{$mode objfpc}{$H+}

uses {$IFDEF UNIX} {$IFDEF UseCThreads}
  cthreads, {$ENDIF} {$ENDIF}
  Interfaces, // this includes the LCL widgetset
  Forms,
  BreakWnd_Unit,
  MainWnd_Unit,
  BreakLogic { you can add units after this };

{$R *.res}

var
  BreakManager: TBreakManager;
  MainWnd: TMainWnd;

begin
  RequireDerivedFormResource := True;
  Application.Initialize;
  Application.CreateForm(TMainWnd, MainWnd);
  BreakManager := TBreakManager.Create(MainWnd);
  Application.Run;
end.

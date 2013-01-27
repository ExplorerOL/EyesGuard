program EyesGuard;

{$mode objfpc}{$H+}

{$APPTYPE CONSOLE}

uses {$IFDEF UNIX} {$IFDEF UseCThreads}
  cthreads, {$ENDIF} {$ENDIF}
  Interfaces, // this includes the LCL widgetset
  Forms,
  //BreakWnd_Unit,
  MainWnd_Unit,
  BreakLogic,
  EventHandler { you can add units after this };

{$R *.res}

var
  BreakManager: TBreakManager;

begin
  RequireDerivedFormResource := True;
  Application.Initialize;
  BreakManager := TBreakManager.Create();
  Application.Run;
end.

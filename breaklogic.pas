unit BreakLogic;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms,
  MainWnd_Unit, BreakWnd_Unit, Settings, Logger;

type
  TIOPolicy = record
    createNonExistingFile: boolean;
    rewriteCorruptedFile: boolean;
  end;

const
  DefaultIOPolicy: TIOPolicy = (
    createNonExistingFile: False;
    rewriteCorruptedFile: False;
    );

const
  DefaultSettingsFileName = 'set.dat';

type
  TBreakManager = class
    constructor Create(var aMainWnd: TMainWnd);
    constructor Create(var aMainWnd: TMainWnd; var aLogger: TLogger;
      aSettingsFileName: string; const aIOPolicy: TIOPolicy);

  public

  private
    Settings: TBreakSettings;
    Logger: TLogger;
    IOPolicy: TIOPolicy;
    MainWnd: TMainWnd;

    procedure readSettings(aSettingsFileName: string);
  end;

implementation

constructor TBreakManager.Create(var aMainWnd: TMainWnd);
var
  l: TLogger;
begin
  l := TLogger.Create(False, True);
  Create(aMainWnd, l, DefaultSettingsFileName, DefaultIOPolicy);
end;

constructor TBreakManager.Create(var aMainWnd: TMainWnd; var aLogger: TLogger;
  aSettingsFileName: string; const aIOPolicy: TIOPolicy);
begin
  Logger := aLogger;
  IOPolicy := aIOPolicy;
  MainWnd := aMainWnd;
  readSettings(aSettingsFileName);
  MainWnd.TrayImageList.GetIcon(1, MainWnd.TrayIcon.Icon);
end;

procedure TBreakManager.readSettings(aSettingsFileName: string);
var
  fin: file of TBreakSettings;
begin
  Logger.Log('Setting file given: ''' + aSettingsFileName + '''.');
  AssignFile(fin, aSettingsFileName);
  if FileExists(aSettingsFileName) then begin
    Logger.Log('File found. Trying to read.');
    Reset(fin);
    if not EOF(fin) then begin
      Read(fin, Settings);
      CloseFile(fin);
      Logger.Log('File is successfully read.');
    end else begin
      CloseFile(fin);
      if IOPolicy.rewriteCorruptedFile then begin
        Logger.Log(
          'Setting file corrupted. Default settings are used. File will be overwritten if nessesary.');
        Rewrite(fin);
        Write(fin, DefaultSettings);
        CloseFile(fin);
        Settings := DefaultSettings;
      end else begin
        Logger.Log(
          'Setting file corrupted. Default settings are used. File will not be overwritten.');
        Settings := DefaultSettings;
      end;
    end;
  end else begin
    if IOPolicy.createNonExistingFile then begin
      Logger.Log('File not found. It will be created. Default settings will be used.');
      Rewrite(fin);
      Write(fin, DefaultSettings);
      CloseFile(fin);
      Settings := DefaultSettings;
    end else begin
      Logger.Log('File not found. It will not be created. Default settings will be used.');
      Settings := DefaultSettings;
    end;
  end;
end;

end.

unit BreakLogic;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms,
  MainWnd_Unit, BreakWnd_Unit, Settings, Logger, EventHandler;

type
  TBreakManager = class
    constructor Create();
    constructor Create(var aLogger: TLogger; aSettingsFileName: string; const aIOPolicy: TIOPolicy);

  public

  private
    Settings: TBreakSettings;
    SettingsFileName: string;
    CanOverwriteSettings: boolean;
    Logger: TLogger;
    IOPolicy: TIOPolicy;
    MainWnd: TMainWnd;

    procedure readSettings();
    procedure writeSettings();
    procedure openSettings();
    procedure saveSettings();
    procedure StartWork();
  end;

implementation

constructor TBreakManager.Create();
var
  l: TLogger;
begin
  l := TLogger.Create(True, False);
  Create(l, DefaultSettingsFileName, IOPolicyStandard);
end;

constructor TBreakManager.Create(var aLogger: TLogger; aSettingsFileName: string; const aIOPolicy: TIOPolicy);
var
  onSave: TSimpleEventList;
begin
  Logger := aLogger;
  IOPolicy := aIOPolicy;
  SettingsFileName := aSettingsFileName;
  readSettings();
  Application.ShowMainForm:=false;
  Application.CreateForm(TMainWnd, MainWnd);
  MainWnd.ActionsOnShow:=TSimpleEventList.Create(@self.openSettings);
  onSave:=TSimpleEventList.Create();
  onSave.add(@self.saveSettings);
  onSave.add(@self.writeSettings);
  MainWnd.ActionsOnSave:=onSave;
end;

procedure TBreakManager.openSettings();
begin
  MainWnd.setSettings(Settings);
  MainWnd.Left := Screen.Width - MainWnd.Width - 100;
  MainWnd.Top := Screen.Height - MainWnd.Height - 100;
  MainWnd.ButApply.Enabled:=False;
  MainWnd.Show;
end;

procedure TBreakManager.saveSettings();
begin
  Settings:=MainWnd.getSettings();
  MainWnd.setSettings(Settings);
end;

procedure TBreakManager.StartWork();
begin
  Logger.Log('Starting work.');
  MainWnd.Timer.Enabled := False;
  MainWnd.Timer.Interval := Settings.TimeBreak - Settings.TimeRemind[1];
end;

procedure TBreakManager.writeSettings();
var
  fout: file of TBreakSettings;
begin
  if CanOverwriteSettings then
  begin
    Logger.Log('Writing settings.');
    AssignFile(fout, SettingsFileName);
    Rewrite(fout);
    Write(fout, Settings);
    CloseFile(fout);
  end else begin
    Logger.Log('Cannot write setting: disallowed by IOPolicy.');
  end;
end;

procedure TBreakManager.readSettings();
var
  fin: file of TBreakSettings;
begin
  Logger.Log('Readind setting from file: ''' + SettingsFileName + '''.');
  AssignFile(fin, SettingsFileName);
  if FileExists(SettingsFileName) then
  begin
    Logger.Log('File found. Trying to read.');
    Reset(fin);
    if not EOF(fin) then
    begin
      Read(fin, Settings);
      CloseFile(fin);
      if CheckSettings(Settings) then
      begin
        Logger.Log('File is successfully read.');
        CanOverwriteSettings := IOPolicy.rewriteGoodFile;
      end else begin
        Logger.Log('File contains invalid data. Default settings are used.');
        Settings := DefaultSettings;
        CanOverwriteSettings := IOPolicy.rewriteCorruptedFile;
      end;
    end else begin
      CloseFile(fin);
      Logger.Log('File is corrupted. Default settings are used.');
      Settings := DefaultSettings;
      CanOverwriteSettings := IOPolicy.rewriteCorruptedFile;
    end;
  end else begin
    Logger.Log('File not found. Default settings will be used.');
    Settings := DefaultSettings;
    CanOverwriteSettings := IOPolicy.createNonExistingFile;
  end;
  if not CanOverwriteSettings then begin
    Logger.Log('Setting IOPolicy: File will not be overwritten.');
  end;
end;

end.

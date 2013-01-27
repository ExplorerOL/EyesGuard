unit Logger;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Dialogs;

type
  TLogger = class
    LogFileName: string;
    Verbose, Messages: boolean;

    constructor Create(aLogFileName: string; aVerbose, aMessages: boolean);
    constructor Create(aVerbose, aMessages: boolean);
    procedure Log(Message: string);

  private
    procedure reportCreate();
  end;

implementation

constructor TLogger.Create(aLogFileName: string; aVerbose, aMessages: boolean);
begin
  LogFileName := aLogFileName;
  Verbose := aVerbose;
  Messages := aMessages;
  reportCreate();
end;

procedure TLogger.reportCreate();
var
  createStr: string;
begin
  createStr := 'Created logger ';
  if LogFileName <> '' then begin
    createStr := createStr + '(''' + LogFileName + ''') ';
  end;
  if Verbose then begin
    createStr := createStr + '(verbose)';
  end;
  if Messages then begin
    createStr := createStr + '(messages)';
  end;
  Log(createStr);
end;

constructor TLogger.Create(aVerbose, aMessages: boolean);
begin
  Create('', aVerbose, aMessages);
end;

procedure TLogger.Log(Message: string);
var
  f: Text;
  t: TDateTime;
begin
  t := Now;
  if LogFileName <> '' then begin
    AssignFile(f, LogFileName);
    if FileExists(LogFileName) then begin
      Append(f);
    end
    else begin
      Rewrite(f);
    end;
    WriteLn(f, FormatDateTime('c', t), ' ', Message);
    CloseFile(f);
  end;
  if Verbose then begin
    WriteLn(FormatDateTime('c', t), ' ', Message);
  end;
  if Messages then begin
    ShowMessage('Logger: ' + Message);
  end;
end;

end.

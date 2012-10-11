unit EventHandler;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils;

type
  TSimpleEvent = procedure() of object;
  TSimpleEventList = class
    List: array of TSimpleEvent;

    constructor Create();
    constructor Create(event: TSimpleEvent);
    procedure add(event: TSimpleEvent);
    procedure executeAll();
  end;

implementation

constructor TSimpleEventList.Create();
begin
  SetLength(List, 0);
end;

constructor TSimpleEventList.Create(event: TSimpleEvent);
begin
  SetLength(List, 1);
  List[0] := event;
end;

procedure TSimpleEventList.executeAll();
var
  i:integer;
begin
  for i:=0 to Length(List)-1 do begin
    List[i]();
  end;
end;

procedure TSimpleEventList.add(event: TSimpleEvent);
var
  n:integer;
begin
  n := Length(List);
  SetLength(List, n+1);
  List[n] := event;
end;

end.


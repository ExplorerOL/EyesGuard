unit Settings;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils;

type
  TBreakSettings = record
    TimeWork: integer;
    TimeBreak: integer;
    EnMonOff: boolean;
    Sound: boolean;
    Off: boolean;
  end;

const
  DefaultSettings: TBreakSettings = (
    TimeWork: 30;
    TimeBreak: 10;
    EnMonOff: False;
    Sound: True;
    Off: False;
    );

implementation

end.

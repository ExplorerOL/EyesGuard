
/***************************************************************************
 *   Copyright (C) 2008 by Vorobyov Dmitry                                 *
 *   eyesguard@yandex.ru                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   The official publication of the license GNU GPL you can find here:    *
 *   http://www.gnu.org/licenses/gpl.html                                  *
 ***************************************************************************/

//---------------------------------------------------------------------------

#ifndef InputOutputH
#define InputOutputH
//---------------------------------------------------------------------------
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <string.h>
#include "MainForm.h"



void ReadSettings();
void WriteSettings();
void UpdateWndSet();
bool UpdateProgramSet();
void CloseWarningMsg();
#endif

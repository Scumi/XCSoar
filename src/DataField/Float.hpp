/*
Copyright_License {

  XCSoar Glide Computer - http://www.xcsoar.org/
  Copyright (C) 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009

	M Roberts (original release)
	Robin Birch <robinb@ruffnready.co.uk>
	Samuel Gisiger <samuel.gisiger@triadis.ch>
	Jeff Goodenough <jeff@enborne.f2s.com>
	Alastair Harrison <aharrison@magic.force9.co.uk>
	Scott Penrose <scottp@dd.com.au>
	John Wharington <jwharington@gmail.com>
	Lars H <lars_hn@hotmail.com>
	Rob Dunning <rob@raspberryridgesheepfarm.com>
	Russell King <rmk@arm.linux.org.uk>
	Paolo Ventafridda <coolwind@email.it>
	Tobias Lohner <tobias@lohner-net.de>
	Mirek Jezek <mjezek@ipplc.cz>
	Max Kellermann <max@duempel.org>
	Tobias Bieniek <tobias.bieniek@gmx.de>

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
}
*/

#ifndef XCSOAR_DATA_FIELD_FLOAT_HPP
#define XCSOAR_DATA_FIELD_FLOAT_HPP

#include "DataField/Base.hpp"
#include "PeriodClock.hpp"

class DataFieldFloat: 
public DataField
{
  private:
  fixed mValue;
  fixed mMin;
  fixed mMax;
  fixed mStep;
  PeriodClock last_step;
    int mSpeedup;
    int mFine;
  mutable TCHAR mOutBuf[OUTBUFFERSIZE+1];

  protected:
  fixed SpeedUp(bool keyup);


  public:
    DataFieldFloat(const TCHAR *EditFormat, const TCHAR *DisplayFormat,
                   fixed Min, fixed Max, fixed Default,
                   fixed Step, int Fine, DataAccessCallback_t OnDataAccess)
      :DataField(EditFormat, DisplayFormat, OnDataAccess),
       mValue(Default), mMin(Min), mMax(Max), mStep(Step), mFine(Fine)
  {
      SupportCombo=true;
    };

  void Inc(void);
  void Dec(void);
  virtual ComboList *CreateComboList();
  void SetFromCombo(int iDataFieldIndex, TCHAR *sValue);

  virtual bool GetAsBoolean(void) const;
  virtual int GetAsInteger(void) const;
  virtual fixed GetAsFixed() const;
  virtual const TCHAR *GetAsString(void) const;
  virtual const TCHAR *GetAsDisplayString(void) const;

  virtual void Set(int Value){ Set(fixed(Value)); };

  #if defined(__BORLANDC__)
  #pragma warn -hid
  #endif
  void Set(fixed Value);
  fixed SetMin(fixed Value);
  fixed SetMax(fixed Value);
  #if defined(__BORLANDC__)
  #pragma warn +hid
  #endif
  virtual void SetAsBoolean(bool Value);
  virtual void SetAsInteger(int Value);
  virtual void SetAsFloat(fixed Value);
  virtual void SetAsString(const TCHAR *Value);
};

#endif

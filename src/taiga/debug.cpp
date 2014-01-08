/*
** Taiga
** Copyright (C) 2010-2014, Eren Okka
** 
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "base/common.h"
#include "base/string.h"
#include "library/anime_db.h"
#include "taiga/debug.h"
#include "ui/dlg/dlg_main.h"
#include "ui/dialog.h"

namespace debug {

Tester::Tester()
    : frequency_(0.0), value_(0) {
}

void Tester::Start() {
  LARGE_INTEGER li;
  
  if (frequency_ == 0.0) {
    ::QueryPerformanceFrequency(&li);
    frequency_ = double(li.QuadPart) / 1000.0;
  }
  
  ::QueryPerformanceCounter(&li);
  value_ = li.QuadPart;
}

void Tester::End(std::wstring str, bool display_result) {
  LARGE_INTEGER li;

  ::QueryPerformanceCounter(&li);
  double value = double(li.QuadPart - value_) / frequency_;

  if (display_result) {
    str = ToWstr(value, 2) + L"ms | Text: [" + str + L"]";
    ui::DlgMain.SetText(str);
  }
}

////////////////////////////////////////////////////////////////////////////////

void Print(std::wstring text) {
#ifdef _DEBUG
  ::OutputDebugString(text.c_str());
#else
  UNREFERENCED_PARAMETER(text);
#endif
}

void Test() {
  // Define variables
  std::wstring str;

  // Start ticking
  Tester test;
  test.Start();

  for (int i = 0; i < 10000; i++) {
    // Do some tests here
    //       ___
    //      {o,o}
    //      |)__)
    //     --"-"--
    //      O RLY?
  }

  // Debug recognition engine
  ui::ShowDialog(ui::kDialogTestRecognition);

  // Show result
  test.End(str, 0);
}

} // namespace debug
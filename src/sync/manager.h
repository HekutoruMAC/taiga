/*
** Taiga
** Copyright (C) 2010-2019, Eren Okka
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

#pragma once

#include <map>
#include <memory>
#include <string>

#include <windows/win/thread.h>

#include "service.h"
#include "base/types.h"
#include "taiga/http.h"
#include "taiga/http_new.h"

namespace sync {

// The service manager handles all the communication between services and the
// application.

class Manager {
public:
  Manager();
  ~Manager();

  void MakeRequest(Request& request);
  void HandleHttpError(HttpResponse& http_response, std::wstring error);
  void HandleHttpResponse(HttpResponse& http_response);

  Service* service(ServiceId service_id) const;
  Service* service(const std::wstring& canonical_name) const;

private:
  void HandleError(Response& response, HttpResponse& http_response);
  void HandleResponse(Response& response, HttpResponse& http_response);

  win::CriticalSection critical_section_;
  std::map<std::wstring, Request> requests_;
  std::map<ServiceId, std::unique_ptr<Service>> services_;
};

ServiceId GetServiceIdBySlug(const std::wstring& slug);
std::wstring GetServiceNameById(const ServiceId service_id);
std::wstring GetServiceSlugById(const ServiceId service_id);

void AfterGetLibrary();
void AfterGetSeason();
void AfterLibraryUpdate();

bool OnTransfer(const taiga::http::Transfer& transfer,
                const std::wstring& status);

}  // namespace sync

inline sync::Manager ServiceManager;

////////////////////////////////////////////////////////////////////////////////
/// DISCLAIMER
///
/// Copyright 2014-2016 ArangoDB GmbH, Cologne, Germany
/// Copyright 2004-2014 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is ArangoDB GmbH, Cologne, Germany
///
/// @author Dr. Frank Celler
////////////////////////////////////////////////////////////////////////////////

#include "WorkMonitor.h"

using namespace arangodb;

////////////////////////////////////////////////////////////////////////////////
/// @brief thread deleter
////////////////////////////////////////////////////////////////////////////////

void WorkMonitor::DELETE_HANDLER(WorkDescription*) { TRI_ASSERT(false); }

////////////////////////////////////////////////////////////////////////////////
/// @brief thread description string
////////////////////////////////////////////////////////////////////////////////

void WorkMonitor::VPACK_HANDLER(arangodb::velocypack::Builder*,
                                WorkDescription*) {
  TRI_ASSERT(false);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief sends the overview
////////////////////////////////////////////////////////////////////////////////

void WorkMonitor::SEND_WORK_OVERVIEW(uint64_t, std::string const&) {
  TRI_ASSERT(false);
}

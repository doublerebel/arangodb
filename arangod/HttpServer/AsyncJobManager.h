////////////////////////////////////////////////////////////////////////////////
/// @brief job manager
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2014-2015 ArangoDB GmbH, Cologne, Germany
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
/// @author Jan Steemann
/// @author Copyright 2014-2015, ArangoDB GmbH, Cologne, Germany
/// @author Copyright 2004-2014, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#ifndef ARANGODB_HTTP_SERVER_ASYNC_JOB_MANAGER_H
#define ARANGODB_HTTP_SERVER_ASYNC_JOB_MANAGER_H 1

#include "Basics/Common.h"
#include "Basics/ReadWriteLock.h"

namespace triagens {
  namespace rest {
    class AsyncCallbackContext;
    class HttpServerJob;
    class HttpResponse;

// -----------------------------------------------------------------------------
// --SECTION--                                              class AsyncJobResult
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @brief AsyncJobResult
////////////////////////////////////////////////////////////////////////////////

    struct AsyncJobResult {

// -----------------------------------------------------------------------------
// --SECTION--                                                      public types
// -----------------------------------------------------------------------------

      public:

////////////////////////////////////////////////////////////////////////////////
/// @brief job states
////////////////////////////////////////////////////////////////////////////////

        typedef enum {
          JOB_UNDEFINED,
          JOB_PENDING,
          JOB_DONE
        }
        Status;

////////////////////////////////////////////////////////////////////////////////
/// @brief id typedef
////////////////////////////////////////////////////////////////////////////////

        typedef uint64_t IdType;

// -----------------------------------------------------------------------------
// --SECTION--                                      constructors and destructors
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @brief constructor for an unspecified job result
////////////////////////////////////////////////////////////////////////////////

        AsyncJobResult ();

////////////////////////////////////////////////////////////////////////////////
/// @brief constructor for a specific job result
////////////////////////////////////////////////////////////////////////////////

        AsyncJobResult (IdType jobId,
                        HttpResponse* response,
                        double stamp,
                        Status status,
                        AsyncCallbackContext* ctx);

////////////////////////////////////////////////////////////////////////////////
/// @brief destructor
////////////////////////////////////////////////////////////////////////////////

        ~AsyncJobResult ();

// -----------------------------------------------------------------------------
// --SECTION--                                                  public variables
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @brief job id
////////////////////////////////////////////////////////////////////////////////

        IdType _jobId;

////////////////////////////////////////////////////////////////////////////////
/// @brief the full HTTP response object of the job, can be 0
////////////////////////////////////////////////////////////////////////////////

        HttpResponse* _response;

////////////////////////////////////////////////////////////////////////////////
/// @brief job creation stamp
////////////////////////////////////////////////////////////////////////////////

        double _stamp;

////////////////////////////////////////////////////////////////////////////////
/// @brief job status
////////////////////////////////////////////////////////////////////////////////

        Status _status;

////////////////////////////////////////////////////////////////////////////////
/// @brief callback context object (normally 0, used in cluster operations)
////////////////////////////////////////////////////////////////////////////////

        AsyncCallbackContext* _ctx;
    };

// -----------------------------------------------------------------------------
// --SECTION--                                             class AsyncJobManager
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @brief AsyncJobManager
////////////////////////////////////////////////////////////////////////////////

    class AsyncJobManager {
      AsyncJobManager (AsyncJobManager const&) = delete;
      AsyncJobManager& operator= (AsyncJobManager const&) = delete;

// -----------------------------------------------------------------------------
// --SECTION--                                                      public types
// -----------------------------------------------------------------------------

      public:

////////////////////////////////////////////////////////////////////////////////
/// @brief callback typedef
////////////////////////////////////////////////////////////////////////////////

        typedef void (*callback_fptr)(std::string&, HttpResponse*);

////////////////////////////////////////////////////////////////////////////////
/// @brief joblist typedef
////////////////////////////////////////////////////////////////////////////////

        typedef std::unordered_map<AsyncJobResult::IdType, AsyncJobResult> JobList;

// -----------------------------------------------------------------------------
// --SECTION--                                        constructors / destructors
// -----------------------------------------------------------------------------

      public:

////////////////////////////////////////////////////////////////////////////////
/// @brief constructor
////////////////////////////////////////////////////////////////////////////////

        AsyncJobManager (callback_fptr);

////////////////////////////////////////////////////////////////////////////////
/// @brief destructor
////////////////////////////////////////////////////////////////////////////////

        ~AsyncJobManager ();

// -----------------------------------------------------------------------------
// --SECTION--                                                    public methods
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @brief returns the result of an async job
////////////////////////////////////////////////////////////////////////////////

        HttpResponse* getJobResult (AsyncJobResult::IdType,
                                    AsyncJobResult::Status&,
                                    bool removeFromList);

////////////////////////////////////////////////////////////////////////////////
/// @brief deletes the result of an async job
////////////////////////////////////////////////////////////////////////////////

        bool deleteJobResult (AsyncJobResult::IdType);

////////////////////////////////////////////////////////////////////////////////
/// @brief deletes all results
////////////////////////////////////////////////////////////////////////////////

        void deleteJobResults ();

////////////////////////////////////////////////////////////////////////////////
/// @brief deletes expired results
////////////////////////////////////////////////////////////////////////////////

        void deleteExpiredJobResults (double stamp);

////////////////////////////////////////////////////////////////////////////////
/// @brief returns the list of pending jobs
////////////////////////////////////////////////////////////////////////////////

        const std::vector<AsyncJobResult::IdType> pending (size_t maxCount);

////////////////////////////////////////////////////////////////////////////////
/// @brief returns the list of done jobs
////////////////////////////////////////////////////////////////////////////////

        const std::vector<AsyncJobResult::IdType> done (size_t maxCount);

////////////////////////////////////////////////////////////////////////////////
/// @brief returns the list of jobs by status
////////////////////////////////////////////////////////////////////////////////

        const std::vector<AsyncJobResult::IdType> byStatus (AsyncJobResult::Status,
                                                            size_t maxCount);

////////////////////////////////////////////////////////////////////////////////
/// @brief initializes an async job
////////////////////////////////////////////////////////////////////////////////

        void initAsyncJob (HttpServerJob*);

////////////////////////////////////////////////////////////////////////////////
/// @brief finishes the execution of an async job
////////////////////////////////////////////////////////////////////////////////

        void finishAsyncJob(AsyncJobResult::IdType jobId, HttpResponse*);

// -----------------------------------------------------------------------------
// --SECTION--                                                 private variables
// -----------------------------------------------------------------------------

      private:

////////////////////////////////////////////////////////////////////////////////
/// @brief lock to protect the _jobs map
////////////////////////////////////////////////////////////////////////////////

        basics::ReadWriteLock _lock;

////////////////////////////////////////////////////////////////////////////////
/// @brief list of pending/done async jobs
////////////////////////////////////////////////////////////////////////////////

        JobList _jobs;

////////////////////////////////////////////////////////////////////////////////
/// @brief function pointer for callback registered at initialization
////////////////////////////////////////////////////////////////////////////////

        callback_fptr callback;
    };
  }
}

#endif

// -----------------------------------------------------------------------------
// --SECTION--                                                       END-OF-FILE
// -----------------------------------------------------------------------------

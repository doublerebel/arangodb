////////////////////////////////////////////////////////////////////////////////
/// @brief Ahuacatl, parser functionality
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2004-2013 triAGENS GmbH, Cologne, Germany
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
/// Copyright holder is triAGENS GmbH, Cologne, Germany
///
/// @author Jan Steemann
/// @author Copyright 2012-2013, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#ifndef TRIAGENS_AHUACATL_AHUACATL_PARSER_FUNCTIONS_H
#define TRIAGENS_AHUACATL_AHUACATL_PARSER_FUNCTIONS_H 1

#include "Basics/Common.h"

#include "Ahuacatl/ahuacatl-context.h"
#include "Ahuacatl/ahuacatl-error.h"
#include "Ahuacatl/ahuacatl-parser.h"

// -----------------------------------------------------------------------------
// --SECTION--                                                          forwards
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Ahuacatl
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief forwards for the parse function provided by the parser (.y)
////////////////////////////////////////////////////////////////////////////////

int Ahuacatlparse (TRI_aql_context_t* const);

////////////////////////////////////////////////////////////////////////////////
/// @brief forward for the init function provided by the lexer (.l)
////////////////////////////////////////////////////////////////////////////////

int Ahuacatllex_init (void**);

////////////////////////////////////////////////////////////////////////////////
/// @brief forward for the shutdown function provided by the lexer (.l)
////////////////////////////////////////////////////////////////////////////////

int Ahuacatllex_destroy (void *);

////////////////////////////////////////////////////////////////////////////////
/// @brief forward for the context function provided by the lexer (.l)
////////////////////////////////////////////////////////////////////////////////

void Ahuacatlset_extra (TRI_aql_context_t*, void*);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                  public functions
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Ahuacatl
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief init the lexer
////////////////////////////////////////////////////////////////////////////////

bool TRI_InitParserAql (TRI_aql_context_t*);

////////////////////////////////////////////////////////////////////////////////
/// @brief parse & validate the query string
////////////////////////////////////////////////////////////////////////////////

bool TRI_ParseAql (TRI_aql_context_t* const);

////////////////////////////////////////////////////////////////////////////////
/// @brief register a parse error
////////////////////////////////////////////////////////////////////////////////

void TRI_SetErrorParseAql (TRI_aql_context_t* const,
                           const char* const,
                           const int,
                           const int);

////////////////////////////////////////////////////////////////////////////////
/// @brief push something on the stack
////////////////////////////////////////////////////////////////////////////////

bool TRI_PushStackParseAql (TRI_aql_context_t* const, const void* const);

////////////////////////////////////////////////////////////////////////////////
/// @brief pop something from the stack
////////////////////////////////////////////////////////////////////////////////

void* TRI_PopStackParseAql (TRI_aql_context_t* const);

////////////////////////////////////////////////////////////////////////////////
/// @brief peek at the end of the stack
////////////////////////////////////////////////////////////////////////////////

void* TRI_PeekStackParseAql (TRI_aql_context_t* const);

////////////////////////////////////////////////////////////////////////////////
/// @brief return a new unique variable name
////////////////////////////////////////////////////////////////////////////////

char* TRI_GetNameParseAql (TRI_aql_context_t* const);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

#endif

// Local Variables:
// mode: outline-minor
// outline-regexp: "/// @brief\\|/// {@inheritDoc}\\|/// @addtogroup\\|/// @page\\|// --SECTION--\\|/// @\\}"
// End:

#pragma once

#include "logging.h"

#define ASSERT_NO_MSG(cond) {if(cond) {} else {__debugbreak();}}

#define ASSERT_MSG(cond, msg) {if(cond) {} else {LOG_CRITICAL("Assertion Failed: File {0} on line {1} : '{2}'", __FILE__, __LINE__, msg); __debugbreak();}}
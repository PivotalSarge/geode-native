#pragma once

#ifndef GEODE_GFCPP_GLOBALS_H_
#define GEODE_GFCPP_GLOBALS_H_

/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file
 */

#ifdef WIN32
#ifndef _WIN32
#define _WIN32
#endif
#endif
#ifdef _WIN32
#ifndef WIN32
#define WIN32
#endif
#endif

#ifdef __linux
#ifndef _LINUX
#define _LINUX 1
#endif
#ifndef LINUX_GCC
#define LINUX_GCC true
#endif
#endif

#ifdef __sun
#ifndef _SOLARIS
#define _SOLARIS 1
#if defined(__sparc) || defined(__sparcv9)
#ifndef _SPARC_SOLARIS
#define _SPARC_SOLARIS 1
#endif
#endif

#if defined(__i386) || defined(__amd64)
#ifndef _X86_SOLARIS
#define _X86_SOLARIS 1
#endif
#endif
#endif
#endif

#ifdef _MSC_VER
// disable: "C++ Exception Specification ignored"
// This is because MSVC did not implement all the C++ exception
// specifications in the ANSI C++ draft.
#pragma warning(disable : 4290)
// Turn off warnings generated by lengthy std templates
// This warns about truncation to 255 characters in debug/browse info
#pragma warning(disable : 4786)
// disable: "<type> needs to have dll-interface to be used by clients'
// Happens on STL member variables which are not public therefore is ok
#pragma warning(disable : 4251)

// MSVC does not use __attribute__.
#define ATTR_UNUSED

#else

#ifdef _SOLARIS

// Solaris does not __attribute__.
#define ATTR_UNUSED

#else

// gcc and clang use __attribute__.
#define ATTR_UNUSED __attribute__((unused))

#endif

#endif

#ifndef __has_cpp_attribute
#define __has_cpp_attribute(x) 0
#endif

#if __cplusplus >= 201402L
#if __has_cpp_attribute(deprecated)
// C++14 standard deprecated attribute
#define __DEPRECATED__(msg) [[deprecated(msg)]]
#else
#error "__has_cpp_attribute(deprecated)"
#endif
#elif defined(__GNUC__)
// GCC style deprecated attribute
#define __DEPRECATED__(msg) __attribute__((deprecated(msg)))
#elif defined(_MSC_VER)
// Visual C++ style deprecated attribute
#define __DEPRECATED__(msg) __declspec(deprecated(msg))
#else
#define __DEPRECATED__(msg)
#endif

#ifdef _WIN32
#if WINVER == 0x0500
#endif
#endif

#include "geode_base.hpp"

#include <cstdint>

namespace apache {
namespace geode {
namespace client {

extern void CPPCACHE_EXPORT millisleep(uint32_t millis);

#ifdef _WIN32
extern void CPPCACHE_EXPORT setNewAndDelete(pNew, pDelete);
#endif

}  // namespace client
}  // namespace geode
}  // namespace apache

#include "Log.hpp"
#include "Assert.hpp"

#endif  // GEODE_GFCPP_GLOBALS_H_

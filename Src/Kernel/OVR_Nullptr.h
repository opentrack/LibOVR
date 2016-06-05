/************************************************************************************

PublicHeader:   OVR_Kernel.h
Filename    :   OVR_Nullptr.h
Content     :   Implements C++11 nullptr for the case that the compiler doesn't.
Created     :   June 19, 2014
Notes       : 

Copyright   :   Copyright 2014 Oculus VR, Inc. All Rights reserved.

Licensed under the Oculus VR Rift SDK License Version 3.1 (the "License"); 
you may not use the Oculus VR Rift SDK except in compliance with the License, 
which is provided at the time of installation or download, or which 
otherwise accompanies this software in either electronic or hard copy form.

You may obtain a copy of the License at

http://www.oculusvr.com/licenses/LICENSE-3.1 

Unless required by applicable law or agreed to in writing, the Oculus VR SDK 
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

************************************************************************************/

#ifndef OVR_Nullptr_h
#define OVR_Nullptr_h

#pragma once

#include "OVR_Types.h"


//-----------------------------------------------------------------------------------
// ***** OVR_HAVE_std_nullptr_t
//
// Identifies if <cstddef.h> includes std::nullptr_t. 
//
#if !defined(OVR_HAVE_std_nullptr_t) && defined(OVR_CPP11_ENABLED)
    #if defined(OVR_STDLIB_LIBCPP)
        #define OVR_HAVE_std_nullptr_t 1
    #elif defined(OVR_STDLIB_LIBSTDCPP)
        #if (__GLIBCXX__ >= 20110325) && (__GLIBCXX__ != 20110428) && (__GLIBCXX__ != 20120702)
            #define OVR_HAVE_std_nullptr_t 1
        #endif
    #elif defined(_MSC_VER) && (_MSC_VER >= 1600) // VS2010+
        #define OVR_HAVE_std_nullptr_t 1
    #elif defined(__clang__)
        #define OVR_HAVE_std_nullptr_t 1
    #elif defined(OVR_CPP_GNUC) && (OVR_CPP_VERSION >= 406) // GCC 4.6+
        #define OVR_HAVE_std_nullptr_t 1
    #endif
#endif


//-----------------------------------------------------------------------------------
// ***** nullptr / std::nullptr_t
//
// Declares and defines nullptr and related types.
//
#if defined(OVR_CPP_NO_NULLPTR)
    namespace std
    {

        using std::nullptr_t;
        inline nullptr_t nullptr_get()
        {
            nullptr_t n = { };
            return n;
        }
        using std::nullptr_get;

        #if !defined(nullptr)
            #define nullptr nullptr_get()
        #endif

    } // namespace std


// Some compilers natively support C++11 nullptr but the standard library being used 
// doesn't declare std::nullptr_t, in which case we provide one ourselves.
#elif !defined(OVR_HAVE_std_nullptr_t) && !defined(OVR_CPP_NO_DECLTYPE)
    namespace std { typedef decltype(nullptr) nullptr_t; }
#endif


#endif


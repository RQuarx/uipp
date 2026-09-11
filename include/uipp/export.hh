#pragma once


#ifdef UIPP_SHARED
#    if defined(_WIN32) or defined(__CYGWIN__)
#        ifdef UIPP_BUILDING
#            define uipp_public msvc::dllexport
#        else
#            define uipp_public msvc::dllimport
#        endif
#    else
#        define uipp_public gnu::visibility("default")
#    endif
#else
#    define uipp_public
#endif

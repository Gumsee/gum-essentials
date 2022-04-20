#pragma once
#ifdef GUM_OS_LINUX
    #include <X11/Xlib.h>
#endif

namespace Gum {
namespace Display
{
    #ifdef GUM_OS_LINUX
        extern ::Display* pXDisplay;
    #endif

    extern void init();
    extern void destroy();
}}
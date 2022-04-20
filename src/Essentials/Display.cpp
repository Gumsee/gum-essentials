#include "Display.h"
#include "Output.h"

namespace Gum {
namespace Display
{
    #ifdef GUM_OS_LINUX
        ::Display* pXDisplay = nullptr;
    #endif

    void init()
    {
        #ifdef GUM_OS_LINUX
            pXDisplay = XOpenDisplay(NULL);

            // Opening display failed: The best we can do at the moment is to output a meaningful error message
            // and cause an abnormal program termination
            if (!pXDisplay)
            {
                Gum::Output::error("Failed to open X11 display; make sure the DISPLAY environment variable is set correctly");
                std::abort();
            }
        #endif

    }

    void destroy()
    {
        #ifdef GUM_OS_LINUX
            XCloseDisplay(pXDisplay);
        #endif
    }
}}
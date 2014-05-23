#include "CoRE4INET_InControls.h"

using namespace CoRE4INET;


Define_Module(BE_InControl);

#ifdef WITH_AS6802_COMMON
Define_Module(CT_BE_InControl);
#endif

#if defined(WITH_AVB_COMMON) && defined(WITH_AS6802_COMMON)
Define_Module(CT_AVB_BE_InControl);
#endif

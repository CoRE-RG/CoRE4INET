#include "CoRE4INET_Shapers.h"

using namespace CoRE4INET;

Define_Module(BE_Shaper);

#ifdef WITH_IEEE8021Q_COMMON
Define_Module(IEEE8021Q_Shaper);
#endif

#ifdef WITH_AS6802_COMMON
Define_Module(PCF_RC_BE_Shaper);
Define_Module(TT_PCF_RC_BE_Shaper);
#endif

#if defined(WITH_AVB_COMMON) && defined(WITH_AS6802_COMMON)
Define_Module(TT_AVBClassA_PCF_RC_BE_Shaper);
Define_Module(TT_AVBClassA_AVBClassB_PCF_RC_BE_Shaper);
#endif

#if defined(WITH_AVB_COMMON) && defined(WITH_AS6802_COMMON) && defined(WITH_IEEE8021Q_COMMON)
Define_Module(TT_AVBClassA_AVBClassB_PCF_RC_8021Q_Shaper);
#endif

#
# OMNeT++/OMNEST Makefile for libTTEthernetModel
#
# This file was generated with the command:
#  opp_makemake -f --deep --make-so -O out -I/home/tillsteinbach/workspaces/omnet4.2/inet/src/linklayer/ethernet -I/home/tillsteinbach/workspaces/omnet4.2/inet/src/networklayer/common -I/home/tillsteinbach/workspaces/omnet4.2/inet/src/base -I/home/tillsteinbach/workspaces/omnet4.2/inet/src/networklayer/contract -I/home/tillsteinbach/workspaces/omnet4.2/inet/src/util -I/home/tillsteinbach/workspaces/omnet4.2/inet/src/linklayer/contract -L/home/tillsteinbach/workspaces/omnet4.2/inet/out/$(CONFIGNAME)/src -linet -DWITH_TTE_COMMON -DINET_IMPORT -KINET_PROJ=/home/tillsteinbach/workspaces/omnet4.2/inet
#

# Name of target to be created (-o option)
TARGET = libTTEthernetModel$(SHARED_LIB_SUFFIX)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I$(INET_PROJ)/src/linklayer/ethernet \
    -I$(INET_PROJ)/src/networklayer/common \
    -I$(INET_PROJ)/src/base \
    -I$(INET_PROJ)/src/networklayer/contract \
    -I$(INET_PROJ)/src/util \
    -I$(INET_PROJ)/src/linklayer/contract \
    -I. \
    -Iapi \
    -Iapi/tte_api \
    -Iapplications \
    -Ibase \
    -Ibuffer \
    -Iconfiguration \
    -Ictc \
    -Ilinklayer \
    -Ilinklayer/ethernet \
    -Inodes \
    -Inodes/ethernet \
    -Ischeduler \
    -Isynchronisation \
    -Iutilities

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L$(INET_PROJ)/out/$(CONFIGNAME)/src  -linet
LIBS += -Wl,-rpath,`abspath $(INET_PROJ)/out/$(CONFIGNAME)/src`

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/api/Task.o \
    $O/api/Callback.o \
    $O/applications/TTETestApp.o \
    $O/applications/TrafficSourceAppBase.o \
    $O/applications/TTEApplicationBase.o \
    $O/applications/TTEAPIApplicationBase.o \
    $O/applications/TTTrafficSourceApp.o \
    $O/applications/TTEAPITestApplication.o \
    $O/applications/RCTrafficSourceApp.o \
    $O/buffer/TTDoubleBuffer.o \
    $O/buffer/BGQueueBuffer.o \
    $O/buffer/TTQueueBuffer.o \
    $O/buffer/BGBuffer.o \
    $O/buffer/RCDoubleBuffer.o \
    $O/buffer/DoubleBuffer.o \
    $O/buffer/RCBuffer.o \
    $O/buffer/TTBuffer.o \
    $O/buffer/QueueBuffer.o \
    $O/buffer/RCQueueBuffer.o \
    $O/buffer/Buffer.o \
    $O/configuration/BaseConfigurationManager.o \
    $O/ctc/RCIncoming.o \
    $O/ctc/TTIncoming.o \
    $O/ctc/Incoming.o \
    $O/linklayer/TTEInput.o \
    $O/linklayer/TTEOutput.o \
    $O/linklayer/BGTrafficHandle.o \
    $O/scheduler/SchedulerEvent.o \
    $O/scheduler/TTEScheduler.o \
    $O/synchronisation/Sync.o \
    $O/utilities/HelperFunctions.o \
    $O/api/APIPayload_m.o \
    $O/buffer/TTBufferEmpty_m.o \
    $O/linklayer/ethernet/CTFrame_m.o \
    $O/scheduler/SchedulerMessage_m.o \
    $O/scheduler/SchedulerMessageEvents_m.o

# Message files
MSGFILES = \
    api/APIPayload.msg \
    buffer/TTBufferEmpty.msg \
    linklayer/ethernet/CTFrame.msg \
    scheduler/SchedulerMessage.msg \
    scheduler/SchedulerMessageEvents.msg

# Other makefile variables (-K)
INET_PROJ=/home/tillsteinbach/workspaces/omnet4.2/inet

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppenvir$D $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS) -DWITH_TTE_COMMON -DINET_IMPORT $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $(TARGET)

$(TARGET) : $O/$(TARGET)
	$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	$(SHLIB_LD) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(LIBS) $(OMNETPP_LIBS) $(LDFLAGS)
	$(SHLIB_POSTPROCESS) $O/$(TARGET)

.PHONY:

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(CXX) -c $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	-rm -rf $O
	-rm -f TTEthernetModel TTEthernetModel.exe libTTEthernetModel.so libTTEthernetModel.a libTTEthernetModel.dll libTTEthernetModel.dylib
	-rm -f ./*_m.cc ./*_m.h
	-rm -f api/*_m.cc api/*_m.h
	-rm -f api/tte_api/*_m.cc api/tte_api/*_m.h
	-rm -f applications/*_m.cc applications/*_m.h
	-rm -f base/*_m.cc base/*_m.h
	-rm -f buffer/*_m.cc buffer/*_m.h
	-rm -f configuration/*_m.cc configuration/*_m.h
	-rm -f ctc/*_m.cc ctc/*_m.h
	-rm -f linklayer/*_m.cc linklayer/*_m.h
	-rm -f linklayer/ethernet/*_m.cc linklayer/ethernet/*_m.h
	-rm -f nodes/*_m.cc nodes/*_m.h
	-rm -f nodes/ethernet/*_m.cc nodes/ethernet/*_m.h
	-rm -f scheduler/*_m.cc scheduler/*_m.h
	-rm -f synchronisation/*_m.cc synchronisation/*_m.h
	-rm -f utilities/*_m.cc utilities/*_m.h

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc api/*.cc api/tte_api/*.cc applications/*.cc base/*.cc buffer/*.cc configuration/*.cc ctc/*.cc linklayer/*.cc linklayer/ethernet/*.cc nodes/*.cc nodes/ethernet/*.cc scheduler/*.cc synchronisation/*.cc utilities/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/api/APIPayload_m.o: api/APIPayload_m.cc \
	api/APIPayload_m.h \
	$(INET_PROJ)/src/base/INETDefs.h
$O/api/Callback.o: api/Callback.cc \
	api/Callback.h \
	api/tte_api/tte_api.h \
	applications/TTEAPIApplicationBase.h \
	applications/TTEApplicationBase.h \
	buffer/Buffer.h \
	buffer/RCBuffer.h \
	buffer/TTBuffer.h \
	ctc/Incoming.h \
	linklayer/ethernet/CTFrame_m.h \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessageEvents_m.h \
	scheduler/SchedulerMessage_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h
$O/api/Task.o: api/Task.cc \
	api/Task.h
$O/applications/RCTrafficSourceApp.o: applications/RCTrafficSourceApp.cc \
	api/Callback.h \
	api/tte_api/tte_api.h \
	applications/RCTrafficSourceApp.h \
	applications/TTEApplicationBase.h \
	applications/TrafficSourceAppBase.h \
	buffer/Buffer.h \
	buffer/RCBuffer.h \
	buffer/TTBuffer.h \
	ctc/Incoming.h \
	linklayer/ethernet/CTFrame_m.h \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessageEvents_m.h \
	scheduler/SchedulerMessage_m.h \
	scheduler/TTEScheduler.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h
$O/applications/TTEAPIApplicationBase.o: applications/TTEAPIApplicationBase.cc \
	api/APIPayload_m.h \
	api/Callback.h \
	api/Task.h \
	api/tte_api/tte_api.h \
	applications/TTEAPIApplicationBase.h \
	applications/TTEApplicationBase.h \
	buffer/BGBuffer.h \
	buffer/Buffer.h \
	buffer/RCBuffer.h \
	buffer/TTBuffer.h \
	ctc/Incoming.h \
	ctc/RCIncoming.h \
	ctc/TTIncoming.h \
	linklayer/ethernet/CTFrame_m.h \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessageEvents_m.h \
	scheduler/SchedulerMessage_m.h \
	scheduler/TTEScheduler.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/contract/TxNotifDetails.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherMACBase.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherMACFullDuplex.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h
$O/applications/TTEAPITestApplication.o: applications/TTEAPITestApplication.cc \
	api/Callback.h \
	api/tte_api/tte_api.h \
	applications/TTEAPIApplicationBase.h \
	applications/TTEAPITestApplication.h \
	applications/TTEApplicationBase.h \
	buffer/Buffer.h \
	buffer/RCBuffer.h \
	buffer/TTBuffer.h \
	ctc/Incoming.h \
	linklayer/ethernet/CTFrame_m.h \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessageEvents_m.h \
	scheduler/SchedulerMessage_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h
$O/applications/TTEApplicationBase.o: applications/TTEApplicationBase.cc \
	api/Callback.h \
	api/tte_api/tte_api.h \
	applications/TTEApplicationBase.h \
	buffer/Buffer.h \
	buffer/RCBuffer.h \
	buffer/TTBuffer.h \
	ctc/Incoming.h \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessageEvents_m.h \
	scheduler/SchedulerMessage_m.h \
	utilities/HelperFunctions.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h
$O/applications/TTETestApp.o: applications/TTETestApp.cc \
	api/Callback.h \
	api/tte_api/tte_api.h \
	applications/TTEApplicationBase.h \
	applications/TTETestApp.h \
	buffer/Buffer.h \
	buffer/RCBuffer.h \
	buffer/TTBuffer.h \
	ctc/Incoming.h \
	linklayer/ethernet/CTFrame_m.h \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessageEvents_m.h \
	scheduler/SchedulerMessage_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h
$O/applications/TTTrafficSourceApp.o: applications/TTTrafficSourceApp.cc \
	api/Callback.h \
	api/tte_api/tte_api.h \
	applications/TTEApplicationBase.h \
	applications/TTTrafficSourceApp.h \
	applications/TrafficSourceAppBase.h \
	buffer/Buffer.h \
	buffer/RCBuffer.h \
	buffer/TTBuffer.h \
	ctc/Incoming.h \
	linklayer/ethernet/CTFrame_m.h \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessageEvents_m.h \
	scheduler/SchedulerMessage_m.h \
	scheduler/TTEScheduler.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h
$O/applications/TrafficSourceAppBase.o: applications/TrafficSourceAppBase.cc \
	api/Callback.h \
	api/tte_api/tte_api.h \
	applications/TTEApplicationBase.h \
	applications/TrafficSourceAppBase.h \
	buffer/Buffer.h \
	buffer/RCBuffer.h \
	buffer/TTBuffer.h \
	ctc/Incoming.h \
	linklayer/ethernet/CTFrame_m.h \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessageEvents_m.h \
	scheduler/SchedulerMessage_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h
$O/buffer/BGBuffer.o: buffer/BGBuffer.cc \
	api/Callback.h \
	api/tte_api/tte_api.h \
	applications/TTEApplicationBase.h \
	buffer/BGBuffer.h \
	buffer/Buffer.h \
	buffer/RCBuffer.h \
	buffer/TTBuffer.h \
	ctc/Incoming.h \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessageEvents_m.h \
	scheduler/SchedulerMessage_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h
$O/buffer/BGQueueBuffer.o: buffer/BGQueueBuffer.cc \
	buffer/BGBuffer.h \
	buffer/BGQueueBuffer.h \
	buffer/Buffer.h \
	buffer/QueueBuffer.h \
	buffer/TTBuffer.h \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessageEvents_m.h \
	scheduler/SchedulerMessage_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h
$O/buffer/Buffer.o: buffer/Buffer.cc \
	api/Callback.h \
	api/tte_api/tte_api.h \
	applications/TTEApplicationBase.h \
	buffer/Buffer.h \
	buffer/RCBuffer.h \
	buffer/TTBuffer.h \
	ctc/Incoming.h \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessageEvents_m.h \
	scheduler/SchedulerMessage_m.h \
	utilities/HelperFunctions.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h
$O/buffer/DoubleBuffer.o: buffer/DoubleBuffer.cc \
	buffer/Buffer.h \
	buffer/DoubleBuffer.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h
$O/buffer/QueueBuffer.o: buffer/QueueBuffer.cc \
	buffer/Buffer.h \
	buffer/QueueBuffer.h \
	buffer/TTBuffer.h \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessageEvents_m.h \
	scheduler/SchedulerMessage_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h
$O/buffer/RCBuffer.o: buffer/RCBuffer.cc \
	api/Callback.h \
	api/tte_api/tte_api.h \
	applications/TTEApplicationBase.h \
	buffer/Buffer.h \
	buffer/RCBuffer.h \
	buffer/TTBuffer.h \
	ctc/Incoming.h \
	linklayer/ethernet/CTFrame_m.h \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessageEvents_m.h \
	scheduler/SchedulerMessage_m.h \
	scheduler/TTEScheduler.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h
$O/buffer/RCDoubleBuffer.o: buffer/RCDoubleBuffer.cc \
	buffer/Buffer.h \
	buffer/DoubleBuffer.h \
	buffer/RCBuffer.h \
	buffer/RCDoubleBuffer.h \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessageEvents_m.h \
	scheduler/SchedulerMessage_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h
$O/buffer/RCQueueBuffer.o: buffer/RCQueueBuffer.cc \
	buffer/Buffer.h \
	buffer/QueueBuffer.h \
	buffer/RCBuffer.h \
	buffer/RCQueueBuffer.h \
	buffer/TTBuffer.h \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessageEvents_m.h \
	scheduler/SchedulerMessage_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h
$O/buffer/TTBuffer.o: buffer/TTBuffer.cc \
	api/Callback.h \
	api/tte_api/tte_api.h \
	applications/TTEApplicationBase.h \
	buffer/Buffer.h \
	buffer/RCBuffer.h \
	buffer/TTBuffer.h \
	buffer/TTBufferEmpty_m.h \
	ctc/Incoming.h \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessageEvents_m.h \
	scheduler/SchedulerMessage_m.h \
	scheduler/TTEScheduler.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h
$O/buffer/TTBufferEmpty_m.o: buffer/TTBufferEmpty_m.cc \
	buffer/TTBufferEmpty_m.h
$O/buffer/TTDoubleBuffer.o: buffer/TTDoubleBuffer.cc \
	buffer/Buffer.h \
	buffer/DoubleBuffer.h \
	buffer/TTBuffer.h \
	buffer/TTDoubleBuffer.h \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessageEvents_m.h \
	scheduler/SchedulerMessage_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h
$O/buffer/TTQueueBuffer.o: buffer/TTQueueBuffer.cc \
	buffer/Buffer.h \
	buffer/QueueBuffer.h \
	buffer/TTBuffer.h \
	buffer/TTQueueBuffer.h \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessageEvents_m.h \
	scheduler/SchedulerMessage_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h
$O/configuration/BaseConfigurationManager.o: configuration/BaseConfigurationManager.cc \
	configuration/BaseConfigurationManager.h
$O/ctc/Incoming.o: ctc/Incoming.cc \
	ctc/Incoming.h
$O/ctc/RCIncoming.o: ctc/RCIncoming.cc \
	ctc/Incoming.h \
	ctc/RCIncoming.h \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessage_m.h \
	scheduler/TTEScheduler.h
$O/ctc/TTIncoming.o: ctc/TTIncoming.cc \
	ctc/Incoming.h \
	ctc/TTIncoming.h \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessageEvents_m.h \
	scheduler/SchedulerMessage_m.h \
	scheduler/TTEScheduler.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h
$O/linklayer/BGTrafficHandle.o: linklayer/BGTrafficHandle.cc \
	linklayer/BGTrafficHandle.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h
$O/linklayer/TTEInput.o: linklayer/TTEInput.cc \
	ctc/Incoming.h \
	linklayer/TTEInput.h \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessage_m.h \
	scheduler/TTEScheduler.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h
$O/linklayer/TTEOutput.o: linklayer/TTEOutput.cc \
	buffer/Buffer.h \
	buffer/RCBuffer.h \
	buffer/TTBuffer.h \
	buffer/TTBufferEmpty_m.h \
	linklayer/TTEOutput.h \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessageEvents_m.h \
	scheduler/SchedulerMessage_m.h \
	scheduler/TTEScheduler.h \
	utilities/HelperFunctions.h \
	$(INET_PROJ)/src/base/AbstractQueue.h \
	$(INET_PROJ)/src/base/EnqueueHook.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/IPassiveQueue.h \
	$(INET_PROJ)/src/base/QueueWithQoS.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h
$O/linklayer/ethernet/CTFrame_m.o: linklayer/ethernet/CTFrame_m.cc \
	linklayer/ethernet/CTFrame_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h
$O/scheduler/SchedulerEvent.o: scheduler/SchedulerEvent.cc \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessage_m.h
$O/scheduler/SchedulerMessageEvents_m.o: scheduler/SchedulerMessageEvents_m.cc \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessageEvents_m.h \
	scheduler/SchedulerMessage_m.h
$O/scheduler/SchedulerMessage_m.o: scheduler/SchedulerMessage_m.cc \
	scheduler/SchedulerMessage_m.h
$O/scheduler/TTEScheduler.o: scheduler/TTEScheduler.cc \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessageEvents_m.h \
	scheduler/SchedulerMessage_m.h \
	scheduler/TTEScheduler.h
$O/synchronisation/Sync.o: synchronisation/Sync.cc \
	synchronisation/Sync.h
$O/utilities/HelperFunctions.o: utilities/HelperFunctions.cc \
	utilities/HelperFunctions.h


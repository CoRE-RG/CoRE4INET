#
# OMNeT++/OMNEST Makefile for libTTEthernetSupport
#
# This file was generated with the command:
#  opp_makemake -f --deep --make-so -o TTEthernetSupport -O out -I/home/tillsteinbach/workspaces/omnet4.2b2/TTEthernetModelV2/emf4cpp-0.0.2/include/emf4cpp -I/home/tillsteinbach/workspaces/omnet4.2b2/TTEthernetModelV2/model-src -I../../inet/src/linklayer/ethernet -I../../inet/src/networklayer/ipv4 -I../../inet/src/networklayer/common -I../../inet/src/networklayer/ipv4/contract -I../../inet/src/util/headerserializers/ipv4 -I../../inet/src/base -I../../inet/src/util/headerserializers -I../../inet/src/networklayer/contract -I../../inet/src/util -I../../inet/src/applications/pingapp -I../../inet/src/linklayer/contract -I../../inet/src/networklayer/arp -L../../inet/out/$(CONFIGNAME)/src -lxerces-c -lemf4cpp-ecore -lemf4cpp-ecorecpp -lemf4cpp-Device_Specification -lemf4cpp-Device_Target_Mapping -lemf4cpp-Device_Targets -lemf4cpp-IP_Configuration -lemf4cpp-Network_Configuration -lemf4cpp-Protocol_Definition -lemf4cpp-System_Specification -lemf4cpp-Virtuallink_Map -linet -DWITH_TTE_COMMON -KINET_PROJ=../../inet -- -L../emf4cpp-0.0.2/lib -L../model-src
#

# Name of target to be created (-o option)
TARGET = libTTEthernetSupport$(SHARED_LIB_SUFFIX)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I../emf4cpp-0.0.2/include/emf4cpp \
    -I../model-src \
    -I../../inet/src/linklayer/ethernet \
    -I../../inet/src/networklayer/ipv4 \
    -I../../inet/src/networklayer/common \
    -I../../inet/src/networklayer/ipv4/contract \
    -I../../inet/src/util/headerserializers/ipv4 \
    -I../../inet/src/base \
    -I../../inet/src/util/headerserializers \
    -I../../inet/src/networklayer/contract \
    -I../../inet/src/util \
    -I../../inet/src/applications/pingapp \
    -I../../inet/src/linklayer/contract \
    -I../../inet/src/networklayer/arp \
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
    -Isynchronisation

# Additional object and library files to link with
EXTRA_OBJS = -L../emf4cpp-0.0.2/lib -L../model-src

# Additional libraries (-L, -l options)
LIBS = -L../../inet/out/$(CONFIGNAME)/src  -lxerces-c -lemf4cpp-ecore -lemf4cpp-ecorecpp -lemf4cpp-Device_Specification -lemf4cpp-Device_Target_Mapping -lemf4cpp-Device_Targets -lemf4cpp-IP_Configuration -lemf4cpp-Network_Configuration -lemf4cpp-Protocol_Definition -lemf4cpp-System_Specification -lemf4cpp-Virtuallink_Map -linet
LIBS += -Wl,-rpath,`abspath ../../inet/out/$(CONFIGNAME)/src`

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/applications/TTETestApp.o \
    $O/applications/TTEAPIApplicationBase.o \
    $O/applications/TTEAPITestApplication.o \
    $O/buffer/TTDoubleBuffer.o \
    $O/buffer/TTQueueBuffer.o \
    $O/buffer/RCDoubleBuffer.o \
    $O/buffer/BufferManager.o \
    $O/buffer/DoubleBuffer.o \
    $O/buffer/RCBuffer.o \
    $O/buffer/TTBuffer.o \
    $O/buffer/QueueBuffer.o \
    $O/buffer/RCQueueBuffer.o \
    $O/buffer/Buffer.o \
    $O/configuration/ConfigurationUtils.o \
    $O/ctc/RCIncoming.o \
    $O/ctc/TTIncoming.o \
    $O/ctc/Incoming.o \
    $O/linklayer/TTEInput.o \
    $O/linklayer/TTEOutput.o \
    $O/scheduler/SchedulerEvent.o \
    $O/scheduler/TTEScheduler.o \
    $O/synchronisation/Sync.o \
    $O/buffer/TTBufferEmpty_m.o \
    $O/linklayer/ethernet/CTFrame_m.o \
    $O/scheduler/SchedulerMessage_m.o \
    $O/scheduler/SchedulerMessageEvents_m.o

# Message files
MSGFILES = \
    buffer/TTBufferEmpty.msg \
    linklayer/ethernet/CTFrame.msg \
    scheduler/SchedulerMessage.msg \
    scheduler/SchedulerMessageEvents.msg

# Other makefile variables (-K)
INET_PROJ=../../inet

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

COPTS = $(CFLAGS) -DWITH_TTE_COMMON $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

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

$O/%.o: %.cc
	@$(MKPATH) $(dir $@)
	$(CXX) -c $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	-rm -rf $O
	-rm -f TTEthernetSupport TTEthernetSupport.exe libTTEthernetSupport.so libTTEthernetSupport.a libTTEthernetSupport.dll libTTEthernetSupport.dylib
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

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc api/*.cc api/tte_api/*.cc applications/*.cc base/*.cc buffer/*.cc configuration/*.cc ctc/*.cc linklayer/*.cc linklayer/ethernet/*.cc nodes/*.cc nodes/ethernet/*.cc scheduler/*.cc synchronisation/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/applications/TTEAPITestApplication.o: applications/TTEAPITestApplication.cc \
	applications/TTEAPITestApplication.h \
	applications/TTEAPIApplicationBase.h \
	api/tte_api/tte_api.h
$O/applications/TTEAPIApplicationBase.o: applications/TTEAPIApplicationBase.cc \
	$(INET_PROJ)/src/linklayer/contract/TxNotifDetails.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherMACFullDuplex.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	applications/TTEAPIApplicationBase.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherMACBase.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	api/tte_api/tte_api.h
$O/applications/TTETestApp.o: applications/TTETestApp.cc \
	$(INET_PROJ)/src/base/INETDefs.h \
	applications/TTETestApp.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	linklayer/ethernet/CTFrame_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h
$O/buffer/TTBuffer.o: buffer/TTBuffer.cc \
	scheduler/SchedulerEvent.h \
	buffer/TTBuffer.h \
	scheduler/SchedulerMessage_m.h \
	scheduler/TTEScheduler.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	scheduler/SchedulerMessageEvents_m.h \
	buffer/Buffer.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	buffer/TTBufferEmpty_m.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h
$O/buffer/RCBuffer.o: buffer/RCBuffer.cc \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessage_m.h \
	scheduler/TTEScheduler.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	scheduler/SchedulerMessageEvents_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	linklayer/ethernet/CTFrame_m.h \
	buffer/RCBuffer.h \
	buffer/Buffer.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h
$O/buffer/TTQueueBuffer.o: buffer/TTQueueBuffer.cc \
	buffer/QueueBuffer.h \
	buffer/TTBuffer.h \
	buffer/TTQueueBuffer.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	buffer/Buffer.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h
$O/buffer/TTDoubleBuffer.o: buffer/TTDoubleBuffer.cc \
	buffer/TTDoubleBuffer.h \
	buffer/TTBuffer.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	buffer/Buffer.h \
	buffer/DoubleBuffer.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h
$O/buffer/TTBufferEmpty_m.o: buffer/TTBufferEmpty_m.cc \
	buffer/TTBufferEmpty_m.h
$O/buffer/QueueBuffer.o: buffer/QueueBuffer.cc \
	buffer/QueueBuffer.h \
	buffer/TTBuffer.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	buffer/Buffer.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h
$O/buffer/BufferManager.o: buffer/BufferManager.cc \
	$(INET_PROJ)/src/base/IPassiveQueue.h \
	$(INET_PROJ)/src/base/AbstractQueue.h \
	buffer/BufferManager.h \
	configuration/ConfigurationUtils.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	buffer/Buffer.h \
	linklayer/TTEOutput.h \
	$(INET_PROJ)/src/base/EnqueueHook.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	ctc/Incoming.h \
	buffer/TTBuffer.h \
	linklayer/TTEInput.h \
	$(INET_PROJ)/src/base/QueueWithQoS.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h
$O/buffer/Buffer.o: buffer/Buffer.cc \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	buffer/Buffer.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h
$O/buffer/RCDoubleBuffer.o: buffer/RCDoubleBuffer.cc \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessage_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	buffer/RCBuffer.h \
	scheduler/SchedulerMessageEvents_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	buffer/DoubleBuffer.h \
	buffer/Buffer.h \
	buffer/RCDoubleBuffer.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h
$O/buffer/DoubleBuffer.o: buffer/DoubleBuffer.cc \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	buffer/Buffer.h \
	buffer/DoubleBuffer.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h
$O/buffer/RCQueueBuffer.o: buffer/RCQueueBuffer.cc \
	buffer/QueueBuffer.h \
	scheduler/SchedulerMessage_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	buffer/RCBuffer.h \
	buffer/RCQueueBuffer.h \
	buffer/Buffer.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	scheduler/SchedulerEvent.h \
	buffer/TTBuffer.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	scheduler/SchedulerMessageEvents_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h
$O/configuration/ConfigurationUtils.o: configuration/ConfigurationUtils.cc \
	configuration/ConfigurationUtils.h
$O/ctc/TTIncoming.o: ctc/TTIncoming.cc \
	scheduler/SchedulerEvent.h \
	ctc/Incoming.h \
	scheduler/SchedulerMessage_m.h \
	scheduler/TTEScheduler.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	scheduler/SchedulerMessageEvents_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	ctc/TTIncoming.h
$O/ctc/RCIncoming.o: ctc/RCIncoming.cc \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessage_m.h \
	scheduler/TTEScheduler.h \
	ctc/RCIncoming.h
$O/ctc/Incoming.o: ctc/Incoming.cc \
	ctc/Incoming.h
$O/linklayer/TTEOutput.o: linklayer/TTEOutput.cc \
	$(INET_PROJ)/src/base/IPassiveQueue.h \
	$(INET_PROJ)/src/base/AbstractQueue.h \
	scheduler/SchedulerMessage_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	buffer/RCBuffer.h \
	linklayer/TTEOutput.h \
	buffer/Buffer.h \
	$(INET_PROJ)/src/base/EnqueueHook.h \
	buffer/TTBufferEmpty_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	scheduler/SchedulerEvent.h \
	buffer/TTBuffer.h \
	scheduler/TTEScheduler.h \
	$(INET_PROJ)/src/base/QueueWithQoS.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	scheduler/SchedulerMessageEvents_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h
$O/linklayer/TTEInput.o: linklayer/TTEInput.cc \
	ctc/Incoming.h \
	configuration/ConfigurationUtils.h \
	linklayer/TTEInput.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h
$O/linklayer/ethernet/CTFrame_m.o: linklayer/ethernet/CTFrame_m.cc \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/ethernet/Ethernet.h \
	linklayer/ethernet/CTFrame_m.h \
	$(INET_PROJ)/src/linklayer/ethernet/EtherFrame_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h
$O/scheduler/SchedulerMessageEvents_m.o: scheduler/SchedulerMessageEvents_m.cc \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessage_m.h \
	scheduler/SchedulerMessageEvents_m.h
$O/scheduler/SchedulerMessage_m.o: scheduler/SchedulerMessage_m.cc \
	scheduler/SchedulerMessage_m.h
$O/scheduler/TTEScheduler.o: scheduler/TTEScheduler.cc \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessage_m.h \
	configuration/ConfigurationUtils.h \
	scheduler/TTEScheduler.h \
	scheduler/SchedulerMessageEvents_m.h
$O/scheduler/SchedulerEvent.o: scheduler/SchedulerEvent.cc \
	scheduler/SchedulerEvent.h \
	scheduler/SchedulerMessage_m.h
$O/synchronisation/Sync.o: synchronisation/Sync.cc \
	synchronisation/Sync.h


//
// Generated file, do not edit! Created by opp_msgc 4.2 from scheduler/SchedulerMessageEvents.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "SchedulerMessageEvents_m.h"

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}



namespace TTEthernetModel {

Register_Class(SchedulerActionTimeEvent);

SchedulerActionTimeEvent::SchedulerActionTimeEvent(const char *name, int kind) : TTEthernetModel::SchedulerEvent(name,kind)
{
    this->action_time_var = 0;
}

SchedulerActionTimeEvent::SchedulerActionTimeEvent(const SchedulerActionTimeEvent& other) : TTEthernetModel::SchedulerEvent()
{
    setName(other.getName());
    operator=(other);
}

SchedulerActionTimeEvent::~SchedulerActionTimeEvent()
{
}

SchedulerActionTimeEvent& SchedulerActionTimeEvent::operator=(const SchedulerActionTimeEvent& other)
{
    if (this==&other) return *this;
    TTEthernetModel::SchedulerEvent::operator=(other);
    this->action_time_var = other.action_time_var;
    return *this;
}

void SchedulerActionTimeEvent::parsimPack(cCommBuffer *b)
{
    TTEthernetModel::SchedulerEvent::parsimPack(b);
    doPacking(b,this->action_time_var);
}

void SchedulerActionTimeEvent::parsimUnpack(cCommBuffer *b)
{
    TTEthernetModel::SchedulerEvent::parsimUnpack(b);
    doUnpacking(b,this->action_time_var);
}

unsigned int SchedulerActionTimeEvent::getAction_time() const
{
    return action_time_var;
}

void SchedulerActionTimeEvent::setAction_time(unsigned int action_time_var)
{
    this->action_time_var = action_time_var;
}

class SchedulerActionTimeEventDescriptor : public cClassDescriptor
{
  public:
    SchedulerActionTimeEventDescriptor();
    virtual ~SchedulerActionTimeEventDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(SchedulerActionTimeEventDescriptor);

SchedulerActionTimeEventDescriptor::SchedulerActionTimeEventDescriptor() : cClassDescriptor("TTEthernetModel::SchedulerActionTimeEvent", "TTEthernetModel::SchedulerEvent")
{
}

SchedulerActionTimeEventDescriptor::~SchedulerActionTimeEventDescriptor()
{
}

bool SchedulerActionTimeEventDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<SchedulerActionTimeEvent *>(obj)!=NULL;
}

const char *SchedulerActionTimeEventDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int SchedulerActionTimeEventDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int SchedulerActionTimeEventDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *SchedulerActionTimeEventDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "action_time",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int SchedulerActionTimeEventDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='a' && strcmp(fieldName, "action_time")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *SchedulerActionTimeEventDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *SchedulerActionTimeEventDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int SchedulerActionTimeEventDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    SchedulerActionTimeEvent *pp = (SchedulerActionTimeEvent *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string SchedulerActionTimeEventDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    SchedulerActionTimeEvent *pp = (SchedulerActionTimeEvent *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getAction_time());
        default: return "";
    }
}

bool SchedulerActionTimeEventDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    SchedulerActionTimeEvent *pp = (SchedulerActionTimeEvent *)object; (void)pp;
    switch (field) {
        case 0: pp->setAction_time(string2ulong(value)); return true;
        default: return false;
    }
}

const char *SchedulerActionTimeEventDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
    };
    return (field>=0 && field<1) ? fieldStructNames[field] : NULL;
}

void *SchedulerActionTimeEventDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    SchedulerActionTimeEvent *pp = (SchedulerActionTimeEvent *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(SchedulerTimerEvent);

SchedulerTimerEvent::SchedulerTimerEvent(const char *name, int kind) : TTEthernetModel::SchedulerEvent(name,kind)
{
    this->timer_var = 0;
}

SchedulerTimerEvent::SchedulerTimerEvent(const SchedulerTimerEvent& other) : TTEthernetModel::SchedulerEvent()
{
    setName(other.getName());
    operator=(other);
}

SchedulerTimerEvent::~SchedulerTimerEvent()
{
}

SchedulerTimerEvent& SchedulerTimerEvent::operator=(const SchedulerTimerEvent& other)
{
    if (this==&other) return *this;
    TTEthernetModel::SchedulerEvent::operator=(other);
    this->timer_var = other.timer_var;
    return *this;
}

void SchedulerTimerEvent::parsimPack(cCommBuffer *b)
{
    TTEthernetModel::SchedulerEvent::parsimPack(b);
    doPacking(b,this->timer_var);
}

void SchedulerTimerEvent::parsimUnpack(cCommBuffer *b)
{
    TTEthernetModel::SchedulerEvent::parsimUnpack(b);
    doUnpacking(b,this->timer_var);
}

unsigned int SchedulerTimerEvent::getTimer() const
{
    return timer_var;
}

void SchedulerTimerEvent::setTimer(unsigned int timer_var)
{
    this->timer_var = timer_var;
}

class SchedulerTimerEventDescriptor : public cClassDescriptor
{
  public:
    SchedulerTimerEventDescriptor();
    virtual ~SchedulerTimerEventDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(SchedulerTimerEventDescriptor);

SchedulerTimerEventDescriptor::SchedulerTimerEventDescriptor() : cClassDescriptor("TTEthernetModel::SchedulerTimerEvent", "TTEthernetModel::SchedulerEvent")
{
}

SchedulerTimerEventDescriptor::~SchedulerTimerEventDescriptor()
{
}

bool SchedulerTimerEventDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<SchedulerTimerEvent *>(obj)!=NULL;
}

const char *SchedulerTimerEventDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int SchedulerTimerEventDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int SchedulerTimerEventDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *SchedulerTimerEventDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "timer",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int SchedulerTimerEventDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "timer")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *SchedulerTimerEventDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *SchedulerTimerEventDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int SchedulerTimerEventDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    SchedulerTimerEvent *pp = (SchedulerTimerEvent *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string SchedulerTimerEventDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    SchedulerTimerEvent *pp = (SchedulerTimerEvent *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getTimer());
        default: return "";
    }
}

bool SchedulerTimerEventDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    SchedulerTimerEvent *pp = (SchedulerTimerEvent *)object; (void)pp;
    switch (field) {
        case 0: pp->setTimer(string2ulong(value)); return true;
        default: return false;
    }
}

const char *SchedulerTimerEventDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
    };
    return (field>=0 && field<1) ? fieldStructNames[field] : NULL;
}

void *SchedulerTimerEventDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    SchedulerTimerEvent *pp = (SchedulerTimerEvent *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

}; // end namespace TTEthernetModel


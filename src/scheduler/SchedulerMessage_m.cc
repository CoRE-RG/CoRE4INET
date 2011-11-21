//
// Generated file, do not edit! Created by opp_msgc 4.2 from scheduler/SchedulerMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "SchedulerMessage_m.h"

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

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("TTEthernetModel::SchedulerMessageKind");
    if (!e) enums.getInstance()->add(e = new cEnum("TTEthernetModel::SchedulerMessageKind"));
    e->insert(NEW_CYCLE, "NEW_CYCLE");
    e->insert(ACTION_TIME_EVENT, "ACTION_TIME_EVENT");
    e->insert(TIMER_EVENT, "TIMER_EVENT");
);

Register_Class(SchedulerMessage);

SchedulerMessage::SchedulerMessage(const char *name, int kind) : cMessage(name,kind)
{
}

SchedulerMessage::SchedulerMessage(const SchedulerMessage& other) : cMessage(other)
{
    copy(other);
}

SchedulerMessage::~SchedulerMessage()
{
}

SchedulerMessage& SchedulerMessage::operator=(const SchedulerMessage& other)
{
    if (this==&other) return *this;
    cMessage::operator=(other);
    copy(other);
    return *this;
}

void SchedulerMessage::copy(const SchedulerMessage& other)
{
}

void SchedulerMessage::parsimPack(cCommBuffer *b)
{
    cMessage::parsimPack(b);
}

void SchedulerMessage::parsimUnpack(cCommBuffer *b)
{
    cMessage::parsimUnpack(b);
}

class SchedulerMessageDescriptor : public cClassDescriptor
{
  public:
    SchedulerMessageDescriptor();
    virtual ~SchedulerMessageDescriptor();

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

Register_ClassDescriptor(SchedulerMessageDescriptor);

SchedulerMessageDescriptor::SchedulerMessageDescriptor() : cClassDescriptor("TTEthernetModel::SchedulerMessage", "cMessage")
{
}

SchedulerMessageDescriptor::~SchedulerMessageDescriptor()
{
}

bool SchedulerMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<SchedulerMessage *>(obj)!=NULL;
}

const char *SchedulerMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int SchedulerMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int SchedulerMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *SchedulerMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int SchedulerMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *SchedulerMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *SchedulerMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int SchedulerMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    SchedulerMessage *pp = (SchedulerMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string SchedulerMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    SchedulerMessage *pp = (SchedulerMessage *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool SchedulerMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    SchedulerMessage *pp = (SchedulerMessage *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *SchedulerMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *SchedulerMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    SchedulerMessage *pp = (SchedulerMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

SchedulerEvent_Base::SchedulerEvent_Base(const char *name, int kind) : TTEthernetModel::SchedulerMessage(name,kind)
{
}

SchedulerEvent_Base::SchedulerEvent_Base(const SchedulerEvent_Base& other) : TTEthernetModel::SchedulerMessage(other)
{
    copy(other);
}

SchedulerEvent_Base::~SchedulerEvent_Base()
{
}

SchedulerEvent_Base& SchedulerEvent_Base::operator=(const SchedulerEvent_Base& other)
{
    if (this==&other) return *this;
    TTEthernetModel::SchedulerMessage::operator=(other);
    copy(other);
    return *this;
}

void SchedulerEvent_Base::copy(const SchedulerEvent_Base& other)
{
}

void SchedulerEvent_Base::parsimPack(cCommBuffer *b)
{
    TTEthernetModel::SchedulerMessage::parsimPack(b);
}

void SchedulerEvent_Base::parsimUnpack(cCommBuffer *b)
{
    TTEthernetModel::SchedulerMessage::parsimUnpack(b);
}

class SchedulerEventDescriptor : public cClassDescriptor
{
  public:
    SchedulerEventDescriptor();
    virtual ~SchedulerEventDescriptor();

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

Register_ClassDescriptor(SchedulerEventDescriptor);

SchedulerEventDescriptor::SchedulerEventDescriptor() : cClassDescriptor("TTEthernetModel::SchedulerEvent", "TTEthernetModel::SchedulerMessage")
{
}

SchedulerEventDescriptor::~SchedulerEventDescriptor()
{
}

bool SchedulerEventDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<SchedulerEvent_Base *>(obj)!=NULL;
}

const char *SchedulerEventDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"customize")) return "true";
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int SchedulerEventDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int SchedulerEventDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *SchedulerEventDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int SchedulerEventDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *SchedulerEventDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *SchedulerEventDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int SchedulerEventDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    SchedulerEvent_Base *pp = (SchedulerEvent_Base *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string SchedulerEventDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    SchedulerEvent_Base *pp = (SchedulerEvent_Base *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool SchedulerEventDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    SchedulerEvent_Base *pp = (SchedulerEvent_Base *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *SchedulerEventDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *SchedulerEventDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    SchedulerEvent_Base *pp = (SchedulerEvent_Base *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

}; // end namespace TTEthernetModel


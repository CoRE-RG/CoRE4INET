//
// Generated file, do not edit! Created by opp_msgc 4.2 from linklayer/ethernet/CTFrame.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "CTFrame_m.h"

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

Register_Class(CTFrame);

CTFrame::CTFrame(const char *name, int kind) : EtherFrame(name,kind)
{
    this->ctID_var = 0;
    this->displayString_var = "b=15,15,rect,white,kind,5";
}

CTFrame::CTFrame(const CTFrame& other) : EtherFrame()
{
    setName(other.getName());
    operator=(other);
}

CTFrame::~CTFrame()
{
}

CTFrame& CTFrame::operator=(const CTFrame& other)
{
    if (this==&other) return *this;
    EtherFrame::operator=(other);
    this->ctID_var = other.ctID_var;
    this->displayString_var = other.displayString_var;
    return *this;
}

void CTFrame::parsimPack(cCommBuffer *b)
{
    EtherFrame::parsimPack(b);
    doPacking(b,this->ctID_var);
    doPacking(b,this->displayString_var);
}

void CTFrame::parsimUnpack(cCommBuffer *b)
{
    EtherFrame::parsimUnpack(b);
    doUnpacking(b,this->ctID_var);
    doUnpacking(b,this->displayString_var);
}

unsigned short CTFrame::getCtID() const
{
    return ctID_var;
}

void CTFrame::setCtID(unsigned short ctID_var)
{
    this->ctID_var = ctID_var;
}

const char * CTFrame::getDisplayString() const
{
    return displayString_var.c_str();
}

void CTFrame::setDisplayString(const char * displayString_var)
{
    this->displayString_var = displayString_var;
}

class CTFrameDescriptor : public cClassDescriptor
{
  public:
    CTFrameDescriptor();
    virtual ~CTFrameDescriptor();

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

Register_ClassDescriptor(CTFrameDescriptor);

CTFrameDescriptor::CTFrameDescriptor() : cClassDescriptor("TTEthernetModel::CTFrame", "EtherFrame")
{
}

CTFrameDescriptor::~CTFrameDescriptor()
{
}

bool CTFrameDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CTFrame *>(obj)!=NULL;
}

const char *CTFrameDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CTFrameDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int CTFrameDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *CTFrameDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "ctID",
        "displayString",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int CTFrameDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "ctID")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "displayString")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CTFrameDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",
        "string",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *CTFrameDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int CTFrameDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CTFrame *pp = (CTFrame *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CTFrameDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CTFrame *pp = (CTFrame *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getCtID());
        case 1: return oppstring2string(pp->getDisplayString());
        default: return "";
    }
}

bool CTFrameDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CTFrame *pp = (CTFrame *)object; (void)pp;
    switch (field) {
        case 0: pp->setCtID(string2ulong(value)); return true;
        case 1: pp->setDisplayString((value)); return true;
        default: return false;
    }
}

const char *CTFrameDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
    };
    return (field>=0 && field<2) ? fieldStructNames[field] : NULL;
}

void *CTFrameDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CTFrame *pp = (CTFrame *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

}; // end namespace TTEthernetModel


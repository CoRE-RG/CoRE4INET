#ifndef __CORE4INET_SCHEDULEREVENT_H_
#define __CORE4INET_SCHEDULEREVENT_H_

#include <SchedulerMessage_m.h>

namespace CoRE4INET {

/**
 * @brief Redefines SchedulerEvent_Base and adds destinationGate
 *
 * @author Till Steinbach
 */
class SchedulerEvent : public CoRE4INET::SchedulerEvent_Base
{
    private:
        cGate *destinationGate_var;
    public:
        SchedulerEvent(const char *name = NULL, int kind = 0) :
            SchedulerEvent_Base(name, kind)
        {
            destinationGate_var = NULL;
        }
        SchedulerEvent(const SchedulerEvent& other) :
            SchedulerEvent_Base(other.getName())
        {
            operator=(other);
        }
        SchedulerEvent& operator=(const SchedulerEvent& other)
        {
            SchedulerEvent_Base::operator=(other);
            return *this;
        }
        virtual SchedulerEvent *dup() const
        {
            return new SchedulerEvent(*this);
        }
        // ADD CODE HERE to redefine and implement pure virtual functions from SchedulerEvent_Base
        virtual cGate* getDestinationGate() const;
        virtual void setDestinationGate(cGate *destinationGate);
};
}

#endif

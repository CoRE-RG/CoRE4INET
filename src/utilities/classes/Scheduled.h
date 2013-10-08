#ifndef SCHEDULED_H_
#define SCHEDULED_H_

#include <Timed.h>
#include <Period.h>

namespace TTEthernetModel {

class Scheduled: public Timed
{
    protected:
        /**
         * TODO
         */
        Period *period;

    public:
        /**
         * @brief Initialization of the module
         */
        void initialize();
        /**
         * TODO
         */
        Period* getPeriod();
};

}
#endif /* SCHEDULED_H_ */

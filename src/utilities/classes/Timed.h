#ifndef TIMED_H_
#define TIMED_H_

#include <Oscillator.h>
#include <Timer.h>

namespace TTEthernetModel {

class Timed: public virtual cSimpleModule
{
    protected:
        /**
         * TODO
         */
        Oscillator *oscillator;
        /**
         * TODO
         */
        Timer *timer;

    public:
        /**
         * @brief Initialization of the module
         */
        void initialize();
        /**
         * TODO
         */
        Timer* getTimer();
};

}
#endif /* TIMED_H_ */

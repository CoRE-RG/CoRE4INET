//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//
#ifndef __CoRE4INET_FLOATINGRESULTRECORDERS_H
#define __CoRE4INET_FLOATINGRESULTRECORDERS_H

//OMNeT++
#include "cresultrecorder.h"

namespace CoRE4INET{

/**
 * @brief BaseClass for floating interval vector recorders
 *
 * Floating interval vectors use the values collected in an interval
 * together with a grouping function
 *
 * To configure the interval the following parameters are chosen in the given order:
 * - 1. Look for an "measure_interval" parameter in the \@statistics definition e.g.:
 * \@statistic[rxPk](title="RX Packets"; source=rxPk; record="floatingIntervalAvgVector(packetBytes)"; measure_interval=50ms);
 * - 2. Look for an "measure_interval" parameter in all modules from this module until the root (the network) e.g.:
 * parameters:
 *     double measure_interval \@unit(s) = default(1s);
 * - 3. default (1s) is chosen
 *
 * @ingroup ResultRecorders
 *
 * @author Till Steinbach
 */
class FloatingIntervalVectorRecorder: public cNumericResultRecorder
{
    protected:
        simtime_t interval;
        std::map<simtime_t, double> inInterval;
        void *handle;        // identifies output vector for the output vector manager
        simtime_t lastTime;  // to ensure increasing timestamp order
    protected:
        virtual void collect(simtime_t_cref t, double value);
        virtual double calculate() = 0;
    public:
        FloatingIntervalVectorRecorder();
        virtual void subscribedTo(cResultFilter *prev);
};

/**
 * @brief floating interval count vector recorder "floatingIntervalCountVector"
 *
 * On every incoming value the values over the past interval are counted and recorded
 *
 * To configure the interval the following parameters are chosen in the given order:
 * - 1. Look for an "measure_interval" parameter in the \@statistics definition e.g.:
 * \@statistic[rxPk](title="RX Packets"; source=rxPk; record="floatingIntervalAvgVector(packetBytes)"; measure_interval=50ms);
 * - 2. Look for an "measure_interval" parameter in all modules from this module until the root (the network) e.g.:
 * parameters:
 *     double measure_interval \@unit(s) = default(1s);
 * - 3. default (1s) is chosen
 *
 * @ingroup ResultRecorders
 *
 * @author Till Steinbach
 */
class FloatingIntervalCountVectorRecorder: public FloatingIntervalVectorRecorder
{
    protected:
        virtual double calculate();
};


class FloatingIntervalCapacityRecorder : public FloatingIntervalVectorRecorder
{
    protected:
        virtual double calculate();
};

/**
 * @brief floating interval sum vector recorder "floatingIntervalSumVector"
 *
 * On every incoming value the values over the past interval are summed and recorded
 *
 * To configure the interval the following parameters are chosen in the given order:
 * - 1. Look for an "measure_interval" parameter in the \@statistics definition e.g.:
 * \@statistic[rxPk](title="RX Packets"; source=rxPk; record="floatingIntervalAvgVector(packetBytes)"; measure_interval=50ms);
 * - 2. Look for an "measure_interval" parameter in all modules from this module until the root (the network) e.g.:
 * parameters:
 *     double measure_interval \@unit(s) = default(1s);
 * - 3. default (1s) is chosen
 *
 * @ingroup ResultRecorders
 *
 * @author Till Steinbach
 */
class FloatingIntervalSumVectorRecorder: public FloatingIntervalVectorRecorder
{
    protected:
        virtual double calculate();
};

class FloatingIntervalSumVectorRecorderPercent: public FloatingIntervalVectorRecorder
{
    protected:
        virtual double calculate();
};

/**
 * @brief floating interval avg vector recorder "floatingIntervalAvgVector"
 *
 * On every incoming value the values over the past interval are averaged and recorded
 *
 * To configure the interval the following parameters are chosen in the given order:
 * - 1. Look for an "measure_interval" parameter in the \@statistics definition e.g.:
 * \@statistic[rxPk](title="RX Packets"; source=rxPk; record="floatingIntervalAvgVector(packetBytes)"; measure_interval=50ms);
 * - 2. Look for an "measure_interval" parameter in all modules from this module until the root (the network) e.g.:
 * parameters:
 *     double measure_interval \@unit(s) = default(1s);
 * - 3. default (1s) is chosen
 *
 * @ingroup ResultRecorders
 *
 * @author Till Steinbach
 */
class FloatingIntervalAvgVectorRecorder: public FloatingIntervalVectorRecorder
{
    protected:
        virtual double calculate();
};

/**
 * @brief floating interval min vector recorder "floatingIntervalMinVector"
 *
 * On every incoming value the minimum of the past interval is recorded
 *
 * To configure the interval the following parameters are chosen in the given order:
 * - 1. Look for an "measure_interval" parameter in the \@statistics definition e.g.:
 * \@statistic[rxPk](title="RX Packets"; source=rxPk; record="floatingIntervalAvgVector(packetBytes)"; measure_interval=50ms);
 * - 2. Look for an "measure_interval" parameter in all modules from this module until the root (the network) e.g.:
 * parameters:
 *     double measure_interval \@unit(s) = default(1s);
 * - 3. default (1s) is chosen
 *
 * @ingroup ResultRecorders
 *
 * @author Till Steinbach
 */
class FloatingIntervalMinVectorRecorder: public FloatingIntervalVectorRecorder
{
    protected:
        virtual double calculate();
};

/**
 * @brief floating interval max vector recorder "floatingIntervalMaxVector"
 *
 * On every incoming value the maximum of the past interval is recorded
 *
 * To configure the interval the following parameters are chosen in the given order:
 * - 1. Look for an "measure_interval" parameter in the \@statistics definition e.g.:
 * \@statistic[rxPk](title="RX Packets"; source=rxPk; record="floatingIntervalAvgVector(packetBytes)"; measure_interval=50ms);
 * - 2. Look for an "measure_interval" parameter in all modules from this module until the root (the network) e.g.:
 * parameters:
 *     double measure_interval \@unit(s) = default(1s);
 * - 3. default (1s) is chosen
 *
 * @ingroup ResultRecorders
 *
 * @author Till Steinbach
 */
class FloatingIntervalMaxVectorRecorder: public FloatingIntervalVectorRecorder
{
    protected:
        virtual double calculate();
};

/**
 * @brief floating interval variance vector recorder "floatingIntervalVarianceVector"
 *
 * On every incoming value the variance (maximum-minimum) of the past interval is recorded
 *
 * To configure the interval the following parameters are chosen in the given order:
 * - 1. Look for an "measure_interval" parameter in the \@statistics definition e.g.:
 * \@statistic[rxPk](title="RX Packets"; source=rxPk; record="floatingIntervalAvgVector(packetBytes)"; measure_interval=50ms);
 * - 2. Look for an "measure_interval" parameter in all modules from this module until the root (the network) e.g.:
 * parameters:
 *     double measure_interval \@unit(s) = default(1s);
 * - 3. default (1s) is chosen
 *
 * @ingroup ResultRecorders
 *
 * @author Till Steinbach
 */
class FloatingIntervalVarianceVectorRecorder: public FloatingIntervalVectorRecorder
{
    protected:
        virtual double calculate();
};

class FloatingIntervalAvailableBandwidthPercent : public FloatingIntervalVectorRecorder
      {
          protected:
              virtual double calculate();
      };

}

#endif

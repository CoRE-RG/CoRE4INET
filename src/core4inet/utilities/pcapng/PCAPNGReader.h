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

#ifndef CORE4INET_UTILITIES_PCAPNG_PCAPNGREADER_H_
#define CORE4INET_UTILITIES_PCAPNG_PCAPNGREADER_H_

#include "core4inet/utilities/pcapng/pcapng.h"

namespace CoRE4INET {

/**
 * @brief Todo
 *
 *
 * @ingroup Utilities
 *
 * @author Sandra Reider
 */
class PCAPNGReader {
private:
    FILE *file;
    const char *filename;

    void readNextBlock();
    void readSectionHeaderBlock();
    void readInterfaceDescriptionBlock();
    void readPacketBlock();

public:
    PCAPNGReader();
    virtual ~PCAPNGReader();
    void initialize();
};

} /* namespace CoRE4INET */

#endif /* CORE4INET_UTILITIES_PCAPNG_PCAPNGREADER_H_ */

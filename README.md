# CoRE4INET

CoRE4INET is an open source extension to the [INET-Framework](https://inet.omnetpp.org/) for the event-based simulation of real-time Ethernet in the [OMNEST/OMNeT++](https://omnetpp.org/) simulation system. It provides real-time Ethernet protocols like AS6802 and AVB. It was created by the [CoRE (Communication over Realtime Ethernet)](https://core-researchgroup.de/) research group at the [HAW-Hamburg (Hamburg University of Applied Sciences)](https://www.haw-hamburg.de/english.html).

<img src="/doc/images/core4inet.png" alt="CoRE4INET Environment" width="35%">


## History
CoRE4INET was first introduced as TTE4INET at the 4th International Workshop on OMNeT++ (2011) along with the 4th International ICST Conference on Simulation Tools and Techniques (2011). You can find the [publication](https://core.inet.haw-hamburg.de/assets/bibliography/eigene/sdkks-eifre-11.pdf) and [slides](https://core.inet.haw-hamburg.de/assets/bibliography/eigene/sdkks-eifre-11_Slides.pdf) here.

Since there were changes necessary to support OMNeT++ 4.2 and INET 2.0, it was completely redesigned. When more real-time Ethernet protocols were added the project was renamed from TTE4INET to CoRE4INET to show that it does not only contain time-triggered protocols.


## News
* Updated dependencies to OMNeT++ 6.0.2 and INET 3.8.3


## Features
* Best Efford Crosstraffic
* IEEE 802.1Q / IEEE P802.1p VLANs and Priorities
* Time-Sensitive Networking (TSN)
* IEEE 802.1 Audio/Video Bridging (AVB)
* TTEthernet (AS6802)
* IP over Realtime-Ethernet


## Reference
If you would like to reference this project please use the following [publication](https://link.springer.com/chapter/10.1007/978-3-030-12842-5_10):

Philipp Meyer, Franz Korf, Till Steinbach, Thomas C. Schmidt, Simulation of Mixed Critical In-vehicular Networks, In: Recent Advances in Network Simulation, (Antonio Virdis, Michael Kirsche Ed.), ser. EAI/Springer Innovations in Communication and Computing, May 2019. [https://doi.org/10.1007/978-3-030-12842-5_10](https://doi.org/10.1007/978-3-030-12842-5_10) 

* [arXiv preprint](https://arxiv.org/abs/1808.03081)


## Quick Start
1. Download OMNeT++ 6.0.2
    * [https://omnetpp.org/download/](https://omnetpp.org/download/)
2. Install OMNeT++
    * [https://doc.omnetpp.org/omnetpp/InstallGuide.pdf](https://doc.omnetpp.org/omnetpp/InstallGuide.pdf)
3. Get INET framework 3.8.3
    * [https://inet.omnetpp.org/Download.html](https://inet.omnetpp.org/Download.html)
    * Disable the feature 'visualization' and all dependent features (causes build issues)
4. Get CoRE framework
    * GitHub: Clone this repository and import it in OMNEST/OMNeT++
5. Working with the framework
    * See the documentation in [doc/](/doc)
    * Start the examples in the framework


## Status
The project has been tested on Ubuntu 22.04 (+WSL) and Windows 11. 


## Further Information
* [CoRE simulation models overview](https://core-researchgroup.de/projects/simulation.html)
* [Abstract Network Description Language (ANDL) overview](https://core-researchgroup.de/projects/simulation/abstract-network-description-language.html)

### Installation
Please see [INSTALL](/INSTALL)

### Documentation
Please see [doc/](/doc)

### Changelog
Please see [WHATSNEW](/WHATSNEW)

## IMPORTANT
The CoRE4INET model is under continuous development: new parts are added, bugs are corrected, and so on. We cannot assert that the implementation will work fully according to the specifications. YOU ARE RESPONSIBLE YOURSELF TO MAKE SURE THAT THE MODELS YOU USE IN YOUR SIMULATIONS WORK CORRECTLY, AND YOU'RE GETTING VALID RESULTS. 

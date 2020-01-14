# CoRE4INET

CoRE4INET is an open source extension to the [INET-Framework](https://inet.omnetpp.org/) for the event-based simulation of real-time Ethernet in the [OMNEST/OMNeT++](https://omnetpp.org/) simulation system. It provides real-time Ethernet protocols like AS6802 and AVB. It was created by the [CoRE (Communication over Realtime Ethernet)](https://core-researchgroup.de/) research group at the [HAW-Hamburg (Hamburg University of Applied Sciences)](https://www.haw-hamburg.de/english.html).

<img src="/doc/images/core4inet.png" alt="CoRE4INET Environment" width="35%">


## News
* Updated to support OMNeT++ 5.5.1 and INET 3.6.6 
* Added IEEE 802.1Qci filtering and TSN nodes.
* Added IEEE 802.1Qbv shaping. (Including scheduled gate control list and credit based shaper)


## Features
* Best Efford Crosstraffic
* IEEE 802.1Q / IEEE P802.1p VLANs and Priorities
* Time-Sensitive Networking (TSN)
* IEEE 802.1 Audio/Video Bridging (AVB)
* TTEthernet (AS6802)
* IP over Realtime-Ethernet


## History
CoRE4INET was first introduced as TTE4INET at the [4th International Workshop on OMNeT++ (2011)](http://www.omnet-workshop.org/2011/) along with the [4th International ICST Conference on Simulation Tools and Techniques (2011)](http://www.simutools.org/2011/). You can find the [publication](http://core.informatik.haw-hamburg.de/images/publications/papers/sdkks-eifre-11a.pdf) and [slides](http://core.informatik.haw-hamburg.de/images/publications/papers/sdkks-eifre-11b.pdf) here.

Since there were changes necessary to support OMNeT++ 4.2 and INET 2.0, it was completely redesigned. When more real-time Ethernet protocols were added the project was renamed from TTE4INET to CoRE4INET to show that it does not only contain time-triggered protocols.


## References
If you would like to reference this project please use the following [publication](http://core.informatik.haw-hamburg.de/images/publications/papers/sdkks-eifre-11a.pdf):

T. Steinbach, H. Dieumo Kenfack, F. Korf, and T. C. Schmidt. An Extension of the OMNeT++ INET Framework for Simulating Real-time Ethernet with High Accuracy. In Proceedings of the 4th International ICST Conference on Simulation Tools and Techniques, SIMUTools '11, pages 375-382, ICST, Brussels, Belgium, Belgium, 2011. ICST (Institute for Computer Sciences, Social-Informatics and Telecommunications Engineering).


## Quick Start
1. Download OMNeT++ 5.5.1
    * [https://omnetpp.org/download/](https://omnetpp.org/download/)
2. Install OMNeT++
    * [https://doc.omnetpp.org/omnetpp/InstallGuide.pdf](https://doc.omnetpp.org/omnetpp/InstallGuide.pdf)
3. Get INET framework 3.6.6
    * [https://inet.omnetpp.org/Download.html](https://inet.omnetpp.org/Download.html)
4. Install CoRE plugins (optional)
    * OMNEST/OMNeT++ -> Help -> Install New Software...
    * URL `http://sim.core-rg.de/updates/`
    * Check [[Abstract Network Description Language](https://core-researchgroup.de/projects/simulation/abstract-network-description-language.html)] | [CoRE Simulation Model Installer] | [Gantt Chart Timing Analyzer]
5. Get CoRE framework (GitHub or CoRE Simulation Model Installer)
    * GitHub: Clone framework and import it in OMNEST/OMNeT++
    * CoRE Simulation Model Installer: OMNEST/OMNeT++ -> Help -> Install CoRE Simulation Models...
6. Working with the framework
    * See the documentation in [doc/](/doc)
    * Start the examples in the framework


## Continuous Integration

The build state of the master branch is monitored:
* Building:
<a><img src="https://jenkins.core-rg.de/buildStatus/icon?job=CoRE4INET/CoRE4INET"></a>
* Tests:
<a><img src="https://jenkins.core-rg.de/buildStatus/icon?job=CoRE4INET/CoRE4INET_tests"></a>

<table>
  <tr>
    <th></th>
    <th>Ubuntu 18.04</th>
    <th>Windows 10</th>
  </tr>
  <tr>
    <td>Building</td>
    <td><img src="https://jenkins.core-rg.de/buildStatus/icon?job=CoRE4INET/CoRE4INET/Nodes=Ubuntu_18.04"></td>
    <td><img src="https://jenkins.core-rg.de/buildStatus/icon?job=CoRE4INET/CoRE4INET/Nodes=Windows_10"></td>
  </tr>
  <tr>
    <td>Tests</td>
    <td><img src="https://jenkins.core-rg.de/buildStatus/icon?job=CoRE4INET/CoRE4INET_tests/Nodes=Ubuntu_18.04"></td>
    <td><img src="https://jenkins.core-rg.de/buildStatus/icon?job=CoRE4INET/CoRE4INET_tests/Nodes=Windows_10"></td>
  </tr>
</table>


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

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

//
// @titlepage
//
//<center><img src="../images/CoRE.png"/><img src="../images/HAW.gif"/></center>
//
// <center><h1>Communication over Realtime Ethernet for INET Framework (CoRE4INET)</h1></center>
// <center>release [VERSION_STRING]</center>
//
// CoRE4INET is an extension to the INET-Framework for the event-based simulation
// of real-time Ethernet variants such as AS6802 (time-triggered Ethernet (<a href="http://www.ttethernet.com" target="_top">TTEthernet</a>)) or Ethernet AVB
// in the OMNEST/OMNeT++ simulation system.
// It was created by the <a href="http://www.informatik.haw-hamburg.de/core.html" target="_top">CoRE (Communication over Realtime Ethernet)</a> research group
// at the <a href="http://www.informatik.haw-hamburg.de/core.html" target="_top">HAW-Hamburg (Hamburg University of Applied Sciences) </a>.
//
// There are several bugfixes and improvements; see the <tt><a href="../doxy/whatsnew.html">WHATSNEW</a></tt> file.
//
// <h2>Requirements</h2>
// - <a href="http://omnetpp.org/" target="_top">OMNeT++</a> (minimum version 4.4.1)
// - <a href="http://inet.omnetpp.org/" target="_top">INET-Framework</a>  (minimum version 2.3.0)
//
// <h2>Introductory material</h2>
//  - For help with the installation see the <tt><a href="../doxy/install.html">INSTALL</a></tt> page.
//
// A few useful starting points for browsing the documentation:
//  - 
//
// <h2>Related documentation</h2>
//   - <a href="../doxy/index.html" target="_top">C++ source documentation (Doxygen)</a>
//   - <a href="http://inet.omnetpp.org/doc/INET/neddoc/index.html" target="_top">INET Model Documentation</a>
//   - <a href="http://inet.omnetpp.org/doc/INET/doxy/index.html" target="_top">INET C++ source documentation (Doxygen)</a>
//
// <h2>References</h2>
// If you would like to reference this project please use the following <a href="http://core.informatik.haw-hamburg.de/images/publications/papers/sdkks-eifre-11a.pdf">publication</a>:
// <ul><li>Steinbach, H. Dieumo Kenfack, F. Korf, and T. C. Schmidt. An Extension of the OMNeT++ INET Framework for Simulating Real-time Ethernet with High Accuracy. In Proceedings of the 4th International ICST Conference on Simulation Tools and Techniques, SIMUTools '11, pages 375-382, ICST, Brussels, Belgium, Belgium, 2011. ICST (Institute for Computer Sciences, Social-Informatics and Telecommunications Engineering). (<a href="http://inet.cpt.haw-hamburg.de/publications/sdks-eoifs-11.bib">bibtex</a>)
// </li></ul>
//
// <h2>History</h2>
// CoRE4INET was first introduced at the <a href="http://www.omnet-workshop.org/2011/" target="_top">4th International Workshop on OMNeT++ (2011)</a>
// along with the <a href="http://www.simutools.org/2011/" target="_top">4th International ICST Conference on Simulation Tools and Techniques (2011)</a>.
// You can find the presentation slides <a href="http://papers.till-steinbach.de/sdkks-eifre-11b.pdf" target="_top">here</a>
//
// Since there were changes necessary to support OMNeT++ 4.2 and INET 2.0, CoRE4INET was completely redesigned in the current version. At that time it was called
// TTE4INET as it ony contained TTEthernet Models. Later it was renamed CORE4INET (Communication over Realtime Ethernet for INET Framework) to better show that the
// model offers implementations vor various real-time Ethernet variants.
//
// <h2>IMPORTANT</h2>
// The CoRE4INET model is continuously being improved: new parts
// are added, bugs are corrected, and so on. We cannot assert that the implementation
// will work fully according to the specifications. YOU ARE RESPONSIBLE YOURSELF
// TO MAKE SURE THAT THE MODELS YOU USE IN YOUR SIMULATIONS WORK CORRECTLY, AND YOU'RE
// GETTING VALID RESULTS.
//
// <h2>Contributions</h2>
// Contributions are highly welcome. Please contact us if you would like to participate!
//
// <h3>Contributors</h3>
// - Till Steinbach (HAW-Hamburg)
// - Hermand Dieumo Kenfack (HAW-Hamburg)
// - Fabian Kempf (HAW-Hamburg)
// - Lazar Todorov (HAW Hamburg)
// - Philipp Meyer (HAW Hamburg)
//
// <h3>Acknowledgements</h3>
// - Giancarlo Vasta for finding and reporting bugs 
//
// <h2>Contact</h2>
// CoRE Research Group
// <a href="mailto:core@informatik.haw-hamburg.de">core@informatik.haw-hamburg.de</a>
//
//
//
//
//
//
// <a href="http://www.ttethernet.com" target="_top">TTEthernet</a> is a registred trademark of  <a href="http://www.tttech.com" target="_top">TTTech Computertechnik AG (Vienna)</a>

package core4inet;

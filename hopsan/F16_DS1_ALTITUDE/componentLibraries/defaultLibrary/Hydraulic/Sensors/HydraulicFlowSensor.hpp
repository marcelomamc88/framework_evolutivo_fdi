/*-----------------------------------------------------------------------------

 Copyright 2017 Hopsan Group

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.


 The full license is available in the file LICENSE.
 For details about the 'Hopsan Group' or information about Authors and
 Contributors see the HOPSANGROUP and AUTHORS files that are located in
 the Hopsan source code root directory.

-----------------------------------------------------------------------------*/

//!
//! @file   HydraulicFlowSensor.hpp
//! @author Björn Eriksson <bjorn.eriksson@liu.se>
//! @date   2010-01-16
//!
//! @brief Contains a Hydraulic Flow Sensor Component
//!
//$Id$

#ifndef HYDRAULICFLOWSENSOR_HPP_INCLUDED
#define HYDRAULICFLOWSENSOR_HPP_INCLUDED

#include "ComponentEssentials.h"

namespace hopsan {

    //!
    //! @brief
    //! @ingroup HydraulicComponents
    //!
    class HydraulicFlowSensor : public ComponentSignal
    {
    private:
        double *mpND_q, *mpOut;

        Port *mpP1;

    public:
        static Component *Creator()
        {
            return new HydraulicFlowSensor();
        }

        void configure()
        {

            mpP1 = addReadPort("P1", "NodeHydraulic", "", Port::NotRequired);
            addOutputVariable("out", "Flow", "Flow", &mpOut);
        }


        void initialize()
        {
            mpND_q = getSafeNodeDataPtr(mpP1, NodeHydraulic::Flow);
            simulateOneTimestep(); //Set initial output node value
        }


        void simulateOneTimestep()
        {
            (*mpOut) = (*mpND_q);
        }
    };
}

#endif // HYDRAULICFLOWSENSOR_HPP_INCLUDED

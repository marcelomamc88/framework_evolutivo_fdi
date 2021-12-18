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
//! @file   SignalDivide.hpp
//! @author Robert Braun <robert.braun@liu.se>
//! @date   2010-01-11
//!
//! @brief Contains a mathematical division function
//!
//$Id$

#ifndef SIGNALDIVIDE_HPP_INCLUDED
#define SIGNALDIVIDE_HPP_INCLUDED

#include "ComponentEssentials.h"

namespace hopsan {

    //!
    //! @brief
    //! @ingroup SignalComponents
    //!
    class SignalDivide : public ComponentSignal
    {

    private:
        double *mpND_in1, *mpND_in2, *mpND_out;

    public:
        static Component *Creator()
        {
            return new SignalDivide();
        }

        void configure()
        {
            addInputVariable("in1", "", "", 0, &mpND_in1);
            addInputVariable("in2", "", "", 0, &mpND_in2);
            addOutputVariable("out", "in1/in2", "", &mpND_out);
        }


        void initialize()
        {
            // We do a weaker check for division be zero at first time step, to avoid initial value troubles.
            // Simulation is allowed to continue and output value is set to zero.
            // User gets a warning message.
            if(*mpND_in2 == 0)
            {
                addWarningMessage("Division by zero at first time step. Output value set to zero.");
                (*mpND_out) = 0;
            }
            else
            {
                (*mpND_out) = (*mpND_in1) / (*mpND_in2);
            }
        }

        void simulateOneTimestep()
        {
            // Stop simulation if division by zero.
            if(*mpND_in2 == 0)
            {
                addErrorMessage("Division by zero.");
                stopSimulation();
            }
            (*mpND_out) = (*mpND_in1) / (*mpND_in2);
        }
    };
}

#endif // SIGNALDIVIDE_HPP_INCLUDED

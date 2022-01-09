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
//! @file   SignalXor.hpp
//! @author Robert Braun <robert.braun@liu.se>
//! @date   2010-10-19
//!
//! @brief Contains a logical and operator
//!
//$Id$

#ifndef SIGNALXOR_HPP_INCLUDED
#define SIGNALXOR_HPP_INCLUDED

#include "ComponentEssentials.h"
#include "ComponentUtilities.h"

namespace hopsan {

    //!
    //! @brief
    //! @ingroup SignalComponents
    //!
    class SignalXor : public ComponentSignal
    {

    private:
        double *mpND_in1, *mpND_in2, *mpND_out;
        bool inputBool1, inputBool2;

    public:
        static Component *Creator()
        {
            return new SignalXor();
        }

        void configure()
        {
            addInputVariable("in1", "", "", 0.0, &mpND_in1);
            addInputVariable("in2", "", "", 0.0, &mpND_in2);
            addOutputVariable("out", "", "", &mpND_out);
        }


        void initialize()
        {
            simulateOneTimestep();
        }


        void simulateOneTimestep()
        {
            //Xor operator equation
            inputBool1 = doubleToBool(*mpND_in1);
            inputBool2 = doubleToBool(*mpND_in2);
            (*mpND_out) = boolToDouble( (inputBool1 || inputBool2) && !(inputBool1 && inputBool2) );
        }
    };
}
#endif // SIGNALXOR_HPP_INCLUDED

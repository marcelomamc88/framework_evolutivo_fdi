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
//! @file   SignalAbsoluteValue.hpp
//! @author Björn Eriksson <robert.braun@liu.se>
//! @date   2011-02-03
//!
//! @brief Contains a Signal Absolute Value Component
//!
//$Id$

#ifndef SIGNALABSOLUTEVALUE_HPP_INCLUDED
#define SIGNALABSOLUTEVALUE_HPP_INCLUDED

#include "ComponentEssentials.h"

namespace hopsan {

    //!
    //! @brief
    //! @ingroup SignalComponents
    //!
    class SignalAbsoluteValue : public ComponentSignal
    {

    private:
        double *mpIn, *mpOut;

    public:
        static Component *Creator()
        {
            return new SignalAbsoluteValue();
        }

        void configure()
        {
            addInputVariable("in", "", "", 0.0, &mpIn);
            addOutputVariable("out", "ABS of in", "", &mpOut);
        }


        void initialize()
        {
            simulateOneTimestep();
        }

        void simulateOneTimestep()
        {
            if(*mpIn > 0)
            {
                (*mpOut) = (*mpIn);
            }
            else
            {
                (*mpOut) = -(*mpIn);
            }
        }
    };
}

#endif // SIGNALABSOLUTEVALUE_HPP_INCLUDED

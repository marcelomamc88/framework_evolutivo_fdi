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
//! @file   SignalSink.hpp
//! @author Björn Eriksson <bjorn.eriksson@liu.se>
//! @date   2010-01-05
//!
//! @brief Contains a Signal Sink Component
//!
//$Id$

#ifndef SIGNALSINK_HPP_INCLUDED
#define SIGNALSINK_HPP_INCLUDED

#include "ComponentEssentials.h"

namespace hopsan {

    //!
    //! @brief
    //! @ingroup SignalComponents
    //!
    class SignalSink : public ComponentSignal
    {

    private:

    public:
        static Component *Creator()
        {
            return new SignalSink();
        }

        void configure()
        {
            addReadMultiPort("in", "NodeSignal", "", Port::NotRequired);
            addReadMultiPort("in_right", "NodeSignal", "", Port::NotRequired);
            addReadPort("in_bottom", "NodeSignal", "", Port::NotRequired);
        }


        void initialize()
        {
            //Nothing to initilize
        }


        void simulateOneTimestep()
        {
            //Nothing to do
        }

        void finalize()
        {
            //Nothing to do
        }
    };
}

#endif // SIGNALSINK_HPP_INCLUDED

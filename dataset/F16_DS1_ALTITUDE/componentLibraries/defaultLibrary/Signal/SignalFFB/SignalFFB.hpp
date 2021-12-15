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

#ifndef SIGNALFFB_HPP_INCLUDED
#define SIGNALFFB_HPP_INCLUDED

#include <iostream>
#include "ComponentEssentials.h"
#include "ComponentUtilities.h"
#include "math.h"

//!
//! @file SignalFFB.hpp
//! @author Petter Krus <petter.krus@liu.se>
//! @date Fri 28 Jun 2013 13:01:39
//! @brief Functional Flow Block
//! @ingroup SignalComponents
//!
//==This code has been autogenerated using Compgen==
//from 
/*{, C:, HopsanTrunk, HOPSAN++, CompgenModels}/SignalFFBDcomponents.nb*/

using namespace hopsan;

class SignalFFB : public ComponentSignal
{
private:
     int mNstep;
//==This code has been autogenerated using Compgen==
     //inputVariables
     double set;
     double exit;
     double exitb;
     double leave;
     //outputVariables
     double state;
     double exiting;
     double exitingb;
     //InitialExpressions variables
     double oldState;
     double oldExiting;
     double oldExit;
     double oldLeave;
     //Expressions variables
     double oldSet;
     //Delay declarations
//==This code has been autogenerated using Compgen==
     //inputVariables pointers
     double *mpset;
     double *mpexit;
     double *mpexitb;
     double *mpleave;
     //inputParameters pointers
     //outputVariables pointers
     double *mpstate;
     double *mpexiting;
     double *mpexitingb;
     EquationSystemSolver *mpSolver;

public:
     static Component *Creator()
     {
        return new SignalFFB();
     }

     void configure()
     {
//==This code has been autogenerated using Compgen==

        mNstep=9;

        //Add ports to the component
        //Add inputVariables to the component
            addInputVariable("set","On trigger","",0.,&mpset);
            addInputVariable("exit","Off trigger, jump to 0 ,signal to next \
block","",0.,&mpexit);
            addInputVariable("exitb","Off trigger, jump to 0 ,signal to next \
block","",0.,&mpexitb);
            addInputVariable("leave","Off trigger, jump to \
0","",0.,&mpleave);

        //Add inputParammeters to the component
        //Add outputVariables to the component
            addOutputVariable("state","State activated","",0.,&mpstate);
            addOutputVariable("exiting","jumping to alt 0","",0.,&mpexiting);
            addOutputVariable("exitingb","jumping to alt 0","",0.,&mpexitingb);

//==This code has been autogenerated using Compgen==
        //Add constantParameters
     }

    void initialize()
     {
        //Read port variable pointers from nodes

        //Read variables from nodes

        //Read inputVariables from nodes
        set = (*mpset);
        exit = (*mpexit);
        exitb = (*mpexitb);
        leave = (*mpleave);

        //Read inputParameters from nodes

        //Read outputVariables from nodes
        state = (*mpstate);
        exiting = (*mpexiting);
        exitingb = (*mpexitingb);

//==This code has been autogenerated using Compgen==
        //InitialExpressions
        oldState = state;
        oldSet = set;
        oldExiting = exiting;
        oldExit = exit;
        oldLeave = leave;


        //Initialize delays

     }
    void simulateOneTimestep()
     {
        //Read variables from nodes

        //Read inputVariables from nodes
        set = (*mpset);
        exit = (*mpexit);
        exitb = (*mpexitb);
        leave = (*mpleave);

        //LocalExpressions

          //Expressions
          state = onPositive(-0.5 - onPositive(-0.5 + exit + exitb - oldExit) \
- onPositive(-0.5 + leave - oldLeave) + onPositive(-0.5 + oldState) + \
2*onPositive(-0.5 - oldSet + set));
          exiting = oldState*onPositive(-0.5 + exit - oldExit);
          exitingb = exiting;
          oldState = state;
          oldSet = set;
          oldExiting = exiting;
          oldExit = exit;
          oldLeave = leave;

        //Calculate the delayed parts


        //Write new values to nodes
        //outputVariables
        (*mpstate)=state;
        (*mpexiting)=exiting;
        (*mpexitingb)=exitingb;

        //Update the delayed variabels

     }
    void deconfigure()
    {
        delete mpSolver;
    }
};
#endif // SIGNALFFB_HPP_INCLUDED
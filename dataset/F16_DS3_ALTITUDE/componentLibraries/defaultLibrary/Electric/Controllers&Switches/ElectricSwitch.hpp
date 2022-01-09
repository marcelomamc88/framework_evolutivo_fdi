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

#ifndef ELECTRICSWITCH_HPP_INCLUDED
#define ELECTRICSWITCH_HPP_INCLUDED

#include <iostream>
#include "ComponentEssentials.h"
#include "ComponentUtilities.h"
#include "math.h"

//!
//! @file ElectricSwitch.hpp
//! @author Petter Krus <petter.krus@liu.se>
//! @date Mon 7 Apr 2014 13:06:52
//! @brief Electric on/off switch
//! @ingroup ElectricComponents
//!
//==This code has been autogenerated using Compgen==
//from 
/*{, C:, HopsanTrunk, ComponentLibraries, defaultLibrary, \
Electric}/ElectricSwitch.nb*/

using namespace hopsan;

class ElectricSwitch : public ComponentQ
{
private:
     Port *mpPel1;
     Port *mpPel2;
     int mNstep;
     //Port Pel1 variable
     double uel1;
     double iel1;
     double cel1;
     double Zcel1;
     //Port Pel2 variable
     double uel2;
     double iel2;
     double cel2;
     double Zcel2;
//==This code has been autogenerated using Compgen==
     //inputVariables
     double state;
     //outputVariables
     //Expressions variables
     //Port Pel1 pointer
     double *mpND_uel1;
     double *mpND_iel1;
     double *mpND_cel1;
     double *mpND_Zcel1;
     //Port Pel2 pointer
     double *mpND_uel2;
     double *mpND_iel2;
     double *mpND_cel2;
     double *mpND_Zcel2;
     //Delay declarations
//==This code has been autogenerated using Compgen==
     //inputVariables pointers
     double *mpstate;
     //inputParameters pointers
     //outputVariables pointers
     EquationSystemSolver *mpSolver;

public:
     static Component *Creator()
     {
        return new ElectricSwitch();
     }

     void configure()
     {
//==This code has been autogenerated using Compgen==

        mNstep=9;

        //Add ports to the component
        mpPel1=addPowerPort("Pel1","NodeElectric");
        mpPel2=addPowerPort("Pel2","NodeElectric");
        //Add inputVariables to the component
            addInputVariable("state","State=1 means conducting"," \
",0.1,&mpstate);

        //Add inputParammeters to the component
        //Add outputVariables to the component

//==This code has been autogenerated using Compgen==
        //Add constantParameters
     }

    void initialize()
     {
        //Read port variable pointers from nodes
        //Port Pel1
        mpND_uel1=getSafeNodeDataPtr(mpPel1, NodeElectric::Voltage);
        mpND_iel1=getSafeNodeDataPtr(mpPel1, NodeElectric::Current);
        mpND_cel1=getSafeNodeDataPtr(mpPel1, NodeElectric::WaveVariable);
        mpND_Zcel1=getSafeNodeDataPtr(mpPel1, NodeElectric::CharImpedance);
        //Port Pel2
        mpND_uel2=getSafeNodeDataPtr(mpPel2, NodeElectric::Voltage);
        mpND_iel2=getSafeNodeDataPtr(mpPel2, NodeElectric::Current);
        mpND_cel2=getSafeNodeDataPtr(mpPel2, NodeElectric::WaveVariable);
        mpND_Zcel2=getSafeNodeDataPtr(mpPel2, NodeElectric::CharImpedance);

        //Read variables from nodes
        //Port Pel1
        uel1 = (*mpND_uel1);
        iel1 = (*mpND_iel1);
        cel1 = (*mpND_cel1);
        Zcel1 = (*mpND_Zcel1);
        //Port Pel2
        uel2 = (*mpND_uel2);
        iel2 = (*mpND_iel2);
        cel2 = (*mpND_cel2);
        Zcel2 = (*mpND_Zcel2);

        //Read inputVariables from nodes
        state = (*mpstate);

        //Read inputParameters from nodes

        //Read outputVariables from nodes

//==This code has been autogenerated using Compgen==


        //Initialize delays

     }
    void simulateOneTimestep()
     {
        //Read variables from nodes
        //Port Pel1
        cel1 = (*mpND_cel1);
        Zcel1 = (*mpND_Zcel1);
        //Port Pel2
        cel2 = (*mpND_cel2);
        Zcel2 = (*mpND_Zcel2);

        //Read inputVariables from nodes
        state = (*mpstate);

        //LocalExpressions

          //Expressions
          iel2 = ((cel1 - cel2)*onPositive(-0.5 + state))/(Zcel1 + Zcel2);
          uel1 = cel1 - iel2*Zcel1;
          uel2 = cel2 + iel2*Zcel2;
          iel1 = -iel2;

        //Calculate the delayed parts


        //Write new values to nodes
        //Port Pel1
        (*mpND_uel1)=uel1;
        (*mpND_iel1)=iel1;
        //Port Pel2
        (*mpND_uel2)=uel2;
        (*mpND_iel2)=iel2;
        //outputVariables

        //Update the delayed variabels

     }
    void deconfigure()
    {
        delete mpSolver;
    }
};
#endif // ELECTRICSWITCH_HPP_INCLUDED

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

#ifndef MECHANICGEARCLUTCH_HPP_INCLUDED
#define MECHANICGEARCLUTCH_HPP_INCLUDED

#include <iostream>
#include "ComponentEssentials.h"
#include "ComponentUtilities.h"
#include "math.h"

//!
//! @file MechanicGearClutch.hpp
//! @author Petter Krus <petter.krus@liu.se>
//! @date Fri 25 Apr 2014 14:00:41
//! @brief This is a combined clutch and gear
//! @ingroup MechanicComponents
//!
//==This code has been autogenerated using Compgen==
//from 
/*{, C:, HopsanTrunk, ComponentLibraries, defaultLibrary, Mechanic, \
Rotational}/MechanicGearClutch.nb*/

using namespace hopsan;

class MechanicGearClutch : public ComponentQ
{
private:
     double Jg;
     double Bg;
     double myfric;
     double wc;
     Port *mpPmr1;
     Port *mpPmr2;
     double delayParts1[9];
     double delayParts2[9];
     double delayParts3[9];
     double delayParts4[9];
     double delayParts5[9];
     double delayParts6[9];
     Matrix jacobianMatrix;
     Vec systemEquations;
     Matrix delayedPart;
     int i;
     int iter;
     int mNoiter;
     double jsyseqnweight[4];
     int order[6];
     int mNstep;
     //Port Pmr1 variable
     double tormr1;
     double thetamr1;
     double wmr1;
     double cmr1;
     double Zcmr1;
     double eqInertiamr1;
     //Port Pmr2 variable
     double tormr2;
     double thetamr2;
     double wmr2;
     double cmr2;
     double Zcmr2;
     double eqInertiamr2;
//==This code has been autogenerated using Compgen==
     //inputVariables
     double gearRatio;
     double tmax;
     //outputVariables
     //Expressions variables
     //Port Pmr1 pointer
     double *mpND_tormr1;
     double *mpND_thetamr1;
     double *mpND_wmr1;
     double *mpND_cmr1;
     double *mpND_Zcmr1;
     double *mpND_eqInertiamr1;
     //Port Pmr2 pointer
     double *mpND_tormr2;
     double *mpND_thetamr2;
     double *mpND_wmr2;
     double *mpND_cmr2;
     double *mpND_Zcmr2;
     double *mpND_eqInertiamr2;
     //Delay declarations
//==This code has been autogenerated using Compgen==
     //inputVariables pointers
     double *mpgearRatio;
     double *mptmax;
     //inputParameters pointers
     double *mpJg;
     double *mpBg;
     double *mpmyfric;
     double *mpwc;
     //outputVariables pointers
     Delay mDelayedPart10;
     Delay mDelayedPart11;
     Delay mDelayedPart20;
     Delay mDelayedPart21;
     Delay mDelayedPart30;
     Delay mDelayedPart31;
     EquationSystemSolver *mpSolver;

public:
     static Component *Creator()
     {
        return new MechanicGearClutch();
     }

     void configure()
     {
//==This code has been autogenerated using Compgen==

        mNstep=9;
        jacobianMatrix.create(6,6);
        systemEquations.create(6);
        delayedPart.create(7,6);
        mNoiter=2;
        jsyseqnweight[0]=1;
        jsyseqnweight[1]=0.67;
        jsyseqnweight[2]=0.5;
        jsyseqnweight[3]=0.5;


        //Add ports to the component
        mpPmr1=addPowerPort("Pmr1","NodeMechanicRotational");
        mpPmr2=addPowerPort("Pmr2","NodeMechanicRotational");
        //Add inputVariables to the component
            addInputVariable("gearRatio","gearing \
wmr1/wmr2","",1.,&mpgearRatio);
            addInputVariable("tmax","Max torque","Nm",500.,&mptmax);

        //Add inputParammeters to the component
            addInputVariable("Jg", "Equivalent inertia at port 2", "kg", \
1.,&mpJg);
            addInputVariable("Bg", "Visc friction coeff. at port 2", "Ns/m", \
0.,&mpBg);
            addInputVariable("myfric", "friction. coeff. of gear (at \
output)", "", 0.01,&mpmyfric);
            addInputVariable("wc", "Friction speed (for numerics)", "rad/s", \
1.,&mpwc);
        //Add outputVariables to the component

//==This code has been autogenerated using Compgen==
        //Add constantParameters
        mpSolver = new EquationSystemSolver(this,6);
     }

    void initialize()
     {
        //Read port variable pointers from nodes
        //Port Pmr1
        mpND_tormr1=getSafeNodeDataPtr(mpPmr1, \
NodeMechanicRotational::Torque);
        mpND_thetamr1=getSafeNodeDataPtr(mpPmr1, \
NodeMechanicRotational::Angle);
        mpND_wmr1=getSafeNodeDataPtr(mpPmr1, \
NodeMechanicRotational::AngularVelocity);
        mpND_cmr1=getSafeNodeDataPtr(mpPmr1, \
NodeMechanicRotational::WaveVariable);
        mpND_Zcmr1=getSafeNodeDataPtr(mpPmr1, \
NodeMechanicRotational::CharImpedance);
        mpND_eqInertiamr1=getSafeNodeDataPtr(mpPmr1, \
NodeMechanicRotational::EquivalentInertia);
        //Port Pmr2
        mpND_tormr2=getSafeNodeDataPtr(mpPmr2, \
NodeMechanicRotational::Torque);
        mpND_thetamr2=getSafeNodeDataPtr(mpPmr2, \
NodeMechanicRotational::Angle);
        mpND_wmr2=getSafeNodeDataPtr(mpPmr2, \
NodeMechanicRotational::AngularVelocity);
        mpND_cmr2=getSafeNodeDataPtr(mpPmr2, \
NodeMechanicRotational::WaveVariable);
        mpND_Zcmr2=getSafeNodeDataPtr(mpPmr2, \
NodeMechanicRotational::CharImpedance);
        mpND_eqInertiamr2=getSafeNodeDataPtr(mpPmr2, \
NodeMechanicRotational::EquivalentInertia);

        //Read variables from nodes
        //Port Pmr1
        tormr1 = (*mpND_tormr1);
        thetamr1 = (*mpND_thetamr1);
        wmr1 = (*mpND_wmr1);
        cmr1 = (*mpND_cmr1);
        Zcmr1 = (*mpND_Zcmr1);
        eqInertiamr1 = (*mpND_eqInertiamr1);
        //Port Pmr2
        tormr2 = (*mpND_tormr2);
        thetamr2 = (*mpND_thetamr2);
        wmr2 = (*mpND_wmr2);
        cmr2 = (*mpND_cmr2);
        Zcmr2 = (*mpND_Zcmr2);
        eqInertiamr2 = (*mpND_eqInertiamr2);

        //Read inputVariables from nodes
        gearRatio = (*mpgearRatio);
        tmax = (*mptmax);

        //Read inputParameters from nodes
        Jg = (*mpJg);
        Bg = (*mpBg);
        myfric = (*mpmyfric);
        wc = (*mpwc);

        //Read outputVariables from nodes

//==This code has been autogenerated using Compgen==


        //Initialize delays
        delayParts1[1] = (-(gearRatio*mTimestep*tormr1) - mTimestep*tormr2 - \
2*Jg*wmr2 + Bg*mTimestep*wmr2)/(2*Jg + Bg*mTimestep);
        mDelayedPart11.initialize(mNstep,delayParts1[1]);
        delayParts2[1] = (-2*thetamr2 - mTimestep*wmr2)/2.;
        mDelayedPart21.initialize(mNstep,delayParts2[1]);
        delayParts3[1] = (-2*thetamr1 + gearRatio*mTimestep*wmr2)/2.;
        mDelayedPart31.initialize(mNstep,delayParts3[1]);

        delayedPart[1][1] = delayParts1[1];
        delayedPart[2][1] = delayParts2[1];
        delayedPart[3][1] = delayParts3[1];
        delayedPart[4][1] = delayParts4[1];
        delayedPart[5][1] = delayParts5[1];
        delayedPart[6][1] = delayParts6[1];
     }
    void simulateOneTimestep()
     {
        Vec stateVar(6);
        Vec stateVark(6);
        Vec deltaStateVar(6);

        //Read variables from nodes
        //Port Pmr1
        cmr1 = (*mpND_cmr1);
        Zcmr1 = (*mpND_Zcmr1);
        //Port Pmr2
        cmr2 = (*mpND_cmr2);
        Zcmr2 = (*mpND_Zcmr2);

        //Read inputVariables from nodes
        gearRatio = (*mpgearRatio);
        tmax = (*mptmax);

        //LocalExpressions

        //Initializing variable vector for Newton-Raphson
        stateVark[0] = wmr2;
        stateVark[1] = thetamr2;
        stateVark[2] = thetamr1;
        stateVark[3] = tormr1;
        stateVark[4] = wmr1;
        stateVark[5] = tormr2;

        //Iterative solution using Newton-Rapshson
        for(iter=1;iter<=mNoiter;iter++)
        {
         //GearClutch
         //Differential-algebraic system of equation parts

          //Assemble differential-algebraic equations
          systemEquations[0] =-((mTimestep*(gearRatio*tormr1 + tormr2))/(2*Jg \
+ Bg*mTimestep)) + wmr2 + delayedPart[1][1];
          systemEquations[1] =thetamr2 - (mTimestep*wmr2)/2. + \
delayedPart[2][1];
          systemEquations[2] =thetamr1 + (gearRatio*mTimestep*wmr2)/2. + \
delayedPart[3][1];
          systemEquations[3] =tormr1 - limit(cmr1 - \
gearRatio*wmr2*Zcmr1,-tmax,tmax);
          systemEquations[4] =wmr1 + (cmr1 - tormr1)/Zcmr1;
          systemEquations[5] =-cmr2 + tormr2 - wmr2*Zcmr2;

          //Jacobian matrix
          jacobianMatrix[0][0] = 1;
          jacobianMatrix[0][1] = 0;
          jacobianMatrix[0][2] = 0;
          jacobianMatrix[0][3] = -((gearRatio*mTimestep)/(2*Jg + \
Bg*mTimestep));
          jacobianMatrix[0][4] = 0;
          jacobianMatrix[0][5] = -(mTimestep/(2*Jg + Bg*mTimestep));
          jacobianMatrix[1][0] = -mTimestep/2.;
          jacobianMatrix[1][1] = 1;
          jacobianMatrix[1][2] = 0;
          jacobianMatrix[1][3] = 0;
          jacobianMatrix[1][4] = 0;
          jacobianMatrix[1][5] = 0;
          jacobianMatrix[2][0] = (gearRatio*mTimestep)/2.;
          jacobianMatrix[2][1] = 0;
          jacobianMatrix[2][2] = 1;
          jacobianMatrix[2][3] = 0;
          jacobianMatrix[2][4] = 0;
          jacobianMatrix[2][5] = 0;
          jacobianMatrix[3][0] = gearRatio*Zcmr1*dxLimit(cmr1 - \
gearRatio*wmr2*Zcmr1,-tmax,tmax);
          jacobianMatrix[3][1] = 0;
          jacobianMatrix[3][2] = 0;
          jacobianMatrix[3][3] = 1;
          jacobianMatrix[3][4] = 0;
          jacobianMatrix[3][5] = 0;
          jacobianMatrix[4][0] = 0;
          jacobianMatrix[4][1] = 0;
          jacobianMatrix[4][2] = 0;
          jacobianMatrix[4][3] = -(1/Zcmr1);
          jacobianMatrix[4][4] = 1;
          jacobianMatrix[4][5] = 0;
          jacobianMatrix[5][0] = -Zcmr2;
          jacobianMatrix[5][1] = 0;
          jacobianMatrix[5][2] = 0;
          jacobianMatrix[5][3] = 0;
          jacobianMatrix[5][4] = 0;
          jacobianMatrix[5][5] = 1;
//==This code has been autogenerated using Compgen==

          //Solving equation using LU-faktorisation
          mpSolver->solve(jacobianMatrix, systemEquations, stateVark, iter);
          wmr2=stateVark[0];
          thetamr2=stateVark[1];
          thetamr1=stateVark[2];
          tormr1=stateVark[3];
          wmr1=stateVark[4];
          tormr2=stateVark[5];
          //Expressions
          eqInertiamr1 = Jg/Power(gearRatio,2);
          eqInertiamr2 = Jg;
        }

        //Calculate the delayed parts
        delayParts1[1] = (-(gearRatio*mTimestep*tormr1) - mTimestep*tormr2 - \
2*Jg*wmr2 + Bg*mTimestep*wmr2)/(2*Jg + Bg*mTimestep);
        delayParts2[1] = (-2*thetamr2 - mTimestep*wmr2)/2.;
        delayParts3[1] = (-2*thetamr1 + gearRatio*mTimestep*wmr2)/2.;

        delayedPart[1][1] = delayParts1[1];
        delayedPart[2][1] = delayParts2[1];
        delayedPart[3][1] = delayParts3[1];
        delayedPart[4][1] = delayParts4[1];
        delayedPart[5][1] = delayParts5[1];
        delayedPart[6][1] = delayParts6[1];

        //Write new values to nodes
        //Port Pmr1
        (*mpND_tormr1)=tormr1;
        (*mpND_thetamr1)=thetamr1;
        (*mpND_wmr1)=wmr1;
        (*mpND_eqInertiamr1)=eqInertiamr1;
        //Port Pmr2
        (*mpND_tormr2)=tormr2;
        (*mpND_thetamr2)=thetamr2;
        (*mpND_wmr2)=wmr2;
        (*mpND_eqInertiamr2)=eqInertiamr2;
        //outputVariables

        //Update the delayed variabels
        mDelayedPart11.update(delayParts1[1]);
        mDelayedPart21.update(delayParts2[1]);
        mDelayedPart31.update(delayParts3[1]);

     }
    void deconfigure()
    {
        delete mpSolver;
    }
};
#endif // MECHANICGEARCLUTCH_HPP_INCLUDED

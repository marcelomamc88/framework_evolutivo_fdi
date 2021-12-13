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

#ifndef AEROTURBFILTER_HPP_INCLUDED
#define AEROTURBFILTER_HPP_INCLUDED

#include <iostream>
#include "ComponentEssentials.h"
#include "ComponentUtilities.h"
#include "math.h"

//!
//! @file \
C:\HopsanTrunk\ComponentLibraries\defaultLibrary\Special\AeroComponents\AeroT\
urbFilter.hpp
//! @author Petter Krus <petter.krus@liu.se>
//! @date Sat 3 May 2014 00:19:08
//! @brief Dryden model of atmospheric turbulence
//! @ingroup AeroComponents
//!
//==This code has been autogenerated using Compgen==
//from 
/*{, C:, Users, petkr14.IEI, Documents, CompgenNG}/AeroFilter.nb*/

using namespace hopsan;

class AeroTurbFilter : public ComponentSignal
{
private:
     double su;
     double sv;
     double sw;
     double Lu;
     double Lv;
     double Lw;
     double delayParts1[9];
     double delayParts2[9];
     double delayParts3[9];
     double delayParts4[9];
     Matrix jacobianMatrix;
     Vec systemEquations;
     Matrix delayedPart;
     int i;
     int iter;
     int mNoiter;
     double jsyseqnweight[4];
     int order[3];
     int mNstep;
//==This code has been autogenerated using Compgen==
     //inputVariables
     double V;
     double noiseu;
     double noisev;
     double noisew;
     //outputVariables
     double du;
     double dv;
     double dw;
     //Delay declarations
//==This code has been autogenerated using Compgen==
     //inputVariables pointers
     double *mpV;
     double *mpnoiseu;
     double *mpnoisev;
     double *mpnoisew;
     //outputVariables pointers
     double *mpdu;
     double *mpdv;
     double *mpdw;
     Delay mDelayedPart10;
     Delay mDelayedPart11;
     Delay mDelayedPart20;
     Delay mDelayedPart21;
     Delay mDelayedPart22;
     Delay mDelayedPart30;
     Delay mDelayedPart31;
     Delay mDelayedPart32;
     EquationSystemSolver *mpSolver;

public:
     static Component *Creator()
     {
        return new AeroTurbFilter();
     }

     void configure()
     {
//==This code has been autogenerated using Compgen==

        mNstep=9;
        jacobianMatrix.create(3,3);
        systemEquations.create(3);
        delayedPart.create(4,6);
        mNoiter=2;
        jsyseqnweight[0]=1;
        jsyseqnweight[1]=0.67;
        jsyseqnweight[2]=0.5;
        jsyseqnweight[3]=0.5;


        //Add ports to the component
        //Add inputVariables to the component
            addInputVariable("V","speed","m/s",100.,&mpV);
            addInputVariable("noiseu","noise input"," ",0.,&mpnoiseu);
            addInputVariable("noisev","noise input"," ",0.,&mpnoisev);
            addInputVariable("noisew","noise input"," ",0.,&mpnoisew);

        //Add outputVariables to the component
            addOutputVariable("du","turbulence horizontal \
speed","m/s",0.,&mpdu);
            addOutputVariable("dv","turbulence lateral \
speed","m/s",0.,&mpdv);
            addOutputVariable("dw","turbulence vertical \
speed","m/s",0.,&mpdw);

//==This code has been autogenerated using Compgen==
        //Add constants/parameters
            addConstant("su", "longitudional turbulense intensity", "m/s", \
1.,su);
            addConstant("sv", "lateral turbulense intensity", "m/s", 1.,sv);
            addConstant("sw", "vertical turbulense intensity", "m/s", 1.,sw);
            addConstant("Lu", "turbulence scale length", "ms/", 525.,Lu);
            addConstant("Lv", "turbulence scale length", "ms/", 525.,Lv);
            addConstant("Lw", "turbulence scale length", "ms/", 525.,Lw);
        mpSolver = new EquationSystemSolver(this,3);
     }

    void initialize()
     {
        //Read port variable pointers from nodes

        //Read variables from nodes

        //Read inputVariables from nodes
        V = (*mpV);
        noiseu = (*mpnoiseu);
        noisev = (*mpnoisev);
        noisew = (*mpnoisew);

        //Read outputVariables from nodes
        du = (*mpdu);
        dv = (*mpdv);
        dw = (*mpdw);

//==This code has been autogenerated using Compgen==


        //Initialize delays
        delayParts1[1] = (-2.*du*Lu - \
0.7978848977752073*Sqrt(Lu)*mTimestep*noiseu*su*Sqrt(Abs(1 + V)) + \
du*mTimestep*Abs(1 + V))/(2.*Lu + mTimestep*Abs(1 + V));
        mDelayedPart11.initialize(mNstep,delayParts1[1]);
        delayParts2[1] = (-32.*dv*Power(Lv,2) - \
1.5957697955504146*Sqrt(Lv)*Power(mTimestep,2)*noisev*sv*Power(Abs(1 + \
V),1.5) + 2.*dv*Power(mTimestep,2)*Power(Abs(1 + V),2))/(16.*Power(Lv,2) + \
8.*Lv*mTimestep*Abs(1 + V) + Power(mTimestep,2)*Power(Abs(1 + V),2));
        mDelayedPart21.initialize(mNstep,delayParts2[1]);
        delayParts2[2] = (16.*dv*Power(Lv,2) + \
5.5279087261542355*Power(Lv,1.5)*mTimestep*noisev*sv*Sqrt(Abs(1 + V)) - \
8.*dv*Lv*mTimestep*Abs(1 + V) - \
0.7978848977752073*Sqrt(Lv)*Power(mTimestep,2)*noisev*sv*Power(Abs(1 + \
V),1.5) + dv*Power(mTimestep,2)*Power(Abs(1 + V),2))/(16.*Power(Lv,2) + \
8.*Lv*mTimestep*Abs(1 + V) + Power(mTimestep,2)*Power(Abs(1 + V),2));
        mDelayedPart22.initialize(mNstep,delayParts2[2]);
        delayParts3[1] = (-32.*dw*Power(Lw,2) - \
1.5957697955504146*Sqrt(Lw)*Power(mTimestep,2)*noisew*sw*Power(Abs(1 + \
V),1.5) + 2.*dw*Power(mTimestep,2)*Power(Abs(1 + V),2))/(16.*Power(Lw,2) + \
8.*Lw*mTimestep*Abs(1 + V) + Power(mTimestep,2)*Power(Abs(1 + V),2));
        mDelayedPart31.initialize(mNstep,delayParts3[1]);
        delayParts3[2] = (16.*dw*Power(Lw,2) + \
5.5279087261542355*Power(Lw,1.5)*mTimestep*noisew*sw*Sqrt(Abs(1 + V)) - \
8.*dw*Lw*mTimestep*Abs(1 + V) - \
0.7978848977752073*Sqrt(Lw)*Power(mTimestep,2)*noisew*sw*Power(Abs(1 + \
V),1.5) + dw*Power(mTimestep,2)*Power(Abs(1 + V),2))/(16.*Power(Lw,2) + \
8.*Lw*mTimestep*Abs(1 + V) + Power(mTimestep,2)*Power(Abs(1 + V),2));
        mDelayedPart32.initialize(mNstep,delayParts3[2]);

        delayedPart[1][1] = delayParts1[1];
        delayedPart[2][1] = delayParts2[1];
        delayedPart[2][2] = mDelayedPart22.getIdx(1);
        delayedPart[3][1] = delayParts3[1];
        delayedPart[3][2] = mDelayedPart32.getIdx(1);
     }
    void simulateOneTimestep()
     {
        Vec stateVar(3);
        Vec stateVark(3);
        Vec deltaStateVar(3);

        //Read variables from nodes

        //Read inputVariables from nodes
        V = (*mpV);
        noiseu = (*mpnoiseu);
        noisev = (*mpnoisev);
        noisew = (*mpnoisew);

        //LocalExpressions

        //Initializing variable vector for Newton-Raphson
        stateVark[0] = du;
        stateVark[1] = dv;
        stateVark[2] = dw;

        //Iterative solution using Newton-Rapshson
        for(iter=1;iter<=mNoiter;iter++)
        {
         //TurbFilter
         //Differential-algebraic system of equation parts

          //Assemble differential-algebraic equations
          systemEquations[0] =du - \
(0.7978848977752073*Sqrt(Lu)*mTimestep*noiseu*su*Sqrt(Abs(1 + V)))/(2.*Lu + \
mTimestep*Abs(1 + V)) + delayedPart[1][1];
          systemEquations[1] =dv + (Sqrt(Lv)*mTimestep*noisev*sv*Sqrt(Abs(1 + \
V))*(-5.5279087261542355*Lv - 0.7978848977752073*mTimestep*Abs(1 + \
V)))/(16.*Power(Lv,2) + 8.*Lv*mTimestep*Abs(1 + V) + \
Power(mTimestep,2)*Power(Abs(1 + V),2)) + delayedPart[2][1] + \
delayedPart[2][2];
          systemEquations[2] =dw + (Sqrt(Lw)*mTimestep*noisew*sw*Sqrt(Abs(1 + \
V))*(-5.5279087261542355*Lw - 0.7978848977752073*mTimestep*Abs(1 + \
V)))/(16.*Power(Lw,2) + 8.*Lw*mTimestep*Abs(1 + V) + \
Power(mTimestep,2)*Power(Abs(1 + V),2)) + delayedPart[3][1] + \
delayedPart[3][2];

          //Jacobian matrix
          jacobianMatrix[0][0] = 1.;
          jacobianMatrix[0][1] = 0.;
          jacobianMatrix[0][2] = 0.;
          jacobianMatrix[1][0] = 0.;
          jacobianMatrix[1][1] = 1.;
          jacobianMatrix[1][2] = 0.;
          jacobianMatrix[2][0] = 0.;
          jacobianMatrix[2][1] = 0.;
          jacobianMatrix[2][2] = 1.;
//==This code has been autogenerated using Compgen==

          //Solving equation using LU-faktorisation
          mpSolver->solve(jacobianMatrix, systemEquations, stateVark, iter);
          du=stateVark[0];
          dv=stateVark[1];
          dw=stateVark[2];
        }

        //Calculate the delayed parts
        delayParts1[1] = (-2.*du*Lu - \
0.7978848977752073*Sqrt(Lu)*mTimestep*noiseu*su*Sqrt(Abs(1 + V)) + \
du*mTimestep*Abs(1 + V))/(2.*Lu + mTimestep*Abs(1 + V));
        delayParts2[1] = (-32.*dv*Power(Lv,2) - \
1.5957697955504146*Sqrt(Lv)*Power(mTimestep,2)*noisev*sv*Power(Abs(1 + \
V),1.5) + 2.*dv*Power(mTimestep,2)*Power(Abs(1 + V),2))/(16.*Power(Lv,2) + \
8.*Lv*mTimestep*Abs(1 + V) + Power(mTimestep,2)*Power(Abs(1 + V),2));
        delayParts2[2] = (16.*dv*Power(Lv,2) + \
5.5279087261542355*Power(Lv,1.5)*mTimestep*noisev*sv*Sqrt(Abs(1 + V)) - \
8.*dv*Lv*mTimestep*Abs(1 + V) - \
0.7978848977752073*Sqrt(Lv)*Power(mTimestep,2)*noisev*sv*Power(Abs(1 + \
V),1.5) + dv*Power(mTimestep,2)*Power(Abs(1 + V),2))/(16.*Power(Lv,2) + \
8.*Lv*mTimestep*Abs(1 + V) + Power(mTimestep,2)*Power(Abs(1 + V),2));
        delayParts3[1] = (-32.*dw*Power(Lw,2) - \
1.5957697955504146*Sqrt(Lw)*Power(mTimestep,2)*noisew*sw*Power(Abs(1 + \
V),1.5) + 2.*dw*Power(mTimestep,2)*Power(Abs(1 + V),2))/(16.*Power(Lw,2) + \
8.*Lw*mTimestep*Abs(1 + V) + Power(mTimestep,2)*Power(Abs(1 + V),2));
        delayParts3[2] = (16.*dw*Power(Lw,2) + \
5.5279087261542355*Power(Lw,1.5)*mTimestep*noisew*sw*Sqrt(Abs(1 + V)) - \
8.*dw*Lw*mTimestep*Abs(1 + V) - \
0.7978848977752073*Sqrt(Lw)*Power(mTimestep,2)*noisew*sw*Power(Abs(1 + \
V),1.5) + dw*Power(mTimestep,2)*Power(Abs(1 + V),2))/(16.*Power(Lw,2) + \
8.*Lw*mTimestep*Abs(1 + V) + Power(mTimestep,2)*Power(Abs(1 + V),2));

        delayedPart[1][1] = delayParts1[1];
        delayedPart[2][1] = delayParts2[1];
        delayedPart[2][2] = mDelayedPart22.getIdx(0);
        delayedPart[3][1] = delayParts3[1];
        delayedPart[3][2] = mDelayedPart32.getIdx(0);

        //Write new values to nodes
        //outputVariables
        (*mpdu)=du;
        (*mpdv)=dv;
        (*mpdw)=dw;

        //Update the delayed variabels
        mDelayedPart11.update(delayParts1[1]);
        mDelayedPart21.update(delayParts2[1]);
        mDelayedPart22.update(delayParts2[2]);
        mDelayedPart31.update(delayParts3[1]);
        mDelayedPart32.update(delayParts3[2]);

     }
    void deconfigure()
    {
        delete mpSolver;
    }
};
#endif // AEROTURBFILTER_HPP_INCLUDED

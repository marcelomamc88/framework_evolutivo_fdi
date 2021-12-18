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

#ifndef HYDRAULICORIFICEG_HPP_INCLUDED
#define HYDRAULICORIFICEG_HPP_INCLUDED

#include <iostream>
#include "ComponentEssentials.h"
#include "ComponentUtilities.h"
#include "math.h"

//!
//! @file HydraulicOrificeG.hpp
//! @author Petter Krus <petter.krus@liu.se>
//  co-author/auditor **Not yet audited by a second person**
//! @date Wed 5 Aug 2015 09:23:32
//! @brief A general orifice with geometric parameters
//! @ingroup HydraulicComponents
//!
//==This code has been autogenerated using Compgen==
//from 
/*{, C:, HopsanTrunk, componentLibraries, defaultLibrary, Hydraulic, \
Restrictors}/HydraulicOrificeG.nb*/

using namespace hopsan;

class HydraulicOrificeG : public ComponentQ
{
private:
     double rho;
     double visc;
     double Ao;
     double dh;
     double lo;
     double Cdt;
     double del;
     double sf;
     Port *mpP1;
     Port *mpP2;
     double delayParts1[9];
     double delayParts2[9];
     double delayParts3[9];
     Matrix jacobianMatrix;
     Vec systemEquations;
     Matrix delayedPart;
     int i;
     int iter;
     int mNoiter;
     double jsyseqnweight[4];
     int order[3];
     int mNstep;
     //Port P1 variable
     double p1;
     double q1;
     double T1;
     double dE1;
     double c1;
     double Zc1;
     //Port P2 variable
     double p2;
     double q2;
     double T2;
     double dE2;
     double c2;
     double Zc2;
//==This code has been autogenerated using Compgen==
     //inputVariables
     //outputVariables
     double Ro;
     double DRL;
     double Cd;
     //Expressions variables
     //Port P1 pointer
     double *mpND_p1;
     double *mpND_q1;
     double *mpND_T1;
     double *mpND_dE1;
     double *mpND_c1;
     double *mpND_Zc1;
     //Port P2 pointer
     double *mpND_p2;
     double *mpND_q2;
     double *mpND_T2;
     double *mpND_dE2;
     double *mpND_c2;
     double *mpND_Zc2;
     //Delay declarations
//==This code has been autogenerated using Compgen==
     //inputVariables pointers
     //inputParameters pointers
     double *mprho;
     double *mpvisc;
     double *mpAo;
     double *mpdh;
     double *mplo;
     double *mpCdt;
     double *mpdel;
     double *mpsf;
     //outputVariables pointers
     double *mpRo;
     double *mpDRL;
     double *mpCd;
     Delay mDelayedPart10;
     EquationSystemSolver *mpSolver;

public:
     static Component *Creator()
     {
        return new HydraulicOrificeG();
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
        mpP1=addPowerPort("P1","NodeHydraulic");
        mpP2=addPowerPort("P2","NodeHydraulic");
        //Add inputVariables to the component

        //Add inputParammeters to the component
            addInputVariable("rho", "Oil density", "kg/m3", 870, &mprho);
            addInputVariable("visc", "Dynamic viscosity ", "m", \
0.12,&mpvisc);
            addInputVariable("Ao", "Orifice area", "m2", 1.e-7,&mpAo);
            addInputVariable("dh", "Orifice hydraulic diameter", "m", \
0.0025,&mpdh);
            addInputVariable("lo", "Length", "m", 0.001,&mplo);
            addInputVariable("Cdt", "Turbulent discharge coeff", "", \
0.611,&mpCdt);
            addInputVariable("del", "Laminar flow coefficient", "", \
0.157,&mpdel);
            addInputVariable("sf", "Shape factor round=1, rectangle=0.", "", \
0,&mpsf);
        //Add outputVariables to the component
            addOutputVariable("Ro","Rynolds number","",0.,&mpRo);
            addOutputVariable("DRL","dh Ro/lo","",0.,&mpDRL);
            addOutputVariable("Cd","Discharge coeff","",0.611,&mpCd);

//==This code has been autogenerated using Compgen==
        //Add constantParameters
        mpSolver = new EquationSystemSolver(this,3);
     }

    void initialize()
     {
        //Read port variable pointers from nodes
        //Port P1
        mpND_p1=getSafeNodeDataPtr(mpP1, NodeHydraulic::Pressure);
        mpND_q1=getSafeNodeDataPtr(mpP1, NodeHydraulic::Flow);
        mpND_T1=getSafeNodeDataPtr(mpP1, NodeHydraulic::Temperature);
        mpND_dE1=getSafeNodeDataPtr(mpP1, NodeHydraulic::HeatFlow);
        mpND_c1=getSafeNodeDataPtr(mpP1, NodeHydraulic::WaveVariable);
        mpND_Zc1=getSafeNodeDataPtr(mpP1, NodeHydraulic::CharImpedance);
        //Port P2
        mpND_p2=getSafeNodeDataPtr(mpP2, NodeHydraulic::Pressure);
        mpND_q2=getSafeNodeDataPtr(mpP2, NodeHydraulic::Flow);
        mpND_T2=getSafeNodeDataPtr(mpP2, NodeHydraulic::Temperature);
        mpND_dE2=getSafeNodeDataPtr(mpP2, NodeHydraulic::HeatFlow);
        mpND_c2=getSafeNodeDataPtr(mpP2, NodeHydraulic::WaveVariable);
        mpND_Zc2=getSafeNodeDataPtr(mpP2, NodeHydraulic::CharImpedance);

        //Read variables from nodes
        //Port P1
        p1 = (*mpND_p1);
        q1 = (*mpND_q1);
        T1 = (*mpND_T1);
        dE1 = (*mpND_dE1);
        c1 = (*mpND_c1);
        Zc1 = (*mpND_Zc1);
        //Port P2
        p2 = (*mpND_p2);
        q2 = (*mpND_q2);
        T2 = (*mpND_T2);
        dE2 = (*mpND_dE2);
        c2 = (*mpND_c2);
        Zc2 = (*mpND_Zc2);

        //Read inputVariables from nodes

        //Read inputParameters from nodes
        rho = (*mprho);
        visc = (*mpvisc);
        Ao = (*mpAo);
        dh = (*mpdh);
        lo = (*mplo);
        Cdt = (*mpCdt);
        del = (*mpdel);
        sf = (*mpsf);

        //Read outputVariables from nodes
        Ro = (*mpRo);
        DRL = (*mpDRL);
        Cd = (*mpCd);

//==This code has been autogenerated using Compgen==


        //Initialize delays

        delayedPart[1][1] = delayParts1[1];
        delayedPart[2][1] = delayParts2[1];
        delayedPart[3][1] = delayParts3[1];

        simulateOneTimestep();

     }
    void simulateOneTimestep()
     {
        Vec stateVar(3);
        Vec stateVark(3);
        Vec deltaStateVar(3);

        //Read variables from nodes
        //Port P1
        T1 = (*mpND_T1);
        c1 = (*mpND_c1);
        Zc1 = (*mpND_Zc1);
        //Port P2
        T2 = (*mpND_T2);
        c2 = (*mpND_c2);
        Zc2 = (*mpND_Zc2);

        //Read inputVariables from nodes

        //Read inputParameters from nodes
        rho = (*mprho);
        visc = (*mpvisc);
        Ao = (*mpAo);
        dh = (*mpdh);
        lo = (*mplo);
        Cdt = (*mpCdt);
        del = (*mpdel);
        sf = (*mpsf);

        //LocalExpressions

        //Initializing variable vector for Newton-Raphson
        stateVark[0] = q2;
        stateVark[1] = p1;
        stateVark[2] = p2;

        //Iterative solution using Newton-Rapshson
        for(iter=1;iter<=mNoiter;iter++)
        {
         //OrificeG
         //Differential-algebraic system of equation parts

          //Assemble differential-algebraic equations
          systemEquations[0] =q2 - (2*(p1 - p2))/Sqrt((Power(Cdt,2)*Power(dh \
- 32*Power(del,2)*lo*(-3 + sf),2)*Power(visc,2) + \
2*Power(del,4)*Power(dh,4)*rho*Abs(p1 - \
p2))/(Power(Ao,2)*Power(Cdt,2)*Power(del,4)*Power(dh,4)));
          systemEquations[1] =p1 - lowLimit(c1 - q2*Zc1,0);
          systemEquations[2] =p2 - lowLimit(c2 + q2*Zc2,0);

          //Jacobian matrix
          jacobianMatrix[0][0] = 1;
          jacobianMatrix[0][1] = -2/Sqrt((Power(Cdt,2)*Power(dh - \
32*Power(del,2)*lo*(-3 + sf),2)*Power(visc,2) + \
2*Power(del,4)*Power(dh,4)*rho*Abs(p1 - \
p2))/(Power(Ao,2)*Power(Cdt,2)*Power(del,4)*Power(dh,4))) + (2*(p1 - \
p2)*rho*dxAbs(p1 - \
p2))/(Power(Ao,2)*Power(Cdt,2)*Power((Power(Cdt,2)*Power(dh - \
32*Power(del,2)*lo*(-3 + sf),2)*Power(visc,2) + \
2*Power(del,4)*Power(dh,4)*rho*Abs(p1 - \
p2))/(Power(Ao,2)*Power(Cdt,2)*Power(del,4)*Power(dh,4)),1.5));
          jacobianMatrix[0][2] = 2/Sqrt((Power(Cdt,2)*Power(dh - \
32*Power(del,2)*lo*(-3 + sf),2)*Power(visc,2) + \
2*Power(del,4)*Power(dh,4)*rho*Abs(p1 - \
p2))/(Power(Ao,2)*Power(Cdt,2)*Power(del,4)*Power(dh,4))) - (2*(p1 - \
p2)*rho*dxAbs(p1 - \
p2))/(Power(Ao,2)*Power(Cdt,2)*Power((Power(Cdt,2)*Power(dh - \
32*Power(del,2)*lo*(-3 + sf),2)*Power(visc,2) + \
2*Power(del,4)*Power(dh,4)*rho*Abs(p1 - \
p2))/(Power(Ao,2)*Power(Cdt,2)*Power(del,4)*Power(dh,4)),1.5));
          jacobianMatrix[1][0] = Zc1*dxLowLimit(c1 - q2*Zc1,0);
          jacobianMatrix[1][1] = 1;
          jacobianMatrix[1][2] = 0;
          jacobianMatrix[2][0] = -(Zc2*dxLowLimit(c2 + q2*Zc2,0));
          jacobianMatrix[2][1] = 0;
          jacobianMatrix[2][2] = 1;
//==This code has been autogenerated using Compgen==

          //Solving equation using LU-faktorisation
          mpSolver->solve(jacobianMatrix, systemEquations, stateVark, iter);
          q2=stateVark[0];
          p1=stateVark[1];
          p2=stateVark[2];
          //Expressions
          q1 = -q2;
          Ro = (dh*rho*Abs(q2))/(Ao*visc);
          DRL = (dh*Ro)/(0.1*dh + lo);
          Cd = Abs(q2)/(Sqrt(2)*Ao*Sqrt((0.1 + Abs(p1 - p2))/rho));
        }

        //Calculate the delayed parts

        delayedPart[1][1] = delayParts1[1];
        delayedPart[2][1] = delayParts2[1];
        delayedPart[3][1] = delayParts3[1];

        //Write new values to nodes
        //Port P1
        (*mpND_p1)=p1;
        (*mpND_q1)=q1;
        (*mpND_dE1)=dE1;
        //Port P2
        (*mpND_p2)=p2;
        (*mpND_q2)=q2;
        (*mpND_dE2)=dE2;
        //outputVariables
        (*mpRo)=Ro;
        (*mpDRL)=DRL;
        (*mpCd)=Cd;

        //Update the delayed variabels

     }
    void deconfigure()
    {
        delete mpSolver;
    }
};
#endif // HYDRAULICORIFICEG_HPP_INCLUDED

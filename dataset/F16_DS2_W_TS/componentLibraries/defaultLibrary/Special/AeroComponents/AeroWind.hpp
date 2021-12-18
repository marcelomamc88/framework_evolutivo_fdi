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

#ifndef AEROWIND_HPP_INCLUDED
#define AEROWIND_HPP_INCLUDED

#include <iostream>
#include "ComponentEssentials.h"
#include "ComponentUtilities.h"
#include "math.h"

//!
//! @file AeroWind.hpp
//! @author Petter Krus <petter.krus@liu.se>
//! @date Fri 26 Sep 2014 09:10:32
//! @brief Wind model with Dryden model of atmospheric turbulence
//! @ingroup AeroComponents
//!
//==This code has been autogenerated using Compgen==
//from 
/*{, C:, Users, petkr14.IEI, Documents, CompgenNG}/AeroWind.nb*/

using namespace hopsan;

class AeroWind : public ComponentSignal
{
private:
     double U0;
     double heading;
     double h0;
     double alpha;
     double au;
     double aw;
     double wh;
     double delayParts1[9];
     double delayParts2[9];
     double delayParts3[9];
     double delayParts4[9];
     double delayParts5[9];
     Matrix jacobianMatrix;
     Vec systemEquations;
     Matrix delayedPart;
     int i;
     int iter;
     int mNoiter;
     double jsyseqnweight[4];
     int order[4];
     int mNstep;
//==This code has been autogenerated using Compgen==
     //inputVariables
     double V;
     double h;
     double noiseu;
     double noisev;
     double noisew;
     //outputVariables
     double du;
     double dv;
     double uw;
     double vw;
     double ww;
     double hf;
     //LocalExpressions variables
     double Uw;
     double sw;
     double su;
     double sv;
     double Lu;
     double Lv;
     double Lw;
     double Ve;
     //Expressions variables
     //Delay declarations
//==This code has been autogenerated using Compgen==
     //inputVariables pointers
     double *mpV;
     double *mph;
     double *mpnoiseu;
     double *mpnoisev;
     double *mpnoisew;
     //inputParameters pointers
     double *mpU0;
     double *mpheading;
     double *mph0;
     double *mpalpha;
     double *mpau;
     double *mpaw;
     double *mpwh;
     //outputVariables pointers
     double *mpdu;
     double *mpdv;
     double *mpuw;
     double *mpvw;
     double *mpww;
     double *mphf;
     Delay mDelayedPart10;
     Delay mDelayedPart11;
     Delay mDelayedPart20;
     Delay mDelayedPart21;
     Delay mDelayedPart30;
     Delay mDelayedPart31;
     Delay mDelayedPart32;
     Delay mDelayedPart40;
     Delay mDelayedPart41;
     Delay mDelayedPart42;
     EquationSystemSolver *mpSolver;

public:
     static Component *Creator()
     {
        return new AeroWind();
     }

     void configure()
     {
//==This code has been autogenerated using Compgen==

        mNstep=9;
        jacobianMatrix.create(4,4);
        systemEquations.create(4);
        delayedPart.create(5,6);
        mNoiter=2;
        jsyseqnweight[0]=1;
        jsyseqnweight[1]=0.67;
        jsyseqnweight[2]=0.5;
        jsyseqnweight[3]=0.5;


        //Add ports to the component
        //Add inputVariables to the component
            addInputVariable("V","speed","m/s",100.,&mpV);
            addInputVariable("h","altitude","m",100.,&mph);
            addInputVariable("noiseu","noise input"," ",0.,&mpnoiseu);
            addInputVariable("noisev","noise input"," ",0.,&mpnoisev);
            addInputVariable("noisew","noise input"," ",0.,&mpnoisew);

        //Add inputParammeters to the component
            addInputVariable("U0", "wind speed at h0", "m/s", 10.,&mpU0);
            addInputVariable("heading", "wind heading", "rad", \
0.,&mpheading);
            addInputVariable("h0", "reference hight", "m", 6.,&mph0);
            addInputVariable("alpha", "Exponent for boundary layer", "", \
1.,&mpalpha);
            addInputVariable("au", "lateral turbulense factor", "", \
0.2,&mpau);
            addInputVariable("aw", "vertical turbulense factor", "", \
0.2,&mpaw);
            addInputVariable("wh", "filter frequency, heading", "rad/s", \
0.1,&mpwh);
        //Add outputVariables to the component
            addOutputVariable("du","inst. horizontal speed \
var","m/s",0.,&mpdu);
            addOutputVariable("dv","inst. lateral speed var","m/s",0.,&mpdv);
            addOutputVariable("uw","inst. horizontal speed","m/s",0.,&mpuw);
            addOutputVariable("vw","inst. lateral speed","m/s",0.,&mpvw);
            addOutputVariable("ww","inst. vertical speed","m/s",0.,&mpww);
            addOutputVariable("hf","internal variable, filtered \
altitude","m/s",0.,&mphf);

//==This code has been autogenerated using Compgen==
        //Add constantParameters
        mpSolver = new EquationSystemSolver(this,4);
     }

    void initialize()
     {
        //Read port variable pointers from nodes

        //Read variables from nodes

        //Read inputVariables from nodes
        V = (*mpV);
        h = (*mph);
        noiseu = (*mpnoiseu);
        noisev = (*mpnoisev);
        noisew = (*mpnoisew);

        //Read inputParameters from nodes
        U0 = (*mpU0);
        heading = (*mpheading);
        h0 = (*mph0);
        alpha = (*mpalpha);
        au = (*mpau);
        aw = (*mpaw);
        wh = (*mpwh);

        //Read outputVariables from nodes
        du = (*mpdu);
        dv = (*mpdv);
        uw = (*mpuw);
        vw = (*mpvw);
        ww = (*mpww);
        hf = (*mphf);

//==This code has been autogenerated using Compgen==

        //LocalExpressions
        Uw = Power(hf/h0,alpha)*U0;
        sw = aw*Uw;
        su = sw/Power(0.177 + 0.0002469*hf,0.4);
        sv = su;
        Lu = (0.3*hf)/Power(0.177 + 0.0002469*hf,1.2);
        Lv = Lu;
        Lw = limit(hf,0,525);
        Ve = lowLimit(Abs(Uw + V),10);

        //Initialize delays
        delayParts1[1] = (-2*hf + hf*mTimestep*wh - \
mTimestep*wh*lowLimit(h,0))/(2 + mTimestep*wh);
        mDelayedPart11.initialize(mNstep,delayParts1[1]);
        delayParts2[1] = (-2.*du*Lu + du*mTimestep*Ve - \
0.7978848977752073*mTimestep*noiseu*su*Sqrt(Lu/Ve)*Ve)/(2.*Lu + \
mTimestep*Ve);
        mDelayedPart21.initialize(mNstep,delayParts2[1]);
        delayParts3[1] = (-32.*dv*Power(Lv,2) + \
2.*dv*Power(mTimestep,2)*Power(Ve,2) - \
1.5957697955504146*Power(mTimestep,2)*noisev*sv*Sqrt(Lv/Ve)*Power(Ve,2))/(16.\
*Power(Lv,2) + 8.*Lv*mTimestep*Ve + Power(mTimestep,2)*Power(Ve,2));
        mDelayedPart31.initialize(mNstep,delayParts3[1]);
        delayParts3[2] = (16.*dv*Power(Lv,2) - 8.*dv*Lv*mTimestep*Ve + \
5.5279087261542355*Lv*mTimestep*noisev*sv*Sqrt(Lv/Ve)*Ve + \
dv*Power(mTimestep,2)*Power(Ve,2) - \
0.7978848977752073*Power(mTimestep,2)*noisev*sv*Sqrt(Lv/Ve)*Power(Ve,2))/(16.\
*Power(Lv,2) + 8.*Lv*mTimestep*Ve + Power(mTimestep,2)*Power(Ve,2));
        mDelayedPart32.initialize(mNstep,delayParts3[2]);
        delayParts4[1] = \
(-1.5957697955504146*Power(mTimestep,2)*noisew*sw*Sqrt(Lw/Ve)*Power(Ve,2) - \
32.*Power(Lw,2)*ww + 2.*Power(mTimestep,2)*Power(Ve,2)*ww)/(16.*Power(Lw,2) + \
8.*Lw*mTimestep*Ve + Power(mTimestep,2)*Power(Ve,2));
        mDelayedPart41.initialize(mNstep,delayParts4[1]);
        delayParts4[2] = \
(5.5279087261542355*Lw*mTimestep*noisew*sw*Sqrt(Lw/Ve)*Ve - \
0.7978848977752073*Power(mTimestep,2)*noisew*sw*Sqrt(Lw/Ve)*Power(Ve,2) + \
16.*Power(Lw,2)*ww - 8.*Lw*mTimestep*Ve*ww + \
Power(mTimestep,2)*Power(Ve,2)*ww)/(16.*Power(Lw,2) + 8.*Lw*mTimestep*Ve + \
Power(mTimestep,2)*Power(Ve,2));
        mDelayedPart42.initialize(mNstep,delayParts4[2]);

        delayedPart[1][1] = delayParts1[1];
        delayedPart[2][1] = delayParts2[1];
        delayedPart[3][1] = delayParts3[1];
        delayedPart[3][2] = mDelayedPart32.getIdx(1);
        delayedPart[4][1] = delayParts4[1];
        delayedPart[4][2] = mDelayedPart42.getIdx(1);
     }
    void simulateOneTimestep()
     {
        Vec stateVar(4);
        Vec stateVark(4);
        Vec deltaStateVar(4);

        //Read variables from nodes

        //Read inputVariables from nodes
        V = (*mpV);
        h = (*mph);
        noiseu = (*mpnoiseu);
        noisev = (*mpnoisev);
        noisew = (*mpnoisew);

        //LocalExpressions
        Uw = Power(hf/h0,alpha)*U0;
        sw = aw*Uw;
        su = sw/Power(0.177 + 0.0002469*hf,0.4);
        sv = su;
        Lu = (0.3*hf)/Power(0.177 + 0.0002469*hf,1.2);
        Lv = Lu;
        Lw = limit(hf,0,525);
        Ve = lowLimit(Abs(Uw + V),10);

        //Initializing variable vector for Newton-Raphson
        stateVark[0] = hf;
        stateVark[1] = du;
        stateVark[2] = dv;
        stateVark[3] = ww;

        //Iterative solution using Newton-Rapshson
        for(iter=1;iter<=mNoiter;iter++)
        {
         //Wind
         //Differential-algebraic system of equation parts

          //Assemble differential-algebraic equations
          systemEquations[0] =hf - (mTimestep*wh*lowLimit(h,0))/(2 + \
mTimestep*wh) + delayedPart[1][1];
          systemEquations[1] =du - \
(0.7978848977752073*mTimestep*noiseu*su*Sqrt(Lu/Ve)*Ve)/(2.*Lu + \
mTimestep*Ve) + delayedPart[2][1];
          systemEquations[2] =dv + \
(mTimestep*noisev*sv*Sqrt(Lv/Ve)*Ve*(-5.5279087261542355*Lv - \
0.7978848977752073*mTimestep*Ve))/(16.*Power(Lv,2) + 8.*Lv*mTimestep*Ve + \
Power(mTimestep,2)*Power(Ve,2)) + delayedPart[3][1] + delayedPart[3][2];
          systemEquations[3] \
=(mTimestep*noisew*sw*Sqrt(Lw/Ve)*Ve*(-5.5279087261542355*Lw - \
0.7978848977752073*mTimestep*Ve))/(16.*Power(Lw,2) + 8.*Lw*mTimestep*Ve + \
Power(mTimestep,2)*Power(Ve,2)) + ww + delayedPart[4][1] + delayedPart[4][2];

          //Jacobian matrix
          jacobianMatrix[0][0] = 1;
          jacobianMatrix[0][1] = 0;
          jacobianMatrix[0][2] = 0;
          jacobianMatrix[0][3] = 0;
          jacobianMatrix[1][0] = 0.;
          jacobianMatrix[1][1] = 1.;
          jacobianMatrix[1][2] = 0;
          jacobianMatrix[1][3] = 0.;
          jacobianMatrix[2][0] = 0.;
          jacobianMatrix[2][1] = 0.;
          jacobianMatrix[2][2] = 1;
          jacobianMatrix[2][3] = 0;
          jacobianMatrix[3][0] = 0;
          jacobianMatrix[3][1] = 0.;
          jacobianMatrix[3][2] = 0;
          jacobianMatrix[3][3] = 1.;
//==This code has been autogenerated using Compgen==

          //Solving equation using LU-faktorisation
          mpSolver->solve(jacobianMatrix, systemEquations, stateVark, iter);
          hf=stateVark[0];
          du=stateVark[1];
          dv=stateVark[2];
          ww=stateVark[3];
          //Expressions
          uw = du + Uw*Cos(heading);
          vw = dv + Uw*Sin(heading);
        }

        //Calculate the delayed parts
        delayParts1[1] = (-2*hf + hf*mTimestep*wh - \
mTimestep*wh*lowLimit(h,0))/(2 + mTimestep*wh);
        delayParts2[1] = (-2.*du*Lu + du*mTimestep*Ve - \
0.7978848977752073*mTimestep*noiseu*su*Sqrt(Lu/Ve)*Ve)/(2.*Lu + \
mTimestep*Ve);
        delayParts3[1] = (-32.*dv*Power(Lv,2) + \
2.*dv*Power(mTimestep,2)*Power(Ve,2) - \
1.5957697955504146*Power(mTimestep,2)*noisev*sv*Sqrt(Lv/Ve)*Power(Ve,2))/(16.\
*Power(Lv,2) + 8.*Lv*mTimestep*Ve + Power(mTimestep,2)*Power(Ve,2));
        delayParts3[2] = (16.*dv*Power(Lv,2) - 8.*dv*Lv*mTimestep*Ve + \
5.5279087261542355*Lv*mTimestep*noisev*sv*Sqrt(Lv/Ve)*Ve + \
dv*Power(mTimestep,2)*Power(Ve,2) - \
0.7978848977752073*Power(mTimestep,2)*noisev*sv*Sqrt(Lv/Ve)*Power(Ve,2))/(16.\
*Power(Lv,2) + 8.*Lv*mTimestep*Ve + Power(mTimestep,2)*Power(Ve,2));
        delayParts4[1] = \
(-1.5957697955504146*Power(mTimestep,2)*noisew*sw*Sqrt(Lw/Ve)*Power(Ve,2) - \
32.*Power(Lw,2)*ww + 2.*Power(mTimestep,2)*Power(Ve,2)*ww)/(16.*Power(Lw,2) + \
8.*Lw*mTimestep*Ve + Power(mTimestep,2)*Power(Ve,2));
        delayParts4[2] = \
(5.5279087261542355*Lw*mTimestep*noisew*sw*Sqrt(Lw/Ve)*Ve - \
0.7978848977752073*Power(mTimestep,2)*noisew*sw*Sqrt(Lw/Ve)*Power(Ve,2) + \
16.*Power(Lw,2)*ww - 8.*Lw*mTimestep*Ve*ww + \
Power(mTimestep,2)*Power(Ve,2)*ww)/(16.*Power(Lw,2) + 8.*Lw*mTimestep*Ve + \
Power(mTimestep,2)*Power(Ve,2));

        delayedPart[1][1] = delayParts1[1];
        delayedPart[2][1] = delayParts2[1];
        delayedPart[3][1] = delayParts3[1];
        delayedPart[3][2] = mDelayedPart32.getIdx(0);
        delayedPart[4][1] = delayParts4[1];
        delayedPart[4][2] = mDelayedPart42.getIdx(0);

        //Write new values to nodes
        //outputVariables
        (*mpdu)=du;
        (*mpdv)=dv;
        (*mpuw)=uw;
        (*mpvw)=vw;
        (*mpww)=ww;
        (*mphf)=hf;

        //Update the delayed variabels
        mDelayedPart11.update(delayParts1[1]);
        mDelayedPart21.update(delayParts2[1]);
        mDelayedPart31.update(delayParts3[1]);
        mDelayedPart32.update(delayParts3[2]);
        mDelayedPart41.update(delayParts4[1]);
        mDelayedPart42.update(delayParts4[2]);

     }
    void deconfigure()
    {
        delete mpSolver;
    }
};
#endif // AEROWIND_HPP_INCLUDED

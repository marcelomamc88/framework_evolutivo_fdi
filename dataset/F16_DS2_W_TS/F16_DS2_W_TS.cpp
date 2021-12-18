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

#define S_FUNCTION_NAME F16_DS2_W_TS
#define S_FUNCTION_LEVEL 2
#define MDL_START

#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include "simstruc.h"
#include "HopsanCore/include/HopsanCore.h"
using namespace hopsan;


HopsanEssentials gHopsanCore;
ComponentSystem* pComponentSystem;
bool isOkToSimulate = false;

#define NUMPARAMS 0

double *pInputNode0;
double *pInputNode1;
double *pInputNode2;
double *pInputNode3;
double *pInputNode4;
double *pInputNode5;
double *pInputNode6;
double *pInputNode7;
double *pInputNode8;
double *pInputNode9;
double *pInputNode10;
double *pInputNode11;
double *pInputNode12;
double *pInputNode13;
double *pInputNode14;
double *pInputNode15;
double *pInputNode16;
double *pOutputNode0;
double *pOutputNode1;
double *pOutputNode2;
double *pOutputNode3;
double *pOutputNode4;
double *pOutputNode5;
double *pOutputNode6;
double *pOutputNode7;
double *pOutputNode8;
double *pOutputNode9;
double *pOutputNode10;
double *pOutputNode11;
double *pOutputNode12;
double *pOutputNode13;
double *pOutputNode14;
double *pOutputNode15;
double *pOutputNode16;
double *pOutputNode17;
double *pOutputNode18;
double *pOutputNode19;
double *pOutputNode20;
double *pOutputNode21;
double *pOutputNode22;
double *pOutputNode23;
double *pOutputNode24;

static void mdlInitializeSizes(SimStruct *S)
{
    // If NUMPARAMS != 0 then the mask setup will not work, so we can not use S-function parameters, for the parameters
    // instead we let the mask create local workspace variables corresponding to our system parameters
    ssSetNumSFcnParams(S, NUMPARAMS);
#if defined(MATLAB_MEX_FILE)
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        return; /* Parameter mismatch will be reported by Simulink. */
    }
#endif

    //Define S-function input signals
    if (!ssSetNumInputPorts(S,17)) return;				//Number of input signals
    ssSetInputPortWidth(S, 0, DYNAMICALLY_SIZED);		//Input signal 0
    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortWidth(S, 1, DYNAMICALLY_SIZED);		//Input signal 1
    ssSetInputPortDirectFeedThrough(S, 1, 1);
    ssSetInputPortWidth(S, 2, DYNAMICALLY_SIZED);		//Input signal 2
    ssSetInputPortDirectFeedThrough(S, 2, 1);
    ssSetInputPortWidth(S, 3, DYNAMICALLY_SIZED);		//Input signal 3
    ssSetInputPortDirectFeedThrough(S, 3, 1);
    ssSetInputPortWidth(S, 4, DYNAMICALLY_SIZED);		//Input signal 4
    ssSetInputPortDirectFeedThrough(S, 4, 1);
    ssSetInputPortWidth(S, 5, DYNAMICALLY_SIZED);		//Input signal 5
    ssSetInputPortDirectFeedThrough(S, 5, 1);
    ssSetInputPortWidth(S, 6, DYNAMICALLY_SIZED);		//Input signal 6
    ssSetInputPortDirectFeedThrough(S, 6, 1);
    ssSetInputPortWidth(S, 7, DYNAMICALLY_SIZED);		//Input signal 7
    ssSetInputPortDirectFeedThrough(S, 7, 1);
    ssSetInputPortWidth(S, 8, DYNAMICALLY_SIZED);		//Input signal 8
    ssSetInputPortDirectFeedThrough(S, 8, 1);
    ssSetInputPortWidth(S, 9, DYNAMICALLY_SIZED);		//Input signal 9
    ssSetInputPortDirectFeedThrough(S, 9, 1);
    ssSetInputPortWidth(S, 10, DYNAMICALLY_SIZED);		//Input signal 10
    ssSetInputPortDirectFeedThrough(S, 10, 1);
    ssSetInputPortWidth(S, 11, DYNAMICALLY_SIZED);		//Input signal 11
    ssSetInputPortDirectFeedThrough(S, 11, 1);
    ssSetInputPortWidth(S, 12, DYNAMICALLY_SIZED);		//Input signal 12
    ssSetInputPortDirectFeedThrough(S, 12, 1);
    ssSetInputPortWidth(S, 13, DYNAMICALLY_SIZED);		//Input signal 13
    ssSetInputPortDirectFeedThrough(S, 13, 1);
    ssSetInputPortWidth(S, 14, DYNAMICALLY_SIZED);		//Input signal 14
    ssSetInputPortDirectFeedThrough(S, 14, 1);
    ssSetInputPortWidth(S, 15, DYNAMICALLY_SIZED);		//Input signal 15
    ssSetInputPortDirectFeedThrough(S, 15, 1);
    ssSetInputPortWidth(S, 16, DYNAMICALLY_SIZED);		//Input signal 16
    ssSetInputPortDirectFeedThrough(S, 16, 1);

    //Define S-function output signals
    if (!ssSetNumOutputPorts(S,26)) return;				//Number of output signals
    ssSetOutputPortWidth(S, 0, DYNAMICALLY_SIZED);		//Output signal 0
    ssSetOutputPortWidth(S, 1, DYNAMICALLY_SIZED);		//Output signal 1
    ssSetOutputPortWidth(S, 2, DYNAMICALLY_SIZED);		//Output signal 2
    ssSetOutputPortWidth(S, 3, DYNAMICALLY_SIZED);		//Output signal 3
    ssSetOutputPortWidth(S, 4, DYNAMICALLY_SIZED);		//Output signal 4
    ssSetOutputPortWidth(S, 5, DYNAMICALLY_SIZED);		//Output signal 5
    ssSetOutputPortWidth(S, 6, DYNAMICALLY_SIZED);		//Output signal 6
    ssSetOutputPortWidth(S, 7, DYNAMICALLY_SIZED);		//Output signal 7
    ssSetOutputPortWidth(S, 8, DYNAMICALLY_SIZED);		//Output signal 8
    ssSetOutputPortWidth(S, 9, DYNAMICALLY_SIZED);		//Output signal 9
    ssSetOutputPortWidth(S, 10, DYNAMICALLY_SIZED);		//Output signal 10
    ssSetOutputPortWidth(S, 11, DYNAMICALLY_SIZED);		//Output signal 11
    ssSetOutputPortWidth(S, 12, DYNAMICALLY_SIZED);		//Output signal 12
    ssSetOutputPortWidth(S, 13, DYNAMICALLY_SIZED);		//Output signal 13
    ssSetOutputPortWidth(S, 14, DYNAMICALLY_SIZED);		//Output signal 14
    ssSetOutputPortWidth(S, 15, DYNAMICALLY_SIZED);		//Output signal 15
    ssSetOutputPortWidth(S, 16, DYNAMICALLY_SIZED);		//Output signal 16
    ssSetOutputPortWidth(S, 17, DYNAMICALLY_SIZED);		//Output signal 17
    ssSetOutputPortWidth(S, 18, DYNAMICALLY_SIZED);		//Output signal 18
    ssSetOutputPortWidth(S, 19, DYNAMICALLY_SIZED);		//Output signal 19
    ssSetOutputPortWidth(S, 20, DYNAMICALLY_SIZED);		//Output signal 20
    ssSetOutputPortWidth(S, 21, DYNAMICALLY_SIZED);		//Output signal 21
    ssSetOutputPortWidth(S, 22, DYNAMICALLY_SIZED);		//Output signal 22
    ssSetOutputPortWidth(S, 23, DYNAMICALLY_SIZED);		//Output signal 23
    ssSetOutputPortWidth(S, 24, DYNAMICALLY_SIZED);		//Output signal 24

    ssSetOutputPortWidth(S, 25, DYNAMICALLY_SIZED);		//Debug output signal
    ssSetNumSampleTimes(S, 1);
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);

    if(!gHopsanCore.hasComponent("HydraulicLaminarOrifice"))
    {
        ssSetErrorStatus(S, "Error: Component libraries failed to load.");
        return;
    }

    //Load Hopsan model
    const char* hmfFilePath = "F16_DS2_W_TS.hmf";
    double startT, stopT; //Unused, but needed by Hopsan API
    pComponentSystem = gHopsanCore.loadHMFModelFile(hmfFilePath, startT, stopT);
    if (pComponentSystem==0)
    {
        while(gHopsanCore.checkMessage())
        {
            HString msg, type, tag;
            gHopsanCore.getMessage(msg, type, tag);
            ssPrintf("%s\n",msg.c_str());
        }
        ssSetErrorStatus(S,"Error could not open model: F16_DS2_W_TS.hmf");
        return;
    }
    pComponentSystem->setDesiredTimestep(0.0002);

    //Setup block mask (e.g. update icon, graphics etc for Simulink block)
    mexCallMATLAB(0, 0, 0, 0, "F16_DS2_W_TSMaskSetup"); //Run the port label script
}


static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, 0.001);
    ssSetOffsetTime(S, 0, 0.0);
}

static void mdlStart(SimStruct *S)
{
    //Update tunable parameters
    const mxArray* in;
    mwSize parsize;
    void* pBuffer=NULL;
    HString valstr;

    isOkToSimulate = pComponentSystem->checkModelBeforeSimulation();
    if (isOkToSimulate)
    {
        pComponentSystem->setNumLogSamples(0);
        pComponentSystem->disableLog();
        pComponentSystem->initialize(0,1);
    }
    else
    {
        while(gHopsanCore.checkMessage())
        {
            HString msg, type, tag;
            gHopsanCore.getMessage(msg, type, tag);
            ssPrintf("%s\n",msg.c_str());
        }
        ssSetErrorStatus(S,"Error isSimulationOk() returned False! Most likely some components could not be loaded or some connections could not be established.");
        return;
    }

    pInputNode0 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Input_Amplitude_RefAngle")->getSafeNodeDataPtr("out", 0);
    pInputNode1 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Input_Amplitude_Torque")->getSafeNodeDataPtr("out", 0);
    pInputNode2 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Input_BaseValue_RefAngle")->getSafeNodeDataPtr("out", 0);
    pInputNode3 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Input_BaseValue_Torque")->getSafeNodeDataPtr("out", 0);
    pInputNode4 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Input_Fault_Beta_Amplitude")->getSafeNodeDataPtr("out", 0);
    pInputNode5 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Input_Fault_Beta_Time")->getSafeNodeDataPtr("out", 0);
    pInputNode6 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Input_Fault_Bp_Amplitude")->getSafeNodeDataPtr("out", 0);
    pInputNode7 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Input_Fault_Bp_Time")->getSafeNodeDataPtr("out", 0);
    pInputNode8 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Input_Fault_c_leak_Amplitude")->getSafeNodeDataPtr("out", 0);
    pInputNode9 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Input_Fault_c_leak_Time")->getSafeNodeDataPtr("out", 0);
    pInputNode10 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Input_TimeEnd_RefAngle")->getSafeNodeDataPtr("out", 0);
    pInputNode11 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Input_TimeEnd_Torque")->getSafeNodeDataPtr("out", 0);
    pInputNode12 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Input_TimeStart_RefAngle")->getSafeNodeDataPtr("out", 0);
    pInputNode13 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Input_TimeStart_Torque")->getSafeNodeDataPtr("out", 0);
    pInputNode14 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Input_Valve_Fault_Amplitude_CilindA")->getSafeNodeDataPtr("out", 0);
    pInputNode15 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Input_Valve_Fault_Fixed_Position_CilindA")->getSafeNodeDataPtr("out", 0);
    pInputNode16 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Input_Valve_Fault_Time_CilindA")->getSafeNodeDataPtr("out", 0);
    pOutputNode0 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Output_Angle")->getSafeNodeDataPtr("in", 0);
    pOutputNode1 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Output_Flow_Chamber1_CilindA")->getSafeNodeDataPtr("in", 0);
    pOutputNode2 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Output_Flow_Chamber1_CilindB")->getSafeNodeDataPtr("in", 0);
    pOutputNode3 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Output_Flow_Chamber2_CilindA")->getSafeNodeDataPtr("in", 0);
    pOutputNode4 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Output_Flow_Chamber2_CilindB")->getSafeNodeDataPtr("in", 0);
    pOutputNode5 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Output_Flow_PressureLine_LeftAilC1")->getSafeNodeDataPtr("in", 0);
    pOutputNode6 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Output_Flow_PressureLine_LeftAilC2")->getSafeNodeDataPtr("in", 0);
    pOutputNode7 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Output_Flow_Tank_LeftAilC1")->getSafeNodeDataPtr("in", 0);
    pOutputNode8 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Output_Flow_Tank_LeftAilC2")->getSafeNodeDataPtr("in", 0);
    pOutputNode9 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Output_Force_CilindA")->getSafeNodeDataPtr("in", 0);
    pOutputNode10 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Output_Force_CilindB")->getSafeNodeDataPtr("in", 0);
    pOutputNode11 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Output_Position_CilindA")->getSafeNodeDataPtr("in", 0);
    pOutputNode12 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Output_Position_CilindB")->getSafeNodeDataPtr("in", 0);
    pOutputNode13 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Output_Pressure_Chamber1_CilindA")->getSafeNodeDataPtr("in", 0);
    pOutputNode14 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Output_Pressure_Chamber1_CilindB")->getSafeNodeDataPtr("in", 0);
    pOutputNode15 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Output_Pressure_Chamber2_CilindA")->getSafeNodeDataPtr("in", 0);
    pOutputNode16 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Output_Pressure_Chamber2_CilindB")->getSafeNodeDataPtr("in", 0);
    pOutputNode17 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Output_Pressure_PressureLine_LeftAilC1")->getSafeNodeDataPtr("in", 0);
    pOutputNode18 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Output_Pressure_PressureLine_LeftAilC2")->getSafeNodeDataPtr("in", 0);
    pOutputNode19 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Output_Pressure_Tank_LeftAilC1")->getSafeNodeDataPtr("in", 0);
    pOutputNode20 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Output_Pressure_Tank_LeftAilC2")->getSafeNodeDataPtr("in", 0);
    pOutputNode21 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Output_Torque")->getSafeNodeDataPtr("in", 0);
    pOutputNode22 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Output_Velocity_CilindA")->getSafeNodeDataPtr("in", 0);
    pOutputNode23 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Output_Velocity_CilindB")->getSafeNodeDataPtr("in", 0);
    pOutputNode24 = pComponentSystem->getSubComponentSystem("Left_Airleron")->getSubComponent("Output_y_servo_valve")->getSafeNodeDataPtr("in", 0);


    // Free parameter buffer memory
    if (pBuffer != NULL) {
        free(pBuffer);
    }
}


static void mdlOutputs(SimStruct *S, int_T tid)
{
    //S-function input signals
    InputRealPtrsType uPtrs1 = ssGetInputPortRealSignalPtrs(S,0);

    //S-function output signals
    real_T *y0 = ssGetOutputPortRealSignal(S,0);
    real_T *y1 = ssGetOutputPortRealSignal(S,1);
    real_T *y2 = ssGetOutputPortRealSignal(S,2);
    real_T *y3 = ssGetOutputPortRealSignal(S,3);
    real_T *y4 = ssGetOutputPortRealSignal(S,4);
    real_T *y5 = ssGetOutputPortRealSignal(S,5);
    real_T *y6 = ssGetOutputPortRealSignal(S,6);
    real_T *y7 = ssGetOutputPortRealSignal(S,7);
    real_T *y8 = ssGetOutputPortRealSignal(S,8);
    real_T *y9 = ssGetOutputPortRealSignal(S,9);
    real_T *y10 = ssGetOutputPortRealSignal(S,10);
    real_T *y11 = ssGetOutputPortRealSignal(S,11);
    real_T *y12 = ssGetOutputPortRealSignal(S,12);
    real_T *y13 = ssGetOutputPortRealSignal(S,13);
    real_T *y14 = ssGetOutputPortRealSignal(S,14);
    real_T *y15 = ssGetOutputPortRealSignal(S,15);
    real_T *y16 = ssGetOutputPortRealSignal(S,16);
    real_T *y17 = ssGetOutputPortRealSignal(S,17);
    real_T *y18 = ssGetOutputPortRealSignal(S,18);
    real_T *y19 = ssGetOutputPortRealSignal(S,19);
    real_T *y20 = ssGetOutputPortRealSignal(S,20);
    real_T *y21 = ssGetOutputPortRealSignal(S,21);
    real_T *y22 = ssGetOutputPortRealSignal(S,22);
    real_T *y23 = ssGetOutputPortRealSignal(S,23);
    real_T *y24 = ssGetOutputPortRealSignal(S,24);
    real_T *y25 = ssGetOutputPortRealSignal(S,25);

    //Read input variables from Simulink and write them to Hopsan
    (*pInputNode0) = (*uPtrs1[0]);
    (*pInputNode1) = (*uPtrs1[1]);
    (*pInputNode2) = (*uPtrs1[2]);
    (*pInputNode3) = (*uPtrs1[3]);
    (*pInputNode4) = (*uPtrs1[4]);
    (*pInputNode5) = (*uPtrs1[5]);
    (*pInputNode6) = (*uPtrs1[6]);
    (*pInputNode7) = (*uPtrs1[7]);
    (*pInputNode8) = (*uPtrs1[8]);
    (*pInputNode9) = (*uPtrs1[9]);
    (*pInputNode10) = (*uPtrs1[10]);
    (*pInputNode11) = (*uPtrs1[11]);
    (*pInputNode12) = (*uPtrs1[12]);
    (*pInputNode13) = (*uPtrs1[13]);
    (*pInputNode14) = (*uPtrs1[14]);
    (*pInputNode15) = (*uPtrs1[15]);
    (*pInputNode16) = (*uPtrs1[16]);

    //Simulate Hopsan until it reaches current Simulink time
    double time = ssGetT(S);
    pComponentSystem->simulate(time);

    //Read output variables from Hopsan and write them to Simulink
    (*y0) = (*pOutputNode0);
    (*y1) = (*pOutputNode1);
    (*y2) = (*pOutputNode2);
    (*y3) = (*pOutputNode3);
    (*y4) = (*pOutputNode4);
    (*y5) = (*pOutputNode5);
    (*y6) = (*pOutputNode6);
    (*y7) = (*pOutputNode7);
    (*y8) = (*pOutputNode8);
    (*y9) = (*pOutputNode9);
    (*y10) = (*pOutputNode10);
    (*y11) = (*pOutputNode11);
    (*y12) = (*pOutputNode12);
    (*y13) = (*pOutputNode13);
    (*y14) = (*pOutputNode14);
    (*y15) = (*pOutputNode15);
    (*y16) = (*pOutputNode16);
    (*y17) = (*pOutputNode17);
    (*y18) = (*pOutputNode18);
    (*y19) = (*pOutputNode19);
    (*y20) = (*pOutputNode20);
    (*y21) = (*pOutputNode21);
    (*y22) = (*pOutputNode22);
    (*y23) = (*pOutputNode23);
    (*y24) = (*pOutputNode24);
    (*y25) = 0; //Debugging port (unused here)

    //Read messages from Hopsan and print them
    while(gHopsanCore.checkMessage()) {
        HString msg, type, tag;
        gHopsanCore.getMessage(msg, type, tag);
        if (type != "debug") {
            ssPrintf("%s\n",msg.c_str());
        }
    }
}

static void mdlTerminate(SimStruct *S)
{
    //Execute finalize code in Hopsan at end of Simulation
    pComponentSystem->finalize();
}


 /* Simulink/Simulink Coder Interfaces */
 #ifdef MATLAB_MEX_FILE /* Is this file being compiled as a MEX-file? */
 #include "simulink.c" /* MEX-file interface mechanism */
 #else
 #include "cg_sfun.h" /* Code generation registration function */
 #endif


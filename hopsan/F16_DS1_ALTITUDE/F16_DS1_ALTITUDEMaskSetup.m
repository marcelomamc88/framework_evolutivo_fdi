set_param(gcb,'Mask','on')
set_param(gcb,'Name','F16_DS1_ALTITUDE')
set_param(gcb,'BackgroundColor','[0.721569, 0.858824, 0.905882]')
set_param(gcb,'MaskDisplay','port_label(''input'',1,''Input_Amplitude_Altitude_Manuever.''); port_label(''input'',2,''Input_TimeEnd_Altitude_Manuever.''); port_label(''input'',3,''Input_TimeStart_Altitude_Manuever.''); port_label(''input'',4,''Input_Fault_Beta_Amplitude.''); port_label(''input'',5,''Input_Fault_Beta_Time.''); port_label(''input'',6,''Input_Fault_Bp_Amplitude.''); port_label(''input'',7,''Input_Fault_Bp_Time.''); port_label(''input'',8,''Input_Fault_c_leak_Amplitude.''); port_label(''input'',9,''Input_Fault_c_leak_Time.''); port_label(''input'',10,''Input_Valve_Fault_Amplitude_CilindA.''); port_label(''input'',11,''Input_Valve_Fault_Fixed_Position_CilindA.''); port_label(''input'',12,''Input_Valve_Fault_Time_CilindA.''); port_label(''output'',1,''Output_Angle.''); port_label(''output'',2,''Output_Flow_Chamber1_CilindA.''); port_label(''output'',3,''Output_Flow_Chamber1_CilindB.''); port_label(''output'',4,''Output_Flow_Chamber2_CilindA.''); port_label(''output'',5,''Output_Flow_Chamber2_CilindB.''); port_label(''output'',6,''Output_Flow_PressureLine_LeftAilC1.''); port_label(''output'',7,''Output_Flow_PressureLine_LeftAilC2.''); port_label(''output'',8,''Output_Flow_Tank_LeftAilC1.''); port_label(''output'',9,''Output_Flow_Tank_LeftAilC2.''); port_label(''output'',10,''Output_Force_CilindA.''); port_label(''output'',11,''Output_Force_CilindB.''); port_label(''output'',12,''Output_Position_CilindA.''); port_label(''output'',13,''Output_Position_CilindB.''); port_label(''output'',14,''Output_Pressure_Chamber1_CilindA.''); port_label(''output'',15,''Output_Pressure_Chamber1_CilindB.''); port_label(''output'',16,''Output_Pressure_Chamber2_CilindA.''); port_label(''output'',17,''Output_Pressure_Chamber2_CilindB.''); port_label(''output'',18,''Output_Pressure_PressureLine_LeftAilC1.''); port_label(''output'',19,''Output_Pressure_PressureLine_LeftAilC2.''); port_label(''output'',20,''Output_Pressure_Tank_LeftAilC1.''); port_label(''output'',21,''Output_Pressure_Tank_LeftAilC2.''); port_label(''output'',22,''Output_Torque.''); port_label(''output'',23,''Output_Velocity_CilindA.''); port_label(''output'',24,''Output_Velocity_CilindB.''); port_label(''output'',25,''Output_y_servo_valve.''); port_label(''output'',26,''DEBUG'')');
set_param(gcb,'MaskPrompts',{})
set_param(gcb,'MaskVariables','')
defaultVals = {};
vals = get_param(gcb,'MaskValues')';
for i=1:length(vals)
    if strcmp(vals{i}, '[]')
        vals{i} = '';
    end
    if isempty(vals{i})
        vals{i} = defaultVals{i};
    end
end
set_param(gcb,'MaskValues', vals)

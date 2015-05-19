@echo off
REM Registering iPORT PT1000-CL Debug Components

regsvr32 /s CyUtilsComp_Dbg.dll
regsvr32 /s CyComComp_Dbg.dll
regsvr32 /s CyImgComp_Dbg.dll
regsvr32 /s CyCamComp_Dbg.dll
regsvr32 /s CyDispComp_Dbg.ocx

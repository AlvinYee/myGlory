@echo off
echo ************************************************************************
echo [INFO]: dbcModel.layoutGenerator starts
echo [version]: 1.0
echo ************************************************************************

set dbc=..\dbc\ESCL.dbc
set I2CCAN_par_h=..\output\I2CCAN_Par.h
set I2CCAN_par_c=..\output\I2CCAN_Par.c
set ESCL_NAME= ESL
if not exist %dbc% goto ErrorWrongPath
if not exist %I2CCAN_par_h% cd.> %I2CCAN_par_h%
if not exist %I2CCAN_par_c% cd.> %I2CCAN_par_c%

python MdlayoutGenerator.py %dbc% %I2CCAN_par_h% %I2CCAN_par_c% %ESCL_NAME%

goto End

:ErrorWrongPath
echo ************************************************************************
echo [ERROR]: dbc file does not exist
echo ************************************************************************

:End
echo ************************************************************************
echo [INFO]: dbcModel.layoutGenerator ends
echo ************************************************************************
pause

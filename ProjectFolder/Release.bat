if not exist Delivered_SW mkdir Delivered_SW

if exist Delivered_SW\PIC_PC070_PROJ.hex del /f  Delivered_SW\PIC_PC070_PROJ.hex
if exist Delivered_SW\PIC_PC070_PROJ.elf del /f  Delivered_SW\PIC_PC070_PROJ.elf
if exist Delivered_SW\PIC_PC070_PROJ.lst del /f  Delivered_SW\PIC_PC070_PROJ.lst
if exist Delivered_SW\PIC_PC070_PROJ.map del /f  Delivered_SW\PIC_PC070_PROJ.map
if exist Delivered_SW\PIC_PC070_PROJ.sym del /f  Delivered_SW\PIC_PC070_PROJ.sym

xcopy Workspace\PIC_PC070_PROJ.X\dist\default\production\PIC_PC070_PROJ.X.production.hex Delivered_SW\PIC_PC070_PROJ.hex*
xcopy Workspace\PIC_PC070_PROJ.X\dist\default\production\PIC_PC070_PROJ.X.production.elf Delivered_SW\PIC_PC070_PROJ.elf*
xcopy Workspace\PIC_PC070_PROJ.X\dist\default\production\PIC_PC070_PROJ.X.production.lst Delivered_SW\PIC_PC070_PROJ.lst*
xcopy Workspace\PIC_PC070_PROJ.X\dist\default\production\PIC_PC070_PROJ.X.production.map Delivered_SW\PIC_PC070_PROJ.map*
xcopy Workspace\PIC_PC070_PROJ.X\dist\default\production\PIC_PC070_PROJ.X.production.sym Delivered_SW\PIC_PC070_PROJ.sym*



@Echo Off
Echo 
Echo WELCOME TO VISHWA RELEASE SCRIPT
Echo 
Echo Please enter RELEASE Version Number
Echo Example: V1_2_3
Echo -
Echo -
Set /P "dname= Name: "


if not exist Delivered_SW\PIC_PC070_PROJ_RELEASE_%dname% mkdir Delivered_SW\PIC_PC070_PROJ_RELEASE_%dname%

xcopy Delivered_SW\PIC_PC070_PROJ.hex Delivered_SW\PIC_PC070_PROJ_RELEASE_%dname%\PIC_PC070_PROJ_%dname%.hex*
xcopy Delivered_SW\PIC_PC070_PROJ.elf Delivered_SW\PIC_PC070_PROJ_RELEASE_%dname%\PIC_PC070_PROJ_%dname%.elf*
xcopy Delivered_SW\PIC_PC070_PROJ.lst Delivered_SW\PIC_PC070_PROJ_RELEASE_%dname%\PIC_PC070_PROJ_%dname%.lst*
xcopy Delivered_SW\PIC_PC070_PROJ.map Delivered_SW\PIC_PC070_PROJ_RELEASE_%dname%\PIC_PC070_PROJ_%dname%.map*
xcopy Delivered_SW\PIC_PC070_PROJ.sym Delivered_SW\PIC_PC070_PROJ_RELEASE_%dname%\PIC_PC070_PROJ_%dname%.sym*

if exist Delivered_SW\PIC_PC070_PROJ_RELEASE_%dname%_HEX.zip del /f Delivered_SW\PIC_PC070_PROJ_RELEASE_%dname%_HEX.zip
"C:\Program Files\7-Zip\7z.exe" a Delivered_SW\PIC_PC070_PROJ_RELEASE_%dname%_HEX.zip Delivered_SW\PIC_PC070_PROJ_RELEASE_%dname%\*

REM RMDIR [/S] [/Q] [drive:]path RD [/S] [/Q] [drive:]path
REM 
REM /S      Removes all directories and files in the specified directory
REM         in addition to the directory itself.  Used to remove a directory
REM         tree.
REM 
REM /Q      Quiet mode, do not ask if ok to remove a directory tree with /S

rmdir /s /q Delivered_SW\PIC_PC070_PROJ_RELEASE_%dname%
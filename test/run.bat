del txt2shp.exe
rd /Q /S out
mkdir out
copy ..\bin\txt2shp.exe /B txt2shp.exe
txt2shp.exe -i d:\projects\txt2shp\test\in -o d:\projects\txt2shp\test\out 

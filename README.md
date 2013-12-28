#txt2shp
txt2shp is simple tool that convert x,y of text file to polygon of esri shape file. 

## Goal
This app must run in internet. And alive self without any people.

## Installation
You must install premake4 make premake4.exe in you system path. Then you type `premake4 vs2010` to generate `vs2010 project file` and `premake4 gmake` to generate `makefile` in `prj` directory. Before compile txt2shp, you make three variables in your system environment variable.

` GDAL_I is gdal's lib name. windows must be gdal_i and linux is gdal.`

` GDALINC is gdal's include directory.`

` GDALLIB is gdal's lib directory.`

then,`cd proj`,type `make config=release all` to generate txt2shp in bin/. And in windows, you open txt2shp.sln file, generate txt2shp.exe in bin/. of course, you can use msbuild.

## Getting Started
you can type txt2shp, here are some usage:

	Usage: txt2shp  -i input directory
					-o output directory
					-x the column index of x coordination 
					-y the column index of y coordination 
	
	Note:
	The column index start 0, so if the x coordination column number is 3 and y is 5,you will set x with 2 and y is 4.

	Example:
	 txt2shp -i you_dir -o you_dir -x 2 -y 4

## About
Thanks to GDAL, Git and other open source softs.

## Copyright
This app is belong to htoo. If you want to change some code, please let me know. Note you have no right to change code but you can use binary file.

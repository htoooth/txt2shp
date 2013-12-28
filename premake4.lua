-----------------------------------------
--premake4的配置文件
--生成win下vs的工程文件和GUN的makefile文件
--生成单和多进程程序
--作者：htoo
--时间：2013年12月28日
--使用方法：
--  premake4.exe --help
--win下：
--  premake4.exe vs2010
--linux下：
--  premake4.exe gmake
--  make help
--  make config=release all
--  make config=dubug all
--注意：本配置文件的只能生成vs和g++的工程文件
--      对其它IDE暂时不做支持。
-----------------------------------------

--定义路径
   
--项目工程文件路径
local prj_dir="prj/"
--生成二进制文件路径
local target_dir="bin/"

-----------------------------------------

--环境变量定义:环境变量必须设置才能使用
--gdal环境变量设置
--gdali:链接库名
local gdali=nil
--gdallib:链接库所在路径
local gdallib=nil
--gdalinc:头文件所在路径
local gdalinc=nil

-----------------------------------------
--以下这几个环境变量必顺在系统环境中设置
--GDALI:GDAL的链接库名
--GDALLIB:GDAL的链接库路径
--GDALINC:GDAL的头文件路径
-----------------------------------------
--win下环境变量设置值:$()
if os.is("windows") then
    gdali="$(GDAL_I)"
    gdallib="$(GDALLIB)"
    gdalinc="$(GDALINC)"

--linux下环境变量设置值:${}
elseif os.is("linux") then
    gdali="${GDAL_I}"
    gdalinc="${GDALINC}"
    gdallib="${GDALLIB}"

end

-----------------------------------------
--生成项目文件
--解决方案名
solution "txt2shp"

    --设置针对Debug和Release分别设置
    configurations {"Debug", "Release"}
-----------------------------------------
    --对Debug下的情况进行设置，例如定义调试符号
    configuration "Debug"

    --在gun下使用新标准
    --对生成makefile进行单独设置
    --premake4可以对生成的工程文件进行单独设置
    --如可以对vs设置：configuration "vs*"
    configuration "gmake"
        --构建工具选项 
        buildoptions {"--std=c++0x"}
        
    --对Release下的情况进行设置，例如定义除去调试符号
    --configuration "Release"
    --  defines {"NOBUG"}
-----------------------------------------

    --工程文件生成的目录    
    location(prj_dir)
-----------------------------------------
    --设置项目
    --项目名
    project "txt2shp"
        --生成二进制程序名
        targetname "txt2shp"
        --二进制文件的路径
        targetdir(target_dir) 
        --项目类型为控制台
        kind "ConsoleApp"
        --采用c++语言
        language "c++"

        --项目源文件路径
        files {"src/*.cpp","src/*.h"}

        --附加库设置
        --链接库名
        links(gdali)
        --链接库路径
        libdirs(gdallib)
        --库的路径
        includedirs(gdalinc)



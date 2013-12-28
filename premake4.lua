-----------------------------------------
--premake4�������ļ�
--����win��vs�Ĺ����ļ���GUN��makefile�ļ�
--���ɵ��Ͷ���̳���
--���ߣ�htoo
--ʱ�䣺2013��12��28��
--ʹ�÷�����
--  premake4.exe --help
--win�£�
--  premake4.exe vs2010
--linux�£�
--  premake4.exe gmake
--  make help
--  make config=release all
--  make config=dubug all
--ע�⣺�������ļ���ֻ������vs��g++�Ĺ����ļ�
--      ������IDE��ʱ����֧�֡�
-----------------------------------------

--����·��
   
--��Ŀ�����ļ�·��
local prj_dir="prj/"
--���ɶ������ļ�·��
local target_dir="bin/"

-----------------------------------------

--������������:���������������ò���ʹ��
--gdal������������
--gdali:���ӿ���
local gdali=nil
--gdallib:���ӿ�����·��
local gdallib=nil
--gdalinc:ͷ�ļ�����·��
local gdalinc=nil

-----------------------------------------
--�����⼸������������˳��ϵͳ����������
--GDALI:GDAL�����ӿ���
--GDALLIB:GDAL�����ӿ�·��
--GDALINC:GDAL��ͷ�ļ�·��
-----------------------------------------
--win�»�����������ֵ:$()
if os.is("windows") then
    gdali="$(GDAL_I)"
    gdallib="$(GDALLIB)"
    gdalinc="$(GDALINC)"

--linux�»�����������ֵ:${}
elseif os.is("linux") then
    gdali="${GDAL_I}"
    gdalinc="${GDALINC}"
    gdallib="${GDALLIB}"

end

-----------------------------------------
--������Ŀ�ļ�
--���������
solution "txt2shp"

    --�������Debug��Release�ֱ�����
    configurations {"Debug", "Release"}
-----------------------------------------
    --��Debug�µ�����������ã����綨����Է���
    configuration "Debug"

    --��gun��ʹ���±�׼
    --������makefile���е�������
    --premake4���Զ����ɵĹ����ļ����е�������
    --����Զ�vs���ã�configuration "vs*"
    configuration "gmake"
        --��������ѡ�� 
        buildoptions {"--std=c++0x"}
        
    --��Release�µ�����������ã����綨���ȥ���Է���
    --configuration "Release"
    --  defines {"NOBUG"}
-----------------------------------------

    --�����ļ����ɵ�Ŀ¼    
    location(prj_dir)
-----------------------------------------
    --������Ŀ
    --��Ŀ��
    project "txt2shp"
        --���ɶ����Ƴ�����
        targetname "txt2shp"
        --�������ļ���·��
        targetdir(target_dir) 
        --��Ŀ����Ϊ����̨
        kind "ConsoleApp"
        --����c++����
        language "c++"

        --��ĿԴ�ļ�·��
        files {"src/*.cpp","src/*.h"}

        --���ӿ�����
        --���ӿ���
        links(gdali)
        --���ӿ�·��
        libdirs(gdallib)
        --���·��
        includedirs(gdalinc)



#ifndef FORMAT_H_INCLUDE

#define FORMAT_H_INCLUDE

#include "common.h"

void RegisterVector();

void RegisterRaster();

///���ʸ����������
OGRSFDriver * GetVectorDriver(const char * pszFormat);

///��ʸ�����ݼ�
OGRDataSource * VectorOpen(const char * pszFilename,
                           GDALAccess eAccess);


///����ʸ�����ݼ�
OGRDataSource * VectorCreate(const char * pszFormat,
                             const char * pszFilename,
                             char ** papszOptions = NULL);

///�ر�ʸ�����ݼ�
void VectorClose(OGRDataSource * poDS);

///���ʸ��������Ϣ
void VectorClean();
#endif
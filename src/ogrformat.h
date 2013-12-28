#ifndef OGRFORMAT_H_INCLUDE

#define OGRFORMAT_H_INCLUDE

#include "common.h"

///ע��ʸ�����ݸ�ʽ
void RegisterVector();

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
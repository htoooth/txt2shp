#ifndef OGRFORMAT_H_INCLUDE

#define OGRFORMAT_H_INCLUDE

#include "common.h"

///注册矢量数据格式
void RegisterVector();

///获得矢量数据驱动
OGRSFDriver * GetVectorDriver(const char * pszFormat);

///打开矢量数据集
OGRDataSource * VectorOpen(const char * pszFilename,
                           GDALAccess eAccess);

///创建矢量数据集
OGRDataSource * VectorCreate(const char * pszFormat,
                             const char * pszFilename,
                             char ** papszOptions = NULL);

///关闭矢量数据集
void VectorClose(OGRDataSource * poDS);

///清除矢量数据信息
void VectorClean();

#endif
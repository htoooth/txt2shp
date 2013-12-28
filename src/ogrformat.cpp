#include "ogrformat.h"

OGRSFDriver * GetVectorDriver( const char * pszFormat ) {
	return OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName( pszFormat );
}

OGRDataSource * VectorOpen( const char * pszFilename, GDALAccess eAccess ) {
	return (OGRDataSource *)OGROpen(pszFilename, eAccess, NULL);
}

OGRDataSource * VectorCreate( const char * pszFormat, const char * pszFilename, char ** papszOptions/*=NULL*/ ) {
	OGRSFDriver * poDriver = GetVectorDriver(pszFormat);
	OGRDataSource * poOGRDataSource =
	    poDriver->CreateDataSource(pszFilename, papszOptions);

	return poOGRDataSource;
}


void RegisterVector() {
	OGRRegisterAll();
}

void VectorClose(OGRDataSource * poDS){
	OGRDataSource::DestroyDataSource(poDS);
}

void VectorClean(){
	OGRCleanupAll();
}
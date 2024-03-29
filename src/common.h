#ifndef COMMON_H_INCLUDE

#define COMMON_H_INCLUDE

#include <list>
#include <memory>

#include <cpl_vsi.h>
#include <cpl_error.h>
#include <cpl_csv.h>
#include <cpl_string.h>
#include <cpl_port.h>
#include <cpl_conv.h>

#include <ogr_api.h>
#include <ogr_feature.h>
#include <ogr_geometry.h>
#include <ogrsf_frmts.h>
#include <gdal.h>

#include "Option.h"
#include "ogrformat.h"

typedef std::shared_ptr<OGRPoint> Point;

#endif
#pragma once

#include <QrShared.hxx>
#include <QrVideoReader.hxx>
#include <QrVideoWriter.hxx>
#include <QrSnapshot.hxx>
#include <QrLogger.hxx>

#if defined(_MSC_VER)
#include "libQrCore.hpp"
#elif defined(__GNUC__)
//#include <libQrCore.hpp>
#endif


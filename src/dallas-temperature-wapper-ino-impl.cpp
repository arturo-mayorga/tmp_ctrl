#include "dallas-temperature-wapper-ino-impl.h"


void DallasTemperatureWrapperInoImpl::begin()
{
    _dallasTempDelegate->begin();
}

void DallasTemperatureWrapperInoImpl::requestTemperatures()
{
    _dallasTempDelegate->requestTemperatures();
}

float DallasTemperatureWrapperInoImpl::getTempFByIndex(int i)
{
    return _dallasTempDelegate->getTempFByIndex(i);
}

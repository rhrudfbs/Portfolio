#pragma once
#include "PLANET.h"
class SETTLLITE :
    public PLANET
{
public:
    CRect Stle_Orbit;

    void SetSor(CRect r)
    {
        Stle_Orbit = r;
    }

    CRect GetSor()
    {
        return Stle_Orbit;
    }
};


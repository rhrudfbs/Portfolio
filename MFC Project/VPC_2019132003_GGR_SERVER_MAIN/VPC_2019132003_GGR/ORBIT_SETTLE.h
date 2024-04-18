#pragma once
#include "PLANET.h"

class ORBIT_SETTLE
{
public:
	CRect Orbit;
	PLANET* P;
	CString Name;

	ORBIT_SETTLE* NEXT;

	void SetSetOrbit()
	{
		Orbit.left = P->GetPlanetLoc().left - 20;
		Orbit.right = P->GetPlanetLoc().right + 20;
		Orbit.top = P->GetPlanetLoc().top - 20;
		Orbit.bottom = P->GetPlanetLoc().bottom + 20;
	}

	CRect GetSetOrbit()
	{
		return Orbit;
	}
};


#pragma once
class ORBIT
{
public:
	CRect Orbit;
	ORBIT* NEXT;


	CRect GetOrbit()
	{
		return Orbit;
	}
};


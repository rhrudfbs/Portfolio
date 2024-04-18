#pragma once
class PLANET
{
public:
	CString Name;
	CPoint Loc_C;
	CRect Loc;
	CRect Orbit;
	int Speed;
	int Dir = 1;
	int Life = 20;
	int Radius;
	int time = 0;
	BOOL SET = FALSE;

	

	PLANET* NEXT;

	void SetPlanetLoc(/*double time*/)
	{
		double pi = 3.1415926535897932384626433832795;

		double a = (Orbit.right - Orbit.left) / 2;
		double b = (Orbit.bottom - Orbit.top) / 2;

		double cen_x = (Orbit.right + Orbit.left) / 2;
		double cen_y = (Orbit.bottom + Orbit.top) / 2;

		double radian = time * 2 * pi / (Speed * 60)/* * Dir*/;

		Loc_C.x = (LONG)(a * cos(radian) + cen_x);
		Loc_C.y = (LONG)(b * sin(radian) + cen_y);

		Loc.left = Loc_C.x - Radius;
		Loc.right = Loc_C.x + Radius;
		Loc.top = Loc_C.y - Radius;
		Loc.bottom = Loc_C.y + Radius;
	}

	void SetPlanetSize(int size)
	{
		Radius = size;
	}

	void SetPlanetDir(int D)
	{
		Dir = D;
	}

	void SetPlanetLife(int L)
	{
		Life = L;
	}

	void SetPlanetSpeed(int S)
	{
		Speed = S;
	}

	void SetPlanetName(CString name)
	{
		Name = name;
	}

	CRect GetPlanetLoc()
	{
		return Loc;
	}

	CString GetPlanetName()
	{
		return Name;
	}
};


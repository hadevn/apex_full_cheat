#pragma once

class GColor
{
public:
	GColor()
	{
		*((int *)this) = 0;
	}
	GColor(int GColor32)
	{
		*((int *)this) = GColor32;
	}
	GColor(int _r, int _g, int _b)
	{
		SetGColor(_r, _g, _b, 255);
	}
	GColor(int _r, int _g, int _b, int _a)
	{
		SetGColor(_r, _g, _b, _a);
	}

	void SetGColor(int _r, int _g, int _b, int _a = 255)
	{
		_GColor[0] = (unsigned char)_r;
		_GColor[1] = (unsigned char)_g;
		_GColor[2] = (unsigned char)_b;
		_GColor[3] = (unsigned char)_a;
	}

	void GetGColor(int &_r, int &_g, int &_b, int &_a) const
	{
		_r = _GColor[0];
		_g = _GColor[1];
		_b = _GColor[2];
		_a = _GColor[3];
	}

	void SetRawGColor(int GColor32)
	{
		*((int*)this) = GColor32;
	}

	int GetRawGColor() const
	{
		return *((int*)this);
	}

	int GetD3DGColor() const
	{
		return ((int)((((_GColor[3]) & 0xff) << 24) | (((_GColor[0]) & 0xff) << 16) | (((_GColor[1]) & 0xff) << 8) | ((_GColor[2]) & 0xff)));
	}

	inline int r() const { return _GColor[0]; }
	inline int g() const { return _GColor[1]; }
	inline int b() const { return _GColor[2]; }
	inline int a() const { return _GColor[3]; }

	unsigned char &operator[](int index)
	{
		return _GColor[index];
	}

	const unsigned char &operator[](int index) const
	{
		return _GColor[index];
	}

	bool operator == (const GColor &rhs) const
	{
		return (*((int *)this) == *((int *)&rhs));
	}

	bool operator != (const GColor &rhs) const
	{
		return !(operator==(rhs));
	}

	GColor &operator=(const GColor &rhs)
	{
		SetRawGColor(rhs.GetRawGColor());
		return *this;
	}

	float* Base()
	{
		float clr[3];

		clr[0] = _GColor[0] / 255.0f;
		clr[1] = _GColor[1] / 255.0f;
		clr[2] = _GColor[2] / 255.0f;

		return &clr[0];
	}

	float* BaseAlpha()
	{
		float clr[4];

		clr[0] = _GColor[0] / 255.0f;
		clr[1] = _GColor[1] / 255.0f;
		clr[2] = _GColor[2] / 255.0f;
		clr[3] = _GColor[3] / 255.0f;

		return &clr[0];
	}

	float Hue() const
	{
		if (_GColor[0] == _GColor[1] && _GColor[1] == _GColor[2])
		{
			return 0.0f;
		}

		float r = _GColor[0] / 255.0f;
		float g = _GColor[1] / 255.0f;
		float b = _GColor[2] / 255.0f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		float delta = max - min;
		float hue = 0.0f;

		if (r == max)
		{
			hue = (g - b) / delta;
		}
		else if (g == max)
		{
			hue = 2 + (b - r) / delta;
		}
		else if (b == max)
		{
			hue = 4 + (r - g) / delta;
		}
		hue *= 60;

		if (hue < 0.0f)
		{
			hue += 360.0f;
		}
		return hue;
	}

	float Saturation() const
	{
		float r = _GColor[0] / 255.0f;
		float g = _GColor[1] / 255.0f;
		float b = _GColor[2] / 255.0f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		float l, s = 0;

		if (max != min)
		{
			l = (max + min) / 2;
			if (l <= 0.5f)
				s = (max - min) / (max + min);
			else
				s = (max - min) / (2 - max - min);
		}
		return s;
	}

	float Brightness() const
	{
		float r = _GColor[0] / 255.0f;
		float g = _GColor[1] / 255.0f;
		float b = _GColor[2] / 255.0f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		return (max + min) / 2;
	}

	GColor FromHSB(float hue, float saturation, float brightness)
	{
		float h = hue == 1.0f ? 0 : hue * 6.0f;
		float f = h - (int)h;
		float p = brightness * (1.0f - saturation);
		float q = brightness * (1.0f - saturation * f);
		float t = brightness * (1.0f - (saturation * (1.0f - f)));

		if (h < 1)
		{
			return GColor(
				(unsigned char)(brightness * 255),
				(unsigned char)(t * 255),
				(unsigned char)(p * 255)
			);
		}
		else if (h < 2)
		{
			return GColor(
				(unsigned char)(q * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(p * 255)
			);
		}
		else if (h < 3)
		{
			return GColor(
				(unsigned char)(p * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(t * 255)
			);
		}
		else if (h < 4)
		{
			return GColor(
				(unsigned char)(p * 255),
				(unsigned char)(q * 255),
				(unsigned char)(brightness * 255)
			);
		}
		else if (h < 5)
		{
			return GColor(
				(unsigned char)(t * 255),
				(unsigned char)(p * 255),
				(unsigned char)(brightness * 255)
			);
		}
		else
		{
			return GColor(
				(unsigned char)(brightness * 255),
				(unsigned char)(p * 255),
				(unsigned char)(q * 255)
			);
		}
	}

	static GColor Red() { return GColor(255, 0, 0); }
	static GColor Green() { return GColor(0, 255, 0); }
	static GColor Blue() { return GColor(0, 0, 255); }
	static GColor LightBlue() { return GColor(100, 100, 255); }
	static GColor Grey() { return GColor(128, 128, 128); }
	static GColor DarkGrey() { return GColor(45, 45, 45); }
	static GColor Black() { return GColor(0, 0, 0); }
	static GColor White() { return GColor(255, 255, 255); }
	static GColor Purple() { return GColor(220, 0, 220); }
	static GColor Yellow() { return GColor(255, 255, 0); }
	static GColor Orange() { return GColor{ 255, 128, 64 }; }
	static GColor Pink() { return GColor{ 255, 128, 255 }; }
	static GColor SkyBlue() { return GColor{ 0, 255, 255 }; }
	static GColor Orange2() { return GColor{ 255, 128, 0 }; }

private:
	unsigned char _GColor[4];
};

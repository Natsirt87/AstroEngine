#pragma once

namespace conv
{
	constexpr double PIXELS_PER_METERS = 64.0;
	constexpr double PI = 3.14159265358979323846;

	template<typename T>
	constexpr T PTM(const T& x) { return x / PIXELS_PER_METERS; }; //Pixels to meters

	template<typename T>
	constexpr T MTP(const T& x) { return x * PIXELS_PER_METERS; }; //Meters to pixels

	template<typename T>
	constexpr T DTR(const T& x) { return PI * x / 180.0; }; //Degrees to radians

	template<typename T>
	constexpr T RTD(const T& x) { return 180.0 * x / PI; }; //Radians to degrees
}


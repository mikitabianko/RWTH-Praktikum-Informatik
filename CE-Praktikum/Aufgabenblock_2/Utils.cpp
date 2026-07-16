#include "Utils.h"

bool bIsGleich(double dA, double dB, double dEpsilon) {
    return std::fabs(dA - dB) < dEpsilon;
}
//
//  ADSR.cpp
//
//  Created by Nigel Redmon on 12/18/12.
//  EarLevel Engineering: earlevel.com
//  Copyright 2012 Nigel Redmon
//
//  For a complete explanation of the ADSR envelope generator and code,
//  read the series of articles by the author, starting here:
//  http://www.earlevel.com/main/2013/06/01/envelope-generators/
//
//  License:
//
//  This source code is provided as is, without warranty.
//  You may copy and distribute verbatim copies of this document.
//  You may modify and use this source code to create binary code for your own purposes, free or commercial.
//
//  1.01  2016-01-02  njr   added calcCoefs to SetTargetRatio functions that were in the ADSR widget but missing in this code
//

#include "ADSR.h"
#include <math.h>


ADSR::ADSR(void) {
    reset();
    setAttackRate(0);
    setDecayRate(0);
    setReleaseRate(0);
    setSustainLevel(1.0);
    setTargetRatioA(0.3);
    setTargetRatioDR(0.0001);
}

ADSR::~ADSR(void) {
}

void ADSR::setAttackRate(float rate) {
    attackRate = rate;
    attackCoef = calcCoef(rate, targetRatioA);
    attackBase = (1.0 + targetRatioA) * (1.0 - attackCoef);
}

float ADSR::getAttackRate() {
    return this->attackRate;
}

void ADSR::setDecayRate(float rate) {
    decayRate = rate;
    decayCoef = calcCoef(rate, targetRatioDR);
    decayBase = (sustainLevel - targetRatioDR) * (1.0 - decayCoef);
}

float ADSR::getDecayRate() {
    return this->decayRate;
}

void ADSR::setReleaseRate(float rate) {
    releaseRate = rate;
    releaseCoef = calcCoef(rate, targetRatioDR);
    releaseBase = -targetRatioDR * (1.0 - releaseCoef);
}

float ADSR::getReleaseRate() {
    return this->releaseRate;
}

float ADSR::calcCoef(float rate, float targetRatio) {
    return exp(-log((1.0 + targetRatio) / targetRatio) / rate);
}

void ADSR::setSustainLevel(float level) {
    sustainLevel = level;
    decayBase = (sustainLevel - targetRatioDR) * (1.0 - decayCoef);
}

float ADSR::getSustainLevel() {
    return this->sustainLevel;
}

void ADSR::setTargetRatioA(float targetRatio) {
    if (targetRatio < 0.000000001)
        targetRatio = 0.000000001;  // -180 dB
    targetRatioA = targetRatio;
    attackCoef = calcCoef(attackRate, targetRatioA);
    attackBase = (1.0 + targetRatioA) * (1.0 - attackCoef);
}

void ADSR::setTargetRatioDR(float targetRatio) {
    if (targetRatio < 0.000000001)
        targetRatio = 0.000000001;  // -180 dB
    targetRatioDR = targetRatio;
    decayCoef = calcCoef(decayRate, targetRatioDR);
    releaseCoef = calcCoef(releaseRate, targetRatioDR);
    decayBase = (sustainLevel - targetRatioDR) * (1.0 - decayCoef);
    releaseBase = -targetRatioDR * (1.0 - releaseCoef);
}

#pragma once


void WASDPush(float& theta, float& moveX, float& moveY, float& speed);

void HitPlayerFanction
(
    float& CernterX, float& CernterY,
    int radious,
    float& LeToX, float& LeToY,
    float& RiToX, float& RiToY,
    float& LeBoX, float& LeBoY,
    float& RiBoX, float& RiBoY
);

void BarrierPosfanction
(
    float& BarrierTheta,
    float& PlayerPosX, float& PlayerPosY,
    float& BarrierPosX, float& BarrierPosY
);

void HitBoxFanction(
    int radious,
    float& centerX, float& centerY,
    float& LeToX, float& LeToY,
    float& RiToX, float& RiToY,
    float& LeBoX, float& LeBoY,
    float& RiBoX, float& RiBoY
);




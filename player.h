#pragma once
void WASDPush(float& theta, float& moveX, float& moveY, float& speed);

void BarrierPosfanction
(
    float& BarrierTheta,
    float& PlayerPosX, float& PlayerposY,
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
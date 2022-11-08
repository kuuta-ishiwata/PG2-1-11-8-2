#include<Novice.h>
#include<stdio.h>

#define _USE_MATH_DEFINES
#include<math.h>

void WASDPush(float& theta,float& moveX,float& moveY,float& speed)
{
    moveX = cosf(theta);
    moveY = sinf(theta);

    moveX *= speed;
    moveY *= speed;

}


void HitPlayerFanction
(
    float& CernterX,float& CernterY,
    int radious,
    float& LeToX, float& LeToY,
    float& RiToX, float& RiToY,
    float& LeBoX, float& LeBoY,
    float& RiBoX, float& RiBoY
)
{





}

void BarrierPosfanction
(
    float &BarrierTheta,
    float &PlayerPosX,float &PlayerPosY,
    float &BarrierPosX,float &BarrierPosY
)
{
    BarrierTheta += 0.1f;

    int X = (75 * cosf(BarrierTheta) - 75 * sinf(BarrierTheta));
    int Y = (75 * cosf(BarrierTheta) + 75 * sinf(BarrierTheta));

    X += PlayerPosX+33;
    Y += PlayerPosY+33;
   
    BarrierPosX = X;
    BarrierPosY = Y;
}

void HitBoxFanction(
    int radious,
    float& centerX, float& centerY,
    float& LeToX, float& LeToY,
    float& RiToX, float& RiToY,
    float& LeBoX, float& LeBoY,
    float& RiBoX, float& RiBoY
)
{

    LeToX = centerX - radious;
    LeToY = centerY - radious;

    RiToX = centerX + radious;
    RiToY = centerY - radious;

    LeBoX = centerX - radious;
    LeBoY = centerY + radious;

    RiBoX = centerX + radious;
    RiBoY = centerY + radious;

};
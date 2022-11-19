#include<Novice.h>
#include<stdio.h>
#define USE_MATH_DEFINES
#include<math.h>


void BossMoveFanction(float& theta, float& moveX, float& moveY, float& speed)
{
  


    moveX = cosf(theta);
    moveY = sinf(theta);

    moveX *= speed;
    moveY *= speed;



}



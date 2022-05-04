#ifndef spiderMove_h
#define spiderMove_h

#include "Arduino.h"
#include "Servo.h"

class SpiderMove
{
  public: 
    SpiderMove(int servoConection[8]);
    void forward();
    void backward();
    void dead();
    void rest();

    bool leftAction(bool flag);
    bool rightAction(bool flag);
 
 private:
    float angleCompfilter(float targetAngle, float lastAngle, float alpha = 0.002);
    bool legsDownLeft();
    bool legsDownRight();
    
    float angleLegUp = 20.0;
    float angleLegDown = 90.0;
    float angleRotForward = 130.0;
    float angleRotMid = 90.0;
    float angleRotBackward = 50.0;
    float lastLegAngle = 40.0;
    float lastRotAngle = 90.0;
    bool forwardDownSkift = false;
    bool isRightMoveing = false;

    Servo leg0;
    Servo leg1;
    Servo leg2;
    Servo leg3;
    Servo leg4;
    Servo leg5;
    Servo rot0;
    Servo rot1;
};

#endif 

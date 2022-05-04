#include"spiderMove.h"
#include<Servo.h>

SpiderMove::SpiderMove(int servoConnection[8]){
  leg0.attach(servoConnection[0]);
  leg1.attach(servoConnection[1]);
  leg2.attach(servoConnection[2]);
  leg3.attach(servoConnection[3]);
  leg4.attach(servoConnection[4]);
  leg5.attach(servoConnection[5]);
  rot0.attach(servoConnection[6]);
  rot1.attach(servoConnection[7]);

}

float SpiderMove::angleCompfilter(float targetAngle, float lastAngle, float alpha){
  float calcAngle = ((1-alpha)*lastAngle)+(alpha*targetAngle);
  return calcAngle;
}

void SpiderMove::forward(){
  if (isRightMoveing == false){
    if (forwardDownSkift == false){
      isRightMoveing = leftAction(true);
      Serial.println("Left Action");
    } else {
      isRightMoveing = legsDownLeft();
      Serial.println("Left Down");
    }
  } else {
    if (forwardDownSkift == true){
      isRightMoveing = rightAction(true);
      Serial.println("Right Action");
    } else {
      isRightMoveing = legsDownRight();
      Serial.println("Right Down");
    }
  }
}

void SpiderMove::backward(){
  if (isRightMoveing == false){
    if (forwardDownSkift == false){
      isRightMoveing = leftAction(false);
    } else {
      isRightMoveing = legsDownLeft();
    }
  } else {
    if (forwardDownSkift == true){
      isRightMoveing = rightAction(false);
    } else {
      isRightMoveing = legsDownRight();
    }
  }
}

void SpiderMove::dead(){
  float angleToSet = angleCompfilter(angleLegUp, lastLegAngle);
  float rotToSet = angleCompfilter(angleRotMid, lastRotAngle);

  leg0.write(angleToSet);
  leg1.write(angleToSet);
  leg2.write(angleToSet);
  leg3.write(angleToSet);
  leg4.write(angleToSet);
  leg5.write(angleToSet);
  rot0.write(angleToSet);

  lastLegAngle = angleToSet;
  lastRotAngle = rotToSet;
}

void SpiderMove::rest(){
  float angleToSet = angleCompfilter(angleLegDown, lastLegAngle);
  float rotToSet = angleCompfilter(angleRotMid, lastRotAngle);

  leg0.write(angleToSet);
  leg1.write(angleToSet);
  leg2.write(angleToSet);
  leg3.write(angleToSet);
  leg4.write(angleToSet);
  leg5.write(angleToSet);
  rot0.write(angleToSet);

  lastLegAngle = angleToSet;
  lastRotAngle = rotToSet;
}

bool SpiderMove::leftAction(bool flag){
  float angleToSet = angleCompfilter(angleLegUp, lastLegAngle);
  float rotToSet;
  if (flag == true){
    rotToSet = angleCompfilter(angleRotForward, lastRotAngle);
  } else {
    rotToSet = angleCompfilter(angleRotBackward, lastRotAngle);
  }

  leg1.write(angleToSet);
  leg2.write(angleToSet);
  leg5.write(angleToSet);
  rot0.write(rotToSet);
  rot1.write(rotToSet);
  
  lastLegAngle = angleToSet;
  lastRotAngle = rotToSet;
  if (lastRotAngle >= angleRotForward - 0.5){
    forwardDownSkift = true;
    return false;
  } else {
    return false;
  }
}

bool SpiderMove::rightAction(bool flag){
  float angleToSet = angleCompfilter(angleLegUp, lastLegAngle);
  float rotToSet;
  if (flag == true){
    rotToSet = angleCompfilter(angleRotBackward, lastRotAngle);
  } else {
    rotToSet = angleCompfilter(angleRotForward, lastRotAngle);
  }

  leg0.write(angleToSet);
  leg3.write(angleToSet);
  leg4.write(angleToSet);
  rot0.write(rotToSet);
  rot1.write(rotToSet);
  
  lastLegAngle = angleToSet;
  lastRotAngle = rotToSet;
  if (lastRotAngle <= angleRotBackward + 0.5){
    forwardDownSkift = false;
    return true;
  } else {
    return true;
  }
}

bool SpiderMove::legsDownLeft(){
  float angleToSet = angleCompfilter(angleLegDown, lastLegAngle);

  leg1.write(angleToSet);
  leg2.write(angleToSet);
  leg5.write(angleToSet);

  lastLegAngle = angleToSet;
  if (lastLegAngle <= angleLegDown - 0.5){
    return false;
  } else {
    return true;
  }
}

bool SpiderMove::legsDownRight(){
  float angleToSet = angleCompfilter(angleLegDown, lastLegAngle);

  leg0.write(angleToSet);
  leg3.write(angleToSet);
  leg4.write(angleToSet);

  lastLegAngle = angleToSet;
  if (lastLegAngle <= angleLegDown - 0.5){
    return true;
  } else {
    return false;
  }
}

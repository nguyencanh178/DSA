/*
    EC CHALLENGE 2024

    CREATED: NGUYEN DUC CANH 8 2024
    PROCESSOR: ARDUINO NANO - CH340P
*/

#include <Leanbot.h>

void setup(){
    Leanbot.begin();
    LbIRLine.doManualCalibration(TB1A);
    LbIRLine.doManualCalibration(TB1B);
    LbIRLine.doManualCalibration(TB2A);
    LbGripper.close();
}

void loop(){
    LbMission.begin();

    do{
        followline();
    }
    vatcan1();
    co2();
    len_thang();
    cuu_hoa();
    ong_tuot();
    roomA();
    nan_nhan();
    xuong_thang();
    follow_wall();

    while (LbMission.isBlackDetected());

    LbMission.end();
}

void followline(){
    for (int i = 0; i < 30; i++) {        
    runline();
    if ( LbIRLine.isBlackDetected() ) {
      break;
    }
    if(!LbIRLine.isBlackDetected()){ // k thay line den thi di chuyen them 10cm
        LbMotion.runLR(1000, 1000);
        LbMotion.waitDistanceMm(100);
    }
    LbMotion.waitDistanceMm(1);
  }
}

void runline(){
    byte lineValue = LbIRLine.read();      // Read the value of 4 line sensors
    LbIRLine.displayOnRGB(CRGB::DarkCyan); // Display the result on RGB Leds for observation
 
  switch (lineValue) {                   // check the position of the black line relative to Leanbot
    case 0b0100:                         // .o.. - if the black line off to the left
    case 0b1110:                         // ooo.
      LbMotion.runLR(0, +1000);         //        turn left
      break;

    case 0b1100:                         // oo..
    case 0b1000:                         // o...
      LbMotion.runLR(-1000, +1000);    //        spin left
      break;

    case 0b0010:                         // ..o. - if the black line off to the right
    case 0b0111:                         // .ooo
      LbMotion.runLR(+1000, 0);         //        turn right
      break;

    case 0b0011:                         // ..oo
    case 0b0001:                         // ...o
      LbMotion.runLR(+1000, -1000);    //        spin right
      break;

    default:                             // all other cases
      LbMotion.runLR(+1000, +1000);    //        go straight
  }
}

void vatcan1(){
    while(1){
        followline();
        long distance = Leanbot.pingCm();

        if (distance == 3){
            LbMotion.runLR(1000, -1000);
            LbMotion.waitRotationDeg(45);
            LbMotion.runLR(1000, 1000);
            LbDelay(4000);
            LbMotion.runLR(-1000, 1000);
            LbMotion.waitRotationDeg(45);
            LbMotion.runLR(1000, 1000);
            LbDelay(4000);
            break;
        }
    }
}

void co2(){
    while(1){
        followline();
        long distance = Leanbot.pingCm();

        if (distance == 2){
            LbGripper.open();
            delay(1000);
            LbGripper.close();
            break;
        }
        LbMotion.runLR(-1000, 1000);
        LbMotion.waitRotationDeg(90);
        LbMotion.runLR(1000, 1000);
        LbDelay(3000);
    }
}

void len_thang(){
    while(1){
        followline();
        while(LbMotion.waitDistanceMm(200)){
            LbMotion.runLR(-1000, 1000);
            LbMotion.waitRotationDeg(90);
        }
        break;
    }
}

void cuu_hoa(){
    while(1){
        followline();
        while (LbMotion.waitDistanceMm(287)){
            LbMotion.runLR(-1000, 1000);
            LbMotion.waitRotationDeg(90);
        }
        while(LbMotion.waitDistanceMm(235)){
            LbGripper.open();
            LbMotion.runLR(-1000, 1000);
            LbMotion.waitRotationDeg(180);
        }
        break;
    }
}

void ong_tuot(){
    while(1){
        followline();
        while(LbMotion.waitDistanceMm(515)){
            LbGripper.close();
        }
        LbMotion.runLR(-1000, 1000);
        LbMotion.waitRotationDeg(180);
        break;
    }
}

void roomA(){
    while(1){
        followline();
        while(LbMotion.waitDistanceMm(416)){
            LbMotion.runLR(-1000, 1000);
            LbMotion.waitRotationDeg(90);
        }
        LbGripper.open();
        delay(1000);
        LbGripper.close();
        break;
    }
}

void nan_nhan(){
    while(1){
        followline();
        while(LbMotion.waitDistanceMm(100)){
            LbMotion.runLR(-1000, 1000);
            LbMotion.waitRotationDeg(90);
        }
        long distance = LbMotion.getDistanceMm();

        if (distance == 416){
            LbGripper.open();
            delay(1000);
            LbGripper.close();
            delay(1000);
            LbMotion.runLR(-1000, 1000);
            LbMotion.waitRotationDeg(180);
            break;
        }
    }
}

void xuong_thang(){
    while(1){
        followline()

        while (LbMotion.waitDistanceMm(279)){
            LbMotion.runLR(1000, -1000);
            LbMotion.waitRotationDeg(90);
        }

        long distance = LbMotion.getDistanceMm();
        if (distance == 660){
            LbMotion.runLR(1000, -1000);
            LbMotion.waitRotationDeg(90);
            break;
        }
    }
}

void follow_wall(){
    int left_value = LbIIRArray.read(ir4L);
    int right_value = LbIRArray.read(ir5R);

    int diff = left_value - right_value;

    if (diff > 200){
        LbMotion.runLR(0, 1000);
    }
    else if (diff < -200){
        LbMotion.runLR(1000, 0);
    }
    else{
        LbMotion.runLR(1000, 1000);
    }
}
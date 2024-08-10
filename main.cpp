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
    nan_nhan();
    ong_tuot();
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

    // case 0b1100:                         // oo..
    // case 0b1000:                         // o...
    //   LbMotion.runLR(-1000, +1000);    //        spin left
    //   break;

    case 0b0010:                         // ..o. - if the black line off to the right
    case 0b0111:                         // .ooo
      LbMotion.runLR(+1000, 0);         //        turn right
      break;

    // case 0b0011:                         // ..oo
    // case 0b0001:                         // ...o
    //   LbMotion.runLR(+1000, -1000);    //        spin right
    //   break;

    default:                             // all other cases
      LbMotion.runLR(+1000, +1000);    //        go straight
  }
}

void vatcan1(){
    while(1){
        followline(); // dò line ban đầu
        long distance = Leanbot.pingCm();

        if (distance == 3){ // khi thấy vật cản cách 3cm
            LbMotion.runLR(1000, -1000); // rẽ phải 65 độ
            LbMotion.waitRotationDeg(65);
            LbMotion.stopAndWait(); // rẽ xong thì dừng lại 
            LbMotion.runLR(1000, 1000); // xong đi thẳng 
            LbDelay(3000); // đi trong 3s
            LbMotion.runLR(-1000, 1000); // sau 3s thì rẽ trái 65 độ
            LbMotion.waitRotationDeg(65);
            LbMotion.stopAndWait(); // rẽ xong dừng lại
            LbMotion.runLR(1000, 1000); // đi thẳng
            LbDelay(3000); // đi trong 3s
            LbMotion.runLR(-1000, 1000); // tương tự như trên
            LbMotion.waitRotationDeg(65);
            LbMotion.stopAndWait();
            LbMotion.runLR(1000, 1000);
            LbDelay(3000);
            LbMotion.runLR(1000, -1000); // rẽ phải 65 độ vào line sang CO2
            LbMotion.waitRotationDeg(65);
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
            break;
        }
        break;
    }
}

/*
    đặt bình xong quay ra check 2 room nếu room nào có thì đi lùi đẩy ống 
    và quay 180* r thả nạn nhân
*/

void cuu_hoa(){
    while(1){
        followline();
        while (LbMotion.waitDistanceMm(870)){
            LbMotion.runLR(-1000, 1000);
            LbMotion.waitRotationDeg(90);
            break;
        }
        while(LbMotion.waitDistanceMm(235)){
            LbGripper.open();
            LbMotion.runLR(-1000, -1000);
            LbMotion.waitDistanceMm(100);
            LbMotion.stopAndWait();
            LbMotion.runLR(-1000, 1000);
            LbMotion.waitDistanceDeg(90);
            break;
            // LbMotion.runLR(-1000, -1000);
            // LbMotion.waitRotationDeg(180);
        }
        break;
    }
}

void nan_nhan(){
    while (){
        int d = Leanbot.pingCm(); // khoảng cách cảm biến nhận số Cm
// hướng leanbot đang hướng về bên room A
        if (d >= 9){ // nếu khoảng cách lớn hơn hoặc = 9 thì 
            followline(); // đi theo line
            LbMotion.waitDistanceMm(100); // chờ khi đi đc 100 mm = 10cm
            LbMotion.stopAndWait(); // dừng lại chờ lệnh
            LbGripper.close(); // đóng tay servo gắp nạn nhân
            LbMotion.runLR(-1000, -1000); // đi lùi
            LbMotion.waitDistanceMm(-100); // chờ khi đi đc 10 cm
            LbMotion.stopAndWait(); // dừng lại
            LbMotion.runLR(-1000, 1000); // quay trái
            LbMotion.waitRotationDeg(90); // một góc 90 độ
        }
        else{ // nếu k có thì quay sang room B
            LbMotion.runLR(1000, -1000); // quay phải
            LbMotion.waitRotationDeg(180); // góc 180 độ
            followline(); // đi theo line
            LbMotion.waitDistanceMm(100); // khi đi đc 10 cm
            LbGripper.close();// thì gắp nạn nhân bên room B
            LbMotion.runLR(-1000, -1000); // đi lùi
            LbMotion.waitDistanceMm(-100); // chờ khi lùi đc 10 cm
            LbMotion.stopAndWait(); // dừng lại
            LbMotion.runLR(1000, -1000); // quay phải 90 độ
            LbMotion.waitRotationDeg(90);
        }
        break;
    }
}

void ong_tuot(){
    while(1){
        LbMotion.runLR(-1000, -1000); // khi quay đc 90 xong thì đi lùi
        while(LbMotion.waitDistanceMm(-515)){ // khi nào đi lùi đc 51,5 cm
            LbMotion.runLR(-1000, 1000); // quay 180 độ
            LbMotion.waitRotationDeg(180);
            LbGripper.open(); // thả nạn nhân xuống ống
            break;
        }
        LbMotion.runLR(-1000, 1000); // quay đầu leanbot
        LbMotion.waitRotationDeg(180);
        LbMotion.stopAndWait();
        followline();
        LbMotion.waitDistanceMm(279); // chờ khi đi đc 27,9 cm thì rẽ phải 90 độ 
        LbMotion.runLR(1000, -1000); // để xuống thang
        LbMotion.waitDistanceMm(90);
        break;
    }
}


void xuong_thang(){
    while(1){
        followline()

        while (LbMotion.waitDistanceMm(870)){
            LbMotion.runLR(1000, -1000);
            LbMotion.waitRotationDeg(90);
            break;
        }
        followline();
        while(LbMotion.waitDistance(168)){
            LbMotion.runLR(-1000, 1000);
            LbMotion.waitDistanceMm(90);
            break;
        }
        break;
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
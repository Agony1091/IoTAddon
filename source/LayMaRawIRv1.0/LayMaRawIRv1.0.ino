/* Authors: Nhat, Nga, Tuan, Muoi/ Tutors: Hoang Anh, Dinh
   Device: RAW IR receiver - Data to SerialMonitor
   Module: HS0038B/ChungHop Remote
   Version: 1.2 */

#include <IRremote.h>

// Pin declaration
int RECV_PIN = 11;
int opto1nutONOFF = 3;
int opto2nutMODE = 4;
int opto3nutWIND = 5;
int opto4nutUP = 6;
int opto5nutDOWN = 7;
// Temporary variables
int giatri = 0;
int t=2000;             // Thoi gian dap ung nhan nut dieu khien
int test = 0;           // Kiem tra dieu kien nhiet do

// State variable
byte ONOFF = 0;
byte mode=4;
byte wind=0;
byte nhietdo=16;
// Call function
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  for(byte i=3;i<=8;i++){                                               //khai báo đầu ra là output
    pinMode(i, OUTPUT);
  }
}

// Dumps out the decode_results structure.
// Call this after IRrecv::decode()
// void * to work around compiler issue
// void dump(void *v) {
// decode_results *results = (decode_results *)v

void dump(decode_results *results) {
  int count = results->rawlen;
  Serial.print("Raw (");
  Serial.print(count-1, DEC);
  Serial.print("): ");
  int t=2000;
  
  for (int i = 1; i < count; i++) {
    if ((i % 2) == 1) {
      Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
    } 
    else {
      Serial.print(-(int)results->rawbuf[i]*USECPERTICK, DEC);
    }
    Serial.print(" ");
  }
}

void hienthi() {                                                //tạo chương trình con hiển thị
  if (irrecv.decode(&results)) {  
    dump(&results);
    irrecv.resume(); // Receive the next value
  }
  Serial.print(ONOFF);Serial.print(" ");
  Serial.print(mode);Serial.print(" ");
  Serial.print(wind);Serial.print(" ");
  Serial.print(nhietdo);Serial.print(" ");                
  Serial.println("");
}

void loop() {
  /* Bien trang thai luu o cuoi mang Raw [ONOFF,Mode,wind,nhietdo]
   *  ONOFF: 0 la dang van hanh, 1 la bat dieu hoa
   *  Mode: che do dieu hoa, Auto: 0, Lam mat: 1; Lam kho: 2; Quat gio: 3; Suoi: 4
   *    Mode = 2; che do gio luon o Auto, wind = 0
   *    Mode = 4; nhiet do khong hien thi
   *  wind: che do gio, Auto: 0, Cap 1: 1; Cap 2: 2; Cap 3: 3
   *  nhietdo: nhietdo dieu hoa, nhiet do dao dong tu 16 - 30
   *  Luu y truoc khi chay code: 
   *  Can set che do Mode ve che do quat gio, che do gio ve auto, nhiet do ve 16 do, dieu khien dieu hoa dang o che do van hanh
   */
  if(giatri<1){
  delay(10000);
  // Lay ma OFF
  digitalWrite(opto1nutONOFF, HIGH);                      //nhấn ONOFF
  delay(t); hienthi();
  digitalWrite(opto1nutONOFF, LOW);                       //nhả ONOFF
  delay(t);
  // Bat tro lai
  digitalWrite(opto1nutONOFF, HIGH);                      //nhấn ON
  delay(t);
  digitalWrite(opto1nutONOFF, LOW);                       //nhả ON
  delay(t);
  // Dieu chinh Mode
  for(mode=0;mode<5;mode++){
   if(mode==0){
   digitalWrite(opto2nutMODE, HIGH);                       //nhấn MODE   
   delay(t);hienthi();                                     //hiển thị mã raw
   digitalWrite(opto2nutMODE, LOW);                        //nhả MODE
   delay(t);
   digitalWrite(opto1nutONOFF, HIGH);                      //nhấn OFF
   delay(t);
   digitalWrite(opto1nutONOFF, LOW);                       //nhả OFF
   delay(t);
   ONOFF = 1;
   digitalWrite(opto1nutONOFF, HIGH);                      //nhấn ON
   delay(t); hienthi();
   digitalWrite(opto1nutONOFF, LOW);                       //nhả ON
   ONOFF = 0;
   // Dieu chinh nut gio
       for(wind=3;wind>=0;wind--)                                   //các chế độ tốc độ gió khác nhau
        {
          digitalWrite(opto3nutWIND, HIGH);                       //nhấn WIND
          delay(t);hienthi();                                     //hiển thị trạng thái
          digitalWrite(opto3nutWIND, LOW);                              //nhả WIND
          delay(t);
          digitalWrite(opto1nutONOFF, HIGH);                      //nhấn OFF
          delay(t);
          digitalWrite(opto1nutONOFF, LOW);                       //nhả OFF
          delay(t);
          ONOFF = 1;
          digitalWrite(opto1nutONOFF, HIGH);                      //nhấn ON
          delay(t); hienthi();
          digitalWrite(opto1nutONOFF, LOW);                       //nhả ON
          ONOFF = 0;
          delay(t);
          test = 1;
          // Dieu chinh nhiet do
          if (nhietdo==16 && test==1){  
            for(nhietdo=17;nhietdo<=30;nhietdo++)
              {
                digitalWrite(opto4nutUP, HIGH);                         //nhấn UP
                delay(t);hienthi();                                     
                digitalWrite(opto4nutUP, LOW);                          //nhả UP
                delay(t);
                digitalWrite(opto1nutONOFF, HIGH);                      //nhấn OFF
                delay(t);
                digitalWrite(opto1nutONOFF, LOW);                       //nhả OFF
                ONOFF = 1;
                delay(t);
                digitalWrite(opto1nutONOFF, HIGH);                      //nhấn ON
                delay(t); hienthi();
                digitalWrite(opto1nutONOFF, LOW);                       //nhả ON
                ONOFF = 0;
                delay(t);
              }
              test = 0; 
          }
          else if (nhietdo==30 && test==1){
                for(nhietdo=29;nhietdo>=16;nhietdo--){
                  digitalWrite(opto4nutUP, HIGH);                         //nhấn UP
                  delay(t);hienthi();                                     
                  digitalWrite(opto4nutUP, LOW);                          //nhả UP
                  delay(t);
                  digitalWrite(opto1nutONOFF, HIGH);                      //nhấn OFF
                  delay(t);
                  digitalWrite(opto1nutONOFF, LOW);                       //nhả OFF
                  ONOFF = 1;
                  delay(t);
                  digitalWrite(opto1nutONOFF, HIGH);                      //nhấn ON
                  delay(t); hienthi();
                  digitalWrite(opto1nutONOFF, LOW);                       //nhả ON
                  ONOFF = 0;
                  delay(t);
                }
                test = 0;
          }
          else {
            Serial.print("Loi!!! Nhiet do khong bang 16 hoac 30 do");
          }          
        }
  }
  }
  giatri = 2;
  }
}




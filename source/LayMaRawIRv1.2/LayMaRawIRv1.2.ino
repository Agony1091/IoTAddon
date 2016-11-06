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
// int t=500;             // Thoi gian dap ung nhan nut dieu khien
int test = 0;              // Kiem tra dieu kien nhiet do

// State variable
int ONOFF = 0;
int mode=4;
int wind=0;
int nhietdo=16;
// Call function
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  for(byte i=3;i<9;i++){                                               //khai báo đầu ra là output
    pinMode(i, OUTPUT);
    digitalWrite(i,LOW);
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
void delay_ms(unsigned int t)
{
  unsigned int prev,now;
  prev = millis();
  now = millis();
  while (now-prev<t){
    now = millis();
  }
}
void loop() {
  delay_ms(5000);
  /*  Bien trang thai luu o cuoi mang Raw [ONOFF,Mode,wind,nhietdo]
   *  ONOFF: 0 la dang van hanh, 1 la bat dieu hoa
   *  Mode: che do dieu hoa, Auto: 0, Lam mat: 1; Lam kho: 2; Quat gio: 3; Suoi: 4
   *  wind: che do gio, Auto: 0, Cap 1: 1; Cap 2: 2; Cap 3: 3
   *  nhietdo: nhietdo dieu hoa, nhiet do dao dong tu 16 - 30
   *  Luu y truoc khi chay code: 
   *  Can set che do Mode ve che do quat gio, che do gio ve tu dong, nhiet do ve 16 do, dieu khien dieu hoa dang o che do van hanh
   */
  if(giatri<1){
  delay_ms(5000);
  
  // Lay ma OFF
  digitalWrite(opto1nutONOFF, HIGH);                       //nhấn ONOFF
  delay_ms(500); 
  digitalWrite(opto1nutONOFF, LOW);hienthi();              //nhả ONOFF
  delay_ms(500);
  // Bat tro lai
  digitalWrite(opto1nutONOFF, HIGH);                       //nhấn ON
  delay_ms(500);
  digitalWrite(opto1nutONOFF, LOW);irrecv.resume();        //nhả ON
  delay_ms(500);
  
  // Dieu chinh Mode,
  for(mode=0;mode<5;mode++){
    digitalWrite(opto2nutMODE, HIGH);                       //nhấn MODE   
    delay_ms(500);                                          
    digitalWrite(opto2nutMODE, LOW);irrecv.resume();        //nhả MODE khong hiển thị mã raw, do trong khi chay du lieu nhiet do da luu roi
    delay_ms(500);
/*  digitalWrite(opto2nutMODE, HIGH);                       //nhấn MODE   
    delay_ms(500);                                          
    digitalWrite(opto2nutMODE, LOW);hienthi();              //nhả MODE + hiển thị mã raw
    delay_ms(500);
    digitalWrite(opto1nutONOFF, HIGH);                      //nhấn OFF
    delay_ms(500);
    digitalWrite(opto1nutONOFF, LOW);irrecv.resume();       //nhả OFF
    delay_ms(500);
    ONOFF = 1;
    digitalWrite(opto1nutONOFF, HIGH);                      //nhấn ON
    delay_ms(500); 
    digitalWrite(opto1nutONOFF, LOW);hienthi();             //nhả ON + hiển thị mã raw
    delay_ms(500);
    ONOFF = 0;  */
   
   // Kiem tra dieu kien Mode
   if(mode==0||mode==1||mode==4){   
   // Can chinh khi chuyen tu mode = 3 sang mode = 4, che do gio dang o cap 1, phai chuyen che do gio sang auto truoc khi bat dau
       if(mode==4){
          digitalWrite(opto3nutWIND, HIGH);                       //nhan WIND
          delay_ms(500);                                          
          digitalWrite(opto3nutWIND, LOW);irrecv.resume();        //nha wind khong hiển thị mã raw
          delay_ms(500);
       }
   // Dieu chinh nut gio, Gio hien thi tren remote ban dau la tu dong
       for(wind=3;wind>=0;wind--)                                 //các chế độ tốc độ gió khác nhau, toc do gio tang dan
        {
          digitalWrite(opto3nutWIND, HIGH);                       //nhan WIND
          delay_ms(500);                                          
          digitalWrite(opto3nutWIND, LOW);hienthi();              //nha wind + hiển thị mã raw
          delay_ms(500);
          digitalWrite(opto1nutONOFF, HIGH);                      //nhấn OFF
          delay_ms(500);
          digitalWrite(opto1nutONOFF, LOW);irrecv.resume();       //nhả OFF
          delay_ms(500);
          ONOFF = 1;
          digitalWrite(opto1nutONOFF, HIGH);                      //nhấn ON
          delay_ms(500);   
          digitalWrite(opto1nutONOFF, LOW);hienthi();             //nhả ON + hiển thị mã raw
          delay_ms(500); 
          ONOFF = 0;       
                   
          // Dieu chinh nhiet do, nhiet do tren remote ban dau la 16 do
          test = 1; 
          if (nhietdo==16 && test==1){  
            for(nhietdo=17;nhietdo<=30;nhietdo++){
                digitalWrite(opto4nutUP, HIGH);                         //nhấn UP
                delay_ms(500);                                     
                digitalWrite(opto4nutUP, LOW);hienthi();                //nhả UP + hiển thị mã raw
                delay_ms(500);
                digitalWrite(opto1nutONOFF, HIGH);                      //nhấn OFF
                delay_ms(500);
                digitalWrite(opto1nutONOFF, LOW);irrecv.resume();       //nhả OFF
                delay_ms(500);
                ONOFF = 1;
                digitalWrite(opto1nutONOFF, HIGH);                      //nhấn ON
                delay_ms(500); 
                digitalWrite(opto1nutONOFF, LOW);hienthi();             //nhả ON + hiển thị mã raw
                delay_ms(500);
                ONOFF = 0;
              }
              test = 0; 
              nhietdo--;
          }
          
          if (nhietdo==30 && test==1){
            for(nhietdo=29;nhietdo>=16;nhietdo--){
                digitalWrite(opto5nutDOWN, HIGH);                       //nhấn UP
                delay_ms(500);                                     
                digitalWrite(opto5nutDOWN, LOW);hienthi();              //nhả UP + hiển thị mã raw
                delay_ms(500);
                digitalWrite(opto1nutONOFF, HIGH);                      //nhấn OFF
                delay_ms(500);
                digitalWrite(opto1nutONOFF, LOW);irrecv.resume();       //nhả OFF
                delay_ms(500);
                ONOFF = 1;
                digitalWrite(opto1nutONOFF, HIGH);                      //nhấn ON
                delay_ms(500); 
                digitalWrite(opto1nutONOFF, LOW);hienthi();             //nhả ON + hiển thị mã raw
                delay_ms(500);
                ONOFF = 0;
             }
             test = 0;
             nhietdo++;
          }
          
          if(nhietdo!=16&&nhietdo!=30&&test==1){
            Serial.print("Loi!!! Nhiet do khong bang 16 hoac 30 do");
          }                  
        }
        wind++;
  }
  if(mode==2){
   // Che do lam kho, do ở chế độ này wind chỉ có 1 giá trị nên không còn vòng lặp wind nữa
          test = 1;
          if (nhietdo==16 && test==1){            
            for(nhietdo=17;nhietdo<=30;nhietdo++){
                digitalWrite(opto4nutUP, HIGH);                         //nhấn UP
                delay_ms(500);                                     
                digitalWrite(opto4nutUP, LOW);hienthi();                //nhả UP + hiển thị mã raw
                delay_ms(500);
                digitalWrite(opto1nutONOFF, HIGH);                      //nhấn OFF
                delay_ms(500);
                digitalWrite(opto1nutONOFF, LOW);irrecv.resume();       //nhả OFF
                delay_ms(500);
                ONOFF = 1;
                digitalWrite(opto1nutONOFF, HIGH);                      //nhấn ON
                delay_ms(500); 
                digitalWrite(opto1nutONOFF, LOW);hienthi();             //nhả ON + hiển thị mã raw
                delay_ms(500);
                ONOFF = 0;
            }
            test = 0;
            nhietdo--;
          }
          
          if (nhietdo==30 && test==1){
            for(nhietdo=29;nhietdo>=16;nhietdo--){
                digitalWrite(opto5nutDOWN, HIGH);                       //nhấn UP
                delay_ms(500);                                     
                digitalWrite(opto5nutDOWN, LOW);hienthi();              //nhả UP + hiển thị mã raw
                delay_ms(500);
                digitalWrite(opto1nutONOFF, HIGH);                      //nhấn OFF
                delay_ms(500);
                digitalWrite(opto1nutONOFF, LOW);irrecv.resume();       //nhả OFF
                delay_ms(500);
                ONOFF = 1;
                digitalWrite(opto1nutONOFF, HIGH);                      //nhấn ON
                delay_ms(500); 
                digitalWrite(opto1nutONOFF, LOW);hienthi();             //nhả ON + hiển thị mã raw
                delay_ms(500);
                ONOFF = 0;
             }
             test = 0;
             nhietdo++;
          }
          
          if(nhietdo!=16&&nhietdo!=30&&test==1) {
            Serial.print("Loi!!! Nhiet do khong bang 16 hoac 30 do");
          }          
        }          
  if(mode==3){
    // Che do quat gio, che do nay khong dieu chinh duoc nhiet do, bien nhiet do de nguyen khong can vong lap
       for(wind=3;wind>0;wind--)                                  //các chế độ tốc độ gió khác nhau, toc do gio tang dan
        {
          digitalWrite(opto3nutWIND, HIGH);                       //nhan WIND
          delay_ms(500);                                          
          digitalWrite(opto3nutWIND, LOW);hienthi();              //nha wind + hiển thị mã raw
          delay_ms(500);
          digitalWrite(opto1nutONOFF, HIGH);                      //nhấn OFF
          delay_ms(500);
          digitalWrite(opto1nutONOFF, LOW);irrecv.resume();       //nhả OFF
          delay_ms(500);
          ONOFF = 1;
          digitalWrite(opto1nutONOFF, HIGH);                      //nhấn ON
          delay_ms(500);   
          digitalWrite(opto1nutONOFF, LOW);hienthi();             //nhả ON + hiển thị mã raw
          delay_ms(500);
          ONOFF = 0;
        }
  }
 }
 }
  giatri = 2;
}





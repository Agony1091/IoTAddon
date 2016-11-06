/*
 * IRremote: IRrecvDump - dump details of IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 * JVC and Panasonic protocol added by Kristian Lauszus (thanks to zenwheel and other people at the original blog post)
 */
/*import processing.serial.*;
Serial mySerial;
PrintWriter output;*/
#include <IRremote.h>


//Serial mySerial;
//PrintWriter output;
int RECV_PIN = 11;
int opto1nutONOFF = 3;
int opto2nutMODE = 4;
int opto3nutWIND = 5;
int opto4nutUP = 6;
int opto5nutDOWN = 7;
int opto6DKLED = 8;
byte j;
byte giatri = 0;
int t=2000;
IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  /*mySerial = new Serial( this, Serial.list()[0], 9600 );
  output = createWriter( "data.txt" );*/
  for(byte i=3;i<=8;i++)                                                //khai báo đầu ra là output
    {
      pinMode(i, OUTPUT);
    }
}

// Dumps out the decode_results structure.
// Call this after IRrecv::decode()
// void * to work around compiler issue
//void dump(void *v) {
//  decode_results *results = (decode_results *)v


void dump(decode_results *results) {
  int count = results->rawlen;
  /*if (results->decode_type == UNKNOWN) {
    Serial.print("Unknown encoding: ");
  } 
  else if (results->decode_type == NEC) {
    Serial.print("Decoded NEC: ");
  } 
  else if (results->decode_type == SONY) {
    Serial.print("Decoded SONY: ");
  } 
  else if (results->decode_type == RC5) {
    Serial.print("Decoded RC5: ");
  } 
  else if (results->decode_type == RC6) {
    Serial.print("Decoded RC6: ");
  }
  else if (results->decode_type == PANASONIC) {  
    Serial.print("Decoded PANASONIC - Address: ");
    Serial.print(results->panasonicAddress,HEX);
    Serial.print(" Value: ");
  }
  else if (results->decode_type == JVC) {
     Serial.print("Decoded JVC: ");
  }*/
  /*Serial.print(results->value, HEX);
  Serial.print(" (");
  Serial.print(results->bits, DEC);
  Serial.println(" bits)");*/
  Serial.print("Raw (");
  Serial.print(count, DEC);
  Serial.print("): ");
  int t=2000;
  /*output.print("Raw (");
  output.print(count, DEC);
  output.print("): ");*/

  for (int i = 0; i < count; i++) {
    if ((i % 2) == 1) {
      Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
    } 
    else {
      Serial.print(-(int)results->rawbuf[i]*USECPERTICK, DEC);
    }
    Serial.print(" ");
  }
}
void hienthi()                                                  //tạo chương trình con hiển thị
{
  if (irrecv.decode(&results)) 
{
    //Serial.println(results.value, HEX);
    dump(&results);
    irrecv.resume(); // Receive the next value
}

}
void loop() {
if(giatri<1)
{

delay(10000); 
byte nhietdo=16;
if(nhietdo==16)
{
digitalWrite(opto2nutMODE, HIGH);  //nhấn MODE
delay(t);hienthi();                                             //hiển thị mã raw
Serial.print(" 0 1 0 16 ");                                     //in trạng thái của điều hòa
Serial.println("");                                             //xuống dòng
delay(1000);
digitalWrite(opto2nutMODE, LOW);                                  //nhả MODE
delay(t);
       for(byte wind=3;wind>=0;wind--)                                   //các chế độ tốc độ gió khác nhau
        {
          digitalWrite(opto3nutWIND, HIGH);                             //nhấn WIND
          delay(t);hienthi();                                     //hiển thị trạng thái
          Serial.print(" 0 1 ");                                  //in trạng thái
          Serial.print(wind);                                      //in trạng thái mức wind
          Serial.print(" 16");                                     //in nhiệt độ
          Serial.println("");
          digitalWrite(opto3nutWIND, LOW);                              //nhả WIND
          delay(t);
            for(nhietdo=17;nhietdo<=30;nhietdo++)
              {
                digitalWrite(opto4nutUP, HIGH);                         //nhấn UP
                delay(t);hienthi();
                
                Serial.print("0 1 ");
                Serial.print(wind);
                Serial.print(" ");
                Serial.print(nhietdo);
                Serial.println("");
                digitalWrite(opto4nutUP, LOW);                          //nhả UP
                delay(t);
                digitalWrite(opto1nutONOFF, HIGH);                      //nhấn OFF
                delay(t);hienthi();
                Serial.println("");
                digitalWrite(opto1nutONOFF, LOW);                       //nhả OFF
                delay(t);
                digitalWrite(opto1nutONOFF, HIGH);                      //nhấn ON
                delay(t); hienthi();
               
                Serial.print("1 1 ");
                Serial.print(wind);
                Serial.print(" ");
                Serial.print(nhietdo);
                Serial.println("");
                digitalWrite(opto1nutONOFF, LOW);                       //nhả ON
                delay(t);
                if(nhietdo==30)                                         //nếu nhiệt độ bằng 30 thì giảm nhiệt độ xuống
                  {
                    for(j=29;j>=16;j--)
                      {
                        if(j!=16)
                          {
                            digitalWrite(opto5nutDOWN, HIGH);
                            delay(t);
                            digitalWrite(opto5nutDOWN, LOW);
                            delay(t); 
                            
                          }
                         else
                          {
                            digitalWrite(opto5nutDOWN, HIGH);
                            delay(t);hienthi();
                            
                            Serial.print("0 1 ");
                            Serial.print(wind);
                            Serial.print(" 16");
                            Serial.println("");
                            digitalWrite(opto5nutDOWN, LOW);
                            delay(t); 
                            digitalWrite(opto1nutONOFF, HIGH);                      //nhấn OFF
                            delay(t);
                            digitalWrite(opto1nutONOFF, LOW);                       //nhả OFF
                            delay(t);hienthi();
                            Serial.println("");
                            digitalWrite(opto1nutONOFF, HIGH);                      //nhấn ON
                            delay(t);hienthi();
                            
                            Serial.print("1 1 ");
                            Serial.print(wind);
                            Serial.print(" 16");
                            Serial.println("");
                            digitalWrite(opto1nutONOFF, LOW);                       //nhả ON
                            delay(t);
                          }
                      }
                  }
              }
        }
}
}
giatri = 2;
}




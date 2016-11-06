//From Arduino to Processing to Txt or cvs etc.
//import
import processing.serial.*;
PrintWriter output;
Serial port ;
int cr = 13;      //ASCII return ==13
int lf = 10;      //ASCII linefeed = 10;
int zero = 48;    //ASCII numberic zero = 48;
int counter = 0;
int BufferSize = 30;
String buf="";
char state;
StringList recordData;
void setup() {
  println(Serial.list());
  port = new Serial(this, Serial.list()[0], 9600);
  port.bufferUntil(lf);
  output = createWriter ("D:\\dust_concentration.csv");
  recordData = new StringList();
}


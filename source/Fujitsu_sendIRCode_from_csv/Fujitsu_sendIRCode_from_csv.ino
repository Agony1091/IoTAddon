#include <IRremote.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <SerialCommand.h> // Thêm vào sketch thư viện Serial Command
SerialCommand sCmd; // Khai báo biến sử dụng thư viện Serial Command

int raw[243];
int i=0;
 
// LER IR to pin 3;

// LCD pin
const int rsLcd = 13;
const int enableLcd = 12;
const int d4Lcd = 11;
const int d5Lcd = 10;
const int d6Lcd = 9;
const int d7Lcd = 8;

// Call functions
IRsend irsend;
LiquidCrystal lcd(rsLcd, enableLcd, d4Lcd, d5Lcd, d6Lcd, d7Lcd);
 
void setup() {
  //Khởi tạo Serial ở baudrate 9600 (trùng với HOST)
  Serial.begin(9600);
  lcd.begin(16, 2); // Start LCD
  lcd.setCursor(0, 0);
  lcd.print("Starting"); 
  // Tạo hàm để ra lệnh từ processing  
  sCmd.addCommand("sendIR", sendIR);
  sCmd.addCommand("sentOK", sentOK);
}
 
void loop() {   
    
  sCmd.readSerial();  // Đón lệnh gọi hàm từ processing

  if (i>=243){
    irsend.sendRaw(raw, 243, 38);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("IR sent");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ready to send");
    i=0;
  }  
}
 
void sendIR(){ 
  //Đoạn code này dùng để đọc TỪNG tham số. Các tham số mặc định có kiểu dữ liệu là "chuỗi"
  char *arg;
  arg = sCmd.next();  
  raw[i] = atoi(arg); // Chuyển chuỗi thành số
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(raw[i]);
  lcd.setCursor(0, 1);
  lcd.print(i);   
  i++;
}

void sentOK(){
  // Hàm xác nhận đã nhận phần tử thành công
  Serial.println("OK"); 
}


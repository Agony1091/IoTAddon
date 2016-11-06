import processing.serial.*; // import thư viện serial, tương tự như hàm include thôi :D
import java.io.FileReader;
import java.io.FileNotFoundException;
 
Serial serial; // Khởi tạo đối tượng Serial có tên là serial (phân biệt hoa thường nhé)
int portIndex = 0; // Lựa chọn vị trí cổng Serial trong danh sách

int[] val;
int i;
int state = 0;
 
void setup() {
  size(100, 100); 
  // mở một screen có kích thức rộng x cao = width x heigth = 100 x 100
  // cho vui, vì Processing lúc nào cũng có yêu cầu này.
  // Không có hàm size này thì biên dịch sẽ gặp lỗi,
  // tương tự như hàm setup() hay loop() trong Arduino 
  println(Serial.list());
  
  // Mở cổng Serial ở vị trí 0 với mức baudrate 9600
  serial = new Serial(this, Serial.list()[portIndex], 9600);
  
}
 
void draw() {
  // Tải bảng mã dữ liệu IR
  Table table = loadTable("D:\\IRCodev1.2.csv","header");
  val = new int[245];
  for (i=0;i<245;i++) {
    // Lấy phần tử thứ i của mã IR
    val[i] = table.getInt(0, i);
    if(i>1)
    { 
      while (state == 0){  // Kiểm phản hồi từ arduino xem phần tử thứ i đã gửi được chưa
        serial.write("sentOK \n");
        //delay(10);
        if (serial.readStringUntil('\n')!=null){
          state = 1;
        }
      }
      serial.write("sendIR " + val[i] + "\n"); // Tương tự Serial.print hay Serial.write trên Arduino
      state = 0;      
      print(val[i]);      
      print(" ,");
      //delay(10);
    }     
  }
  print(i);
  delay(100000);
}
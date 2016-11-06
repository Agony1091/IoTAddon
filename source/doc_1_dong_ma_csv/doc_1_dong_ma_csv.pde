/*==========================================================
Project: Read data from Text file into Processing
Author: ScottC
Created: 23rd Jun 2011 (Updated 26th Aug 2014)
Description: Use processing to read a text file and populate an ArrayList.
             The ArrayList is then printed to the debug window.
             
Processing version tested: 2.2.1
References: This was made possible using bits and pieces from these sites
         http://www.kodejava.org/examples/28.html
         http://processing.org/reference/ArrayList.html
         http://processing.org/reference/splitTokens_.html
         
===========================================================  */
import processing.serial.*;
import java.io.FileReader;
import java.io.FileNotFoundException;
Serial comPort;
int chuoi;
ArrayList sensorData;
ArrayList columnOne;

void setup(){
  //comPort = new Serial(this, Serial.list()[0], 9600);
  sensorData=new ArrayList();
  columnOne=new ArrayList();
  readData("D:/b.csv");
}

void readData(String myFileName){
  
  File file=new File(myFileName);
  BufferedReader br=null;
  
  try{
    br=new BufferedReader(new FileReader(file));
    String text=null;
    
    while((text=br.readLine())!=null){
      String [] subtext = splitTokens(text,",");
      columnOne.add(int(subtext[0]));
      sensorData.add(text);
    }
  }catch(FileNotFoundException e){
    e.printStackTrace();
  }catch(IOException e){
    e.printStackTrace();
  }finally{
    try {
      if (br != null){
        br.close();
      }
    } catch (IOException e) {
      e.printStackTrace();
    }
  }
  //for (int i=0; i<sensorData.size()-1; i++){
    //print(columnOne.get(100));//+ ".....");
    print(sensorData.get(4));
 // }
}

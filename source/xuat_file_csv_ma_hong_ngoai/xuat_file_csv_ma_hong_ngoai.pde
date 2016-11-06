/* 
  Saving Values from Arduino to a .csv File Using Processing - Pseduocode
 
  This sketch provides a basic framework to read data from Arduino over the serial port and save it to .csv file on your computer.
  The .csv file will be saved in the same folder as your Processing sketch.
  This sketch takes advantage of Processing 2.0's built-in Table class.
  This sketch assumes that values read by Arduino are separated by commas, and each Arduino reading is separated by a newline character.
  Each reading will have it's own row and timestamp in the resulting csv file. This sketch will write a new file a set number of times. Each file will contain all records from the beginning of the sketch's run.  
  This sketch pseduo-code only. Comments will direct you to places where you should customize the code.
  This is a beginning level sketch.
 
  The hardware:
  * Sensors connected to Arduino input pins
  * Arduino connected to computer via USB cord
        
  The software:
  *Arduino programmer
  *Processing (download the Processing software here: https://www.processing.org/download/
  *Download the Software Serial library from here: http://arduino.cc/en/Reference/softwareSerial
 
  Created 12 November 2014
  By Elaine Laguerta
  http://url/of/online/tutorial.cc
 
*/
 
import processing.serial.*;
Serial myPort; //creates a software serial port on which you will listen to Arduino
//Table dataTable; //table where we will read in and store values. You can name it something more creative!
Table table; // Table object
PFont font;
int numReadings = 2; //keeps track of how many readings you'd like to take before writing the file. 
int readingCounter = 0; //counts each reading to compare to numReadings. 
 
String fileName;
void setup()
{
  size(400, 400);
  String portName = Serial.list()[0]; 
  //CAUTION: your Arduino port number is probably different! Mine happened to be 1. Use a "handshake" sketch to figure out and test which port number your Arduino is talking on. A "handshake" establishes that Arduino and Processing are listening/talking on the same port.
  //Here's a link to a basic handshake tutorial: https://processing.org/tutorials/overview/
  table = new Table();
  myPort = new Serial(this, portName, 9600); //set up your port to listen to the serial port 
  table.addColumn("id");
  //This column stores a unique identifier for each record. We will just count up from 0 - so your first reading will be ID 0, your second will be ID 1, etc. 
  //the following adds columns for time. You can also add milliseconds. See the Time/Date functions for Processing: https://www.processing.org/reference/ 
  table.addColumn("1");  table.addColumn("2");  table.addColumn("3");  table.addColumn("4");  table.addColumn("5");  table.addColumn("6");  table.addColumn("7");  table.addColumn("8");  table.addColumn("9");  table.addColumn("10");
  table.addColumn("11");  table.addColumn("12");  table.addColumn("13");  table.addColumn("14");  table.addColumn("15");  table.addColumn("16");  table.addColumn("17");  table.addColumn("18");  table.addColumn("19");  table.addColumn("20");
  table.addColumn("21");  table.addColumn("22");  table.addColumn("23");  table.addColumn("24");  table.addColumn("25");  table.addColumn("26");  table.addColumn("27");  table.addColumn("28");  table.addColumn("29");  table.addColumn("30");
  table.addColumn("31");  table.addColumn("32");  table.addColumn("33");  table.addColumn("34");  table.addColumn("35");  table.addColumn("36");  table.addColumn("37");  table.addColumn("38");  table.addColumn("39");  table.addColumn("40");
  table.addColumn("41");  table.addColumn("42");  table.addColumn("43");  table.addColumn("44");  table.addColumn("45");  table.addColumn("46");  table.addColumn("47");  table.addColumn("48");  table.addColumn("49");  table.addColumn("50");
  table.addColumn("51");  table.addColumn("52");  table.addColumn("53");  table.addColumn("54");  table.addColumn("55");  table.addColumn("56");  table.addColumn("57");  table.addColumn("58");  table.addColumn("59");  table.addColumn("60");
  table.addColumn("61");  table.addColumn("62");  table.addColumn("63");  table.addColumn("64");  table.addColumn("65");  table.addColumn("66");  table.addColumn("67");  table.addColumn("68");  table.addColumn("69");  table.addColumn("70");
  table.addColumn("71");  table.addColumn("72");  table.addColumn("73");  table.addColumn("74");  table.addColumn("75");  table.addColumn("76");  table.addColumn("77");  table.addColumn("78");  table.addColumn("79");  table.addColumn("80");
  table.addColumn("81");  table.addColumn("82");  table.addColumn("83");  table.addColumn("84");  table.addColumn("85");  table.addColumn("86");  table.addColumn("87");  table.addColumn("88");  table.addColumn("89");  table.addColumn("90");
  table.addColumn("91");  table.addColumn("92");  table.addColumn("93");  table.addColumn("94");  table.addColumn("95");  table.addColumn("96");  table.addColumn("97");  table.addColumn("98");  table.addColumn("99");  table.addColumn("100");
  table.addColumn("101");  table.addColumn("102");  table.addColumn("103");  table.addColumn("104");  table.addColumn("105");  table.addColumn("106");  table.addColumn("107");  table.addColumn("108");  table.addColumn("109");  table.addColumn("110");
  table.addColumn("111");  table.addColumn("112");  table.addColumn("113");  table.addColumn("114");  table.addColumn("115");  table.addColumn("116");  table.addColumn("117");  table.addColumn("118");  table.addColumn("119");  table.addColumn("120");
  table.addColumn("121");  table.addColumn("122");  table.addColumn("123");  table.addColumn("124");  table.addColumn("125");  table.addColumn("126");  table.addColumn("127");  table.addColumn("128");  table.addColumn("129");  table.addColumn("130");
  table.addColumn("131");  table.addColumn("132");  table.addColumn("133");  table.addColumn("134");  table.addColumn("135");  table.addColumn("136");  table.addColumn("137");  table.addColumn("138");  table.addColumn("139");  table.addColumn("140");
  table.addColumn("141");  table.addColumn("142");  table.addColumn("143");  table.addColumn("144");  table.addColumn("145");  table.addColumn("146");  table.addColumn("147");  table.addColumn("148");  table.addColumn("149");  table.addColumn("150");
  table.addColumn("151");  table.addColumn("152");  table.addColumn("153");  table.addColumn("154");  table.addColumn("155");  table.addColumn("156");  table.addColumn("157");  table.addColumn("158");  table.addColumn("159");  table.addColumn("160");
  table.addColumn("161");  table.addColumn("162");  table.addColumn("163");  table.addColumn("164");  table.addColumn("165");  table.addColumn("166");  table.addColumn("167");  table.addColumn("168");  table.addColumn("169");  table.addColumn("170");
  table.addColumn("171");  table.addColumn("172");  table.addColumn("173");  table.addColumn("174");  table.addColumn("175");  table.addColumn("176");  table.addColumn("177");  table.addColumn("178");  table.addColumn("179");  table.addColumn("180");
  table.addColumn("181");  table.addColumn("182");  table.addColumn("183");  table.addColumn("184");  table.addColumn("185");  table.addColumn("186");  table.addColumn("187");  table.addColumn("188");  table.addColumn("189");  table.addColumn("190");
  table.addColumn("191");  table.addColumn("192");  table.addColumn("193");  table.addColumn("194");  table.addColumn("195");  table.addColumn("196");  table.addColumn("197");  table.addColumn("198");  table.addColumn("199");  table.addColumn("200");
  table.addColumn("201");  table.addColumn("202");  table.addColumn("203");  table.addColumn("204");  table.addColumn("205");  table.addColumn("206");  table.addColumn("207");  table.addColumn("208");  table.addColumn("209");  table.addColumn("210");
  table.addColumn("211");  table.addColumn("212");  table.addColumn("213");  table.addColumn("214");  table.addColumn("215");  table.addColumn("216");  table.addColumn("217");  table.addColumn("218");  table.addColumn("219");  table.addColumn("220");
  table.addColumn("221");  table.addColumn("222");  table.addColumn("223");  table.addColumn("224");  table.addColumn("225");  table.addColumn("226");  table.addColumn("227");  table.addColumn("228");  table.addColumn("229");  table.addColumn("230");
  table.addColumn("231");  table.addColumn("232");  table.addColumn("233");  table.addColumn("234");  table.addColumn("235");  table.addColumn("236");  table.addColumn("237");  table.addColumn("238");  table.addColumn("239");  table.addColumn("240");
  table.addColumn("241");  table.addColumn("242");  table.addColumn("243");  table.addColumn("244"); 
  
  
 
}
void serialEvent(Serial myPort){
  String val = myPort.readStringUntil('\n'); //The newline separator separates each Arduino loop. We will parse the data by each newline separator. 
  if (val!= null) { //We have a reading! Record it.
    val = trim(val); //gets rid of any whitespace or Unicode nonbreakable space
    println(val); //Optional, useful for debugging. If you see this, you know data is being sent. Delete if  you like. 
    float sensorVals[] = float(split(val, ',')); //parses the packet from Arduino and places the valeus into the sensorVals array. I am assuming floats. Change the data type to match the datatype coming from Arduino. 
    TableRow newRow = table.addRow(); //add a row for this new reading
    newRow.setInt("id", table.lastRowIndex());//record a unique identifier (the row's index)
    //record time stamp
    //newRow.setInt("year", year());
   // newRow.setInt("month", month());
   // newRow.setInt("day", day());
   // newRow.setInt("hour", hour());
   // newRow.setInt("minute", minute());
    //newRow.setInt("second", second());
    //record sensor information. Customize the names so they match your sensor column names. 
    newRow.setFloat("1",sensorVals[0]);newRow.setFloat("2",sensorVals[1]);newRow.setFloat("3",sensorVals[2]);newRow.setFloat("4",sensorVals[3]);newRow.setFloat("5",sensorVals[4]);newRow.setFloat("6",sensorVals[5]);newRow.setFloat("7",sensorVals[6]);newRow.setFloat("8",sensorVals[7]);newRow.setFloat("9",sensorVals[8]);newRow.setFloat("10",sensorVals[9]);
    newRow.setFloat("11",sensorVals[10]);newRow.setFloat("12",sensorVals[11]);newRow.setFloat("13",sensorVals[12]);newRow.setFloat("14",sensorVals[13]);newRow.setFloat("15",sensorVals[14]);newRow.setFloat("16",sensorVals[15]);newRow.setFloat("17",sensorVals[16]);newRow.setFloat("18",sensorVals[17]);newRow.setFloat("19",sensorVals[18]);newRow.setFloat("20",sensorVals[19]);
    newRow.setFloat("21",sensorVals[20]);newRow.setFloat("22",sensorVals[21]);newRow.setFloat("23",sensorVals[22]);newRow.setFloat("24",sensorVals[23]);newRow.setFloat("25",sensorVals[24]);newRow.setFloat("26",sensorVals[25]);newRow.setFloat("27",sensorVals[26]);newRow.setFloat("28",sensorVals[27]);newRow.setFloat("29",sensorVals[28]);newRow.setFloat("30",sensorVals[29]);
    newRow.setFloat("31",sensorVals[30]);newRow.setFloat("32",sensorVals[31]);newRow.setFloat("33",sensorVals[32]);newRow.setFloat("34",sensorVals[33]);newRow.setFloat("35",sensorVals[34]);newRow.setFloat("36",sensorVals[35]);newRow.setFloat("37",sensorVals[36]);newRow.setFloat("38",sensorVals[37]);newRow.setFloat("39",sensorVals[38]);newRow.setFloat("40",sensorVals[39]);
    newRow.setFloat("41",sensorVals[40]);newRow.setFloat("42",sensorVals[41]);newRow.setFloat("43",sensorVals[42]);newRow.setFloat("44",sensorVals[43]);newRow.setFloat("45",sensorVals[44]);newRow.setFloat("46",sensorVals[45]);newRow.setFloat("47",sensorVals[46]);newRow.setFloat("48",sensorVals[47]);newRow.setFloat("49",sensorVals[48]);newRow.setFloat("50",sensorVals[49]);
    newRow.setFloat("51",sensorVals[50]);newRow.setFloat("52",sensorVals[51]);newRow.setFloat("53",sensorVals[52]);newRow.setFloat("54",sensorVals[53]);newRow.setFloat("55",sensorVals[54]);newRow.setFloat("56",sensorVals[55]);newRow.setFloat("57",sensorVals[56]);newRow.setFloat("58",sensorVals[57]);newRow.setFloat("59",sensorVals[58]);newRow.setFloat("60",sensorVals[59]);
    newRow.setFloat("61",sensorVals[60]);newRow.setFloat("62",sensorVals[61]);newRow.setFloat("63",sensorVals[62]);newRow.setFloat("64",sensorVals[63]);newRow.setFloat("65",sensorVals[64]);newRow.setFloat("66",sensorVals[65]);newRow.setFloat("67",sensorVals[66]);newRow.setFloat("68",sensorVals[67]);newRow.setFloat("69",sensorVals[68]);newRow.setFloat("70",sensorVals[69]);
    newRow.setFloat("71",sensorVals[70]);newRow.setFloat("72",sensorVals[71]);newRow.setFloat("73",sensorVals[72]);newRow.setFloat("74",sensorVals[73]);newRow.setFloat("75",sensorVals[74]);newRow.setFloat("76",sensorVals[75]);newRow.setFloat("77",sensorVals[76]);newRow.setFloat("78",sensorVals[77]);newRow.setFloat("79",sensorVals[78]);newRow.setFloat("80",sensorVals[79]);
    newRow.setFloat("81",sensorVals[80]);newRow.setFloat("82",sensorVals[81]);newRow.setFloat("83",sensorVals[82]);newRow.setFloat("84",sensorVals[83]);newRow.setFloat("85",sensorVals[84]);newRow.setFloat("86",sensorVals[85]);newRow.setFloat("87",sensorVals[86]);newRow.setFloat("88",sensorVals[87]);newRow.setFloat("89",sensorVals[88]);newRow.setFloat("90",sensorVals[89]);
    newRow.setFloat("91",sensorVals[90]);newRow.setFloat("92",sensorVals[91]);newRow.setFloat("93",sensorVals[92]);newRow.setFloat("94",sensorVals[93]);newRow.setFloat("95",sensorVals[94]);newRow.setFloat("96",sensorVals[95]);newRow.setFloat("97",sensorVals[96]);newRow.setFloat("98",sensorVals[97]);newRow.setFloat("99",sensorVals[98]);newRow.setFloat("100",sensorVals[99]);
    newRow.setFloat("101",sensorVals[100]);newRow.setFloat("102",sensorVals[101]);newRow.setFloat("103",sensorVals[102]);newRow.setFloat("104",sensorVals[103]);newRow.setFloat("105",sensorVals[104]);newRow.setFloat("106",sensorVals[105]);newRow.setFloat("107",sensorVals[106]);newRow.setFloat("108",sensorVals[107]);newRow.setFloat("109",sensorVals[108]);newRow.setFloat("110",sensorVals[109]);
    newRow.setFloat("111",sensorVals[110]);newRow.setFloat("112",sensorVals[111]);newRow.setFloat("113",sensorVals[112]);newRow.setFloat("114",sensorVals[113]);newRow.setFloat("115",sensorVals[114]);newRow.setFloat("116",sensorVals[115]);newRow.setFloat("117",sensorVals[116]);newRow.setFloat("118",sensorVals[117]);newRow.setFloat("119",sensorVals[118]);newRow.setFloat("120",sensorVals[119]);
    newRow.setFloat("121",sensorVals[120]);newRow.setFloat("122",sensorVals[121]);newRow.setFloat("123",sensorVals[122]);newRow.setFloat("124",sensorVals[123]);newRow.setFloat("125",sensorVals[124]);newRow.setFloat("126",sensorVals[125]);newRow.setFloat("127",sensorVals[126]);newRow.setFloat("128",sensorVals[127]);newRow.setFloat("129",sensorVals[128]);newRow.setFloat("130",sensorVals[129]);
    newRow.setFloat("131",sensorVals[130]);newRow.setFloat("132",sensorVals[131]);newRow.setFloat("133",sensorVals[132]);newRow.setFloat("134",sensorVals[133]);newRow.setFloat("135",sensorVals[134]);newRow.setFloat("136",sensorVals[135]);newRow.setFloat("137",sensorVals[136]);newRow.setFloat("138",sensorVals[137]);newRow.setFloat("139",sensorVals[138]);newRow.setFloat("140",sensorVals[139]);
    newRow.setFloat("141",sensorVals[140]);newRow.setFloat("142",sensorVals[141]);newRow.setFloat("143",sensorVals[142]);newRow.setFloat("144",sensorVals[143]);newRow.setFloat("145",sensorVals[144]);newRow.setFloat("146",sensorVals[145]);newRow.setFloat("147",sensorVals[146]);newRow.setFloat("148",sensorVals[147]);newRow.setFloat("149",sensorVals[148]);newRow.setFloat("150",sensorVals[149]);
    newRow.setFloat("151",sensorVals[150]);newRow.setFloat("152",sensorVals[151]);newRow.setFloat("153",sensorVals[152]);newRow.setFloat("154",sensorVals[153]);newRow.setFloat("155",sensorVals[154]);newRow.setFloat("156",sensorVals[155]);newRow.setFloat("157",sensorVals[156]);newRow.setFloat("158",sensorVals[157]);newRow.setFloat("159",sensorVals[158]);newRow.setFloat("160",sensorVals[159]);
    newRow.setFloat("161",sensorVals[160]);newRow.setFloat("162",sensorVals[161]);newRow.setFloat("163",sensorVals[162]);newRow.setFloat("164",sensorVals[163]);newRow.setFloat("165",sensorVals[164]);newRow.setFloat("166",sensorVals[165]);newRow.setFloat("167",sensorVals[166]);newRow.setFloat("168",sensorVals[167]);newRow.setFloat("169",sensorVals[168]);newRow.setFloat("170",sensorVals[169]);
    newRow.setFloat("171",sensorVals[170]);newRow.setFloat("172",sensorVals[171]);newRow.setFloat("173",sensorVals[172]);newRow.setFloat("174",sensorVals[173]);newRow.setFloat("175",sensorVals[174]);newRow.setFloat("176",sensorVals[175]);newRow.setFloat("177",sensorVals[176]);newRow.setFloat("178",sensorVals[177]);newRow.setFloat("179",sensorVals[178]);newRow.setFloat("180",sensorVals[179]);
    newRow.setFloat("181",sensorVals[180]);newRow.setFloat("182",sensorVals[181]);newRow.setFloat("183",sensorVals[182]);newRow.setFloat("184",sensorVals[183]);newRow.setFloat("185",sensorVals[184]);newRow.setFloat("186",sensorVals[185]);newRow.setFloat("187",sensorVals[186]);newRow.setFloat("188",sensorVals[187]);newRow.setFloat("189",sensorVals[188]);newRow.setFloat("190",sensorVals[189]);
    newRow.setFloat("191",sensorVals[190]);newRow.setFloat("192",sensorVals[191]);newRow.setFloat("193",sensorVals[192]);newRow.setFloat("194",sensorVals[193]);newRow.setFloat("195",sensorVals[194]);newRow.setFloat("196",sensorVals[195]);newRow.setFloat("197",sensorVals[196]);newRow.setFloat("198",sensorVals[197]);newRow.setFloat("199",sensorVals[198]);newRow.setFloat("200",sensorVals[199]);
    newRow.setFloat("201",sensorVals[200]);newRow.setFloat("202",sensorVals[201]);newRow.setFloat("203",sensorVals[202]);newRow.setFloat("204",sensorVals[203]);newRow.setFloat("205",sensorVals[204]);newRow.setFloat("206",sensorVals[205]);newRow.setFloat("207",sensorVals[206]);newRow.setFloat("208",sensorVals[207]);newRow.setFloat("209",sensorVals[208]);newRow.setFloat("210",sensorVals[209]);
    newRow.setFloat("211",sensorVals[210]);newRow.setFloat("212",sensorVals[211]);newRow.setFloat("213",sensorVals[212]);newRow.setFloat("214",sensorVals[213]);newRow.setFloat("215",sensorVals[214]);newRow.setFloat("216",sensorVals[215]);newRow.setFloat("217",sensorVals[216]);newRow.setFloat("218",sensorVals[217]);newRow.setFloat("219",sensorVals[218]);newRow.setFloat("220",sensorVals[219]);
    newRow.setFloat("221",sensorVals[220]);newRow.setFloat("222",sensorVals[221]);newRow.setFloat("223",sensorVals[222]);newRow.setFloat("224",sensorVals[223]);newRow.setFloat("225",sensorVals[224]);newRow.setFloat("226",sensorVals[225]);newRow.setFloat("227",sensorVals[226]);newRow.setFloat("228",sensorVals[227]);newRow.setFloat("229",sensorVals[228]);newRow.setFloat("230",sensorVals[229]);
    newRow.setFloat("231",sensorVals[230]);newRow.setFloat("232",sensorVals[231]);newRow.setFloat("233",sensorVals[232]);newRow.setFloat("234",sensorVals[233]);newRow.setFloat("235",sensorVals[234]);newRow.setFloat("236",sensorVals[235]);newRow.setFloat("237",sensorVals[236]);newRow.setFloat("238",sensorVals[237]);newRow.setFloat("239",sensorVals[238]);newRow.setFloat("240",sensorVals[239]);
    newRow.setFloat("241",sensorVals[240]);newRow.setFloat("242",sensorVals[241]);newRow.setFloat("243",sensorVals[242]);newRow.setFloat("244",sensorVals[243]);
    readingCounter++; //optional, use if you'd like to write your file every numReadings reading cycles
    //saves the table as a csv in the same folder as the sketch every numReadings. 
    if (readingCounter % numReadings ==0)//The % is a modulus, a math operator that signifies remainder after division. The if statement checks if readingCounter is a multiple of numReadings (the remainder of readingCounter/numReadings is 0)
    {
       saveTable(table, "D:\\nhietdo.csv");
    }
   }
}
 
void draw()
{ 
   //visualize your sensor data in real time here! In the future we hope to add some cool and useful graphic displays that can be tuned to different ranges of values. 
}

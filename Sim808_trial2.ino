//==============================================
// My libraries
//==============================================
#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>


//==============================================
// Define what pins to use for my softwareserial 
// and the length of my message
//==============================================
#define LengthofMessage 160
#define TransferPin 10
#define ReceivedPin 11
SoftwareSerial mySerial(TransferPin,ReceivedPin);
DFRobot_SIM808 sim808(&mySerial);//Connect RX,TX,PWR,


    
//==============================================
// variables that i will going to use
//==============================================
int messageIndex = 0;
char message[LengthofMessage];
char MESSAGE[300];
char lat[12];
char lon[12];
char wspeed[12];
char phone[16];
char datetime[24];



//==============================================
// functions
//==============================================
void sendSMS();
void getGPS();
void readSMS();



void setup()
{
  mySerial.begin(9600);
  Serial.begin(9600);

  //******** Initialize sim808 module ***********
  while(!sim808.init())
  {
      Serial.print("Sim808 initialize error\r\n");
      delay(1000);
  }
  delay(3000);
  Serial.println("Initialization Success, PLEASE SEND SMS MESSAGE!");

  
  //************* Turn on the GPS power************
  if( sim808.attachGPS())
      Serial.println("GPS POWER SUCCESS");
  else 
      Serial.println("GPS POWER FAILURE");

  
}




void loop()
{
  //*********** Detecting unread SMS **********************
   messageIndex = sim808.isSMSunread();

   //*********** At least, there is one UNREAD SMS *********
   if (messageIndex > 0)
   { 
      readSMS();
      getGPS();
      sendSMS();
      Serial.println("PLEASE SEND SMS MESSAGE!");
   }
}




//====================================
// Method for readSMS()
//====================================

void readSMS()
{
  Serial.print("messageIndex: ");
  Serial.println(messageIndex);
  
  sim808.readSMS(messageIndex, message, LengthofMessage, phone, datetime);
             
  //***********In order to full SIM Memory, is better to delete it**********\\
  sim808.deleteSMS(messageIndex);
  Serial.print("From number: ");
  Serial.println(phone);  
  Serial.print("Datetime: ");
  Serial.println(datetime);        
  Serial.print("Received Message: ");
  Serial.println(message);
}





//====================================
// Method for getGPS()
//====================================
void getGPS()
{ 
  while(!sim808.attachGPS())
  {
    Serial.println("Possible GPS power failure");
    delay(1000);
  }
  delay(3000);

  Serial.println("GPS Initialize Success");
    
  while(!sim808.getGPS())
  {
    
  }

  float la = sim808.GPSdata.lat;
  float lo = sim808.GPSdata.lon;
  float ws = sim808.GPSdata.speed_kph;

  dtostrf(la, 4, 6, lat); //put float value of la into char array of lat. 6 = number of digits before decimal sign. 2 = number of digits after the decimal sign.
  dtostrf(lo, 4, 6, lon); //put float value of lo into char array of lon
  dtostrf(ws, 6, 2, wspeed);  //put float value of ws into char array of wspeed

  sprintf(MESSAGE, "Latitude : %s\nLongitude : %s\nWind Speed : %s kph\nYour Vehicle Current Location.  Click This Link.\nhttp://www.latlong.net/Show-Latitude-Longitude.html\nhttp://maps.google.com/maps?q=%s,%s\nLatitude : %s\nLongitude : %s\n", lat, lon, wspeed, lat, lon);
}






//====================================
// Method for sendSMS()
//====================================
void sendSMS()
{
  Serial.println("Start to send message ...");
  Serial.println(MESSAGE);
  Serial.println(phone);
  sim808.sendSMS(phone,MESSAGE);
  phone[16] = "+639399150254";
}

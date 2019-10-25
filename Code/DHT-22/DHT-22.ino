/*  DHT11/ DHT22 Sensor Temperature and Humidity Tutorial
 *  Program made by Dejan Nedelkovski,
 *  www.HowToMechatronics.com 
 */
/*
 * You can find the DHT Library from Arduino official website
 * http://playground.arduino.cc/Main/DHTLib
 */






 
 
#include <dht.h>
#include<EEPROM.h>
#include <DS3231.h>
#include<string.h>

DS3231  rtc(SDA, SCL);



#define dataPin 8 // Defines pin number to which the sensor is connected
dht DHT; // Creats a DHT object
int inputPin = 2;
int pirState = LOW;
int val = 0 ;
int addr = 0;
int rain = 0;
const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum
int baddr=100;
int f=0;


void suggest_song(int DIK, int rain_flag)
{
  char* cold_songs[] = {"A Hazy Shade of Winter - Simon and Garfunkel","Cold As Ice - Foreigner","She's So Cold - The Rolling Stones","Stone Cold Crazy - Queen", "Freeze Frame - J.Giles Band", "Ice Ice Baby - Vanilla Ice"};
  char* comfort_songs[]={"I Look to You","Heal My Broken Heart","Wings of a Butterfly","Chet Faker","Blackbear","Good Old Days - Kesha"};
  char* hot_songs[] = {"Jump In The Fire - Metallica", "The Heat Is On", "Skies on Fire","Hot Blooded","Burn","On Fire"};
  char* rain_songs[] = {"Riders On The Storm. The Doors", "Raining In Baltimore. Counting Crows" , "Sunset Soon Forgotten. Iron & Wine" , "Lay Me Down. Sam Smith, John Legend" , "All My Days. Alexi Murdoch" , "Thank You. Dido" };   

  int x = rand()%6;
  //Serial.println(cold_songs[x]);
  String s;
  //Serial.print("Preferable Song : ");
  if(rain_flag==0){
    
  if(DIK<60)
  {
    s = cold_songs[x];
    Serial.println(s);
  }
  else if(DIK>=60 && DIK<75)
  {s = comfort_songs[x];
    Serial.println(s);
  }
  else
  {
s = hot_songs[x];
    Serial.println(s);  }}

  else
  {
    
    s = rain_songs[x];
    Serial.println(s);
  }
  
  return;
}


void setup() {
  pinMode(13,OUTPUT);
  Serial.begin(9600);
   rtc.begin(); // Initialize the rtc object
   //rtc.setDOW(TUESDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(14, 23, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(12, 12, 2017);   // Set the date to January 1st, 2014
  
}
void loop() {


  String data,list,list1,list2;

  for(int i = 0 ; i<4;i++)
  {
    char c = EEPROM.read(i);
  data+=c;
  if(i==1) data+=":";
    //Serial.print(c);
    
  }

  for(int i = 100 ; i<200;i++)
  {
    char c = EEPROM.read(i);
  list+=c;
  
//  if(i==1) data+=":";
    //Serial.print(c);
    
  }
   for(int i = 200 ; i<300;i++)
  {
    char c = EEPROM.read(i);
  list1+=c;
  
//  if(i==1) data+=":";
    //Serial.print(c);
    
  } 
   for(int i = 300 ; i<400;i++)
  {
    char c = EEPROM.read(i);
  list2+=c;
  
//  if(i==1) data+=":";
    //Serial.print(c);
    
  } 



  

  String tm=rtc.getTimeStr();
  //Serial.println("TIME IS"+tm);


//  Serial.println("DATA"+data);

  if(tm.substring(0,5)==data)
{


for(int i=0;i<60;i++){
  
  digitalWrite(13,HIGH);
  delay(100);
  
  
  digitalWrite(13,LOW);
}
}
  val = digitalRead(inputPin);
  if(val== HIGH){
  if (pirState == LOW) {
      // we have just turned on
    //  Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    

    // read the sensor on analog A0:
 
String a,b,c,d,e,f;
   while(Serial.available()) {
    
String b="Alarm";
a= Serial.readString();// read the incoming data as string
Serial.println(a);
//Serial.println(a.substring(0,5));


String todo="Todo";

String weather = "Weather";

String lst="List";

if(a.substring(0,7)==weather)
{
  int sensorReading = analogRead(A0);
  // map the sensor range (four options):
  // ex: 'long int map(long int, long int, long int, long int, long int)'
  int range = map(sensorReading, sensorMin, sensorMax, 0, 4);
  
  // range value:
  switch (range) {
 case 0:    // Sensor getting wet
    Serial.println("Heavy Rain");
    rain=1;
    break;
 case 1:
    Serial.println("Medium Rain");
    rain = 1;
    break;
 case 2:    // Sensor getting wet
    Serial.println("Rain Warning");
    rain=0;
    break;
 case 3:    // Sensor dry - To shut this up delete the " Serial.println("Not Raining"); " below.
    Serial.println("Not Raining");
    rain=0;
    break;
  }

  int readData = DHT.read22(dataPin); // Reads the data from the sensor
  float t = DHT.temperature; // Gets the values of the temperature
  float h = DHT.humidity; // Gets the values of the humidity
  float dew = t - ((100-h)/5);

  float DIK = .99 * t + .36 *dew + 41.5;

   Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");
  // Send time
  Serial.println(rtc.getTimeStr());
  // Printing the results on the serial monitor
  Serial.print("Temperature = ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("    Humidity = ");
  Serial.print(h);
  Serial.println(" % ");
  Serial.print("Dew point = ");
  Serial.print(dew);
  Serial.print(" *C ");
  Serial.print("DIK = ");
  Serial.print(DIK);
  Serial.print("\n ");
  if(DIK>75)
  {
    Serial.print(" HOT \n");
    suggest_song(DIK,rain);
  }
  else if(DIK<60)
  {
    Serial.print(" COLD \n");
    suggest_song(DIK,rain);
  }
  else if(DIK>=60 && DIK<=67.5)
  {
    Serial.print(" HOT COMFORTABLE \n");
    suggest_song(DIK,rain);
  }
  else
  {
    Serial.print(" COLD COMFORTABLE \n");
    suggest_song(DIK,rain);
  } 
}

if(a.substring(0,4)==lst)
{

  if(list.substring(0,10)==rtc.getDateStr())
      Serial.println(list);

  if(list1.substring(0,10)==rtc.getDateStr())
      Serial.println(list1);
  if(list2.substring(0,10)==rtc.getDateStr())
      Serial.println(list2);
    

      
}



if(a.substring(0,4)==todo)
{
  Serial.println("Set Month");
  delay(10000);
  while(Serial.available())
  {
    c=Serial.readString();
        
    Serial.println("Set Date");
    delay(10000);

    while(Serial.available())
    {
      d=Serial.readString();
        
      Serial.println("Set Year");
      delay(10000);

      while(Serial.available())
      {
        e=Serial.readString();
        Serial.println("Set Your List");

        delay(30000);
        while(Serial.available())
        {
            f=Serial.readString();
            c=c.substring(0,2);
            d=d.substring(0,2);
            e=e.substring(0,4);
            f=f.substring(0,80);
            c=c+"."+d+"."+e+" "+f;
            int k;  
             for(int i = baddr,j=0 ; i<baddr+99;i++,j++)
              {
                EEPROM.write(i,c[j]);
                k=i;
                
               }
              baddr=k+1;
              if(baddr==400) baddr=100;


          
          
        }

        

        



        
      }
      
    }

    
  }
  
  
}










if(a.substring(0,5)==b)
{
  Serial.println("Set Hour");
  delay(5000);

  while(Serial.available()) {

    c=Serial.readString();
    Serial.println("Set Min");
  delay(5000);
  while(Serial.available()) {
  d=Serial.readString();
  }

  Serial.println(c+""+d);
  if(c[0]<10) c="0"+c;
  c=c.substring(0,2);
  d=d.substring(0,2);
  Serial.println("C IS"+c+"D IS"+d);
  

  
  int k;

  for(int i = addr,j=0 ; i<addr+2;i++,j++)
  {
    EEPROM.write(j,c[j]);
    k=i;
  }
  addr=k+1;

   for(int i = addr,j=0 ; i<addr+2;i++,j++)
  {
    EEPROM.write(j+2,d[j]);
    k=i;
  }
  addr=k+1;
  Serial.println(c+""+d+""+addr);

    String data;

  for(int i = 0 ; i<4;i++)
  {
    char c = EEPROM.read(i);
  data+=c;
    //Serial.print(c);
    
  }


  Serial.println("DATA"+data);



    


    

/*   for(int i = addr ; i<addr+4;i++)
  {
    EEPROM.write(i,a[i]);
    k=i;
  }
  addr=k+1;
  String data;

  for(int i = addr ; i<a.length();i++)
  {
    char c = EEPROM.read(i);
  data+=c;
    //Serial.print(c);
    
  }*/


  //Serial.println(data);


    

    
  }



  
}


//Serial.println(a);

}

/*
for(int i = addr ; i<a.length();i++)
{
  char c = EEPROM.read(i);
 data+=c;
  Serial.print(c);
}
*/
//Serial.print(data);
//Serial.print("\n");

//Serial.println(a);

  
  }
  
   else {
    if (pirState == HIGH){
      // we have just turned of
    //  Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }

  }
  
  delay(2000); // Delays 2 secods, as the DHT22 sampling rate is 0.5Hz
}


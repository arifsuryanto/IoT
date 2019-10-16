#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>    //memanggil library SoftwareSerial
#include <DFPlayer_Mini_Mp3.h> //memanggil library DFPlayer mini
#include <FirebaseArduino.h>
#include <LiquidCrystal.h>

//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

SoftwareSerial mySerial(D6, D7); // Declare pin RX & TX
const char* ssid = "Masjid At-Taqwa";
const char* password = "solatdulud";
#define FIREBASE_HOST "wifi-audio-player.firebaseio.com"
#define FIREBASE_AUTH "v4Cb6a25bz7TgqWXemdQ8i3Zx0rFEtWABMq7Oaep"

WiFiServer server(80);
int i = 1;
String a = "Eminem - Lose Yourself";
void setup() {
  Serial.begin(115200);
  mySerial.begin (9600);
  delay(10);

  //lcd.begin(16, 2);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  
  //firebase start
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  //mulai mp3
   mp3_set_serial (mySerial); //set softwareSerial for DFPlayer
   delay(10);
   
   mp3_reset();  //soft-Reset module DFPlayer
   
   delay(10);   //wait 1ms for respon command
   
   mp3_set_volume (15); //set Volume module DFPlayer
   delay(1000);
   mp3_play (i); //Play mp3 0001.mp3 dalam folder mp3 di memory
   delay(1000);
   // end of servo
}
 
void loop() {
  
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  


  
  // Match the request

  if (request.indexOf("/play") != -1) {
    mp3_play();
  } 
  if (request.indexOf("/pause") != -1){
    mp3_pause();
    
  }
   if (request.indexOf("/next") != -1) {
    mp3_next();
    i=i+1;
  } 
  if (request.indexOf("/prev") != -1){
    mp3_prev();
    i=i-1;
  }
 if ( i == 1 )
  a = "Eminem - Lose Yourself";
   else if (i == 2)
  a = "Rossa - Ayat Ayat Cinta";
   else if (i == 3)
  a = "Macklemore ft Ryan L - Cant Hold Us";
   else if (i == 4)
  a = "Secret Love Song (feat. Jason Derulo)";
   else if (i == 5)
  a = "Bravesboy - Kamu Seperti Jogja";
   else if (i == 6)
  a = "Eminem - No Love ft. Lil Wayne";
   else if (i == 7)
  a = "Rossa - Aku Bukan Untukmu";
   else if (i == 8)
  a = "Kendrick Lamar - DNA";
   else if (i == 9)
  a = "Rossa - Memeluk Bulan";
   else if (i == 10)
  a = "Kendrick Lamar - Humble";
   else if (i == 11)
  a = "Bad Meets Evil - Lighters ft. Bruno Mars";
   else if (i == 12)
  a = "Rossa - Tak Sanggup Lagi";
   else if (i == 13)
  a = "Imagine Dragons - Believer";
   else if (i == 14)
  a = "Eminem - Without Me";
   else if (i = 15)
  a = "Eminem - Beautiful Pain";
   else if (i == 16)
  a = "Bravesboy - Putuskan Saja Pacarmu";
   else if (i == 17)
   {a = "Ed Sheeran - Perfect";}



     Firebase.pushString("Judul Lagu", a);
     
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

 
//  if(i == x) {
 //   client.print("On");  
 /// } else {
  //  client.print("Off");
  //}
  client.println("<br><br>");
  //client.println("Click <a href=\"/LED=ON\">here</a> turn the LED on pin 5 ON<br>");
 // client.println("Click <a href=\"/LED=OFF\">here</a> turn the LED on pin 5 OFF<br>");
  client.println("</html>");
  client.println("<!DOCTYPE html>");
  client.println("<html>");
  client.println("<head>");
  client.println("<style>");
  client.println(".button {");
  client.println("  background-color: #4CAF50; /* Green */");
 // client.println("  backfround-image: https://d2v9y0dukr6mq2.cloudfront.net/video/thumbnail/HOX7rov7iorrrmav/speaker-and-music-effect-background_sxjx4oed__F0000.png;");
  client.println("  border: none;");
  client.println("  color: white;");
  client.println("  padding: 15px 32px;");
  client.println("  text-align: center;");
  client.println("  text-decoration: none;");
  client.println("  display: inline-block;");
  client.println("  font-size: 16px;");
  client.println("  margin: 4px 2px;");
  client.println("  cursor: pointer;}");
  
  client.println(".button2 {background-color: #008CBA;} /* Blue */");
  client.println(".button3 {background-color: #f44336;} /* Red */ ");
  client.println(".button5 {background-color: #555555;} /* Black */");
  client.println("</style>");
  client.println("</head>");
  client.println("<body>");
  
  client.println("<CENTER>");
  client.println("<h2>WI-FI AUDIO PLAYER");
  client.println("<br><h2>");
  Serial.println(a);
  client.println(a);
  client.println("</br></h2>");
  client.println("</h2><p>EXPO SISTEM DIGITAL 2019</p>");
  
  client.println("<a href=\"/play\"><button class=\"button\">Play</button></a>");
  client.println("<a href=\"/pause\"><button class=\"button button2\">Pause</button></a>");
  client.println("<a href=\"/next\"><button class=\"button button3\">Next</button></a>");
  client.println("<a href=\"/prev\"><button class=\"button button5\">Previous</button></a>");
  client.println("<CENTER>");
  
  client.println("</body>");
  client.println("</html>");
  delay(1);
  
   //   lcd.setCursor(0, 1);
  //  lcd.print(a);
//   for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
//    // scroll one position left:
//    lcd.scrollDisplayLeft();
//    // wait a bit:
  //  delay(150);
// 
//}
}

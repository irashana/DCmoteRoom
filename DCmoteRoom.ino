
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>



   

unsigned long previousMillis = 0;  
 const long interval = 1000;     

const char* host     = "www.dcmote.xyz"; // Your domain   
String path          = "/json.php?";  
ESP8266WebServer server(80);
#include "FS.h"
#include <SPI.h>
int buttonState = 0; 
    String line ="";
    String result ="";
    String ddd="", iotmode="", iotf=""  ;
    
  WiFiClient client;

const String HTTP_HEAD           = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/><title>{v}</title>";
const String HTTP_STYLE          = "<style>.c{text-align: center;} div,input{padding:5px;font-size:1em;} input{width:95%;} body{text-align: center;font-family:verdana;} button{border:0;border-radius:0.3rem;background-color:#1fa3ec;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;} .q{float: right;width: 64px;text-align: right;} .l{background: url(\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAMAAABEpIrGAAAALVBMVEX///8EBwfBwsLw8PAzNjaCg4NTVVUjJiZDRUUUFxdiZGSho6OSk5Pg4eFydHTCjaf3AAAAZElEQVQ4je2NSw7AIAhEBamKn97/uMXEGBvozkWb9C2Zx4xzWykBhFAeYp9gkLyZE0zIMno9n4g19hmdY39scwqVkOXaxph0ZCXQcqxSpgQpONa59wkRDOL93eAXvimwlbPbwwVAegLS1HGfZAAAAABJRU5ErkJggg==\") no-repeat left center;background-size: 1em;}</style>";
const String HTTP_SCRIPT        = "<script>function c(l){document.getElementById('s').value=l.innerText||l.textContent;document.getElementById('p').focus();}</script>";
const String HTTP_HEAD_END      = "</head><body><div style='text-align:left;display:inline-block;min-width:260px;'>";

const String HOMEPAGE = "<form action=\"/ff1\" method=\"get\"><button>ON</button></form><br/> <form action=\"/ff2\" method=\"get\"><button>OFF</button></form><br/> <form action=\"/wifi\" method=\"get\"><button>Configure </button></form><br/>";
//const String DID=" <form action=\"/did\" method=\"get\"><button>Device ID</button></form><br/>";
const String H1 ="<center><H3>";
const String H2 ="</H3></center>";
const String H3 ="<center><H4>";
const String H4 ="</H4></center>";
const String SEEIP="<center><h4>when connected to network  your IP address will show  </h4><br/><form action=\"/seeip\" method=\"get\"><button>Click to see IP </button></form><br/>  </center> ";
const String TRYTOWIFI="<center><h4> wait 20 second try again if not connect to network  </h4><br/><form action=\"/wifi\" method=\"get\"><button>Try again </button></form> </center> ";
const String NOTSAVEDWIFI="<center><h2>Sorry Try Again</h2><br/><form action=\"/wifi\" method=\"get\"><button>Try Again</button></form><br/>  </center> ";
const String WIFI1  = "<form method='get' action='wifisave'><input id='s' name='s' length=32 placeholder='SSID'><br/><br/><input id='p' name='p' length=64 type='password' placeholder='password'><br/>";
const String WIFI2  = "<br/><button type='submit'>save this network</button></form>";
const String APWIFI1  = "<form method='get' action='apwifisave'><input id='sss' name='sss' length=32 placeholder='SSID'><br/><br/><input id='ppp' name='ppp' length=64 type='password' placeholder='password'><br/>";
const String APWIFI2  = "<br/><button type='submit'>Change Access Point </button></form>";
const String IOT1 = "<form method='get' action='iot1'> <br/><button type='submit'> IOT Mode ON </button></form>";
const String IOT0 = "<form method='get' action='iot0'> <br/><button type='submit'> IOT Mode OFF </button></form>";
const String DID = "<form method='get' action='didsave'><input id='did' name='did' length=32 placeholder='Device ID'><br/> <br/><button type='submit'>Save Device ID  </button></form>";
const String BACKHOME="<center><form action=\"/\" method=\"get\"><button>Back to Home</button></form><br/>  </center> ";
const String MYIP="<center><H2>Your ip address  </center> ";
const String BTNRST="<form action=\"/0wifi\" method=\"get\"><button>Reset</button></form> <br/>";



int sw =0;


void handleRoot() {
String s =HTTP_HEAD;
       s += HTTP_STYLE;
      s += HTTP_SCRIPT;  
      s += HTTP_HEAD_END;
      s += "<H1>DCmoteRoom</H1>";
      s+=HOMEPAGE;
       s+= H1;
      s+= WiFi.localIP().toString();
      s+=H2;  
        s += "<center><H3>www.dcmote.xyz</H3></center>";
      
       
  server.send(200, "text/html", s);
    digitalWrite(D3,LOW);
     delay(50);
     digitalWrite(D3,HIGH);
    delay(50);
}



void wifi() {

  String s =HTTP_HEAD;
       s += HTTP_STYLE;
      s += HTTP_SCRIPT; 
      s += HTTP_HEAD_END;
       s+=H3;
      s+="Your Network ssid and password ";
      s+=H4;
      s+=WIFI1;  
      s+=WIFI2;  
      s+=H3;
      s+="Change Access Point ";
      s+=H4;
      s+=APWIFI1;  
      s+=APWIFI2;
      s+="<br/>";
      s+=DID;  
      s+=IOT1;     
      s+=IOT0;  
      s+="<br/>";
         
      
      s+=BTNRST;
       s+="<H6>";
      s+="When you click reset button device id is remove ";
       s+="<H6/>";
          s+="<H6>";
      s+=" and access point changing to default";
       s+="<H6/><br/>";
    //   s+=DID;
      
  
      
       
  server.send(200, "text/html", s);
    digitalWrite(D3,LOW);
     delay(50);
     digitalWrite(D3,HIGH);
    delay(50);
}
void seeip() {

  String s =HTTP_HEAD;
       s += HTTP_STYLE;
      s += HTTP_SCRIPT; 
      s += HTTP_HEAD_END;
      s+=MYIP;  
      s+=H1;
      s+= WiFi.localIP().toString();
      s+=H2;
      s += H3; 
      s+="ip address may be not found when not connected to network ";
      s +=H4;
      
  
      
       
  server.send(200, "text/html", s);
    digitalWrite(D3,LOW);
     delay(50);
     digitalWrite(D3,HIGH);
    delay(50);
}

void wifisave() {
 String ss= server.arg("s");
 String p= server.arg("p");
 
 if (ss=="" or p=="") {
  String s =HTTP_HEAD;
         s += HTTP_STYLE;
         s += HTTP_SCRIPT; 
         s += HTTP_HEAD_END;
         s += NOTSAVEDWIFI;
         server.send(200, "text/html", s);
  
  }else{
      
    
 
  String s =HTTP_HEAD;
         s += HTTP_STYLE;
         s += HTTP_SCRIPT; 
         s += HTTP_HEAD_END;
         s+=H1;  
         s+="Wifi Network is Saved "; 
         s+=H2; 
         s+=H1;
         s+=ss; 
         s+=H2;
         s+=H1;
         s+= WiFi.localIP().toString();
         s+=H2;
         s+=SEEIP;
         s+=TRYTOWIFI;
         server.send(200, "text/html", s);

            SPIFFS.begin();///////////////spiffs
         File myssid = SPIFFS.open("/myssid.txt", "w");
           File mypw = SPIFFS.open("/mypw.txt", "w");
         if (!myssid) {
        Serial.println("file open failed");
         }

         for (int i = 1; i <= 1; i++) {
        myssid.print(ss);
        mypw.print(p); 

         myssid.close();
           mypw.close();
        ESP.reset(); 
       
      }
               }

        digitalWrite(D3,LOW);
     delay(50);
     digitalWrite(D3,HIGH);
    delay(50);
       

}



void apwifisave() {
  Serial.begin(115200);
 String ss= server.arg("sss");
 String pp= server.arg("ppp");
 Serial.println(ss + "  "+ pp );
 if (ss=="" or pp=="") {
  String s =HTTP_HEAD;
         s += HTTP_STYLE;
         s += HTTP_SCRIPT; 
         s += HTTP_HEAD_END;
         s += NOTSAVEDWIFI;
         server.send(200, "text/html", s);
  
  }else{
      
    
 
  String s =HTTP_HEAD;
         s += HTTP_STYLE;
         s += HTTP_SCRIPT; 
         s += HTTP_HEAD_END;
         s+=H1;  
         s+="Wifi Network is Saved "; 
         s+=H2; 
         s+=H1;
         s+=ss; 
         s+=H2;
         s+=H1;
         s+= WiFi.softAPIP().toString();
         s+=H2;
     //    s+=SEEIP;
         s+=TRYTOWIFI;
         server.send(200, "text/html", s);

            SPIFFS.begin();///////////////spiffs
         File myapssid = SPIFFS.open("/ap.txt", "w");
           File myappw = SPIFFS.open("/apw.txt", "w");
         if (!myapssid) {
        Serial.println("file open failed");
         }

         for (int i = 1; i <= 1; i++) {
        myapssid.print(ss);
        myappw.print(pp); 

         myapssid.close();
           myappw.close();
        ESP.reset(); 
       
      }
               }
      
         digitalWrite(D3,LOW);
     delay(50);
     digitalWrite(D3,HIGH);
    delay(50);

}

void resetwifi() {
 
      
    
 
  String s =HTTP_HEAD;
         s += HTTP_STYLE;
         s += HTTP_SCRIPT; 
         s += HTTP_HEAD_END;
         s+=H1;  
         s+="Wifi Accesss Point has been reset "; 
         s+=H2; 
         s+=H3;  
         s+="See bellow to get default ssid and password  "; 
         s+=H4; 
         s+=H1;
         s+="your SSID"; 
         s+=H2;
         s+=H1;
         s+="dcmoteRoom"; 
         s+=H2;
         s+=H1;
         s+="your Password"; 
         s+=H2;
         s+=H1;
         s+="dcmoteroom"; 
         s+=H2;
         s+=H1;
         s+= WiFi.softAPIP().toString();
         s+=H2;
         s+=BACKHOME;
         
     
         server.send(200, "text/html", s);

            SPIFFS.begin();///////////////spiffs
         File myapssid = SPIFFS.open("/ap.txt", "w");
           File myappw = SPIFFS.open("/apw.txt", "w");
         if (!myapssid) {
        Serial.println("file open failed");
         }

         for (int i = 1; i <= 1; i++) {
        myapssid.print("dcmoteRoom");
        myappw.print("dcmoteroom"); 

         myapssid.close();
           myappw.close();
        ESP.reset(); 
       
      }
        digitalWrite(D3,LOW);
     delay(50);
     digitalWrite(D3,HIGH);
    delay(50);
              
}

//////////// did save 
void didsave() {
  Serial.begin(115200);
 String did= server.arg("did");

 Serial.println(did);
 if (did=="" ) {
  String s =HTTP_HEAD;
         s += HTTP_STYLE;
         s += HTTP_SCRIPT; 
         s += HTTP_HEAD_END;
         s += "Device ID Not Found ";
         server.send(200, "text/html", s);
  
  }else{
      
    
 
  String s =HTTP_HEAD;
         s += HTTP_STYLE;
         s += HTTP_SCRIPT; 
         s += HTTP_HEAD_END;
         s+=H1;  
         s+="Device ID is Saved "; 
         s+=H2; 
         s+=H1;
      //   s+=ss; 
         s+=H2;
         s+=H1;
    /////
         s+=H2;
     //    s+=SEEIP;
   ///      s+=TRYTOWIFI;
         server.send(200, "text/html", s);

            SPIFFS.begin();///////////////spiffs
         File mydid = SPIFFS.open("/did.txt", "w");
         
         if (!mydid) {
        Serial.println("file open failed");
         }

         for (int i = 1; i <= 1; i++) {
        mydid.print(did);
    

         mydid.close();
         
        ESP.reset(); 
       
      }
               }
      

         digitalWrite(D3,LOW);
     delay(50);
     digitalWrite(D3,HIGH);
    delay(50);

}

//////////////////////iot mode 
void iot1(){  server.send(200, "text/html", "<center><H1> IOT Mode is turned on</H></center>");     
     SPIFFS.begin();///////////////spiffs
         File iot = SPIFFS.open("/iot.txt", "w");
      
         if (!iot) {
        Serial.println("file open failed");
         }

         for (int i = 1; i <= 1; i++) {
        iot.print("ON");
           iot.close();
        ESP.reset(); 
       
}
  digitalWrite(D3,LOW);
     delay(50);
     digitalWrite(D3,HIGH);
    delay(50);


}

void iot0(){  server.send(200, "text/html", "<center><H1> IOT Mode is turned off</H1></center>");     
     SPIFFS.begin();///////////////spiffs
         File iot = SPIFFS.open("/iot.txt", "w");
      
         if (!iot) {
        Serial.println("file open failed");
         }

         for (int i = 1; i <= 1; i++) {
        iot.print("OFF");
           iot.close();
        ESP.reset(); 
       
}
  digitalWrite(D3,LOW);
     delay(50);
     digitalWrite(D3,HIGH);
    delay(50);
}
//////////////////////////// android 
void cmd0(){  server.send(200, "text/html", "DCmote Room ON");  digitalWrite(D1,HIGH);  digitalWrite(D3,LOW); delay(50); digitalWrite(D3,HIGH); delay(50);  }
void cmd1(){  server.send(200, "text/html", "DCmote Room OFF");   digitalWrite(D1,LOW); digitalWrite(D3,LOW); delay(50); digitalWrite(D3,HIGH); delay(50);  }




void on11() {
   digitalWrite(D1,HIGH);
  String s =HTTP_HEAD;
       s += HTTP_STYLE;
      s += HTTP_SCRIPT; 
      s += HTTP_HEAD_END;
       s += "<H1>DCmoteRoom</H1>";
      s+=HOMEPAGE;
       s+= H1;
      s+= WiFi.localIP().toString();
      s+=H2;  
        s += "<center><H3>www.dcmote.xyz</H3></center>";
      
       
  server.send(200, "text/html", s);
    digitalWrite(D3,LOW);
     delay(50);
     digitalWrite(D3,HIGH);
    delay(50);
}
void off11() {
        digitalWrite(D1,LOW);
  String s =HTTP_HEAD;
       s += HTTP_STYLE;
      s += HTTP_SCRIPT; 
      s += HTTP_HEAD_END;
      s += "<H1>DCmoteRoom</H1>";
      s+=HOMEPAGE;
       s+= H1;
      s+= WiFi.localIP().toString();
      s+=H2;  
        s += "<center><H3>www.dcmote.xyz</H3></center>";
      
       
  server.send(200, "text/html", s);
    digitalWrite(D3,LOW);
     delay(50);
     digitalWrite(D3,HIGH);
    delay(50);
}







void setup() {
    pinMode(D1,OUTPUT);
  pinMode(D2,INPUT_PULLUP);
  pinMode(D3,OUTPUT);
  digitalWrite(D3,HIGH);
   Serial.begin(115200);
    SPIFFS.begin();///////////////spiffs
    File apssid = SPIFFS.open("/ap.txt", "r");                               ///
    File  appw = SPIFFS.open("/apw.txt", "r");  
        File  mydid = SPIFFS.open("/did.txt", "r");  
          File  iot = SPIFFS.open("/iot.txt", "r");  
    ddd = mydid.readStringUntil(1);
        iotf = iot.readStringUntil(1);
    String sss = apssid.readStringUntil(1);   //('\n');                                 ///
    String ppp = appw.readStringUntil(1);
    apssid.close();
       appw.close();
     


    
    File myssid = SPIFFS.open("/myssid.txt", "r");                               ///
    File  mypw = SPIFFS.open("/mypw.txt", "r");  
    String s = myssid.readStringUntil(1);   //('\n');                                 ///
    String p = mypw.readStringUntil(1);
    myssid.close();
       mypw.close();
      mydid.close();
        iot.close();

       char apss[50];
    sss.toCharArray(apss, 50) ;
    char appp[50];
    ppp.toCharArray(appp, 50) ;
      
    Serial.println(ddd);
    Serial.println(s + "  " + p);
    Serial.println(sss + "  " + ppp);
    char ss[50];
    s.toCharArray(ss, 50) ;
    char pp[50];
    p.toCharArray(pp, 50) ;
  

  

  delay(1000);
 
  Serial.println();

  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(apss, appp);

IPAddress myIP  = WiFi.softAPIP();
 Serial.print("AP IP address: ");
  Serial.println(myIP);

  Serial.println("HTTP server started");
/////////////////////////////////////////////////////////////////////////////////////
///////// this code for connect to network

 WiFi.begin(ss, pp);
 // while (WiFi.status() != WL_CONNECTED) {
  //  delay(500);
  //  Serial.print(".");
 // }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  



  
  server.on("/", handleRoot);


   server.on("/ff1", on11);
  server.on("/ff2", off11);
 
  server.on("/wifi", wifi);
  server.on("/wifisave", wifisave);
  server.on("/apwifisave", apwifisave);
  server.on("/0wifi", resetwifi);
  server.on("/seeip", seeip);
  server.on("/didsave", didsave);    

      ////////////////// this code for android 
      server.on("/cmd0",cmd0);
      server.on("/cmd1",cmd1);

     
       
         server.on("/iot1",iot1);
            server.on("/iot0",iot0);  
         

      ;

          

      
     
        


  server.begin();

      path += "email=";
  path += "@indom";
  path += "&did=";
 // path += "2ca63cddd54f9490efad22421891a9d1";
    path += ddd;

}

void rest(){


   digitalWrite(D3,HIGH);
    delay(200);
     digitalWrite(D3,LOW);
     delay(200);
       digitalWrite(D3,HIGH);
    delay(200);
     digitalWrite(D3,LOW);
     delay(200);
       digitalWrite(D3,HIGH);
    delay(200);
     digitalWrite(D3,LOW);
     delay(200);
       digitalWrite(D3,HIGH);
    delay(200);
     digitalWrite(D3,LOW);
     delay(200);
       digitalWrite(D3,HIGH);
    delay(200);
     digitalWrite(D3,LOW);
     delay(200);
       digitalWrite(D3,HIGH);
    delay(200);
     digitalWrite(D3,LOW);
     delay(200);
      digitalWrite(D3,HIGH);
    delay(200);
      buttonState = digitalRead(D2);
      if (buttonState==LOW){ 
     digitalWrite(D3,HIGH);
    delay(100);
     digitalWrite(D3,LOW);
     delay(100);
       digitalWrite(D3,HIGH);
    delay(100);
     digitalWrite(D3,LOW);
     delay(100);
       digitalWrite(D3,HIGH);
    delay(100);
     digitalWrite(D3,LOW);
     delay(100);
        digitalWrite(D3,HIGH);
    delay(100);
     digitalWrite(D3,LOW);
     delay(100);
       digitalWrite(D3,HIGH);
    delay(100);
     digitalWrite(D3,LOW);
     delay(100);
       digitalWrite(D3,HIGH);
    delay(100);
     digitalWrite(D3,LOW);
     delay(100);
     digitalWrite(D3,HIGH);
    delay(100);

         SPIFFS.begin();///////////////spiffs
         File myapssid = SPIFFS.open("/ap.txt", "w");
           File myappw = SPIFFS.open("/apw.txt", "w");
             File iot = SPIFFS.open("/iot.txt", "w");
         if (!myapssid) {
        Serial.println("file open failed");
         }

         for (int i = 1; i <= 1; i++) {
        myapssid.print("dcmoteRoom");
        myappw.print("dcmoteroom"); 
           iot.print("OFF");



          
           iot.close();
         myapssid.close();
           myappw.close();
        ESP.reset(); 
         }
        
        }
    

  }

void loop() {
  unsigned long currentMillis = millis();
  server.handleClient();
    buttonState = digitalRead(D2);
  if (buttonState==LOW){ 
    rest();  } 

   
 // Serial.println(currentMillis);

if (currentMillis - previousMillis >= interval) {
  
    previousMillis = currentMillis;

  
if ( iotf=="OFF"   ){}else{
     const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
 
  //  Serial.println("connection failed");
     
     ///   if (rest>6){  rest=0; ESP.reset();}
    return;
  }
  

 //client.print(String("GET ") + path + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" +  "Connection: keep-alive\r\n\r\n");
   client.print(String("GET ") + path + " HTTP/1.1\r\n" +"Host: " + host + "\r\n" + "Connection: close\r\n\r\n");


  delay(30); // wait for server to respond

  while(client.available()){
 //    digitalWrite(pin2,HIGH);
     line = client.readStringUntil('\r');  
       
  
           result = line.substring(0,40);
// Serial.println(result);
 int data1 = result.indexOf("##");
//  Serial.println("The index of @ in the string " + result + " is " + data1);
 String Data =result.substring(1,data1);
// Serial.println(" Data is Tracked " + Data);

 int s1data = Data.indexOf("@1>");
  int s2data = Data.indexOf("@2>");
   int s3data = Data.indexOf("@3>");
    int s4data = Data.indexOf("@4>");
    int last =Data.indexOf('#');

    String s1= Data.substring(s1data,s2data);
     String s2= Data.substring(s2data,s3data);
      String s3= Data.substring(s3data,s4data);
       String s4= Data.substring(s4data,last);
   //  Serial.println(" My S1 data is  " + s1 );
   //   Serial.println(" My S2 data is  " + s2 );
   //    Serial.println(" My S3 data is  " + s3 );
   //     Serial.println(" My S4 data is  " + s4 );
 
           
      if (s1=="@1>on"){  digitalWrite(D1,HIGH);   }// Serial.println(" 1 is on");
       if (s2=="@2>on"){   }//  Serial.println(" 2 is on"); 
       if (s3=="@3>on"){      } //Serial.println(" 3 is on");
        if (s4=="@4>on"){    } //Serial.println(" 4 is on");  

          if (s1=="@1>off"){  digitalWrite(D1,LOW); } // Serial.println(" 1 is off");
          if (s2=="@2>off"){   } // Serial.println(" 2 is off"); 
          if (s3=="@3>off"){  } // Serial.println(" 3 is off"); 
          if (s4=="@4>off"){     } //Serial.println(" 4 is off");
          
       digitalWrite(D3,LOW);
     delay(50);
       digitalWrite(D3,HIGH);
    delay(50);
     digitalWrite(D3,LOW);
     delay(50);
     digitalWrite(D3,HIGH);
    delay(50);
  
  }
}

  }

  if (currentMillis>30000){currentMillis=0;}
}
 
 


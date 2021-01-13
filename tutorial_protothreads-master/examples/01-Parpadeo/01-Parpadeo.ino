#include <pt.h>

struct pt hilo1;
struct pt hilo2;
struct pt hilo3;



//Connect with pin 14 and 15
 // void gps1();
#include <TinyGPS.h>
//long   lat,lon; // create variable for latitude and longitude object
float lat,lon;
TinyGPS gps; // create gps object



#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN  9  //Pin 9 para el reset del RC522
  
#define SS_PIN  8   //Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); ///Creamos el objeto para el RC522
int con=0;


byte ActualUID[4]; //almacenará el código del Tag leído
byte Usuario1[4]= {0xE9, 0x95, 0xA4, 0x99} ; //código del usuario 1
byte Usuario2[4]= {0xD9, 0x0E, 0x40, 0xA3} ; //código del usuario 2

void setup() {
  Serial.begin(9600); // connect serial
Serial.println("The GPS Received Signal:");
Serial3.begin(9600); // connect gps sensor



  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13 , OUTPUT);
  pinMode(8,INPUT);
  Serial.begin(9600); //Iniciamos La comunicacion serial
  SPI.begin();        //Iniciamos el Bus SPI
  mfrc522.PCD_Init(); // Iniciamos el MFRC522
  Serial.println("Control de acceso:");

  
  PT_INIT(&hilo2);
  PT_INIT(&hilo1);
  PT_INIT(&hilo3);
  
}


void loop() {
  parpadeo(&hilo2);
  parpadeo(&hilo1);
  parpadeo(&hilo3);
}

void parpadeo(struct pt *pt) {
  PT_BEGIN(pt);
  // void setup() {
  static long t = 0;
  pinMode(12, OUTPUT);

  
  // }
  
  
  // void loop() {
  //Serial.println(f);


    int la,lo;
    while(Serial3.available()){ // check for gps data
    if(gps.encode(Serial3.read()))// encode gps data
    { 
    gps.f_get_position(&lat,&lon); // get latitude and longitude
      
   /* Serial.print("Position: ");
    
    //Latitude
    Serial.print("Latitude: ");
    Serial.print(lat,7);
    
    Serial.print(",");
    
    //Longitude
    Serial.print("Longitude: ");
    Serial.println(lon,6); 
    */
    //la=lat*1000000;
   // lo=lon*1000000;


     //Latitude
    //Serial.print("Latitude: \n");
    //Serial.print(la,7);
    
    //Serial.print(",");
    
    //Longitude
    //Serial.print("Longitude:\n ");
    //Serial.println(lo,6); 
    
   }
  }
   PT_END(pt);
}





void parpadeo2(struct pt *pt) {
  PT_BEGIN(pt);
  do{
// Revisamos si hay nuevas tarjetas  presentes
  if ( mfrc522.PICC_IsNewCardPresent()) 
        {  //Serial.println((String(ban)));
      //Seleccionamos una tarjeta
            if ( mfrc522.PICC_ReadCardSerial()) 
            { 
                  // Enviamos serialemente su UID
                  Serial.print(F("Card UID:"));
                  for (byte i = 0; i < mfrc522.uid.size; i++) {
                          Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                          Serial.print(mfrc522.uid.uidByte[i], HEX);   
                          ActualUID[i]=mfrc522.uid.uidByte[i];          
                  } 
                  Serial.print("     ");                 
                  //comparamos los UID para determinar si es uno de nuestros usuarios  
                  if(compareArray(ActualUID,Usuario1))
                    { 
                       
                        contador();
                    }
                    
                  else {          
                             Serial.println("Acceso denegado...");
                             digitalWrite(13,HIGH);
                             delay(1000);
                             digitalWrite(13, LOW);
                             delay(1000);
                  }
                                     
                  // Terminamos la lectura de la tarjeta tarjeta  actual
                  mfrc522.PICC_HaltA();
          
            }
 }
 } while(true);
  PT_END(pt);
}


 boolean compareArray(byte array1[],byte array2[])
{
  if(array1[0] != array2[0])return(false);
  if(array1[1] != array2[1])return(false);
  if(array1[2] != array2[2])return(false);
  if(array1[3] != array2[3])return(false);
  return(true);
}
void contador(){
  con=con+1;
  if (con==1)
  {
    digitalWrite(11, HIGH);
    delay(1000);
    Serial.println("Acceso activado...");
  }
  else{
    if(con==2)
    {
      digitalWrite(11, LOW);
      delay(1000);
      Serial.println("Acceso desactivado...");
      
    }
    con=0;    
  }
  Serial.println((String)(con));
  
 }






 

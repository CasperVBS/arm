#include <Wire.h> 
#include <Servo.h>    
#include <LiquidCrystal_I2C.h>

//scherm

LiquidCrystal_I2C lcd(0x27, 20, 4);

//servo maken
Servo servo_base;          
Servo servo_grijper; 
Servo servo_voor_achter; 
Servo servo_boven_onder;


int menu_Licht = 52;
int pos_draai_langzaam_controle = 0;
int pos_grijp_langzaam;
int pos_draai_langzaam;
int pos_open_langzaam;
int einde = 0;
int grijper_dicht_langzaam_controle = 0;
int grijper_open_langzaam_controle = 0;
int menue = 0;

// pottentiometer input voor manuele besturing
int potPin_Grijper = A0;
int potPin_Base = A1;
int potPin_voor_achter = A2;
int potPin_boven_onder = A3;

// pottentiometer waarde voor manuele besturing
int potVal_Grijper = 0;
int potVal_Base = 0;
int potVal_voor_achter = 0;
int potVal_boven_onder = 0;



//knop
int switchPinKnop1 = 40;
int switchStateKnop1 = LOW;

int switchPinKnop2 = 38;
int switchStateKnop2 = LOW;

int switchPinKnop3 = 42;
int switchStateKnop3 = LOW;

int switchPinKnop4 = 36;
int switchStateKnop4 = LOW;

int switchPinKnopMenue = 44;
int switchStateKnopMenue = LOW;

int switchPinReset = 26;
int switchStateReset = LOW;


void setup() {
 
// servo aan poort vast maken
  servo_base.attach(7);    
  servo_grijper.attach(6);    
  servo_voor_achter.attach(5);    
  servo_boven_onder.attach(5);   


// servo klaarzetten 
  servo_base.write(0);
  delay(40);
 // servo_grijper.write(40);
  delay(40);
 // servo_voor_achter.write(0);
  delay(40);  


//knop
    Serial.print("setuptest");
    Serial.begin(9600);
    delay(200);
    
     
    pinMode(switchPinReset, INPUT);
     delay(100);

     //knop bedining
      pinMode(switchPinKnop1, INPUT);
        delay(100);
      pinMode(switchPinKnop2, INPUT);
        delay(100);
      pinMode(switchPinKnop3, INPUT);
        delay(100);
      pinMode(switchPinKnop4, INPUT);
        delay(100);
      pinMode(switchPinKnopMenue, INPUT);
        delay(100);

  // licht 
   pinMode(menu_Licht, OUTPUT);
   
 //scherm
  lcd.init();                   // initialiseer het LCD scherm
  lcd.backlight();
 
}



void loop() {
       Serial.print("looptest");
     debug();
     controlerenKnopEinde();
       selectKnoppen();
       
      
    pot();
    
                   
  if (einde == 0){
    
 
   
  }
   

}

void selectKnoppen () {
          knoppenStateGeven();
          DebugKnoppen();
         
      if (switchStateKnop1 == HIGH) {
        
            if (menue == 0){
              
            }
            
           else if (menue == 1){
              //opdracht
            }
            delay(200);
         }
            
      if (switchStateKnop2 == HIGH) {

                    
            if (menue == 0){
                klappen();
                }
            
           if (menue == 1){
              //opdracht
            }
            delay(200);
        }
            
      if (switchStateKnop3 == HIGH) {

                    
            if (menue == 0){
              //opdracht
            }
            
           if (menue == 1){
             //opdracht 
            }
            delay(200);
        }
            
      if (switchStateKnop4 == HIGH) {

                    
            if (menue == 0){
              //opdracht
            }
            
           if (menue == 1){
             //opdracht 
            }
            delay(200);

        }


            // menue 
            
      if (switchStateKnopMenue == HIGH) {

                    
            if (menue == 0){
              menue = 1;
              digitalWrite(menu_Licht, HIGH);
            }
            
           else if (menue == 1){
              menue = 0;
              digitalWrite(menu_Licht, LOW);
            }
            delay(200);
        }
  
}




void pot(){
    // potentiometer meten
   potVal_Grijper  = analogRead(potPin_Grijper);
   potVal_Base = analogRead(potPin_Base);
   potVal_voor_achter   = analogRead(potPin_voor_achter);
   potVal_boven_onder   = analogRead(potPin_boven_onder);

   
   lcd.clear();
   lcd.setCursor(0, 0); 
   lcd.print("Grijper:");
   lcd.setCursor(16, 0);    
   lcd.print(potVal_Grijper);
   
   lcd.setCursor(0, 1); 
   lcd.print("Base:");
   lcd.setCursor(16, 1);    
   lcd.print(potVal_Base);
   
   lcd.setCursor(0, 2); 
   lcd.print("voor achter:");
   lcd.setCursor(16, 2);    
   lcd.print(potVal_voor_achter);
   
   lcd.setCursor(0, 3); 
   lcd.print("boven onder:");
   lcd.setCursor(16, 3);    
   lcd.print(potVal_boven_onder);
   
   delay(200);
}







void klappen (){

  for (int i = 0; i <= 100; i++) {
    servo_grijper.write(50);
    delay(300);
    servo_grijper.write(100);
    delay(300);
    controlerenKnopEinde();
  }
  
 
}

void openen (){
  servo_grijper.write(90);

    if (grijper_dicht_langzaam_controle == 0){

   for (pos_open_langzaam = 0; pos_open_langzaam == 90; pos_open_langzaam++){
    servo_grijper.write(pos_open_langzaam);
    delay(15);
    controlerenKnopEinde();
   }
     if (pos_open_langzaam = 90){
    
     grijper_open_langzaam_controle = 1;
     
    }
  }  
}




void grijpen (){

  if (grijper_dicht_langzaam_controle == 0){
  
  servo_grijper.write(90);

  for (pos_grijp_langzaam = 130; pos_grijp_langzaam >= 44; pos_grijp_langzaam--){
    
    servo_grijper.write(pos_grijp_langzaam);
    delay(15);
    controlerenKnopEinde();

  }
  if (pos_grijp_langzaam = 90){
    
     grijper_dicht_langzaam_controle = 1;
     
    }
  }
}


void base_draai_90(){
  if (pos_draai_langzaam_controle == 0){
    
  for (pos_draai_langzaam = 0; pos_draai_langzaam = 90; pos_draai_langzaam++){
    servo_base.write(pos_draai_langzaam);
    delay(10);
  }
  
  }

  
  pos_draai_langzaam_controle = 1;
  
  
}















void debug (){
  
   if (pos_grijp_langzaam = 1){

   // grijpen
    Serial.print("dicht");
    Serial.print(grijper_dicht_langzaam_controle);

    
    }
  }


void DebugKnoppen() {
          if (switchStateKnop1 == HIGH) {
        
            if (menue == 0){
                Serial.print("|1.1|");
            }
            
           else if (menue == 1){
                Serial.print("|2.1|");
            }
            
         }
           if (switchStateKnop2 == HIGH) {

                    
            if (menue == 0){
              Serial.print("|1.2|");
            }
            
           if (menue == 1){
              Serial.print("|2.2|");
            }
            
        }
            
      if (switchStateKnop3 == HIGH) {

                    
            if (menue == 0){
              Serial.print("|1.3|");
            }
            
           if (menue == 1){
             Serial.print("|2.3|"); 
            }
            
        }
            
      if (switchStateKnop4 == HIGH) {

                    
            if (menue == 0){
              Serial.print("|1.4|");
            }
            
           if (menue == 1){
             Serial.print("|2.4|"); 
            }
            
        } 
      
      if (switchStateKnopMenue == HIGH) {

                    
            if (menue == 0){
              Serial.print("menu1");
            }
            
           if (menue == 1){
             Serial.print("menu2"); 
            }
            
        } 
}


void MeneuLicht(){
             if (menue == 0){
             digitalWrite(menu_Licht, LOW);
            }
            
           if (menue == 1){
             digitalWrite(menu_Licht, HIGH); 
            }
}

void knoppenStateGeven(){
  switchStateKnop1 = digitalRead(switchPinKnop1);
  switchStateKnop2 = digitalRead(switchPinKnop2);
  switchStateKnop3 = digitalRead(switchPinKnop3);
  switchStateKnop4 = digitalRead(switchPinKnop4);
  switchStateKnopMenue = digitalRead(switchPinKnopMenue);
}







void controlerenKnopEinde(){
    switchStateReset = digitalRead(switchPinReset); 
   

    if (switchStateReset == HIGH) {
      eindPositsie();
    }
}

void eindPositsie (){
  servo_base.write(0);
  delay(40);
  servo_grijper.write(0);
  delay(40);
  servo_voor_achter.write(0);
  delay(40);
 
  einde = 1;
   
  }

  

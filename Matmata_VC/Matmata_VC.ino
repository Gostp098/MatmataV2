#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define the pin numbers for the components
const int motorForwardPin = 0;    // Motor forward  (left motor)
const int motorBackwardPin = 1;   // Motor backward  (right motor)
const int waterPumpPin = 2;       // Water pump 
const int waterOutPumpPin = 3;    // Water out pump  (drain)
const int spinningPin = 4;        // Spinning 
const int DoorContactPin = 5;     // Door contact 
const int WaterHeater = 6;        // Water heater 
const int prduit_PL = 7;            //  relay prela
const int produit_L = 8;            // Empty relay 
const int produit_R = 9;            // Empty relay 
const int PO1 = 10;            // Dorr oneing pulsation
const int PC2 = 11;            // door closing pulsation



const int buttonNextPin = A0;  // Pin for the next button
const int buttonPrevPin = A1;  // Pin for the previous button
const int buttonSelectPin = A2; // Pin for the select button

const int numPrograms = 9;    // Number of programs
int currentProgram = 0;       // Current selected program

LiquidCrystal_I2C lcd(0x27, 20, 4); // 20x4 LCD setup

// Program names (update with your own program names)
String programNames[] = {"Energetique", "Couleur  ", "Cotton  ", "Delicat", "Courte  ", "Rincage ", "Blanc   ", "TEST  ", "VIDE"};

void setup() {
  // Set the pins as outputs or inputs
  pinMode(motorForwardPin, OUTPUT);
  pinMode(motorBackwardPin, OUTPUT);
  pinMode(waterPumpPin, OUTPUT);
  pinMode(waterOutPumpPin, OUTPUT);
  pinMode(spinningPin, OUTPUT);
  pinMode(DoorContactPin, OUTPUT);
  pinMode(WaterHeater, OUTPUT);
  pinMode(prduit_PL, OUTPUT);
  pinMode(produit_L, OUTPUT);
  pinMode(produit_R, OUTPUT);

    // Initialize components to default state
  digitalWrite(motorForwardPin, 1);
  digitalWrite(motorBackwardPin, 1);
  digitalWrite(waterPumpPin, 1);
  digitalWrite(waterOutPumpPin, 1);
  digitalWrite(spinningPin, 1);
  digitalWrite(WaterHeater, 1);
  digitalWrite(DoorContactPin, 1);
  digitalWrite(prduit_PL, 1);
  digitalWrite(produit_L, 1);
  digitalWrite(produit_R, 1);

  pinMode(buttonNextPin, INPUT);
  pinMode(buttonPrevPin, INPUT);
  pinMode(buttonSelectPin, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Select Program:");
  lcd.setCursor(0, 1);
  lcd.print(programNames[currentProgram]);

   return ; 
}

void loop() {
  int buttonNextState = digitalRead(buttonNextPin);
  int buttonPrevState = digitalRead(buttonPrevPin);
  int buttonSelectState = digitalRead(buttonSelectPin);

  if (buttonNextState == HIGH) {
    currentProgram = (currentProgram + 1) % numPrograms;
    lcd.setCursor(0, 1);
    lcd.print("                "); // Clear the previous program name
    lcd.setCursor(0, 1);
    lcd.print(programNames[currentProgram]);
    delay(200); // Debounce delay
  }

  if (buttonPrevState == HIGH) {
    currentProgram = (currentProgram - 1 + numPrograms) % numPrograms;
    lcd.setCursor(0, 1);
    lcd.print("                "); // Clear the previous program name
    lcd.setCursor(0, 1);
    lcd.print(programNames[currentProgram]);
    delay(200); // Debounce delay
  }

  if (buttonSelectState == HIGH) {
    // Run the selected program
    runProgram(currentProgram);
    delay(200); // Debounce delay
  }
}

void runProgram(int programNumber) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("EnCours:");
  
  lcd.print(programNames[programNumber]);

  // Add code to run the selected program here
  // For example:
  switch (programNumber) {
    case 0:
    // energetique
    digitalWrite(DoorContactPin, 0);
    digitalWrite(PO1, 0);
        3000;
    digitalWrite(PO1, 1);



    displayText("50 min "); 
preWashing();
WashingHotCycle();
    displayText("20 min");    
Rinsing();
    displayText("15 min");   
Rinsing();
    displayText("10 min");   
Spinning();      
EndProg();
      break;
      
    case 1:
//coleur
digitalWrite(DoorContactPin, 0);
    digitalWrite(PO1, 0);
        3000;
    digitalWrite(PO1, 1);

WashingColdCycle();
  displayText("20 min");    
Rinsing();
  displayText("15 min");   
Rinsing();
  displayText("10 min");   
Spinning();      
EndProg();

      break;
    case 2:
      // Code for Program 3 COTTON

digitalWrite(DoorContactPin, 0);
    digitalWrite(PO1, 0);
        3000;
    digitalWrite(PO1, 1);

WashingColdCycleV2();
displayText("15 min");   
Rinsing();
  displayText("10 min");   
Spinning();      
EndProg();


      break;
    case 3:
    //Delicat
    digitalWrite(DoorContactPin, 0);
        digitalWrite(PO1, 0);
        3000;
    digitalWrite(PO1, 1);

displayText("30 min");      
    preWashing();
displayText("20 min");     
    Rinsing();
displayText("15 min");   
    Rinsing();
displayText("10 min");   
    Spinning();      
    EndProg();


      break;
    case 4:
//COURTE

digitalWrite(DoorContactPin, 0);
    digitalWrite(PO1, 0);
        3000;
    digitalWrite(PO1, 1);

displayText("12 min");   
Rinsing();
displayText("8 min");   
SpinningShortCycle();      
EndProg();
      break;


    case 5:
     
      // Code for Program 7 Rincage

digitalWrite(DoorContactPin, 0);
    digitalWrite(PO1, 0);
        3000;
    digitalWrite(PO1, 1);

displayText("15 min");   
Rinsing();
displayText("10 min");   
Spinning();      
EndProg();


      break;
    case 6:
      // Code for Program 8 Blanc
digitalWrite(DoorContactPin, 0);
    digitalWrite(PO1, 0);
        3000;
    digitalWrite(PO1, 1);

displayText("45 min"); 
    preWashing();
    WashingHotCycleV2();
displayText("15 min");   
  Rinsing();
displayText("10 min");   
  Spinning();      
  EndProg();

      break;
    case 7:
 
// Script essai

displayText("60 s ");
testMotorForward();


displayText("54 s ");
testMotorBackward();


displayText("48 s ");
testWaterPump();


displayText("42 s ");
testVidange();


displayText("36 s ");
testSpinningetVidange();


displayText("30 s ");
    digitalWrite(PO1, 0);
        3000;
    digitalWrite(PO1, 1);
testProte();

    digitalWrite(PC2, 0);
        3000;
    digitalWrite(PC2, 1);




displayText("24 s"); 
testHeater();



displayText("18 s "); 
testProduit();
displayText("Completed!"); 
 delay(5000);

  break;
case 8:
displayText("Programme vide ");

        delay(5000);
/*
displayText("18 s "); 
//testProduit();

 EndProg();

      // Code for Program 8 vide
      WashingHotCycle();
 test1();
/* displayText("15 min");   
Rinsing();
displayText("10 min");   
Spinning();     */  /*
    lcd.setCursor(0, 3);         // Set cursor to the desired position
    lcd.print("                "); // Clear the line
    lcd.setCursor(0, 2);         // Set cursor to the desired position
    lcd.print("                "); // Clear the line
EndProg();  */
      break;



 


   
  }

  // Add a delay or other mechanism to let the user know the program is running
  delay(1000); // 1 second delay for demonstration
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Select Program:");
  lcd.setCursor(0, 1);
  lcd.print(programNames[currentProgram]);
}


void displayText(const char* text) {
    lcd.setCursor(0, 3);         // Set cursor to the desired position
    lcd.print("                "); // Clear the line
    lcd.setCursor(0, 3);         // Set cursor back to the same position
    lcd.print(text);              // Print the text passed as parameter
}




//prelave
void preWashing() {
   


   digitalWrite(prduit_PL, 0); 

   digitalWrite(waterPumpPin, 0); 

   digitalWrite(waterOutPumpPin, 0);
    // Toggle reserve relay
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("Prelavage");

 const int cycleCount = 9; // Number of washing cycles

  for (int cycle = 0; cycle < cycleCount; cycle++) {
    // Forward
    digitalWrite(motorForwardPin, 0);
    delay(30000);  // 30s in milliseconds
    digitalWrite(motorForwardPin, 1);
    delay(2000);

    // Backward
Backward();

  }
    digitalWrite(waterPumpPin, 0); 
    delay(2000); // A3ML DELAY BIN PRELAV O VIDABGE     

      digitalWrite(waterOutPumpPin, 1);
     digitalWrite(prduit_PL, 1); 


Draining();
}


//lavage
void WashingHotCycle() {
  digitalWrite(produit_L, 0);  
   digitalWrite(WaterHeater, 0); 
   digitalWrite(waterPumpPin, 0); 

   digitalWrite(waterOutPumpPin, 0);
  
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("lavage chaud");

   displayText("40 min "); 
 const int cyclecount = 10; // Number of washing cycles

  for (int cycle = 0; cycle < cyclecount; cycle++) {
    // Forward
    digitalWrite(motorForwardPin, 0);
    delay(30000);  // 30s in milliseconds
    digitalWrite(motorForwardPin, 1);
    delay(2000);

    // Backward
Backward();

  }

     displayText("30 min "); 

   const int cycleCount = 10; // Number of washing cycles

  for (int cycle = 0; cycle < cycleCount; cycle++) {
    // Forward
    digitalWrite(motorForwardPin, 0);
    delay(30000);  // 30s in milliseconds
    digitalWrite(motorForwardPin, 1);
    delay(2000);

    // Backward
Backward();

  }


    digitalWrite(waterPumpPin, 0); 
    delay(2000); // A3ML DELAY BIN PRELAV O VIDABGE     

      digitalWrite(waterOutPumpPin, 1);
      digitalWrite(WaterHeater, 1);
      digitalWrite(produit_L, 1);  
Draining();
}


//lavage
void WashingHotCycleV2() {
  digitalWrite(produit_L, 0);  
   digitalWrite(WaterHeater, 0); 
   digitalWrite(waterPumpPin, 0); 

   digitalWrite(waterOutPumpPin, 0);
  
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("lavage chaud");

   displayText("35 min "); 
 const int cyclecount = 10; // Number of washing cycles

  for (int cycle = 0; cycle < cyclecount; cycle++) {
    // Forward
    digitalWrite(motorForwardPin, 0);
    delay(30000);  // 30s in milliseconds
    digitalWrite(motorForwardPin, 1);
    delay(2000);

    // Backward
Backward();

  }

     displayText("35 min "); 

   const int cycleCount = 10; // Number of washing cycles

  for (int cycle = 0; cycle < cycleCount; cycle++) {
    // Forward
    digitalWrite(motorForwardPin, 0);
    delay(30000);  // 30s in milliseconds
    digitalWrite(motorForwardPin, 1);
    delay(2000);

    // Backward
Backward();

  }


    digitalWrite(waterPumpPin, 0); 
    delay(2000); // A3ML DELAY BIN PRELAV O VIDABGE     

      digitalWrite(waterOutPumpPin, 1);
      digitalWrite(WaterHeater, 1);
      digitalWrite(produit_L, 1);  
Draining();
}




//lavage
void WashingColdCycle() {
   
  // digitalWrite(WaterHeater, 0); 
   digitalWrite(produit_L, 0);  

   digitalWrite(waterPumpPin, 0); 

   digitalWrite(waterOutPumpPin, 0);
    // Toggle reserve relay
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("Lavage froid");

   displayText("40 min "); 
 const int cyclecount = 10; // Number of washing cycles

  for (int cycle = 0; cycle < cyclecount; cycle++) {
    // Forward
    digitalWrite(motorForwardPin, 0);
    delay(30000);  // 30s in milliseconds
    digitalWrite(motorForwardPin, 1);
    delay(2000);

    // Backward
Backward();

  }

     displayText("30 min "); 

   const int cycleCount = 10; // Number of washing cycles

  for (int cycle = 0; cycle < cycleCount; cycle++) {
    // Forward
    digitalWrite(motorForwardPin, 0);
    delay(30000);  // 30s in milliseconds
    digitalWrite(motorForwardPin, 1);
    delay(2000);

    // Backward
Backward();

  }




    digitalWrite(waterPumpPin, 0); 
    delay(2000); // A3ML DELAY BIN PRELAV O VIDABGE     
      
      digitalWrite(produit_L, 1);  
      digitalWrite(waterOutPumpPin, 1);
  //    digitalWrite(WaterHeater, 1);

Draining();
}




//lavage pour les cycle qui on un seul rincage
void WashingColdCycleV2() {
   
  // digitalWrite(WaterHeater, 0); 
   digitalWrite(produit_L, 0);  

   digitalWrite(waterPumpPin, 0); 

   digitalWrite(waterOutPumpPin, 0);
    // Toggle reserve relay
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("Lavage froid");

   displayText("35 min "); 
 const int cyclecount = 10; // Number of washing cycles

  for (int cycle = 0; cycle < cyclecount; cycle++) {
    // Forward
    digitalWrite(motorForwardPin, 0);
    delay(30000);  // 30s in milliseconds
    digitalWrite(motorForwardPin, 1);
    delay(2000);

    // Backward
Backward();

  }

     displayText("25 min "); 

   const int cycleCount = 10; // Number of washing cycles

  for (int cycle = 0; cycle < cycleCount; cycle++) {
    // Forward
    digitalWrite(motorForwardPin, 0);
    delay(30000);  // 30s in milliseconds
    digitalWrite(motorForwardPin, 1);
    delay(2000);

    // Backward
    Backward();

  }




    digitalWrite(waterPumpPin, 0); 
    delay(2000); // A3ML DELAY BIN PRELAV O VIDABGE     
      
      digitalWrite(produit_L, 1);  
      digitalWrite(waterOutPumpPin, 1);
  //    digitalWrite(WaterHeater, 1);

Draining();
}


//rinsage
void Rinsing() {


   digitalWrite(produit_R, 0);  
  digitalWrite(waterPumpPin, 0); 
     digitalWrite(waterOutPumpPin, 0);
 // Toggle reserve relay
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("Rinsage");

  const int cycleCount = 3; // Number of cycles each cycle is 1 min

  for (int cycle = 0; cycle < cycleCount; cycle++) {
    // Forward
    digitalWrite(motorForwardPin, 0);
    delay(30000);  // 30s in milliseconds
    digitalWrite(motorForwardPin, 1);
    delay(2000);

    // Backward
  Backward();

  }

     
     digitalWrite(waterOutPumpPin, 1);

      digitalWrite(waterPumpPin, 1); 
      digitalWrite(produit_R, 1);  

delay(2000);
Draining();
}




//Vidange
void Draining() {

digitalWrite(waterOutPumpPin, 1);

 const int cycleCount = 1; // Number of washing cycles

  for (int cycle = 0; cycle < cycleCount; cycle++) {
    // Forward
    digitalWrite(motorForwardPin, 0);
    delay(30000);  // 30s in milliseconds
    digitalWrite(motorForwardPin, 1);
    delay(2000);

    // Backward
Backward();


  }
      digitalWrite(waterOutPumpPin, 0);
  delay(2000);
}



//esorage 9 min
void Spinning() {
 // digitalWrite(spinningLED, HIGH);
  // Toggle reserve relay
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("Essorage");
 digitalWrite(spinningPin, LOW);
     digitalWrite(waterOutPumpPin, 1);
     
      digitalWrite(spinningPin, 0);
      digitalWrite(motorForwardPin, 0);

                delay(540000);// 9 min
      digitalWrite(motorForwardPin, 1);
      digitalWrite(spinningPin, 1);  
      
      
    digitalWrite(waterOutPumpPin, 0);






}

void EndProg(){


 delay(30000); // 1min
  digitalWrite(DoorContactPin, 1);
  
    digitalWrite(PC2, 0);
        3000;
    digitalWrite(PC2, 1);

    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("Fin du Programme");
       lcd.setCursor(0, 3);
    lcd.print("                ");
 blinkText("OUVRIR LA PORTE", 0, 2, 30); // Blink text at (0,1) for 30 times
  delay(5000); // Wait a few seconds before blinking again
}

void blinkText(const char* text, int col, int row, int durationSeconds) {
  for (int i = 0; i < durationSeconds; i++) {
    lcd.setCursor(col, row);
    lcd.print(text);         // Display the text
    delay(500);              // Half a second delay (on)
    lcd.setCursor(col, row);
    lcd.print("                "); // Clear text (off)
    delay(500);              // Half a second delay (off)
  }
}

void testMotorForward() {
 // Assuming a pin has been connected to a relay
 digitalWrite(motorForwardPin, LOW);

    lcd.setCursor(0, 1);
    lcd.print("test Gauche");
 delay(5000);
 digitalWrite(motorForwardPin, HIGH);
 delay(1000);
}

void testMotorBackward() {
 // Assuming a pin has been connected to a relay
 digitalWrite(motorBackwardPin, LOW);
  digitalWrite(motorForwardPin, LOW);


 
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("test droite");

 delay(5000);
 digitalWrite(motorBackwardPin, HIGH);
  digitalWrite(motorForwardPin, HIGH);

 
 delay(1000);
}
void testWaterPump() {
      lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("test remplissage");

  digitalWrite(waterPumpPin, 0);
  delay(5000);

  digitalWrite(waterPumpPin, 1);
  delay(1000);

}
// logique vidange 3ks test
void testVidange(){
 digitalWrite(waterOutPumpPin, 0);
      lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("test vidange");


 delay(5000);
  digitalWrite(waterOutPumpPin, 1);
   delay(1000);

   

}


void testSpinningetVidange() {
 // Assuming a pin has been connected to a relay

     lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("test essorage");

 digitalWrite(spinningPin, LOW);
 digitalWrite(motorBackwardPin, LOW);

 delay(5000);

 digitalWrite(spinningPin, HIGH);
 digitalWrite(motorBackwardPin, HIGH);


 delay(1000);
}

void testProte() {
// Toggle DoorContactPin relay
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("test Porte");
  digitalWrite(DoorContactPin, 0);
  delay(5000);
  digitalWrite(DoorContactPin, 1);
  delay(1000);
}

void testHeater(){
  // Toggle WaterHeater relay

    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("test chauffage");
  digitalWrite(WaterHeater, 0);

  delay(5000);
  digitalWrite(WaterHeater, 1);
  delay(1000);
}

void testProduit(){
  // Toggle reserve relay
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("test produit");

  digitalWrite(prduit_PL, 0);
  delay(5000);
  digitalWrite(prduit_PL, 1);
  delay(1000);

    digitalWrite(produit_L, 0);
  delay(5000);
  digitalWrite(produit_L, 1);
  delay(1000);

    digitalWrite(produit_R, 0);
  delay(5000);
  digitalWrite(produit_R, 1);
  delay(1000);


}

//esorage 7 min
void SpinningShortCycle() {
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("Essorage");
 digitalWrite(spinningPin, LOW);
     digitalWrite(waterOutPumpPin, 1);
     
      digitalWrite(spinningPin, 0);
      digitalWrite(motorForwardPin, 0);

                delay(420000); //7 min
      digitalWrite(motorForwardPin, 1);
      digitalWrite(spinningPin, 1);  
      
      
    digitalWrite(waterOutPumpPin, 0);


}

void Backward(){


    // Backward
    digitalWrite(motorBackwardPin, 0);
    digitalWrite(motorForwardPin, 0);

    delay(30000);  // 30s in milliseconds
    digitalWrite(motorBackwardPin, 1);
    digitalWrite(motorForwardPin, 1);
    delay(2000);

}

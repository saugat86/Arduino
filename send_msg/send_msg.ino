#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
// Create an LCD object. Parameters: (RS, E, D4, D5, D6, D7):
LiquidCrystal lcd = LiquidCrystal(0, 1, 8, 9, 10, 11);
// Configure software serial port
SoftwareSerial SIM900(6,7); 

void setup() {
  // Arduino communicates with SIM900 GSM shield at a baud rate of 19200
  // Make sure that corresponds to the baud rate of your module
  SIM900.begin(19200);
  lcd.begin(16, 2); 
  // Give time to your GSM shield log on to network
  delay(20000);   
  
  // Send the SMS
  if(!sendSMS()){
    // Set the cursor on the third column and the first row, counting starts at 0:
    lcd.setCursor(2, 0);
    // Print the string 'Hello World!':
    lcd.print("Successfully send data!");
  }
  else{
    // Set the cursor on the third column and the first row, counting starts at 0:
    lcd.setCursor(2, 0);
    // Print the string 'Hello World!':
    lcd.print("Unsuccessful!");
  }
}

void loop() { 
  
}

bool sendSMS() {
  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM900.println("AT+CMGS=\"+9779808874501\""); 
  delay(100);
  
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  SIM900.println("Message example from Arduino Uno."); 
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26); 
  delay(100);
  SIM900.println();
  // Give module time to send SMS
  delay(5000); 
}

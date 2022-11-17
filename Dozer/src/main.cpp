#include <Arduino.h>
#include "LiquidCrystal_I2C.h"
#include "Keypad.h"
#include "defs.h"
#include "AccelStepper.h"

// define
#define DRV_M0 12
#define DRV_M1 14
#define DRV_EN 13
#define DRV_RESET 27
#define DRV_SLEEP 26
#define DRV_STEP 25
#define DRV_DIR 33
#define motorInterfaceType 1

LiquidCrystal_I2C lcd(0x27, 20, 4);
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
AccelStepper myStepper = AccelStepper(motorInterfaceType, DRV_STEP, DRV_DIR);

void keypadEvent(KeypadEvent key);
boolean blink = false;
boolean ledPin_state;
const int stepsPerRevolution = 200;
String inputString;
int inputValue;
int dispenseAmount = 0;
String outPut;
int currentPosition;



void setup()
{
    Serial.begin(115200);
    lcd.init();
    lcd.init();
    lcd.setCursor(4, 1);
    lcd.print("Dozer V 0.0.1");
    // Store initial LED state. HIGH when LED is on.
    keypad.addEventListener(keypadEvent); // Add an event listener for this keypad
    pinMode(DRV_M0, OUTPUT);
    pinMode(DRV_M1, OUTPUT);
    pinMode(DRV_EN, OUTPUT);
    pinMode(DRV_RESET, OUTPUT);
    pinMode(DRV_SLEEP, OUTPUT);
    digitalWrite(DRV_M0, LOW);
    digitalWrite(DRV_M1, LOW);
    digitalWrite(DRV_EN, LOW);
    digitalWrite(DRV_RESET, HIGH);
    digitalWrite(DRV_SLEEP, HIGH);
    delay(1000);
    pinMode(LED_BUILTIN, OUTPUT);
    lcd.clear();
    myStepper.setMaxSpeed(1000);
	myStepper.setAcceleration(800);
	myStepper.setSpeed(600);
	
}

void loop()
{
    char key = keypad.getKey();
    

    if (key)
    {
        lcd.clear();
        Serial.println(key);
        outPut = outPut + key;
        inputString = inputString + key;
        inputValue = inputString.toInt();
        lcd.print(outPut);
        
        
    }

}

// Taking care of some special events.
void keypadEvent(KeypadEvent key)
{
    switch (keypad.getState())
    {
    case PRESSED:
        if (key == 'D')
        {
            dispenseAmount = dispenseAmount + (outPut.toInt()*200);
            Serial.print(dispenseAmount);
            myStepper.moveTo(dispenseAmount);
            while( myStepper.distanceToGo() != 0){
                myStepper.run();
            }
        
            
            lcd.clear();
            lcd.print("Dispensing");
            lcd.print("  ");
            lcd.print(outPut);
            delay(1000);
            lcd.clear();
            lcd.print("Done dipensing");
            outPut="";
            

            lcd.clear();
        }
        else if (key == 'C')
        {
            outPut="";
        }
        break;

        case RELEASED:
            if (key == 'D')
            {
                outPut="";
            }
            break;

        // case HOLD:
        //     if (key == '*')
        //     {
        //         Serial.println("I am held"); // Blink the LED when holding the * key.
        //     }
        //     break;
    }
}
// // Set the current position to 0:
// stepper.setCurrentPosition(0);

// // Run the motor forward at 200 steps/second until the motor reaches 400 steps (2 revolutions):
// while (stepper.currentPosition() != 400)
// {
//     stepper.setSpeed(200);
//     stepper.runSpeed();
// }

// delay(1000);

// // Reset the position to 0:
// stepper.setCurrentPosition(0);

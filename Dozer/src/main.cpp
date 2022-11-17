#include <Arduino.h>
#include "LiquidCrystal_I2C.h"
#include "Keypad.h"
#include "defs.h"
#include "AccelStepper.h"

// define
#define DRV_M0 32
#define DRV_M1 31
#define DRV_EN 34
#define DRV_RESET 30
#define DRV_SLEEP 29
#define DRV_STEP 28
#define DRV_DIR 27
#define motorInterfaceType 1

LiquidCrystal_I2C lcd(0x27, 20, 4);
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
AccelStepper stepper = AccelStepper(motorInterfaceType, DRV_STEP, DRV_DIR);

////
byte ledPin = 2;

boolean blink = false;
boolean ledPin_state;
const int stepsPerRevolution = 200;

void setup()
{
    Serial.begin(115200);
    lcd.init();
    lcd.setCursor(4,1);
    lcd.print("Dozer V 0.0.1");
    pinMode(LED_BUILTIN, OUTPUT);    // Sets the digital pin as output.
    digitalWrite(LED_BUILTIN, HIGH); // Turn the LED on.
    // ledPin_state = digitalRead(ledPin);   // Store initial LED state. HIGH when LED is on.
    // keypad.addEventListener(keypadEvent); // Add an event listener for this keypad
    pinMode(DRV_M0, OUTPUT);
    pinMode(DRV_M1, OUTPUT);
    pinMode(DRV_EN, OUTPUT);
    pinMode(DRV_RESET, OUTPUT);
    pinMode(DRV_SLEEP, OUTPUT);
    digitalWrite(DRV_M0, HIGH);
    digitalWrite(DRV_M1, HIGH);
    digitalWrite(DRV_EN, LOW);
    digitalWrite(DRV_RESET, HIGH);
    digitalWrite(DRV_SLEEP, HIGH);
    delay(1000);
    lcd.clear();
}

void loop()
{
        char key = keypad.getKey();

        if (key) {
            Serial.println(key);
        }
        if (blink){
            digitalWrite(ledPin,!digitalRead(ledPin));    // Change the ledPin from Hi2Lo or Lo2Hi.
            delay(100);
        }
    }

    // Taking care of some special events.
    void keypadEvent(KeypadEvent key){
        switch (keypad.getState()){
        case PRESSED:
            if (key == '#') {
                Serial.print("Hello World!");     // Remember LED state, lit or unlit.
            }
            break;

        case RELEASED:
            if (key == '*') {
                digitalWrite(LED_BUILTIN,ledPin_state);    // Restore LED state from before it started blinking.
                blink = false;
            }
            break;

        case HOLD:
            if (key == '*') {
                blink = true;    // Blink the LED when holding the * key.
            }
            break;
        }
    // Set the current position to 0:
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
}

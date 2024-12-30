#include "Keyboard.h"

const char keyCode = '^';      // Setzten der Taste die gedrückt werden soll, format: 'Taste'
const int buttonPin = 2;       // Pin, an dem der Taster angeschlossen ist
const unsigned long debounceDelay = 50; // Entprellzeit in Millisekunden

bool buttonState = HIGH;       // Aktueller Zustand des Buttons
bool lastButtonState = HIGH;   // Letzter Zustand des Buttons
unsigned long lastDebounceTime = 0; // Zeit, wann der Zustand zuletzt geändert wurde

void setup() {
  // Konfiguriere mit Pull-up-Widerstand
  pinMode(buttonPin, INPUT_PULLUP);

  Keyboard.begin();
}

void loop() {
  // Lese den aktuellen Zustand des Buttons
  int reading = digitalRead(buttonPin);

  // Prüfen, ob der Zustand sich geändert hat
  if (reading != lastButtonState) {
    // Entprell-Zeit starten
    lastDebounceTime = millis();
  }

  // Wenn die Entprellzeit abgelaufen ist
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Wenn sich der Zustand tatsächlich geändert hat
    if (reading != buttonState) {
      buttonState = reading;

      // Aktionen basierend auf dem Button-Zustand
      if (buttonState == LOW) {
        Keyboard.press(keyCode); 
      } else {
        Keyboard.releaseAll();  
      }
    }
  }

  lastButtonState = reading;
}

#include <Arduino.h>

//WristByte firmware, step 1: keep time and print it over serial
//No display yet. The button pin can change once the board exists

const int BTN_PIN = 0; //BOOT button on the ESP32 device
its
const unsigned long DEBOUNCE_MS = 40;

int hours = 12, minutes = 0, seconds = 0,
unsigned long lastTick = 0;

bool lastReading = HIGH;
bool stableState = HIGH;
unsigned long lastChange = 0;

void tickSecond() {
    seconds++;
    if (seconds >= 60) { seconds = 0; minutes++; }
    if (minutes >= 60) { minutes = 0; hours++; }
    if (hours >=24)  hours = 0;
}

void printTime() {
    char buf[9]
    snprint(buf, sizeof(buf), "%02d:%02d:%02d", hours, minutes, seconds);
    Serial.println(buf);
}

//Each press adds one minutes, so there's a way to set the time for now.
void handleButton() {
    bool reading = digitalRead(BTN_PIN);
    if (reading != lastReading) {
        lastChange = millis();
        lastReading = reading;
    
    }

    if (millis() - lastChange > DEBOUNCE_MS && reading != stableState) {
        stableState = reading;
        if (stableState == LOW) {
            minutes = (minutes + 1) % 60;
            seconds = 0
            printTime()
        }
    }
}

void setup() {
    Serial.begin(115200)
    pinMode(BTN_PIN, INPUT_PULLUP);
    Serial.println("WristByte booting...")
}

void loop() {
    handleButton();
    if (millis() - lastTick >= 1000) {
        lastTick += 1000;
        tickSecond();
        printTime()
    }
}
const int BANK_PIN = 9;
const int ROW_PINS[] = {1, 0, 2, 3, 4, 5, 6, 7};
const int COLUMN_PINS[] = {17, 18, 19, 23, 13, 22, 11, 12};
const int PIEZO_PIN = 8;

#include "pitches.h"
#include "audio.h"
#include "video.h"

void setup() {
    pinMode(PIEZO_PIN, OUTPUT);
    digitalWrite(PIEZO_PIN, LOW);
    
    pinMode(BANK_PIN, OUTPUT);
    digitalWrite(BANK_PIN, LOW);
    
    for (int j = 0; j < 8; j++) {
        pinMode(ROW_PINS[j], OUTPUT);
        digitalWrite(ROW_PINS[j], LOW);
    }
    
    for (int j = 0; j < 8; j++) {
        pinMode(COLUMN_PINS[j], OUTPUT);
        digitalWrite(COLUMN_PINS[j], HIGH);
    }
}

int frameIdx = 0;
int toneIdx = 0;
unsigned long prevFrameMillis = 0;
unsigned long prevToneMillis = 0;

void loop() {
    unsigned long currentTime = millis();
    
    if (currentTime > prevToneMillis + DELAYS[toneIdx]) {
        auto tone_ = TONES[toneIdx];
        
        if (tone_ == 0)
            noTone(PIEZO_PIN);
        else
            tone(PIEZO_PIN, tone_);
        
        prevToneMillis = currentTime;
        toneIdx = (toneIdx + 1) % N_TONES;
    }
    
    if (currentTime > prevFrameMillis + 42) { // 42 ms between frames, 24 FPS
        prevFrameMillis = currentTime;
        frameIdx = (frameIdx + 1) % N_FRAMES;
    }
    
    for (int bank = 0; bank < 2; bank++) {
        digitalWrite(BANK_PIN, bank);
        
        for (int column = 0; column < 8; column++) {
            uint8_t data = VIDEO[frameIdx * 16 + bank * 8 + column];
            
            digitalWrite(COLUMN_PINS[column], LOW);
            
            // write to the column
            for (int row = 0; row < 8; row++) {
                // should take MSB and left shift instead of doing subtraction...
                digitalWrite(ROW_PINS[row], (data >> (7 - row)) & 0b1);
            }
            
            // clear the column
            for (int row = 0; row < 8; row++) {
                digitalWrite(ROW_PINS[row], LOW);
            }
            
            digitalWrite(COLUMN_PINS[column], HIGH);
        }
    }
}

#include <Arduino.h>
#include "../.pio/libdeps/nanoatmega328/MIDI Library/src/MIDI.h"

MIDI_CREATE_DEFAULT_INSTANCE();

const int FIRST_MIDI_BTN = 2;
const int LAST_MIDI_BTN = 9;

const int BTN_UP = 10;
const int BTN_DOWN = 11;

const int MIDI_CHANNEL = 1;

const int MAX_PAGE = 15;
const int PER_PAGE = 8;
unsigned int page = 0;
const int TIME_DELAY_MILLIS = 50;

unsigned long time_btn_1 = 0;
unsigned long time_btn_2 = 0;
unsigned long time_btn_3 = 0;
unsigned long time_btn_4 = 0;
unsigned long time_btn_5 = 0;
unsigned long time_btn_6 = 0;
unsigned long time_btn_7 = 0;
unsigned long time_btn_8 = 0;
unsigned long time_btn_up = 0;
unsigned long time_btn_down = 0;

int btn_state_1 = LOW;
int btn_state_2 = LOW;
int btn_state_3 = LOW;
int btn_state_4 = LOW;
int btn_state_5 = LOW;
int btn_state_6 = LOW;
int btn_state_7 = LOW;
int btn_state_8 = LOW;
int btn_state_up = LOW;
int btn_state_down = LOW;



enum Buttons {
    BTN_1 = FIRST_MIDI_BTN,
    BTN_2 = FIRST_MIDI_BTN + 1,
    BTN_3 = FIRST_MIDI_BTN + 2,
    BTN_4 = FIRST_MIDI_BTN + 3,
    BTN_5 = FIRST_MIDI_BTN + 4,
    BTN_6 = FIRST_MIDI_BTN + 5,
    BTN_7 = FIRST_MIDI_BTN + 6,
    BTN_8 = LAST_MIDI_BTN
};

void handleMidiButtons();

void handleControlButtons();

void handleMidiMessage(int index, bool shouldSend);

void setup() {
    MIDI.begin();
    pinMode(BTN_1, INPUT);
    pinMode(BTN_2, INPUT);
    pinMode(BTN_3, INPUT);
    pinMode(BTN_4, INPUT);
    pinMode(BTN_5, INPUT);
    pinMode(BTN_6, INPUT);
    pinMode(BTN_7, INPUT);
    pinMode(BTN_8, INPUT);
    pinMode(BTN_UP, INPUT);
    pinMode(BTN_DOWN, INPUT);
}

void loop() {
    handleMidiButtons();
    handleControlButtons();
}

void handleControlButtons() {
    int input_btn_up = digitalRead(BTN_UP);
    if (input_btn_up == HIGH) {
        if(btn_state_up == LOW && millis() - time_btn_up >= TIME_DELAY_MILLIS) {
            time_btn_up = millis();
            if (page != MAX_PAGE) {
                page++;
            } else {
                page = 0;
            }
        }
        btn_state_up = HIGH;

    }
    int input_btn_down = digitalRead(BTN_DOWN);
    if (input_btn_down == HIGH) {
        if(btn_state_down == LOW && millis() - time_btn_down >= TIME_DELAY_MILLIS) {
            time_btn_down = millis();
            if (page != 0) {
                page--;
            } else {
                page = MAX_PAGE;
            }
        }
        btn_state_down = HIGH;

    }
}

void handleMidiButtons() {
    for (int btn = FIRST_MIDI_BTN; btn <= LAST_MIDI_BTN; btn++) {
        int input = digitalRead(btn);
        if (input == HIGH) {
            int index = btn - FIRST_MIDI_BTN;
            bool shouldSend = false;
            handleMidiMessage(index, shouldSend);
        }
    }
}

void handleMidiMessage(int index, bool shouldSend) {
    switch (index + 1) {
        case 1:
            if(btn_state_1 == LOW && millis() - time_btn_1 >= TIME_DELAY_MILLIS) {
                time_btn_1 = millis();
                shouldSend = true;
            }
            btn_state_1 = HIGH;
            break;
        case 2:
            if(btn_state_2 == LOW && millis() - time_btn_2 >= TIME_DELAY_MILLIS) {
                time_btn_2 = millis();
                shouldSend = true;
            }
            btn_state_2 = HIGH;
            break;
        case 3:
            if(btn_state_3 == LOW && millis() - time_btn_3 >= TIME_DELAY_MILLIS) {
                time_btn_3 = millis();
                shouldSend = true;
            }
            btn_state_3 = HIGH;
            break;
        case 4:
            if(btn_state_4 == LOW && millis() - time_btn_4 >= TIME_DELAY_MILLIS) {
                time_btn_4 = millis();
                shouldSend = true;
            }
            btn_state_4 = HIGH;
            break;
        case 5:
            if(btn_state_5 == LOW && millis() - time_btn_5 >= TIME_DELAY_MILLIS) {
                time_btn_5 = millis();
                shouldSend = true;
            }
            btn_state_5 = HIGH;
            break;
        case 6:
            if(btn_state_6 == LOW && millis() - time_btn_6 >= TIME_DELAY_MILLIS) {
                time_btn_6 = millis();
                shouldSend = true;
            }
            btn_state_6 = HIGH;
            break;
        case 7:
            if(btn_state_7 == LOW && millis() - time_btn_7 >= TIME_DELAY_MILLIS) {
                time_btn_7 = millis();
                shouldSend = true;
            }
            btn_state_7 = HIGH;
            break;
        case 8:
            if(btn_state_8 == LOW && millis() - time_btn_8 >= TIME_DELAY_MILLIS) {
                time_btn_8 = millis();
                shouldSend = true;
            }
            btn_state_8 = HIGH;
            break;
    }
    if(shouldSend) {
        MIDI.sendProgramChange(page * PER_PAGE + index, MIDI_CHANNEL);
    }
}

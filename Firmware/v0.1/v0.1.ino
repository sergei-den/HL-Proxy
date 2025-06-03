/*
  HL Proxy Firmware v0.1
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

uint8_t pin_tx = 3;
uint8_t pin_rx = 2;

uint8_t pin_button = 9;

uint8_t push_short = 0;
uint32_t button_delay;
uint32_t button_wait;

void setup() {
  Serial.begin(9600);

  pinMode(pin_button, INPUT);

  mySwitch.enableTransmit(10);
  mySwitch.setProtocol(1);
  mySwitch.setRepeatTransmit(100);
}

void loop() {

  button_delay = 0;

  //uint8_t button_state = digitalRead(pin_button);

  while (digitalRead(pin_button) == LOW) {
    button_delay++;
    //delay(1);
  }

  if ((button_delay > 0) && (button_delay < 200000)) {
    button_delay = 0;
    button_wait = 0;
    push_short++;
    Serial.println("SHORT");
  }
  else if ((button_delay > 0) && (button_delay > 200000)) {
    // Programming Functions
    button_delay = 0;
    Serial.println("LONG");

    push_short = 0;
    button_wait = 0;
  }
  else {
    button_wait++;

    // Remote push emulate
    if ((push_short > 0) && (button_wait > 200000)) {
      Serial.println("REMOTE");
      Serial.write(push_short + ".");

      push_short = 0;
      button_wait = 0;
    }
  }




  //Serial.println(push_short);
  //delay(500);










  //Serial.write("1");

/*
    Serial.println("holding");

  //Same switch as above, but using decimal code
  //mySwitch.send(2243956, 24);
  //delay(10);
*/
}

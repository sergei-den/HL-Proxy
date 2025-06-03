/*
  HL Proxy Firmware v0.1
*/

#include <RCSwitch.h>

#define pin_tx 3
#define pin_tx_vcc 19
#define pin_rx 2
#define pin_button 9

#define code_a 2243956
#define code_b 2243957
#define code_c 2243958
#define pin_a 16
#define pin_b 17
#define pin_c 18

uint8_t push_short = 0;
uint32_t button_delay;
uint32_t button_wait;

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);

  pinMode(pin_button, INPUT);

  pinMode(pin_a, OUTPUT);
  pinMode(pin_b, OUTPUT);
  pinMode(pin_c, OUTPUT);
  pinMode(pin_tx_vcc, OUTPUT);

  digitalWrite(pin_a, LOW);
  digitalWrite(pin_b, LOW);
  digitalWrite(pin_c, LOW);
  digitalWrite(pin_tx_vcc, LOW);


  mySwitch.enableReceive(pin_rx);
  mySwitch.enableTransmit(pin_tx);
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
    //Serial.println("LONG");
    //Serial.println(push_short);

    if (push_short == 0) {
        digitalWrite(pin_a, HIGH);
        delay(3000);
        digitalWrite(pin_a, LOW);
    }
    else if (push_short == 1) {
        digitalWrite(pin_b, HIGH);
        delay(3000);
        digitalWrite(pin_b, LOW);
    }
    else if (push_short == 2) {
        digitalWrite(pin_c, HIGH);
        delay(3000);
        digitalWrite(pin_c, LOW);
    }

    push_short = 0;
    button_wait = 0;
  }
  else {
    button_wait++;

    // Remote push emulate
    if ((push_short > 0) && (button_wait > 200000)) {
      //Serial.println("REMOTE");
      //Serial.println(push_short);

      digitalWrite(pin_tx_vcc, HIGH);
      delay(200);
      if (push_short == 0) {
          mySwitch.send(code_a, 24);
      }
      else if (push_short == 1) {
          mySwitch.send(code_b, 24);
      }
      else if (push_short == 2) {
          mySwitch.send(code_c, 24);
      }
      digitalWrite(pin_tx_vcc, LOW);

      push_short = 0;
      button_wait = 0;
    }
  }


  if (mySwitch.available()) { 
    if (mySwitch.getReceivedValue() == code_a) {
        digitalWrite(pin_a, HIGH);
        delay(3000);
        digitalWrite(pin_a, LOW);
    }
    else if (mySwitch.getReceivedValue() == code_b) {
        digitalWrite(pin_b, HIGH);
        delay(3000);
        digitalWrite(pin_b, LOW);
    }
    else if (mySwitch.getReceivedValue() == code_c) {
        digitalWrite(pin_c, HIGH);
        delay(3000);
        digitalWrite(pin_c, LOW);
    }
    mySwitch.resetAvailable();
  }



/*
    Serial.println("holding");

  //Same switch as above, but using decimal code
  //mySwitch.send(2243956, 24);
  //delay(10);
*/
}

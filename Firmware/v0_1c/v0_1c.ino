/*

  HL Proxy Firmware v0.1
  (c) 2023 Sergei Denisenko

*/

#include <RCSwitch.h>

#define cpu_clk 4 // Mhz

#define pin_tx 3
#define pin_tx_vcc 19
#define pin_rx 0
#define pin_button 9

#define code_a 2243956
#define code_b 2243958
#define code_c 2243960
#define pin_a 16
#define pin_b 17
#define pin_c 18

uint8_t push_short = 0;
uint32_t button_delay;
uint32_t button_wait;

RCSwitch rx = RCSwitch();
RCSwitch tx = RCSwitch();

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

  rx.enableReceive(pin_rx);
  tx.enableTransmit(pin_tx);
  tx.setProtocol(1);
  tx.setRepeatTransmit(300);
  tx.setPulseLength(1210);
}

void loop() {
  button_delay = 0;

  while (digitalRead(pin_button) == LOW) {
    button_delay++;
  }

  if ((button_delay > 0) && (button_delay < (cpu_clk * 20000))) {
    button_delay = 0;
    button_wait = 0;
    push_short++;
    //Serial.println("SHORT");
  }
  else if ((button_delay > 0) && (button_delay > (cpu_clk * 20000))) {
    // Programming Functions
    button_delay = 0;
    //Serial.println("LONG");
    //Serial.println(push_short);

    if (push_short == 0) {
        digitalWrite(pin_a, HIGH);
        delay(5000);
        digitalWrite(pin_a, LOW);
    }
    else if (push_short == 1) {
        digitalWrite(pin_b, HIGH);
        delay(5000);
        digitalWrite(pin_b, LOW);
    }
    else if (push_short == 2) {
        digitalWrite(pin_c, HIGH);
        delay(5000);
        digitalWrite(pin_c, LOW);
    }

    push_short = 0;
    button_wait = 0;
  }
  else {
    button_wait++;

    // Remote push emulate
    if ((push_short > 0) && (button_wait > (cpu_clk * 20000))) {
      //Serial.println("REMOTE");
      //Serial.println(push_short);

      noInterrupts();
      digitalWrite(pin_tx_vcc, HIGH);
      delay(200);
      if (push_short == 1) {
          tx.send(code_a, 25);
      }
      else if (push_short == 2) {
          tx.send(code_b, 25);
      }
      else if (push_short == 3) {
          tx.send(code_c, 25);
      }
      digitalWrite(pin_tx_vcc, LOW);
      interrupts();

      push_short = 0;
      button_wait = 0;
    }
  }

  if (rx.available()) {
    if (rx.getReceivedValue() == code_a) {
        digitalWrite(pin_a, HIGH);
        delay(5000);
        digitalWrite(pin_a, LOW);
    }
    else if (rx.getReceivedValue() == code_b) {
        digitalWrite(pin_b, HIGH);
        delay(5000);
        digitalWrite(pin_b, LOW);
    }
    else if (rx.getReceivedValue() == code_c) {
        digitalWrite(pin_c, HIGH);
        delay(5000);
        digitalWrite(pin_c, LOW);
    }
    rx.resetAvailable();
  }
}

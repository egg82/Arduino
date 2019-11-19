/*
  Audio Hacker Library
  Copyright (C) 2013 nootropic design, LLC
  All rights reserved.

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
  A 12-bit sampler to record sampled audio to SRAM.
  Input is sampled at 44.1 kHz and reproduced on the output.
  Recordings sampled at 22 kHz and stored to SRAM.

  See Audio Hacker project page for details.
  http://nootropicdesign.com/audiohacker/projects.html
 */


#include <AudioHacker.h>

#define DEBUG

unsigned int playbackBuf = 2048;
unsigned int passthroughSampleRate;
unsigned int timer1Start;
volatile unsigned int timer1EndEven;
volatile unsigned int timer1EndOdd;
volatile boolean warning = false;
boolean adjustablePlaybackSpeed = false;  // set to true with pot connected to A0
int currentA0Position;
volatile long address = 0;
volatile long endAddress = 0;
volatile byte addressChipNumber = 0;
volatile byte endAddressChipNumber = 0;

unsigned long lastDebugPrint = 0;
unsigned int readBuf[2];
unsigned int writeBuf;
boolean evenCycle = true;
unsigned int recordStartTime;
unsigned int recordEndTime;
boolean sampleRecorded = false;

void setup() {
#ifdef DEBUG
  Serial.begin(115200);        // connect to the serial port
#endif

  passthroughSampleRate = DEFAULT_SAMPLE_RATE;
  timer1Start = UINT16_MAX - (F_CPU / passthroughSampleRate);

  AudioHacker.begin();

#ifdef DEBUG
  Serial.print("sample rate = ");
  Serial.print(passthroughSampleRate);
  Serial.print(" Hz");
  Serial.println();
#endif
}

void loop() {

#ifdef DEBUG
  if ((millis() - lastDebugPrint) >= 1000) {
    lastDebugPrint = millis();

    // Print the number of instruction cycles remaining at the end of the ISR.
    // The more work you try to do in the ISR, the lower this number will become.
    // If the number of cycles remaining reaches 0, then the ISR will take up
    // all the CPU time and the code in loop() will not run.

    Serial.print("even cycles remaining = ");
    Serial.print(UINT16_MAX - timer1EndEven);
    Serial.print("   odd cycles remaining = ");
    Serial.print(UINT16_MAX - timer1EndOdd);
    Serial.println();
    if (((UINT16_MAX - timer1EndEven) < 20) || (((UINT16_MAX - timer1EndOdd) < 20))) {
      Serial.println("WARNING: ISR execution time is too long. Reduce sample rate or reduce the amount of code in the ISR.");
    }

  }
#endif

timer1Start = UINT16_MAX - (F_CPU / passthroughSampleRate);
}

ISR(TIMER1_OVF_vect) {
  TCNT1 = timer1Start;
  unsigned int signal;

AudioHacker.writeDAC(playbackBuf);


    // Read ADC
    signal = AudioHacker.readADC();

  playbackBuf = signal;

#ifdef DEBUG
  if (evenCycle) {
    timer1EndEven = TCNT1;
  } else {
    timer1EndOdd = TCNT1;
  }
#endif
  evenCycle = !evenCycle;
}



/*
 *Copyright 2021-2022 Kieffer Bros., LLC 
 *
 *Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *and associated documentation files (the "Software"), to deal in the Software without restriction,
 *including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
 *subject to the following conditions:
 *
 *The above copyright notice and this permission notice shall be included in all copies or 
 *substantial portions of the Software.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 *INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 *AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
 *OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifdef ACTIVE_LOW
#define ACTIVE LOW
#define INACTIVE HIGH
#else
#define ACTIVE HIGH
#define INACTIVE LOW
#endif

namespace Hopper
{
  const unsigned char k_OpticalPin = 0;
  const unsigned char k_ProximityPin = 1;
  const unsigned char k_LightPin = 2;
  const unsigned char k_MotorPin = 3;
  const unsigned long k_DelayInterval = 30000; // ms
  const unsigned long k_LightDelayInterval = 500; // ms
  const unsigned long k_LightMotorInterval = 250; // ms
  const unsigned long k_ProximityInterval = 3000; // ms
  const unsigned long k_LoopDelay = 100; // ms

  enum In : unsigned char
  {
    Optical = 0x01,
    Proximity = 0x02
  };

  enum Internal : unsigned char
  {
    Timer = 0x04
  };

  enum Out : unsigned char
  {
    Light = 0x08,
    Motor = 0x16
  };

  unsigned long s_Time = 0;
  unsigned long s_Timer = 0;
  unsigned char s_State = 0;

}

using namespace Hopper;

void setup()
{
  pinMode(k_OpticalPin, INPUT);
  pinMode(k_ProximityPin, INPUT);
	pinMode(k_LightPin, OUTPUT);
	pinMode(k_MotorPin, OUTPUT);

  s_Time = millis();
}

void loop()
{
	unsigned char next = 0, prev = s_State;
  unsigned long time = millis();
	
	// read analog input
	next |= digitalRead(k_OpticalPin) ? In::Optical : 0;
	next |= digitalRead(k_ProximityPin) ? In::Proximity : 0;
	
	if ((prev & Out::Motor) == Out::Motor)
	{
		// motor is active: keep timer running unless proximity is high
		if ((next & In::Optical) == In::Optical && s_Timer > k_DelayInterval + k_ProximityInterval)
		{
			s_Timer = 0;
		}
		else
		{
			next |= Internal::Timer;
		}
	}
	else if ((next & In::Optical) == In::Optical || (prev & In::Optical) == In::Optical)
	{
		// set run timer if optical is active
		if ((next & In::Optical) == In::Optical)
		{
			next |= Internal::Timer;
		}
		
		// reset timer if optical signal has changed
		if ((next & In::Optical) != (prev & In::Optical))
		{
			s_Timer = 0.0f;
		}
	}
	
	// timer is running
	if ((next & Internal::Timer) == Internal::Timer)
	{
    unsigned long dt = time - s_Time;
		s_Timer += dt;

		// power motor
		if (s_Timer > k_DelayInterval)
		{
			next |= Out::Motor;
			
			// flash light for motor
			if ((s_Timer / k_LightMotorInterval) % 2 == 1)
			{
				next |= Out::Light;
			}
		}
		// flash light for delay
		else if ((s_Timer / k_LightDelayInterval) % 2 == 1)
		{
			next |= Out::Light;
		}
	}

	s_State = next;
  s_Time = time;
	
	digitalWrite(k_LightPin, (next & Out::Light) == Out::Light ? ACTIVE : INACTIVE);
	digitalWrite(k_MotorPin, (next & Out::Motor) == Out::Motor ? ACTIVE : INACTIVE);
	
	delay(k_LoopDelay);
}

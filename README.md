#Hopper Controller#
An Arduino sketch for controlling a light and motor with two binary sensors. Objects are moved to hopper and after optical sensor is tripped for set duration motor is activated. Light flashes at slow (by default) interval when optical sensor is tripped and faster (by default) interval when motor is active. Motor remains active until the proximity sensor is tripped by a steel bolt on the disc which inidicates a closed position for the hopper. The counter weight keeps the hopper closed and helps correct any over shoot from the motor. Two solid state relays can be used to isolate the AC components

				 Motor & Disc
  Optical Sensor       |
         |			   |
      o--˅-------/	   ˅  
      | \oOO OOO/     ___   []<--Light
      |  \OOOOO/-----/-  \
      ■   -- --   ˄ |  O  |
      ˄ 	  |   |  \___/ □ <--Proximity Sensor
      |  	  |  Rope
Counter Weight|
              ˅
            Hopper
	
 ┌────────────────┬─+┌Optical┐-──┐
 │     [5VDC]     │  └─┬─────┘   │
 │       |        └─+┌Proximity┐-┤
 │  ┌───USB───┐	     └────┬────┘ │
 │	│         │        │  │      │
 └5V│         │GND──────────┬────┴─────────┐
    │ Arduino │D0──────┘  │ │              │
    │         │D1─────────┘ │              │
    │         │D2┐          │              │
    │         │D3───────────│───┐          │
  	└─────────┘  │          │   │          │
                 │          │   │          │
				 └+┌─SSR─┐-─┘   └─+┌─SSR─┐-┘
     ┌────────┬───+└─────┘-─┐ ┌───+└─────┘-─┐
     │        └─────────────│─┘             │
     │ 	        ┌──[Light]──┘               │
     │          │                           │
     └+[120VAC]─┴──────────────────[Motor]──┘
	
	
	
	
	
	
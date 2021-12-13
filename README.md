# Hopper Controller #
An Arduino sketch for controlling a light and motor with two binary sensors. Objects are moved to hopper and after the IR obstruction sensor (garage door sensor) is tripped for a specified duration motor is activated. Light flashes at slow (by default) interval when IR sensor is tripped and at a faster (by default) interval when motor is active. Motor remains active until the proximity sensor is tripped by a steel bolt on the disc which inidicates a closed position for the hopper. The counter weight keeps the hopper closed and helps correct any over shoot from the motor. Two solid state relays can be used to isolate the AC components.

## Mechanical Use Case ##
```
                    Motor & Disc
       IR Sensor         |
           |             |
        o--˅-------/     |  
        | \□OO OOO/     _˅_   []<--Light
        |  \OOOOO/-----/-  \
Weight->■   -- --   ˄ |  O  |
            ˄   ˄   |  \___/ □ <--Proximity Sensor
            |   |  Rope
         Fixed  |
              Hopper Door
```

## Circuit Diagram ##
```
                 ┌+┌─Optical─┐-┐
                 │ └──Emit───┘ │	
┌────────────────┼+┌─Optical─┐-┤
│     [5VDC]     │ └┬Receive─┘ │
│       |        └+┌Proximity┐-┤
│  ┌───USB───┐	   └────┬────┘ │
│  │         │      │   │      │
└5V│         │GND──────────┬───┴──────────┐
   │ Arduino │D0────┘   │  │              │
   │         │D1────────┘  │              │
   │         │D2┐          │              │
   │         │D3───────────│───┐          │
   └─────────┘  │          │   │          │
                │          │   │          │
                └+┌─SSR─┐-─┘   └─+┌─SSR─┐-┘
    ┌────────┬───+└─────┘-─┐ ┌───+└─────┘-┐
    │        └─────────────│─┘            │
    │ 	       ┌──[Light]──┘              │
    │          │                          │
    └+[120VAC]─┴──────────────────[Motor]─┘
```
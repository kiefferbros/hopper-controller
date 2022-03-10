# Hopper Controller #
An Arduino sketch for controlling a light and motor with two NPN sensors. Objects are moved into the hopper and after the infrared obstruction sensor (garage door sensor) is tripped for a specified duration, the motor is activated. The light flashes at a slow interval (by default) when IR sensor is first tripped and goes solid when the motor is active. Motor remains active until the proximity sensor is tripped by a steel bolt on the disc which inidicates a closed position for the hopper. The counter weight keeps the hopper closed and helps correct any over shoot from the motor. Two solid state relays can be used to isolate the AC components.

## Mechanical Use Case ##
```
                    Motor & Disc
        IR Sensor        |
            |            |
        o---|------/     |  
        | \O˅O OOO/     _˅_   []<--Light
        |  \□OOOO/-----/-  \
Weight->■   -- --   ˄ |  O  |
            ˄   ˄   |  \___/ □ <--Proximity Sensor
            |   |  Rope
         Fixed  |
              Hopper Door
```

## Circuit Diagram ##
```
  ┌─────────────────────────────┐
  │             ┌─+┌───IR────┐-─┤
  └─-[13VDC]+───┤  └──Emit───┘  │	
        │       └─+┌───IR────┐-─┤
        │          └┬Receive─┘  │
┌───────────────┐   │           │
│       │       └─+┌Proximity┐-─┤
│  ┌───PWR───┐	   └────┬────┘  │
│  │         │      │   │       │
└5V│         │      │   │  ┌────┴─────────┐
   │ Arduino │D6────┘   │  │              │
   │         │D7────────┘  │              │
   │         │D8┐          │              │
   │         │D9───────────│───┐          │
   └─────────┘  │          │   │          │
                │          │   │          │
                └+┌─SSR─┐-─┘   └─+┌─SSR─┐-┘
    ┌────────┬────└─────┘──┐ ┌────└─────┘─┐
    │        └─────────────│─┘            │
    │ 	       ┌──[Light]──┘              │
    │          │                          │
    └─[120VAC]─┴──────────────────[Motor]─┘
```

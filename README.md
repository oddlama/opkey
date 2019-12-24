# OpKey

Optical Key Sensor and MIDI controller for acoustic pianos, because why not.

## Hardware

All hardware pcbs are designed in KiCad. You will find them in the `hardware/` folder.
Do not forget to include the provided library for all components which are not found in the standard library.

* The controller board
* The sensor board (the normal 15 sensors veriant and one remainder for the low part of the keyboard)
  - 15 sensor variant is stacked 5 times
  - 13+2 sensors variant terminates the chain at the left end of the keyboard and adds auxiliary inputs for two pedal sensors
* A mini board for auxiliary sensors (pedals)

### Connection Diagram

```
                     LED strip
 o─o─o─o─o─o─o─o─o─o─o─o─o─o─o─o─o─o─o─o─o─o─o─o─o─o─o────╖
                                                          ║
  ╔═══ Soft Pedal (Una Corda)                             ║
  ║ ╔═ Damp Pedal (Sustain)                               ║
  ║ ║                                                     ║
┌─╨─╨──────────┐ ┌────────────┐     ┌────────────┐  ┌─────╨──────┐
│ 13+2 Sensors │ │ 15 Sensors │  …  │ 15 Sensors │  │ Controller │
│    Board 0   ╞═╡   Board 1  ╞/ … /╡   Board 6  ╞══╡ Controller ╞═ [+5V]
└──────────────┘ └────────────┘     └────────────┘  └────────────┘
```

### Issues

* 5V rail needs to be regulated
* Has filling both sides with copper been a good idea?
* SPI signal quality is crappy (cannot get above 4-5MHz, while ADC could do 20MHz and ESP32 could do 80MHz)
* The flat cables weren't my best idea... They proved to be a real pain in the ass.
  (Very unusual part, expensive and not available in correct lengths)
* All sensors are currently in line with each other, while the pivot points for black keys
  differs from the pivot point of white keys. This causes black keys to have a lot more travel at the
  sensor than white keys.
* We definitely need a way to properly calibrate all keys. The reflected amount of light
  varies, because of the wood texture of the keys, voltage drop from the length of all modules,
  and probably some other factors (mounting angle difference, factory deviation for IR LEDs and sensors...)
* The low-pass filter seems to work fine, but maybe it should be tested properly.
* Could a differentiator be used after the sensor to get more accurate and comparable velocity measurements? 
* The reference volatage at the ADCs could have been a mistake,
  because the sensor output voltage is not regulated.
* Some deterministic BLE transmission every .5 seconds causes sensor values to fluctuate by 2-3 bits. (Some kind of BLE heartbeat?)
  This could be either an induced current in the sensing line, or more likely a voltage drop caused by the TX module.
  Though indeed my antenna is exactly in line with the long side of the module, and therefore most of the traces on that PCB.
* The 3 zener diode package for USB line protection is upside down. (Wrong part pinout or footprint selected)
* We need USB midi out for low latency, and pure MIDI out for even better latency (don't forget optocouplers).
* Replace ESP32 by several proper processors (would allow full ADC utilization, see Software#Issues below for more)


## Software

The software for the ESP32 controller currently works like this:

Core 0 is responsible for BLE communication and LED visualization.
The BLE framework is the nimble, which is the recommended BLE framework according to Espressif.
Unfortunately, it really isn't a piece of cake.
See my issues [#4012](https://github.com/espressif/esp-idf/issues/4012)
and [#4328](https://github.com/espressif/esp-idf/issues/4328),
lets hope that there won't be any other issues.

Core 1 has been completely dedicated to this single FreeRTOS thread, to reduce scheduling
to the bare minimum. This allows it to be fully utilized for SPI communication and key state
calculation. While in theory the whole scheduling could be disabled by actually removing the
core from FreeRTOS initialization (via `start1.c`), this would also prevent us from using
`stdout` for UART communication. So I can't focus on this while the software is still heavily debugged.
Nontheless, this still gives us somewhat deterministic timings between sensor reads (good enough - down to some us).

SPI communication is polling, allowing us to process the previous sample while the
hardware SPI driver is busy with transactions for the next sample.

### Software summary

#### Core 0:

* Reads sensor's over SPI 
* Calculates key states
* Notifies other modules if key is pressed

#### Core 1:

* System threads (BLE driver, ...)
* Handles BLE communication
* Controls LED strip (calculates color and send's LED states)

### Issues

* Can the two SPI channels be used simultaneously?
* BLE midi has unpredictable latency.
* Recorded files seem to be missing the time code correction (probably an arecordmidi problem)
* Even though the two cores should be operating simultaneously, they are heavily influenced
  by each other (forced cache synchronization, fences in FreeRTOS code). e.g. TX for BLE on core 0
  causes core 1 to slow down, which is like the best thing ever for deterministic timing requirements!
  Admit it, you simply gotta love it.
* Separated hardware for each "process" would most likely eliminate most of these concerns.
  - One processor for each ADC (for SPI communication and key state calculation).
  - One processor to convert these signals to MIDI line
  - One processor for visualization
  - External BLE processor (nRF51 with [bluetoe](https://github.com/TorstenRobitzki/bluetoe))

Please don't judge the code layout too much, the ESP SDK really seems to hate good code.
Their giant pile of bloated cmake prevents you from using proper cmake (and forces you to use flat code layout).

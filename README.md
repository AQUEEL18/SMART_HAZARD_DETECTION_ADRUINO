# STARK | Multi-Hazard Detection and Emergency Response System

An Arduino Uno-based environmental monitoring and emergency alert prototype developed using Tinkercad Circuits.



\


---

## 1. Project Overview

The Multi-Hazard Detection and Emergency Response System is an educational embedded-systems project designed to monitor environmental conditions and activate warning and response mechanisms when potentially hazardous conditions are detected.

The prototype uses an MQ-135 air-quality sensor, a PIR motion sensor, a temperature sensor (TMP36, physically included), an LCD display, LEDs, a buzzer and a transistor-driven DC fan.

The Arduino continuously reads sensor inputs, evaluates predefined thresholds and controls the corresponding outputs.

The primary objective is to demonstrate how sensors, microcontrollers, decision-making logic and actuators can work together in an automated monitoring system.

**Development environment:** Tinkercad Circuits
**Microcontroller:** Arduino Uno R3
**Programming language:** Arduino C/C++
**Application:** Multi-hazard monitoring and emergency-response demonstration

## 2. Project Objectives

- Monitor air-quality-related sensor readings using the MQ-135.
- Classify sensor readings into SAFE, MILD and DANGER conditions.
- Read a digital input intended for flame detection.
- Monitor motion using a PIR sensor.
- Display system status and sensor readings on an I2C LCD.
- Provide continuous green status indication.
- Activate a red danger indicator when an alarm condition occurs.
- Activate an audible buzzer during danger.
- Switch on a DC fan through a transistor driver during danger.
- Display diagnostic readings through the Arduino Serial Monitor.

## 3. System Architecture

The system is divided into four functional sections.

### Input Layer

| Component        | Function                                                                                           |
| ---------------- | -------------------------------------------------------------------------------------------------- |
| MQ-135           | Air-quality/gas sensor input                                                                       |
| TMP36            | Temperature sensor physically included                                                             |
| PIR sensor       | Motion detection                                                                                   |
| D8 digital input | Used by the current software as a flame input; actual sensor mapping needs correction/verification |

### Processing Layer

The Arduino Uno:

1. Reads the sensor inputs.
2. Evaluates the MQ-135 analog value.
3. Classifies the gas reading.
4. Checks the digital flame input.
5. Reads the PIR output.
6. Determines whether an alarm is required.
7. Controls the display, LEDs, buzzer and fan.

### Indication Layer

- Green LED: continuously ON.
- Red LED: ON during danger.
- I2C LCD: displays overall status, gas reading and PIR status.
- Serial Monitor: prints diagnostic information.

### Emergency Response Layer

- Buzzer sounds at 1 kHz during danger.
- Fan switches ON through a transistor-based driver.
- Red LED indicates the active alarm state.

## 4. Components Used

| No. | Component                         |    Quantity | Purpose                                         |
| --: | --------------------------------- | ----------: | ----------------------------------------------- |
|   1 | Arduino Uno R3                    |           1 | Main controller                                 |
|   2 | MQ-135 Air Quality Sensor Module  |           1 | Analog air-quality/gas response                 |
|   3 | TMP36 Temperature Sensor          |           1 | Temperature sensing hardware                    |
|   4 | PIR Motion Sensor                 |           1 | Motion detection                                |
|   5 | I2C LCD 16×2                      |           1 | System status display                           |
|   6 | Green LED                         |           1 | Continuous status indication                    |
|   7 | Red LED                           |           1 | Danger indication                               |
|   8 | LED current-limiting resistors    |           2 | LED protection                                  |
|   9 | Buzzer                            |           1 | Audible warning                                 |
|  10 | DC motor/fan                      |           1 | Demonstration of emergency ventilation response |
|  11 | NPN transistor or suitable driver |           1 | Fan switching                                   |
|  12 | Base resistor                     |           1 | Limits transistor base current                  |
|  13 | Flyback diode                     |           1 | Motor voltage-spike protection                  |
|  14 | Breadboard                        |           1 | Circuit assembly                                |
|  15 | Jumper wires                      | As required | Electrical connections                          |

Push buttons and the blue warning LED are not part of the final software implementation.

## 5. Arduino Pin Configuration

The following table records the final sketch's pin assignments.

| Arduino Pin | Component          | Function                               |
| ----------- | ------------------ | -------------------------------------- |
| A0          | MQ-135 AO          | Analog air-quality reading             |
| D2          | PIR OUT            | Motion detection                       |
| D8          | Digital input      | Interpreted as flame input by the code |
| D9          | Fan driver control | Fan ON/OFF                             |
| D10         | Red LED            | Danger indication                      |
| D11         | Green LED          | Continuous status indication           |
| D13         | Buzzer             | Audible alarm                          |
| A4          | LCD SDA            | I2C data                               |
| A5          | LCD SCL            | I2C clock                              |
| 5V / GND    | Sensors and LCD    | Power and common reference             |

### Important TMP36 connection discrepancy

The TMP36 is physically present and was reported connected to D8. However, the final program executes `digitalRead(D8)` and interprets LOW as flame detected.

A TMP36 is an analog temperature sensor. It requires an analog input and a voltage-to-temperature calculation.

Therefore:

- The present code does not measure temperature.
- D8 is not a valid temperature-measurement connection.
- The current software expects a digital flame-sensor signal on D8.
- The TMP36 must not be connected to the same input as a separate flame sensor.

This is an outstanding hardware/software integration limitation, not a completed temperature-detection feature.

## 6. System Operating Logic

The final program uses two MQ-135 thresholds:

| MQ-135 Analog Reading | Classification |
| --------------------: | -------------- |
|              Below 60 | SAFE           |
|                 60–99 | MILD           |
|         100 and above | DANGER         |

These values are raw Arduino ADC readings, not ppm or a certified air-quality measurement.

### Alarm conditions

The alarm is activated when:

`Gas danger OR Flame danger`

PIR motion is informational only and does not trigger an alarm.

### Output behaviour

| Operating condition | Green LED | Red LED | Buzzer | Fan |
| ------------------- | --------- | ------- | ------ | --- |
| SAFE                | ON        | OFF     | OFF    | OFF |
| MILD                | ON        | OFF     | OFF    | OFF |
| Gas DANGER          | ON        | ON      | ON     | ON  |
| Flame DANGER        | ON        | ON      | ON     | ON  |

The green LED stays illuminated continuously, including during danger. The red LED indicates the active danger period.

### LCD Display

The first row displays the overall system status.

Example:

`STATUS: DANGER`

The second row displays the raw gas reading and PIR status.

Example:

`GAS:125 P:Y`

The Serial Monitor additionally reports gas reading, flame interpretation, PIR status and overall state.

## 7. Software Implementation

The final Arduino sketch is stored separately from this README.

Recommended source location:

`code/multi_hazard_detection.ino`

The program uses:

- `LiquidCrystal_I2C` library for LCD interfacing.
- `analogRead()` for MQ-135 readings.
- `digitalRead()` for PIR and D8 inputs.
- `digitalWrite()` for LEDs and fan control.
- `tone()` and `noTone()` for buzzer operation.
- `if`, `else if` and Boolean conditions for hazard classification.
- `Serial.print()` and `Serial.println()` for debugging.

The final source code is maintained as the project implementation reference.

## 8. System Workflow

1. Arduino starts and configures the input/output pins.
2. Serial communication is initialised.
3. LCD initialises and displays the startup message.
4. MQ-135 analog reading is collected.
5. PIR digital state is read.
6. D8 digital state is read and interpreted as flame status.
7. Gas status is classified as SAFE, MILD or DANGER.
8. The overall alarm condition is calculated.
9. Red LED, buzzer and fan are controlled according to the alarm state.
10. Green LED remains ON.
11. LCD and Serial Monitor are updated.
12. The system repeats the process approximately every 500 milliseconds.

## 9. Testing and Validation

The simulation is intended to demonstrate the following cases:

| Test                                     | Expected result                          |
| ---------------------------------------- | ---------------------------------------- |
| Low MQ-135 reading, D8 HIGH              | SAFE                                     |
| MQ-135 reading between 60 and 99         | MILD                                     |
| MQ-135 reading 100 or above              | DANGER                                   |
| D8 LOW                                   | DANGER                                   |
| PIR HIGH                                 | PIR displayed as Y; no independent alarm |
| Gas reading returns below 60 and D8 HIGH | Alarm outputs OFF                        |
| Danger condition becomes active          | Red LED, buzzer and fan ON               |

The project owner reports that the Tinkercad circuit and simulation have been completed and that the fan driver operates. Detailed independent test measurements and calibration results should be added to the testing record when documented.

## 10. Physical Implementation

The design can be developed further using a physical Arduino Uno and compatible electronic modules.

The physical implementation should follow these stages:

1. Assemble and verify the Arduino power and ground connections.
2. Connect and test the I2C LCD.
3. Connect the MQ-135 analog output to A0.
4. Connect the PIR output to D2.
5. Connect the appropriate digital flame-sensor output to D8 if retaining the current flame logic.
6. Connect the green and red LEDs through current-limiting resistors.
7. Connect the buzzer using an appropriate output interface.
8. Connect the fan through a correctly rated transistor or MOSFET driver.
9. Connect a suitable external fan supply and common ground.
10. Add a flyback diode across a brushed DC motor load with correct polarity.
11. Test every input and output independently.
12. Calibrate sensor behaviour under safe, controlled conditions.

The TMP36 must be connected to a separate analog input and integrated into a revised program before temperature monitoring can be demonstrated.

## 11. Limitations

### MQ-135 Sensor

The MQ-135 is a broad-response gas sensor. Its analog reading depends on sensor warm-up, calibration, supply voltage, environmental conditions and target gases.

The thresholds of 60 and 100 are demonstration settings only. They do not represent validated ppm values or certified air-quality limits.

### Temperature Monitoring

The TMP36 is included physically but is not read as an analog temperature sensor in the final sketch. Temperature monitoring is therefore not implemented in this software version.

### Flame Detection

The software assumes an active-LOW digital flame input on D8. This requires a compatible digital flame sensor connected to D8. The reported TMP36 connection conflicts with this assumption.

### PIR Sensor

The PIR sensor detects motion-related infrared changes. It does not identify a person or guarantee that a person is present.

### Emergency Fan

The fan is an educational actuator demonstrating automatic switching. Activating ordinary ventilation during a real fire or flammable-gas event can be unsafe. Real installations require a hazard-specific, professionally designed response.

### Simulation Limitations

A successful Tinkercad simulation does not prove real-world sensor accuracy, calibration, response time, environmental reliability or safety compliance.

This project is not a certified fire alarm, gas detector or life-safety system.

## 12. Future Improvements

Possible future development includes:

- Proper TMP36 analog integration and temperature thresholds.
- Verification and integration of a separate flame sensor.
- MQ-135 calibration and sensor filtering.
- Sensor-disconnection and fault detection.
- Hysteresis to prevent rapid threshold switching.
- Non-blocking timing using `millis()`.
- Event logging and improved diagnostics.
- A safer, professionally assessed emergency-response strategy.
- Physical prototype testing and documented measurements.

## 13. Repository Structure

Recommended project organisation:

```text
stark-multi-hazard-detection-system/
│
├── README.md
│
├── code/
│   └── multi_hazard_detection.ino
│
├── circuit/
│   ├── final-circuit.png
│   └── circuit-notes.md
│
├── docs/
│   ├── project-overview.md
│   ├── pin-configuration.md
│   └── physical-implementation.md
│
├── testing/
│   └── test-results.md
│
└── resources/
    └── datasheets/
```

Only add files when the corresponding content is ready. Do not label unverified images or measurements as completed experimental evidence.

## 14. Conclusion

The STARK Multi-Hazard Detection and Emergency Response System demonstrates an introductory embedded monitoring architecture using an Arduino Uno, MQ-135 sensor, PIR sensor, LCD, LEDs, buzzer and transistor-driven fan.

The final software implements MQ-135 threshold classification, an active-LOW digital input alarm, PIR context reporting and automatic output control.

The project provides a foundation for learning sensor interfacing, Arduino programming, decision logic, actuator control, simulation and physical prototyping.

The documented TMP36/D8 mismatch and sensor-calibration limitations must be resolved before claiming complete multi-hazard temperature and flame detection.

---

**Developed under\:AQUEEL.SHAIK'S Engineering Lab**
**Project type:** Embedded Systems / Electronics / Tinkercad Simulation
**Status:** Tinkercad implementation reported complete; hardware/software integration limitations documented.




    THIS IS THE LINK FOR THE TINKER CAD ASSIGHNMENT OR THE PROJECT I  HAVE DONE 
    https://www.tinkercad.com/things/4SAbJ6AThaS-multi-hazard-detection-and-emergency-response-system?sharecode=etYa8CCMt825LskzIdlxuz2O5Ddp1HZ-ZBd9UakzCnA

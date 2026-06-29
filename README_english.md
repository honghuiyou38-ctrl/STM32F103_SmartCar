# STM32F103 Smart Car v1.0

## MCU:STM32F103C8T6 (HCLK: 72 MHz)

## Project Overview
This is the first version of a smart car platform based on the STM32F103 microcontroller. The current version supports Bluetooth remote control, DC motor driving, OLED display, and motor lock mode. It can serve as a basic platform for smart car development.

---

Features

- Developed using the STM32 HAL Library
- UART DMA + UART Idle Line Reception
- Hardware I2C OLED Driver
- Dual-channel PWM Motor Control via TB6612
- Modular Software Design

---

## Functions

Available

- Bluetooth Remote Control
- OLED Display (Hardware I2C)
- TB6612 Motor Driver
- Motor Lock Mode

Under Development
- 8-Channel Line Tracking
- PID Speed Control

---

## Hardware：

### 1.Motor Driver (TB6612)

|Function| MCU Pin| Description|
|--------|--------|------------|
|Right Motor PWMA| PA6 (TIM3_CH1)| PWM Output (10 ms period)|
|Left Motor PWMB| PA7 (TIM3_CH2)| PWM Output|
|Right Motor AIN1| PB12| GPIO Output (HIGH = Forward, LOW = Reverse)|
|Right Motor AIN2| PB13| GPIO Output|
|Left Motor BIN1| PB14| GPIO Output|
|Left Motor BIN2| PB15| GPIO Output|
> TB6612 Logic: AIN1 = HIGH and AIN2 = LOW → Forward; reversing the levels rotates the motor in the opposite direction. PWM signals are generated using the STM32 HAL Library.»

---

### 2. Encoder (Hall Sensor ×2, 13-wire)

Under development.

---

### OLED Display (SSD1306, 128×64, Hardware I2C)

|Function| MCU Pin| Description|
|--------|--------|------------|
| **SCL** | PB6 | I2C1 Clock |
| **SDA** | PB7 | I2C1 Data |
| **VCC** | 3.3V | — |
| **GND** | GND | — |

---

### 4. Bluetooth Module (HC-05 / HC-06)


| Function| MCU Pin| Description |
|---------|--------|-------------|
| **RXD** | PA9 | USART1_TX |
| **TXD** | PA10 | USART1_RX |
| **VCC** | 5V | — |
| **GND** | GND | — |

>Communication:
- USART1 (115200 bps)
- UART DMA + Idle Line Reception
- Supports the following commands:
  - "front"
  - "back"
  - "left"
  - "right"
  - "stop"
---

### 5. Button & LED

| Module| MCU Pin| Trigger| Description |
|-------|--------|--------|-------------|
|KEY0| PA0| Active Low| External interrupt input for motor lock mode|
|LED1| PA12| Active High| Indicates the motor lock status|

---

## Software：
### PC
- STM32CubeIDE
- Serial Port Assistant

### Mobile
- HC Bluetooth Assistant

## Framework
- STM32 HAL Library
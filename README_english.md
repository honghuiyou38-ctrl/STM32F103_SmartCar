# STM32F103 Based Smart Car (STM32f103_smartcar_v1.0)

## MCU: STM32F103C8T6 (HCLK Clock Tree: 72MHz)

## Project Overview
This is the initial version developed with STM32F103. It has implemented basic Bluetooth remote control, motor drive, OLED display, car line tracking and gyroscope attitude calculation. This project can serve as a basic platform for smart car development.

## Project Features
• Developed with STM32 HAL Library
• UART DMA + Idle Interrupt for Bluetooth data reception
• Hardware I2C driver for OLED screen
• TB6612 dual-channel PWM speed regulation
• Modular code architecture

---

## Functions
- Bluetooth Remote Control
- Hardware I2C Driven OLED Display
- TB6612 Motor Driver
- Mode Switch Button
- 8-channel Line Tracking (Under Development)
- MPU6050 Gyroscope Attitude Solving

Under Development:
- PID Closed-Loop Control

---

## Hardware Description

### 1. Motor Driver (TB6612)

| Function | MCU Pin | Description |
|------|---------|------|
| Right Motor PWMA | PA6 (TIM3 CH1) | PWM signal, period: 10ms |
| Left Motor PWMB | PA7 (TIM3 CH2) | PWM signal |
| Right Motor Direction AIN1 | PB12 | GPIO output, High = Forward / Low = Reverse |
| Right Motor Direction AIN2 | PB13 | GPIO output |
| Left Motor Direction BIN1 | PB14 | GPIO output |
| Left Motor Direction BIN2 | PB15 | GPIO output |
> TB6612 Logic: AIN1=High + AIN2=Low → Forward, vice versa for reverse. PWM signals are generated directly by HAL library.

---

### 2. 8-Channel Line Tracking Sensor Module
| Sensor No. | MCU Pin | Position on Car Body |
|--------|---------|---------|
| X1 (Leftmost) | PA1 | Left Channel 1 |
| X2 | PA2 | Left Channel 2 |
| X3 | PA3 | Left Channel 3 |
| X4 | PA4 | Left Channel 4 |
| X5 | PA5 | Right Channel 4 |
| X6 | PB0 | Right Channel 3 |
| X7 | PB1 | Right Channel 2 |
| X8 (Rightmost) | PA15 | Right Channel 1 |
> Low level (GPIO read 0) detected on black track line, High level on white ground. Sensors are mounted at the front of the car, about 20cm ahead of rear wheels.

---

### 3. OLED Display (SSD1306, 128×64, Hardware I2C)

| Function | MCU Pin | Description |
|------|---------|------|
| SCL | PB6 | Hardware I2C1 Clock Line |
| SDA | PB7 | Hardware I2C1 Data Line |
| VCC | 3.3V | Power Supply |
| GND | GND | Ground |

---

### 4. Bluetooth Module (HC-05 / HC-06)

| Function | MCU Pin | Description |
|------|---------|------|
| RXD | PA9 | USART1 TX Pin |
| TXD | PA10 | USART1 RX Pin |
| VCC | 5V | Power Supply |
| GND | GND | Ground |

> Communication Specifications:
- USART1, Baud rate: 115200 bps
- Data reception via UART DMA + Idle Interrupt
- Supported control commands: front, back, left, right, stop, MPUON, MPUOFF, etc.

---

### 5. Gyroscope Module (MPU6050)

| Function | MCU Pin | Description |
|------|---------|------|
| I2C SDA | PB11 | Fast-mode Hardware I2C Data Line |
| I2C SCL | PB10 | Fast-mode Hardware I2C Clock Line |
| AD0 | GND | I2C Address = 0x68 |
| VCC | 3.3V | Power Supply |
| GND | GND | Ground |

---

### 6. Buttons & LED Indicators

## Software Environment
### PC Side:
- STM32CubeIDE
- Serial Port Assistant Tool

### Mobile Side:
- HC Bluetooth Assistant

## Library Used
- STM32 HAL Library
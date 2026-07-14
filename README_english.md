# STM32F103 Based Smart Car (STM32f103_smartcar_v1.0)
 ## MCU: STM32F103C8T6 (HCLK: 72MHz)
 ## Project Overview
 This is the initial version developed based on STM32F103. It implements basic functions including Bluetooth remote control, motor driving, OLED display, line tracking, ultrasonic obstacle avoidance, and gyroscope attitude calculation. It serves as a fundamental development platform for intelligent vehicles.
 ## Project Features
 • Developed with STM32 HAL Library
 • UART DMA + idle interrupt for Bluetooth data reception
 • Hardware I2C driven OLED display
 • Hardware I2C driven MPU6050 gyroscope
 • TB6612 dual-channel PWM speed regulation
 • Modular code design
 ---
 ## Functions
 - Bluetooth remote control
 - Hardware I2C OLED display
 - TB6612 motor driver control
 - Mode switching via physical buttons
 - 8-channel line tracking
 - MPU6050 gyroscope attitude solving
 - HC-S04 ultrasonic obstacle avoidance
 ---
 ## Hardware Description
 ### 1. Motor Driver (TB6612)
 | Function | MCU Pin | Description |
 |------|---------|------|
 | **Right Motor PWMA** | PA6 (TIM3 CH1) | PWM signal, period: 10ms |
 | **Left Motor PWMB** | PA7 (TIM3 CH2) | PWM signal |
 | **Right Motor Direction AIN1** | PB12 | GPIO output, High=Forward / Low=Reverse |
 | **Right Motor Direction AIN2** | PB13 | GPIO output |
 | **Left Motor Direction BIN1** | PB14 | GPIO output |
 | **Left Motor Direction BIN2** | PB15 | GPIO output |
 > TB6612 Logic: AIN1=H + AIN2=L → Forward, opposite for Reverse. PWM output controlled directly by HAL library.
 ---
 ### 2. 8-Channel Line Tracking Module
 | Sensor | MCU Pin | Vehicle Position |
 |--------|---------|---------|
 | **X1 (Far Left)** | PA1 | Left 1 |
 | **X2** | PA2 | Left 2 |
 | **X3** | PA3 | Left 3 |
 | **X4** | PA4 | Left 4 |
 | **X5** | PA5 | Right 4 |
 | **X6** | PB0 | Right 3 |
 | **X7** | PB1 | Right 2 |
 | **X8 (Far Right)** | PA15 | Right 1 |
 > Black line = Low level (GPIO read 0), White ground = High level. Installed at the front of the vehicle, about 20cm from the rear wheels.
 ---
 ### 3. OLED Display (SSD1306, 128×64, Hardware IIC)
 | Function | MCU Pin | Description |
 |------|---------|------|
 | **SCL** | PB6 | Hardware I2C1 clock pin |
 | **SDA** | PB7 | Hardware I2C1 data pin |
 | **VCC** | 3.3V | — |
 | **GND** | GND | — |
 ---
 ### 4. Bluetooth Module (HC-05/06)
 | Function | MCU Pin | Description |
 |------|---------|------|
 | **RXD** | PA9 | USART1 TX |
 | **TXD** | PA10 | USART1 RX |
 | **VCC** | 5V | — |
 | **GND** | GND | — |
 > Communication Protocol:
 - USART1 (115200 bps)
 - UART DMA + idle interrupt reception
 - Supports front, back, left, right, stop, MPUON, MPUOFF and other control commands
 ---
 ### 6. Gyroscope Module (MPU6050)
 | Function | MCU Pin | Description |
 |------|---------|------|
 | **I2C SDA** | PB11 | Hardware I2C1 fast-mode data pin |
 | **I2C SCL** | PB10 | Hardware I2C1 fast-mode clock pin |
 | **AD0** | GND | Device address: 0x68 |
 | **VCC** | 3.3V | — |
 | **GND** | GND | — |
 ---
 ### 7. Servo & HC-SR04 Obstacle Avoidance
 | Function | MCU Pin | Description |
 |------|---------|------|
 | **Servo Signal** | PB8 | TIM4_CH3 |
 | **TRIG** | PB3 | Output 10us high pulse to trigger ultrasonic emission |
 | **ECHO** | PB4 | Input pin for echo signal reception |
 | **VCC** | 5V | — |
 | **GND** | GND | — |
 > TIM2 implemented microsecond delay
 ---
 ### 8. Buttons & LED Indicators
 | Function | MCU Pin | Trigger Mode | Behavior |
 |------|---------|---------|------|
 | **KEY0 (Task Switch)** | PA0 | Low-level trigger | Toggle LED1 & line tracking mode |
 | **KEY1 (Task Switch)** | PB5 | Low-level trigger | Toggle LED2 & obstacle avoidance mode |
 | **LED1** | PA12 | High-level on | Status indicator |
 | **LED2** | PA11 | High-level on | Status indicator |
 ---
 ## Software Environment
 ### PC Side:
 - STM32CubeIDE, Serial Port Assistant
 ### Mobile Side:
 - HC Bluetooth Assistant
 ### Library
 - STM32 HAL Library
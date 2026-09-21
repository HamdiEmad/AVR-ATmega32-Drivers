# ATmega32 Drivers

A modular driver library for the **ATmega32 AVR microcontroller**, developed in **Embedded C** using a layered **MCAL/HAL architecture**, with parameter validation and driver-level unit testing.

The project focuses on building reusable, maintainable, and testable embedded software components while applying structured software design principles.

---

## 🚀 Features

* Modular **MCAL and HAL architecture**
* Reusable driver APIs
* Parameter and configuration **validation**
* Error-status based APIs
* Driver-level **unit testing**
* Separation of application logic from low-level hardware access
* Structured and maintainable Embedded C code
* Designed with future extensibility toward **RTOS** and **AUTOSAR-oriented embedded software**

---

## 🏗️ Software Architecture

The project follows a layered embedded software architecture:

```text
┌──────────────────────────────┐
│         Application          │
└──────────────┬───────────────┘
               │
               ▼
┌──────────────────────────────┐
│             HAL              │
│ LCD / Keypad / Motor / LED   │
│ Button / Sensors / ...       │
└──────────────┬───────────────┘
               │
               ▼
┌──────────────────────────────┐
│            MCAL              │
│ DIO / Timer / USART / ADC /  │
│ SPI / TWI / EXTI / PWM / ... │
└──────────────┬───────────────┘
               │
               ▼
┌──────────────────────────────┐
│          ATmega32            │
│           Hardware           │
└──────────────────────────────┘
```

### MCAL — Microcontroller Abstraction Layer

The **MCAL** layer contains low-level drivers that directly interface with the ATmega32's internal peripherals and registers.

The ATmega32 provides peripherals including three Timer/Counters, USART, SPI, Two-Wire Serial Interface (TWI), ADC, EEPROM, Watchdog Timer, and interrupt sources.

The driver library is planned to cover:

* DIO
* Timers
* External Interrupts
* ADC
* USART
* SPI
* TWI (I²C-compatible)
* EEPROM

### HAL — Hardware Abstraction Layer

The **HAL** layer contains drivers for external hardware components connected to the microcontroller.

Examples include:

* LCD
* Keypad
* LED
* Button
* Seven-Segment Display
* DC Motor
* Servo Motor
* Buzzer
* Sensors

---

## 🛡️ Parameter Validation

Driver APIs implement **parameter and configuration validation** to detect invalid inputs before performing hardware operations.

Depending on the driver, validation may include:

* Port validation
* Pin validation
* NULL-pointer validation
* Parameter range validation
* Mode validation
* Configuration validation
* Invalid peripheral state detection

Example:

```c
DIO_errorStatus DIO_enumReadPinValue(uint8 port, uint8 pin, uint8 *value)
{
    DIO_errorStatus ret_val = DIO_OK;

    if (port < DIO_PORTA || port > DIO_PORTD)
    {
        ret_val = DIO_INVALID_PORT;
    }
    if (pin > DIO_PIN7 || pin < DIO_PIN0)
    {
        ret_val = DIO_INVALID_PIN;
    }
    if (value == NULL)
    {
        ret_val = DIO_NULLPTR;
    }

    /* Hardware access */

    return ret_val;
}
```

The purpose of validation is to make driver interfaces more robust and to provide predictable error handling.

---

## 🧪 Unit Testing

The project includes **driver-level unit tests and test cases** to verify individual driver functions.

Testing covers both valid and invalid scenarios.

### Valid Input Testing

Examples:

* Valid ports
* Valid pins
* Valid configurations
* Valid peripheral modes
* Valid parameter ranges

### Invalid Input Testing

Examples:

* Invalid port numbers
* Invalid pin numbers
* NULL pointers
* Out-of-range parameters
* Invalid configurations
* Unsupported modes

The tests are intended to verify that drivers:

1. Accept valid inputs correctly.
2. Reject invalid inputs correctly.
3. Return the expected error status.
4. Produce the expected behavior.

> Unit testing is focused on verifying driver behavior at the software-function level, while hardware and peripheral behavior can additionally be verified through simulation or physical testing.

---

## 📂 Repository Structure

```text
ATmega32-Drivers/
│
├── APP/
│   └── main.c
│
├── MCAL/
│   ├── DIO/
│   ├── TIMER/
│   ├── USART/
│   ├── ADC/
│   ├── SPI/
│   ├── TWI/
│   ├── EXTI/
│   └── EEPROM/
│
├── HAL/
│   ├── LCD/
│   ├── KEYPAD/
│   ├── LED/
│   ├── BUTTON/
│   ├── SEV_SEG/
│   ├── DC_MOTOR/
│   ├── SERVO/
│   └── BUZZER/
│
├── TEST/
│   ├── DIO/
│   ├── TIMER/
│   ├── USART/
│   └── ...
│
├── LIB/
│   ├── BIT_MATH.h
│   └── STD_TYPES.h
│
├── README.md
└── LICENSE
```

> The repository structure may evolve as additional drivers, test modules, and examples are added.

---

## 🔌 Driver Status

### MCAL

| Driver             | Status         |
| ------------------ | -------------- |
| DIO                | ✅ Implemented |
| Timer/Counter      | 🚧 In Progress |
| External Interrupt | 🚧 In Progress |
| USART              | ⬜ Planned     |
| ADC                | ⬜ Planned     |
| SPI                | ⬜ Planned     |
| TWI                | ⬜ Planned     |
| EEPROM             | 🚧 In Progress |
| Watchdog Timer     | ⬜ Planned     |

### HAL

| Driver        | Status    |
| ------------- | --------- |
| LCD           | ⬜ Planned |
| Keypad        | 🚧 In Progress |
| LED           | ✅ Implemented |
| Button        | ✅ Implemented |
| Seven Segment | 🚧 In Progress |
| DC Motor      | ⬜ Planned |
| Servo Motor   | ⬜ Planned |
| Buzzer        | ✅ Implemented |

**Legend**

* ✅ Implemented
* 🚧 In Progress
* ⬜ Planned

---

## 🛠️ Development Environment

| Component            | Technology |
| -------------------- | ---------- |
| Microcontroller      | ATmega32   |
| Architecture         | 8-bit AVR  |
| Programming Language | Embedded C |
| Compiler             | AVR-GCC    |
| IDE                  | Eclipse    |
| Simulation           | Proteus    |
| Target Clock         | 8 MHz      |

---

## 🧠 Design Principles

The project is developed around the following principles:

* **Layered Architecture**
* **Modularity**
* **Separation of Concerns**
* **Hardware Abstraction**
* **Parameter Validation**
* **Error Handling**
* **Reusable APIs**
* **Testability**
* **Maintainability**
* **Scalability**

The application layer should interact with driver APIs rather than directly manipulating peripheral registers whenever possible.

---

## 🎯 Project Goals

The main objectives of this project are:

1. Build a reusable driver library for the ATmega32.
2. Practice professional Embedded C development.
3. Apply a structured MCAL/HAL architecture.
4. Develop robust APIs with parameter validation.
5. Verify driver behavior through unit testing.
6. Improve software reliability and maintainability.
7. Create reusable components for future embedded projects.
8. Build a strong foundation for advanced embedded software development.

---

## 🔄 Driver Development Workflow

A typical driver development workflow is:

```text
Requirement
    │
    ▼
Driver Design
    │
    ▼
Implementation
    │
    ▼
Parameter Validation
    │
    ▼
Unit Testing
    │
    ▼
Hardware / Proteus Testing
    │
    ▼
Debugging
    │
    ▼
Integration
```

This workflow separates implementation, software-level verification, and hardware-level verification.

---

## 📌 Example

A typical application can use the driver API without directly accessing peripheral registers:

```c
#include "DIO.h"

int main(void)
{
    DIO_enumSetPinDirection(
        DIO_PORTA,
        DIO_PIN0,
        DIO_OUTPUT
    );

    DIO_enumSetPinValue(
        DIO_PORTA,
        DIO_PIN0,
        DIO_HIGH
    );

    while (1)
    {
        /* Application code */
    }

    return 0;
}
```

The driver is responsible for translating the API call into the required register-level operations.

---

## 📈 Future Roadmap

### Short-Term

* Complete MCAL driver coverage
* Complete HAL driver coverage
* Expand unit-test coverage
* Add more driver test cases
* Improve driver documentation
* Add Proteus simulation examples
* Add example applications

### Medium-Term

* Automated test execution
* Static code analysis
* Continuous Integration (CI)
* Improved driver configuration mechanisms
* More portable driver interfaces
* Improved test coverage and reporting

### Long-Term

#### RTOS Exploration

Explore integrating an **RTOS** to study real-time embedded software concepts such as:

* Task scheduling
* Multitasking
* Inter-task communication
* Synchronization
* Timing and periodic tasks
* Resource management

#### AUTOSAR-Oriented Development

Explore **AUTOSAR Classic Platform concepts** as a future learning direction, particularly its layered approach to automotive embedded software.

AUTOSAR Classic separates the system into Application Software, Runtime Environment (RTE), and Basic Software (BSW). The BSW includes the Microcontroller Abstraction Layer (MCAL), ECU Abstraction, and Services layers.

Potential areas of exploration include:

* AUTOSAR layered architecture
* AUTOSAR MCAL concepts
* Standardized driver interfaces
* ECU abstraction
* Basic Software (BSW)
* RTE concepts
* Configuration-driven development

> **Note:** RTOS and AUTOSAR are future learning and development directions. They are **not part of the current implementation**, and the current ATmega32 drivers should not be considered AUTOSAR-compliant drivers.

---

## 📚 Learning Objectives

This repository serves as a practical project for developing knowledge in:

* AVR microcontroller architecture
* Embedded C
* Register-level programming
* Peripheral driver development
* MCAL/HAL architecture
* Hardware abstraction
* Defensive programming
* Parameter validation
* Unit testing
* Embedded software design
* Real-time systems
* Automotive embedded software concepts

---

## 👨‍💻 Author

**Hamdi Emad**

Engineering Student — Computers and Systems Engineering

### Areas of Interest

* Embedded Systems
* Robotics
* PCB Design
* IoT
* Real-Time Systems
* Automotive Embedded Systems

---

## 📄 License

This project is intended primarily for educational purposes and embedded-systems development.

This project also uses the official ATmega32 documentation provided by
Microchip Technology.

Datasheet link: `https://ww1.microchip.com/downloads/en/DeviceDoc/doc2503.pdf`

See the `LICENSE` file for more information.

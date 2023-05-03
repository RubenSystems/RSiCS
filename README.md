# RSiCS
*by chatgpt*

RSiCS (Realtime Secure Communication System) is a custom transport layer protocol built on top of UDP, designed for efficient and fast communication with low overhead. It has been developed with a focus on efficiency for IoT devices and phones, but it can also be used in a standard client-server architecture for larger computers.

## Features

- Fast and efficient: RSiCS is designed for real-time communication with low overhead, making it an ideal choice for IoT devices and phones with limited processing power and network bandwidth.
- Customizable: RSiCS is highly customizable, allowing you to configure it to meet your specific requirements and use cases.

## Use cases 
- Video streaming
- Stock quotes 
- Message passing 
- Autocomplete

## How it works

RSiCS uses a custom transport layer protocol built on top of UDP. This allows it to provide fast and efficient communication with low overhead. The protocol includes encryption and authentication mechanisms to ensure the security and privacy of communication.

The RSiCS library provides a simple API for developers to integrate into their software. The API allows for the creation of both server and client applications, and supports both synchronous and asynchronous communication.

## Getting Started
Clone the project, cd into the directory run (on linux) 

```
make
make install
```

then just link your project to librsics.so and #include anything you need
Alternativly, you can use ctypes and use it in python3. 

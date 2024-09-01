# C++ Server Application for TCP Socket Communication

## Overview

This C++ server application manages TCP socket communications to handle client requests. It is designed to parse requests, manage connections, respond to specific commands such as opening web pages, and retrieve device statuses like battery percentage, CPU usage, RAM usage, and disk space. The application demonstrates modular design principles for scalability and maintainability.

## Features

- **Client-Server Communication:** Handles multiple client connections and ensures robust communication through TCP sockets.
- **Request Handling:** Parses client requests and responds with appropriate messages, including HTTP responses.
- **Website Management:** Can open specified websites like Facebook, Google, YouTube, and Twitter through commands.
- **Device Status Monitoring:** Retrieves and returns device status information, such as battery level, CPU usage, RAM usage, and disk space.
- **Modular Design:** The application uses a modular approach for easy scalability and maintenance.


## Prerequisites

To compile and run this application, you need:

- A C++ compiler that supports C++11 or later.
- A Unix-like operating system (Linux, macOS) or Windows with suitable adjustments.
- Basic understanding of TCP/IP networking and socket programming.

## Installation and Setup

1. **Clone the Repository:**

   ```bash
   git clone <repository-url>
   cd <repository-directory>
   ```

2. **Compile the Application:**

   Use a C++ compiler to compile the source files. For example, using `g++`:

3. **Run the Server:**

   ```bash
   ./server
   ```

## Usage

- Start the server application by running the compiled binary.
- The server listens for incoming client connections.
- Clients can send requests such as "hi", "exit", or commands to open websites (e.g., "website google") or retrieve device status (e.g., "deviceStatus cpu").
- The server responds with appropriate HTTP responses based on the client's requests.

## Commands

- **`hi`**: Responds with "Hello, client!".
- **`exit`**: Closes the client connection gracefully.
- **`website [name]`**: Opens the specified website (options include `facebook`, `google`, `youtube`, `twitter`).
- **`deviceStatus [type]`**: Retrieves the specified device status (options include `battery`, `cpu`, `ram`, `disk`).

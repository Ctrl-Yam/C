# posix-web-server

A simple HTTP web server written from scratch in C on Linux (WSL). This project uses raw POSIX socket system calls to handle TCP connections and process HTTP requests without external libraries.

## How It Works

The server follows the standard Linux socket lifecycle:

1. **`socket()`** – Allocates an IPv4 TCP socket resource (returns File Descriptor `3`).
2. **`bind()`** – Assigns host address `0.0.0.0` and port `8080` to the socket using `struct sockaddr_in` and `htons()`.
3. **`listen()`** – Marks the socket as passive, setting a connection backlog queue of 10.
4. **`accept()`** – Blocks until a client connects, then spawns a dedicated client file descriptor (`4`).
5. **`read()` & `write()`** – Reads raw HTTP headers sent by the browser and responds with an HTTP/1.1 200 OK header and HTML payload.

## Building and Running

### Prerequisites
* GCC compiler
* Linux / WSL environment (`build-essential`)

### Quickstart

1. Clone the repository:
   ```bash
   git clone [https://github.com/Ctrl-Yam/posix-web-server.git](https://github.com/Ctrl-Yam/posix-web-server.git)
   cd posix-web-server

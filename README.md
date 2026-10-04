# C Web Server from Scratch

Instead of just spinning up a Python or Express server, I wanted to build one from the ground up in C on Linux (WSL) to see what's actually happening at the OS level.

No external libraries or frameworks—just raw C and POSIX socket system calls.

## How It Works

When you hit `localhost:8080` in your browser, here's the exact lifecycle:

1. **`socket()`** – Asks the kernel to allocate an IPv4 TCP socket (gives back File Descriptor `3`).
2. **`bind()`** – Ties that socket handle to `0.0.0.0:8080` using `struct sockaddr_in` (and `htons()` so network byte order doesn't flip the port).
3. **`listen()`** – Tells the OS to start listening for incoming connections with a backlog queue of 10.
4. **`accept()`** – Pauses execution until a connection arrives, then spawns a dedicated client handle (`4`) for that line.
5. **`read()` & `write()`** – Captures the raw HTTP request header sent by the browser, then streams back an `HTTP/1.1 200 OK` header with an HTML response.

## Running It

You'll need `gcc` installed in a Linux environment or WSL.

1. **Clone the repo:**
   ```bash
   git clone [https://github.com/Ctrl-Yam/c-web-server.git](https://github.com/Ctrl-Yam/c-web-server.git)
   cd c-web-server

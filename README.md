# Basic Doc for the HTTP Flood Code

This program sends multiple simultaneous HTTP requests to a target server, useful for testing the server's response to heavy load. It uses threads to create multiple connections at the same time and sends a custom HTTP request.

## 1. Prerequisites

### Compiler:
- **Windows**: You need a C compiler compatible with Windows, such as **MinGW** or **MSVC**.
- **Libraries**: The code uses the **Winsock2** library for network connections and **pthread** for multithreading. These libraries are standard in the Windows environment.

### Installing MinGW (optional):
If you don't have a compiler installed, you can download **MinGW** and install the required dependencies.
1. Download MinGW from [here](https://sourceforge.net/projects/mingw/).
2. During installation, make sure to include the `gcc` compiler and the `pthread` library.

### Compilation:

To compile the program, use the following command in the terminal:

```bash
gcc -o httpflood httpflood.c -lws2_32 -lpthread
```

- **`-lws2_32`**: Links the `Winsock2` library for network functions.
- **`-lpthread`**: Links the `pthread` library for thread support.

## 2. Usage

### Syntax:
```bash
httpflood.exe <host> <path> <method> <port>
```

### Parameters:
1. **host**: The hostname or domain to which the HTTP requests will be sent.
2. **path**: The resource path on the server (e.g., `/index.html`, `/api/v1/resource`).
3. **method**: The HTTP method to be used in the requests (e.g., `GET`, `POST`, etc.).
4. **port**: The port on which the server is listening (e.g., `80` for HTTP or `443` for HTTPS).

### Example of Usage:
```bash
httpflood.exe www.example.com / GET 80
```
This command will send multiple `GET` requests to `www.example.com` on the resource `/` using port `80`.

### Expected Result:
- The program will create multiple threads, each sending an HTTP request to the target server.
- Each request will receive a response (if the server replies), and the response will be printed on the console.

## 3. Output

The program will print messages on the console indicating progress, errors, and the responses received from the server.

### Possible Error Messages:
1. **`Socket error`**: Indicates that there was a failure in creating the socket.
2. **`Failed to connect socket`**: Failed to connect to the server. This could be due to an IP, port, or firewall issue.
3. **`Error to send package`**: An error occurred while sending the HTTP request.
4. **`Receive error`**: An error occurred while receiving the server's response.

### Server Response:
If the request is successful, the HTTP response from the server will be displayed on the console. The response content is limited to the size of the buffer (4096 bytes in this example).

## 4. Adjustments and Limitations

1. **Number of Threads**: The number of threads is set to `100` in the code (`threads_n`). If needed, adjust this value based on your system's capacity and the desired behavior. Use with caution, as creating too many threads may overwhelm the system or the target server.
   
2. **IP Resolution**: The `gethostbyname` function is used to convert the hostname to an IP address. If DNS resolution fails, the program will display an error message.

3. **Network Limitations**: This program may generate significant network traffic. Be careful when using it, as sending too many requests to a server could be interpreted as an attack, potentially blocking your IP.

## 5. Final Notes

- This program is designed for educational purposes or supervised capacity testing by the server administrator. Misuse could result in legal or technical issues.
- **Do not use this program for malicious activities, such as DDoS attacks**.

# Basic TCP Server

A realy basic TCP server to explain how create TCP server in C.

## Usage

Compile the server
```
make
```

Run the server on `0.0.0.0:8080`
```
bin/server
```

Check the server is listing
```sh
lsof -i:8080
```

Connect to the server using telnet
```
telnet 0.0.0.0 8080
```

The connection should imediatly be close by the server and the
server logs should display "Client connected!" when everithing
work properly.

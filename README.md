# at-communication

A command-line tool for querying a cellular modem over AT commands. It is written in C for the Teltonika RUTX11 router (OpenWrt / RutOS) and prints the results as plain text or JSON.

## Features

| Option              | Description                                           | AT command                |
| ------------------- | ----------------------------------------------------- | ------------------------- |
| `-b, --band`        | Mobile network frequency band                         | `AT+QCFG="band"`          |
| `-c, --cell`        | Serving cell info                                     | `AT+QENG="servingcell"`   |
| `-N, --neighbour`   | Neighbour cells                                       | `AT+QENG="neighbourcell"` |
| `-i, --imei`        | IMEI number                                           | `AT+GSN`                  |
| `-I, --info`        | Modem manufacturer and model                          | `ATI`                     |
| `-o, --operator`    | Currently selected operator                           | `AT+COPS?`                |
| `-O, --operators`   | Available operators (a scan can take up to 3 minutes) | `AT+COPS=?`               |
| `-t, --temperature` | Modem temperatures                                    | `AT+QTEMP`                |
| `-j, --json`        | Format the output as JSON                             |                           |
| `-D, --debug`       | Print everything sent to and received from the modem  |                           |
| `-m, --mock PATH`   | Read modem responses from a file instead of the serial port, for testing without hardware |  |

## How it works

The tool opens the modem's AT port (`/dev/ttyUSB2`, 115200 baud, 8N1), sends a command and reads the response lines until it sees `OK` or an error. Commands are retried on timeout. Modem errors (`ERROR`, `+CME ERROR`, `+CMS ERROR`) are translated into readable messages using the error code tables for the device.

Device-specific code is located in `src/devices/<model>/`. Commands are called through function pointers that are set up at startup for the selected device, so supporting another modem means adding a new directory and an entry in `modem_list.h`.

## Building

The project is an OpenWrt package. Copy the `at-communication` directory into your OpenWrt / RutOS SDK `package/` directory, select `at-communication` (Base system) in `make menuconfig` and build:

```sh
make package/at-communication/compile
```

## Usage

```sh
at-communication --help              # provides a list of all commands
at-communication -I                  # modem manufacturer and model
at-communication -t -j               # temperatures as JSON
at-communication -c -b               # serving cell and band
at-communication -O                  # scan for operators (slow)
```

Several options can be combined in one call.

## Project layout

```
at-communication/src/
├── src/main.c, argument_parser.c    # CLI entry point and option parsing
├── src/command_utils.c              # sending commands, reading and checking responses
├── src/serial_utils.c               # serial port setup and I/O (and mock mode)
├── src/parser_utils.c, json_utils.c, output_utils.c
└── src/devices/EG06/                # Quectel EG06 commands, parsers and error codes
```

## Known issues

- `--number`, `--messages`, `--message` (SMS) and `--device` are not finished yet.
- JSON output for serving and neighbour cells is not implemented yet.
- The serial port path is fixed to `/dev/ttyUSB2`.

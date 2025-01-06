# htlib

A lightweight, cross-platform C library for hashmaps.

## Features

> [!caution]
> The library is not ready. It is still missing features for automatic resizing and there is an issue with tables using integer keys and string values.

*   Supports various key and value types:
    *   Signed/unsigned integers
    *   Signed/unsigned floats/doubles
    *   C strings
*   No external dependencies (standard C only)
*   CMake build system
*   GoogleTest framework for unit testing
*   Doxygen for API documentation

## Getting Started

1.  Clone the repository: `git clone https://github.com/your-username/htlib.git`
2.  Build the library:
    *   `mkdir build && cd build`
    *   `cmake ..`
    *   `make`
3.  Run tests: `./htlib_test`
4.  Install (optional): `make install`

## Usage

See the `htlib.h` header file for API documentation.

## Documentation

API documentation is generated using Doxygen and can be found in the `docs` folder. You can also view the documentation online at [RARM.github.com/htlib](https://RARM.github.com/htlib).

## Contributing

Contributions are welcome! Please feel free to submit pull requests.

## License

This project is released to the public domain using the Unlicense. See the [UNLICENSE](UNLICENSE) file for details. 

[Unlicense](https://unlicense.org/)
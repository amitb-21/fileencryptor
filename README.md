# File Encryption/Decryption Tool

A C++ application that recursively encrypts or decrypts all files in a directory using a Caesar cipher algorithm. The application supports both direct execution and process-based execution models.

## Features

- **Recursive Directory Processing**: Automatically processes all files in a directory and its subdirectories
- **Caesar Cipher Encryption**: Uses a simple but effective Caesar cipher with configurable key
- **Dual Execution Models**: Supports both direct function calls and separate process execution
- **Binary File Support**: Handles both text and binary files correctly
- **Environment-based Configuration**: Encryption key is read from a `.env` file
- **Error Handling**: Comprehensive error handling with informative messages

## Project Structure

```
.
├── .env                                    # Environment file containing encryption key
├── Makefile                               # Build configuration
├── main.cpp                               # Main application entry point
├── src/
│   └── app/
│       ├── encryptDecrypt/
│       │   ├── Cryption.cpp               # Core encryption/decryption logic
│       │   ├── Cryption.hpp               # Cryption header file
│       │   └── CryptionMain.cpp           # Standalone cryption executable
│       ├── fileHandling/
│       │   ├── IO.cpp                     # File I/O operations
│       │   ├── IO.hpp                     # IO header file
│       │   ├── ReadEnv.cpp                # Environment file reader
│       │   └── ReadEnv.hpp                # ReadEnv header file
│       └── processes/
│           ├── ProcessManagement.cpp      # Task queue and process management
│           ├── ProcessManagement.hpp      # ProcessManagement header file
│           └── Task.hpp                   # Task structure definition
└── test/
    ├── test1.txt                          # Sample test file
    └── test2.txt                          # Sample test file
```

## Requirements

- **C++ Compiler**: g++ with C++17 support
- **Operating System**: Linux/Unix (uses POSIX file system APIs)
- **Build System**: Make

## Installation

1. Clone or download the project files
2. Navigate to the project directory
3. Ensure you have g++ installed with C++17 support

## Configuration

The encryption key is stored in the `.env` file in the root directory. By default, it contains:

```
123456
```

You can modify this file to use a different encryption key. The key should be a numeric value.

## Building

To build the project, use the provided Makefile:

```bash
# Build all targets
make

# Build only the main application
make encrypt_decrypt

# Build only the cryption utility
make cryption

# Clean build artifacts
make clean
```

This will create two executables:
- `encrypt_decrypt`: Main application
- `cryption`: Standalone cryption utility

## Usage

### Main Application

Run the main application:

```bash
./encrypt_decrypt
```

The application will prompt you for:
1. **Directory path**: Enter the path to the directory you want to process
2. **Action**: Enter either "encrypt" or "decrypt"

Example:
```
Enter the directory path: test
Enter the action (encrypt/decrypt): encrypt
```

### Standalone Cryption Utility

The cryption utility can be used independently:

```bash
./cryption "<filepath>,<action>"
```

Example:
```bash
./cryption "test/test1.txt,ENCRYPT"
./cryption "test/test1.txt,DECRYPT"
```

## How It Works

### Encryption Algorithm

The application uses a Caesar cipher algorithm:
- **Encryption**: Each byte is shifted forward by the key value: `(byte + key) % 256`
- **Decryption**: Each byte is shifted backward by the key value: `(byte - key + 256) % 256`

### Processing Flow

1. **Directory Traversal**: The application recursively scans the specified directory
2. **File Processing**: Each file is opened in binary mode for reading and writing
3. **Task Creation**: A task is created for each file with the specified action
4. **Queue Management**: Tasks are added to a processing queue
5. **Execution**: Tasks are executed either directly or via separate processes

### File Handling

- Files are opened in binary mode (`std::ios::binary`) to handle both text and binary files
- The entire file content is read into memory, processed, and written back
- File streams are properly closed after processing

## Error Handling

The application includes comprehensive error handling for:
- Invalid directory paths
- File access permissions
- Missing or invalid `.env` file
- Malformed task data
- File I/O errors

## Development Notes

### Process Management

The application includes two execution models:

1. **Direct Execution** (Currently Active): Functions are called directly within the main process
2. **Process-based Execution** (Commented): Uses `fork()` and `execv()` to run cryption as separate processes

To switch to process-based execution, uncomment the relevant code in `ProcessManagement.cpp`.

### Debugging

The code includes debug output and is configured for debugging:
- Compiled with `-g` flag for debugging symbols
- Includes debug print statements for task execution
- VS Code debugging support mentioned in comments

## Testing

Sample test files are provided in the `test/` directory:
- `test1.txt`: Contains "Hello World"
- `test2.txt`: Contains "Hello Guys"

To test the application:

1. Build the project: `make`
2. Run encryption: `./encrypt_decrypt`
3. Enter `test` as directory and `encrypt` as action
4. Check that files are encrypted (content should be unreadable)
5. Run decryption: `./encrypt_decrypt`
6. Enter `test` as directory and `decrypt` as action
7. Verify files are restored to original content

## Security Considerations

- This is a simple Caesar cipher implementation intended for educational purposes
- The encryption is not cryptographically secure
- The key is stored in plain text in the `.env` file
- For production use, consider implementing stronger encryption algorithms

## Troubleshooting

### Common Issues

1. **Compilation Errors**: Ensure g++ supports C++17 and all header files are present
2. **File Permission Errors**: Check that the application has read/write permissions for target files
3. **Missing .env File**: The application will use key 0 if `.env` is missing (no encryption effect)
4. **Invalid Directory**: Ensure the directory path exists and is accessible

### Build Issues

If you encounter build issues:

```bash
# Clean and rebuild
make clean
make

# Check compiler version
g++ --version

# Verify C++17 support
g++ -std=c++17 --version
```

## License

This project is provided as-is for educational purposes. Feel free to modify and distribute according to your needs.

## Contributing

To contribute to this project:
1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## Version History

- **v1.0**: Initial release with basic encryption/decryption functionality
- **v1.1**: Added proper error handling and fixed file I/O issues
- **v1.2**: Improved process management and added comprehensive documentation

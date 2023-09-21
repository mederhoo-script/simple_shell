# Simple Shell Peer Project

## Team Members
- Hammed Amusat Oriyomi
- Kingjerry Oludayo

## Description
This project is a simple shell program written in C. It provides a command-line interface for users to interact with the operating system. The shell supports basic commands such as `cd`, `exit`, and can execute other system commands.

## Usage
To compile the shell program, use the following command:
```bash
gcc simpleshell.c -o shell
```

To run the shell in interactive mode, simply execute the compiled binary:
```bash
./shell
```

To run a command directly from the command line, pass it as an argument to the shell binary:
```bash
./shell ls -l
```

## Features
- Supports basic commands: `cd`, `exit`
- Can execute other system commands
- Supports environment variables: `$$`, `$?`, `$PATH`

## Command Syntax
The shell recognizes the following commands:

### cd
Change the current working directory.

Syntax:
```bash
cd <directory>
```

Example:
```bash
cd /home/user/documents
```

### exit
Exit the shell. Optionally, you can provide an exit status.

Syntax:
```bash
exit [<status>]
```

Example:
```bash
exit 0
```

### Environment Variables
The shell supports the following environment variables:

- `$$`: PID of the shell process.
- `$?`: Exit status of the last command.
- `$PATH`: Value of the PATH environment variable.

### setenv
Set an environment variable.

Syntax:
```bash
setenv <VARIABLE> <VALUE>
```

Example:
```bash
setenv MY_VAR some_value
```

### unsetenv
Unset an environment variable.

Syntax:
```bash
unsetenv <VARIABLE>
```

Example:
```bash
unsetenv MY_VAR
```

### echo
Echo the value of an environment variable.

Syntax:
```bash
echo $<VARIABLE>
```

Example:
```bash
echo $MY_VAR
```

## Contributing
To contribute to this project, fork the repository, make your changes, and submit a pull request. Please ensure that your code follows the project's coding style and conventions.

## Issues
If you encounter any issues or have suggestions for improvement, please open an issue on the GitHub repository.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
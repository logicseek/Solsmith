## Overview

Solsmith is a testing program generator specifically designed to discover defects in the Solidity compiler by generating valid Solidity code to test the compiler's correctness. To generate test programs that are more likely to expose defects in the Solidity compiler, we have designed a series of unique code generation strategies tailored for Solidity. These strategies include more frequent enabling of optimizations, manually adjusting the generation probabilities of different syntax components, avoiding undefined behavior, and preventing behavioral differences caused by intermediate representations. Among these, more frequent enabling of optimizations allows for more efficient compiler testing, manually adjusting the generation probabilities of different syntax components increases the diversity of the generated test programs, and avoiding undefined behavior and intermediate representation-induced differences ensures the consistency of the generated test programs across different environments.

## Usage

### Build and Run

This project has been developed and tested using **Visual Studio**.

To build and run the project:

1. Open the solution file `ConsoleApplication1.sln` in Visual Studio.  
2. Build and run the project. The entry point is in `ConsoleApplication1.cpp`.

### Configuration

You can customize the number of generated programs and the output directory by modifying `ConsoleApplication1.cpp`:

```cpp
for (int i = 0; i < 10000; i++) {
    std::string testpath = "your/output/directory/";
    // ...
}

The loop count (`10000`) controls how many programs are generated.

The `testpath` string specifies the directory where the generated files will be saved.

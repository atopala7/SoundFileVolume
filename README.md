# SoundFileVolume

## Overview
This command-line tool, split into two separate programs, is aimed at investigating the computational costs associated with adjusting the volume of sound samples. The programs compare two approaches: direct multiplication and a lookup table method. The objective is to optimize mathematical operations for sound processing across different hardware architectures, such as x86_64 and AArch64 servers.

## Requirements
- **GCC compiler**: Needed for compiling the source code.
- **sox utility**: Required for converting WAV files to the raw audio format.
- **Knowledge**: A basic understanding of digital audio processing and C programming is recommended.

## Compilation Instructions
Compile each program with minimal optimizations to ensure an accurate performance assessment. Use the following GCC commands:

- For `first.c`:
  ```bash
  gcc -g -O0 first.c -o first
  ```

- For `second.c`:
  ```bash
  gcc -g -O0 second.c -o second
  ```

The -O0 flag tells the compiler to apply only minimal optimizations, preserving the program's intended logic and runtime characteristics.

## Usage

1. Audio File Preparation: Convert a WAV music file to a raw format:
    ```bash
    sox <input.wav> -t raw sound.raw
    ```

2. Execute the Program: Run the chosen program with the raw audio file as an argument:
    - For first.c:
      ```bash
      ./first sound.raw
      ```

    - For second.c:
      ```bash
      ./second sound.raw
      ```

3. Output: An output.raw file is generated, containing the sound samples with adjusted volume.

## How They Work
- first.c: Adjusts the volume of each sound sample by multiplying it with a fixed volume factor (0.5 for halving the volume).
- second.c: Uses a precomputed lookup table for volume adjustment. It calculates and stores all possible outcomes of scaling a sample by the volume factor in memory, which are then retrieved as needed, avoiding repetitive multiplication.

## Performance Measurement

The programs measure and report the time and processor cycles required for volume adjustment, offering insights into the computational efficiency of each method across different system architectures.

## Key Differences
- Direct Multiplication (first.c): Employs a straightforward multiplication operation for each sound sample to adjust volume.
- Lookup Table (second.c): Optimizes volume adjustment by using a precomputed lookup table, potentially improving performance on systems where memory access is faster than performing arithmetic operations.

## Conclusion
Selecting between direct multiplication and a lookup table for sound volume adjustment can greatly affect computational efficiency, depending on the hardware architecture. first.c demonstrates a conventional approach, while second.c introduces an optimization strategy that may be beneficial under certain conditions, emphasizing the importance of algorithm design tailored to specific system characteristics.

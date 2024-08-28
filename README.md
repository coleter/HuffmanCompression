# Huffman Compression Project

## Overview

This project implements Huffman compression and decompression algorithms in C. Huffman coding is a lossless data compression algorithm that assigns variable-length codes to input characters, with shorter codes assigned to more frequent characters. The project includes functions to encode a file into a compressed format and to decode a compressed file back to its original form.

## Features

- **Compression**: The program compresses a given text file using Huffman coding and generates a `.huf` file.
- **Decompression**: The program can decode a `.huf` file back to its original text form and generates a `.dec` file.
- **Frequency Table**: The program creates a frequency table for the characters in the input file, which is then used to build the Huffman tree.

## Files

- `hcompress.c`: Contains the main program and the implementation of Huffman compression and decompression functions.
- `hcompress.h`: Header file for `hcompress.c`.
- `linkedList.c`: Implements a linked list used to manage nodes in the priority queue.
- `linkedList.h`: Header file for `linkedList.c`.
- `decind.txt`: Sample text file for compression and decompression

## How to Compile

You can compile the project using the provided Makefile. Run the following command:

```bash
make
```
This will generate an executable file named hcompress.

## How to Run

To **compress** a file:
```bash
./hcompress -e <filename>
```
To **decompress** a file:

```bash
./hcompress -d <filename>
```
### Example:
To **compress** a file called `sample.txt`:

```bash
./hcompress -e sample.txt
```  
This will create a compressed file called `sample.txt.huf`  

To **decompress** `sample.txt.huf`,
```bash
./hcompress -d sample.txt.huf
```
This will create a new, decompressed file called `sample.txt.dec`

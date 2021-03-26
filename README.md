# LZW-Compression

Lossless data compression algorithm that utilizes reoccurring patterns to save disk save. Can also be used to compress non-text files. 

## Overview
A single code greater than 255 is assigned to reoccuring patterns. Patterns and codes are stored in a dictonary. Same dictonary used to encode and decode. 

## Usage

Compile using `g++ main.cpp` <br/>
* Encoding
`./a.out msg.txt encoded.txt`
* Decoding
`./a.out encoded.txt decoded.txt`

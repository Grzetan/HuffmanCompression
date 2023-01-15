# HuffmanCompression

Compile project using `cmake .` and `make`.

To compress a file use:

```bash
./main -i text.txt -o compressed.txt -t k
```

`-i` is an input file.
`-o` is a name of output file.
`-t` is type. Either `k` (compress) or `d` (decompress).

While compressing `dict.txt` will be created which has huffman codes for every character. It will be used when decompressing.

To decompress a file use:

```bash
./main -i compressed.txt -o decompressed.txt -s dict.txt -t d
```

`-i` is an input file.
`-o` is a name of output file.
`-t` is type. Either `k` (compress) or `d` (decompress).
`-s` is a path to dict file created during compressing.

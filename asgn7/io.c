#include "io.h"

#include "code.h"
#include "endian.h"
#include "word.h"

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

static uint8_t bitbuf[BLOCK] = { 0 };
static uint8_t symbuf[BLOCK] = { 0 };
static int bitindex = 0; // index for buffer
static int symindex = 0; // index for buffer

bool getbit_buf(uint8_t *bitbuf, int bitindex) {
    uint8_t byte = bitbuf[bitindex / 8];
    return (byte & (1 << bitindex % 8)) >> (bitindex % 8);
}

void setbit_buf(uint8_t *bitbuf, int bitindex) {
    uint8_t byte = bitbuf[bitindex / 8];
    bitbuf[bitindex / 8] = byte | (1 << bitindex % 8);
}

void clrbit_buf(uint8_t *bitbuf, int bitindex) {
    uint8_t byte = bitbuf[bitindex / 8];
    bitbuf[bitindex / 8] = byte & ~(1 << bitindex % 8);
}

bool getbit(uint16_t x, int i) {
    return (x & (1 << i)) >> i;
}

void setbit_16(uint16_t *x, int i) {
    *x = *x | (1 << i);
}

void clrbit_16(uint16_t *x, int i) {
    *x = *x & ~(1 << i);
}

void setbit_8(uint8_t *x, int i) {
    *x = *x | (1 << i);
}

void clrbit_8(uint8_t *x, int i) {
    *x = *x & ~(1 << i);
}

int read_bytes(int infile, uint8_t *buf, int to_read) { //to_read must be in boundary of the buffer
    int total = 0;
    long bytes = 0;
    while ((bytes = read(infile, buf, to_read)) > 0) {
        total += bytes;
        to_read -= bytes;
        buf += bytes;
    }
    return total;
}

int write_bytes(int outfile, uint8_t *buf, int to_write) {
    int total = 0;
    long bytes = 0;
    while ((bytes = write(outfile, buf, to_write)) > 0) {
        total += bytes;
        to_write -= bytes;
        buf += bytes;
    }
    return total;
}

void read_header(int infile, FileHeader *header) {
    read_bytes(infile, (uint8_t *) header, sizeof(FileHeader));
    if (big_endian() == true) {
        header->magic = swap32(header->magic);
        header->protection = swap16(header->protection);
    }
}

void write_header(int outfile, FileHeader *header) {
    if (big_endian() == true) {
        header->magic = swap32(header->magic);
        header->protection = swap16(header->protection);
    }
    write_bytes(outfile, (uint8_t *) header, sizeof(FileHeader));
}

static int end_of_sym = -1;

bool read_sym(int infile, uint8_t *sym) {
    if (symindex == 0) {
        int read = read_bytes(infile, symbuf, BLOCK);
        if (read == 0) {
            return false;
        }
        if (read < BLOCK) {
            end_of_sym = read + 1;
        }
    }
    *sym = symbuf[symindex];
    symindex++;
    if (symindex == BLOCK) {
        symindex = 0;
    }
    if (end_of_sym == symindex) {
        return false;
    }
    return true;
}

void write_pair(int outfile, uint16_t code, uint8_t sym, int bitlen) {
    if (big_endian()) {
        code = swap16(code);
    }
    for (int i = 0; i < bitlen; i++) { // copy codes to buffer
        if (getbit(code, i) == 1) {
            setbit_buf(bitbuf, bitindex);
        } else {
            clrbit_buf(bitbuf, bitindex);
        }
        bitindex++;
        if (bitindex == BLOCK * 8) { //hit end of the buffer
            write_bytes(outfile, bitbuf, BLOCK);
            bitindex = 0;
        }
    }
    for (int i = 0; i < 8; i++) { // copy syms to buffer
        if (getbit(sym, i) == 1) {
            setbit_buf(bitbuf, bitindex);
        } else {
            clrbit_buf(bitbuf, bitindex);
        }
        bitindex++;
        if (bitindex == BLOCK * 8) { //hit end of the buffer
            write_bytes(outfile, bitbuf, BLOCK);
            bitindex = 0;
        }
    }
}

int byte(uint32_t bits) {
    return bits % 8 == 0 ? bits / 8 : (bits / 8) + 1;
}

void flush_pairs(int outfile) {
    if (bitindex > 0) {
        write_bytes(outfile, bitbuf, byte(bitindex));
    }
    bitindex = 0;
}

bool read_pair(int infile, uint16_t *code, uint8_t *sym, int bitlen) {
    uint16_t temp_code = 0;
    uint8_t temp_sym = 0;
    int read = 0;
    for (int i = 0; i < bitlen; i++) {
        if (bitindex == 0) {
            read = read_bytes(infile, bitbuf, BLOCK);
        }
        if (getbit_buf(bitbuf, bitindex) == 1) {
            setbit_16(&temp_code, i);
        } else {
            clrbit_16(&temp_code, i);
        }
        bitindex++;
        if (bitindex == BLOCK * 8) { //hit end of the buffer
            bitindex = 0;
        }
    }

    for (int i = 0; i < 8; i++) {
        if (bitindex == 0) {
            read = read_bytes(infile, bitbuf, BLOCK);
        }
        if (getbit_buf(bitbuf, bitindex) == 1) {
            setbit_8(&temp_sym, i);
        } else {
            clrbit_8(&temp_sym, i);
        }
        bitindex++;
        if (bitindex == BLOCK * 8) { //hit end of the buffer
            bitindex = 0;
        }
    }
    if (big_endian()) {
        temp_code = swap16(temp_code);
    }
    *code = temp_code;
    *sym = temp_sym;
    if (temp_code == STOP_CODE) {
        return false;
    }
    return true;
}

void write_word(int outfile, Word *w) {
    for (uint32_t i = 0; i < w->len; i++) {
        symbuf[symindex] = w->syms[i];
        symindex++;
        if (symindex == BLOCK * 8) {
            write_bytes(outfile, symbuf, BLOCK);
        }
    }
}

void flush_words(int outfile) {
    if (symindex > 0) {
        write_bytes(outfile, symbuf, symindex);
        symindex = 0;
    }
}

//
// Created by bigun on 12/28/2018.
//

#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
//#include <bitmap_image.hpp>
#include "EasyBMP/EasyBMP.h"

#ifndef VBFEDIT_EIFIMAGE_H
#define VBFEDIT_EIFIMAGE_H

static const uint8_t EIF_SIGNATURE[] = {'E','B','D',0x10,'E','I','F'};
static const uint8_t EIF_TYPE_MONOCHROME = 0x04;
static const uint8_t EIF_TYPE_MULTICOLOR = 0x07;
static const uint8_t EIF_TYPE_SUPERCOLOR = 0x0E;
static const int EIF_MULTICOLOR_PALETTE_SIZE = 0x300;

struct EifBaseHeader {
    uint8_t  signature[7];
    uint8_t  type;
    uint32_t length;
    uint16_t width;
    uint16_t height;
};

class EifImageBase {
protected:
    unsigned width;
    unsigned height;
    std::vector<uint8_t> bitmap_data;
public:
    virtual int openEif(const std::vector<uint8_t>& data) = 0;
    virtual int openBmp(std::string fileName) = 0;
    virtual void saveBmp(std::string fileName) = 0;
    virtual void saveEif(std::string fileName) = 0;
    virtual ~EifImageBase(){};
};

class EifImage8bit: public EifImageBase {
public:
    int openEif(const std::vector<uint8_t>& data) override;
    void saveBmp(std::string file_name) override;
    int openBmp(std::string file_name) override;
    void saveEif(std::string file_name)override;
};

class EifImage16bit: public EifImageBase {
    std::vector<uint8_t> palette;
    uint8_t searchPixel(RGBApixel rgb_pixel);
public:
    int openEif(const std::vector<uint8_t>& data) override;
    void saveBmp(std::string file_name) override;
    int openBmp(std::string file_name) override;
    void saveEif(std::string file_name)override;
};

class EifImage32bit: public EifImageBase {
public:
    int openEif(const std::vector<uint8_t>& data) override;
    int openBmp(std::string file_name) override;
    void saveBmp(std::string file_name) override;
    void saveEif(std::string file_name) override;
};

#endif //VBFEDIT_EIFIMAGE_H


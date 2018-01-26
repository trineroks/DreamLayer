#include "BinReader.h"
#include <climits>


BinReader::BinReader() {
}

BinReader::BinReader(int size) {
	data = new char[size];
}

BinReader::BinReader(char* _data) {
	data = _data;
}

BinReader::~BinReader() {
}

char BinReader::readByte() {
	return data[offset++];
}

int BinReader::readInt() {
	return (((data[offset++]) << 24) | ((data[offset++] & CHAR_MAX) << 16) | ((data[offset++] & CHAR_MAX) << 8) | data[offset++] & CHAR_MAX);
}

short BinReader::readShort() {
	return (((data[offset++]) << 8) | (data[offset++] & CHAR_MAX));
}

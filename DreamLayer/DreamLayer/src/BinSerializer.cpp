#include "BinSerializer.h"

BinSerializer::BinSerializer(int size) {
	data = new char[size];
}

BinSerializer::BinSerializer(char* _data) {
	data = _data;
}

BinSerializer::~BinSerializer() {
	delete data;
	data = nullptr;
}

void BinSerializer::writeByte(char val) {
	data[offset] = val;
	offset++;
}

void BinSerializer::writeInt(int val) {
	writeByte((char)(val >> 24));
	writeByte((char)(val >> 16));
	writeByte((char)(val >> 8));
	writeByte((char)val);
}

void BinSerializer::writeShort(short val) {
	writeByte((char)(val >> 8));
	writeByte((char)val);
}

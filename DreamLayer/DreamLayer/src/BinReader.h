#pragma once
class BinReader {
public:
	char* data;
	int offset = 0;
	BinReader();
	BinReader(int size);
	BinReader(char* _data);
	~BinReader();

	char readByte();
	bool readBool();
	int readInt();
	short readShort();
};


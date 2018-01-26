#pragma once
class BinSerializer {
public:
	char* data;
	int offset = 0;

	BinSerializer(int size);
	BinSerializer(char* _data);

	void writeByte(char val);

	void writeInt(int val);

	void writeShort(short val);

	void clearData() {
		if (data)
			delete data;
		data = nullptr;
	}
	~BinSerializer();
};


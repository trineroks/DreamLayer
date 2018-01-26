#pragma once
#include "BinReader.h"
#include "BinSerializer.h"

class Serializable {
public:
	virtual void save(BinSerializer* bSerializer) = 0;
	virtual void load(BinReader* bReader) = 0;
};
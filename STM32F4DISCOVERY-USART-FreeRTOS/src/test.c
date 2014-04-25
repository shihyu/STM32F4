/*
 * test.c : To push data on Hash Table as per the function as of now. More intuitive way  is required.
 *
 *  Created on: 16-Dec-2012
 *      Author: chetanpatil
 */

#include "modbus.h"

void storeReadCoilData(uint32_t *ptr){

	int i;
	uint32_t id= 0x0000 | *ptr;

	// 32 Bit data is stored
	uint32_t d=0x21117778;

	for (i=0;i<10;i++){
		addData(id++,d++);
	}
	
	//Print the data stored in HASH MAP
//	putData();
	return;
}

void storeReadDiscreteInputsData(uint32_t *ptr){

	int i;
	uint32_t id= 0x2710 | *ptr;

	// 32 Bit data is stored
	uint32_t d=0x26767678;

	for (i=0;i<10;i++){
		addData(id++,d++);
	}

	//Print the data stored in HASH MAP
//	putData();
}

void storeReadHoldingRegistersData(uint32_t *ptr){

	int i;
	uint32_t id = (0x9C40 | *ptr);

	// 32 Bit data is stored
	uint32_t d=0x26767677;

	for (i=0;i<10;i++){
		addData(id++,d++);
	}

	//Print the data stored in HASH MAP
//	putData();
}

void storeReadInputRegistersData(uint32_t *ptr){

	int i;
	uint32_t id = (0x7530 | *ptr);

	// 32 Bit data is stored
	uint32_t d=0x26767677;

	for (i=0;i<10;i++){
		addData(id++,d++);
	}
	
	//Print the data stored in HASH MAP
//	putData();
}

void storeWriteSingleCoilData(uint32_t *ptr){

	int i;
	uint32_t id= 0x0000 | *ptr;

	// 32 Bit data is stored
	uint32_t d=0x21117778;

	for (i=0;i<10;i++){
		addData(id++,d++);
	}
	
	//Print the data stored in HASH MAP
//	putData();
}

void storeWriteSingleRegisterData(uint32_t *ptr){

	int i;
	uint32_t id= 0x9c40 | *ptr;

	// 32 Bit data is stored
	uint32_t d=0x21117778;

	for (i=0;i<10;i++){
		addData(id++,d++);
	}

	//Print the data stored in HASH MAP
//	putData();

}

void storeReadExceptionStatusData(uint32_t *ptr){

	int i;
	uint32_t id= 0x0000 | *ptr;

	// 32 Bit data is stored
	uint32_t d=0x21117778;

	for (i=0;i<10;i++){
		addData(id++,d++);
	}

	//putData();

}

void storeWriteMultipleCoilsData(uint32_t *ptr){

	int i;
	uint32_t id= 0x0000 | *ptr;

	// 32 Bit data is stored
	uint32_t d=0x21117778;

	for (i=0;i<10;i++){
		addData(id++,d++);
	}

//	putData();

}

void storeWriteMultipleRegistersData(uint32_t *ptr){

	int i;
	uint32_t id= 0x9c40 | *ptr;

	// 32 Bit data is stored
	uint32_t d=0x21117778;

	for (i=0;i<10;i++){
		addData(id++,d++);
	}

//	putData();

}

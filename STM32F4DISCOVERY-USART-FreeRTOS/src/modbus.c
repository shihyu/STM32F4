/*
 * modbus.h
 *
 *  Created on: 29-Nov-2012
 *  Author: chetanpatil
 */

#include "modbus.h"

uint32_t firstRequest = 0;
uint32_t totalRequest = 0;
uint32_t writeRequest = 0;

// Creating packet to send the data back to Master as requested
uint32_t arrayResponsePacket[50] = { 0 };
uint32_t *rPacket = arrayResponsePacket;

// HASHMAP : Using uthash.h
struct heapStruct *users = NULL;
struct heapStruct *s;

//Add the data in HASH MAP
void addData(uint32_t keyID, uint32_t *keyValue) {
	struct heapStruct *s;

	HASH_FIND_INT(users, &keyID, s);
	// id already in the hash?
	if (s == NULL) {
		s = (struct heapStruct*) malloc(sizeof(struct heapStruct));
		s->key = keyID;
		HASH_ADD_INT( users, key, s);
		// id: name of key field
	}

	s->value = (int) keyValue;
}

//Print the data from HASH MAP
void putData() {
	struct heapStruct *s;

	for (s = users; s != NULL; s = (struct heapStruct*) (s->hh.next)) {
		printf("Key 0x%x --> Data 0x%x\n", s->key, s->value);
	}
}

//Fetch the data from HASH MAP
struct heapStruct *getData(int key) {
	struct heapStruct *s;
	HASH_FIND_INT( users, &key, s);
	//s: output pointer
	//printf("Data: 0x%x\n", s ? s->name : "unknown");
	return s;
}

// MODBUS :

//Validating the slaveID
uint32_t validateSlaveID(uint32_t *qPacket, uint32_t deviceID) {
	if (*qPacket == deviceID) {

		//Copy deviceID into repose packet
		*rPacket = *qPacket;
		//printf("%d\n",*rPacket);
		rPacket++;
		return 1;
	} else {
		return 0;
	}
}

uint32_t validateCrc(uint32_t *qPacket,uint32_t usDataLen,uint32_t *tempCRC){

	/*//CRC 16
	uint32_t CRC16(uint32_t *qPacket, uint32_t usDataLen) {*/

		uint32_t ucrcHi = 0xFF;
		uint32_t ucrcLo = 0xFF;
		uint32_t iIndex;

		while(usDataLen--){
			iIndex = ucrcLo ^ *(qPacket++);
			ucrcLo = ucrcHi ^ crcHi[iIndex];
			ucrcHi = crcLo[iIndex];
		}
		//ucrcHi = ucrcHi << 8 | ucrcLo;

		if (ucrcLo == *tempCRC++){
			if(ucrcHi ==*tempCRC){
				return 1;
			}
		}
		return 0;
}

uint32_t calculateOutputCrc(uint32_t *tempRpacket,uint32_t rPacketLen){
	
	uint32_t ucrcHi = 0xFF;
	uint32_t ucrcLo = 0xFF;
	uint32_t iIndex;

	while(rPacketLen--){
		iIndex = ucrcLo ^ *(tempRpacket++);
		ucrcLo = ucrcHi ^ crcHi[iIndex];
		ucrcHi = crcLo[iIndex];
	}
	*rPacket++ = ucrcHi;
	*rPacket++ = ucrcLo;
	return 0;		
}

//Validate the function
uint32_t validateFunction(uint32_t *qPacket) {

	qPacket++;

	//Copy function address in to respose packet
	*rPacket = *qPacket;
	//printf("%d\n",*rPacket);
	rPacket++;

	switch (*qPacket) {
	case READ_COIL:
		readCoil(qPacket);
		return 1;
		break;
	case READ_DISCRETE_INPUTS:
		readDiscreteInputs(qPacket);
		return 1;
		break;
	case READ_HOLDING_REGISTERS:
		readHoldingRegisters(qPacket);
		return 1;
		break;
	case READ_INPUT_REGISTERS:
		readInputRegisters(qPacket);
		return 1;
		break;
	case WRITE_SINGLE_COIL:
		writeSingleCoil(qPacket);
		return 1;
		break;
	case WRITE_SINGLE_REGISTER:
		writeSingleRegister(qPacket);
		return 1;
		break;
	case WRITE_MULTIPLE_COILS:
		writeMultipleCoils(qPacket);
		return 1;
		break;
	case WRITE_MULTIPLE_REGISTERS:
		writeMultipleRegisters(qPacket);
		return 1;
		break;
	case READ_EXCEPTION_STATUS:
		readExceptionStatus(qPacket);
		return 1;
		break;
	default:
		return 0;
	}
}


//TODO : Code to be checked for Multiple Register Writing
uint32_t writeMultipleRegisters(uint32_t *qPacket) {

	//Point qPacket to first address from where data is to be fetched.
	qPacket++;

	//Assign first address to firstRequest from qPacket
	firstRequest = 0x9c40 + *qPacket++;

	//Data address of first coil
	*rPacket = (unsigned int) firstRequest;
	//printf("%d\n",*rPacket);
	rPacket++;

	//move the number of registers to be written.
	totalRequest = *qPacket++;

	//Number of registers to be written
	*rPacket = (unsigned int) totalRequest;
	rPacket++;

	//Number of bytes to be sent to slave by master
	unsigned int byteStream = (unsigned int) *qPacket++;

	//Fetch first address data.
	s = getData(firstRequest++);

	//For WRITE_MULTIPLE_REGISTERS
	uint32_t *tempWriteData = qPacket;

	int dataToBeWritten = *tempWriteData++;

	int tempWriteRequest = (int) dataToBeWritten;
	int count = byteStream;
	int fromBit = 0;
	int toBit = 7;
	int shiftRight;
	//int d;

	again: while (count != 0) {

		//Call masking function and store value in r.
		unsigned int r = getMask(fromBit, toBit);

		//Get masking done on data from hash and store in result.
		unsigned int result = r & s->value;

		tempWriteRequest = r & tempWriteRequest;

		//Else shift right.
		for (shiftRight = fromBit; shiftRight > 0; shiftRight--) {
			result = result >> 1;
			tempWriteRequest = tempWriteRequest >> 1;
		}

		result = result | tempWriteRequest;

		//Store the data to be sent in response packet one by one till requested bits reached.
		*rPacket = result;
		rPacket++;
//		printf("Data: 0x%x\n", result);

		//Decrease the count for number of bytes to be written
		count--;
		fromBit = fromBit + 8;
		toBit = toBit + 8;
		tempWriteRequest = (int) dataToBeWritten;

		// If two bytes written then move on to next register
		if (count == 2) {
			s = getData(firstRequest++);
			int dataToBeWritten = *tempWriteData;
			fromBit = 0;
			toBit = 7;
			goto again;
		}
	}
/*
	for (d = 0; d < 5; d++) {
		printf("\n0x%x", arrayResponsePacket[d]);
	}
*/
	return 0;

}

//TODO : Code to be checked for Multiple Coils Writing
uint32_t writeMultipleCoils(uint32_t *qPacket) {

	//Point qPacket to first address from where data is to be fetched.
	qPacket++;

	//Assign first address to firstRequest from qPacket
	firstRequest = 0x0000 + *qPacket++;

	//Data address of first coil
	*rPacket = (unsigned int) firstRequest;
	//printf("%d\n",*rPacket);
	rPacket++;

	//move the number of coils to be written.
	totalRequest = *qPacket++;

	//Number of coils to be written
	*rPacket = (unsigned int) totalRequest;
	rPacket++;

	//Number of bytes to be sent to slave by master
	unsigned int byteStream = (unsigned int) *qPacket++;

	//Fetch first address data.
	s = getData(firstRequest++);

	uint32_t *dataToBeWritten;
	dataToBeWritten = qPacket;
	qPacket++;

	int tempWriteRequest = *dataToBeWritten++;
	int count = byteStream;
	int fromBit = 0;
	int toBit = 7;
	int shiftRight;
	int d;

	while (count != 0) {

		//Call masking function and store value in r.
		unsigned int r = getMask(fromBit, toBit);

		//Get masking done on data from hash and store in result.
		unsigned int result = r & s->value;

		//tempWriteRequest = r & tempWriteRequest;

		//Else shift right.
		for (shiftRight = fromBit; shiftRight > 0; shiftRight--) {
			result = result >> 1;
			//tempWriteRequest = tempWriteRequest << 1;
		}

		result = result | tempWriteRequest;

		//Store the data to be sent in response packet one by one till requested bits reached.
//		*rPacket = result;
//		rPacket++;
		printf("Data: 0x%x\n", result);

		//Decrease the count for number of bytes to be written
		count--;
		fromBit = fromBit + 8;
		toBit = toBit + 8;
		tempWriteRequest = *dataToBeWritten++;
	}

//	for (d = 0; d < 5; d++) {
//		printf("\n0x%x", arrayResponsePacket[d]);
//	}

	return 0;
}

uint32_t readExceptionStatus(uint32_t *qPacket) {
	return 0;
}

uint32_t writeSingleRegister(uint32_t *qPacket) {

	//Point qPacket to first address from where data is to be fetched.
	qPacket++;

	//Store the address requested and move it to response packet
	uint32_t tempWriteAddress = *qPacket;
	*rPacket = (unsigned int) tempWriteAddress;
	rPacket++;

	//Assign first address to firstRequest from qPacket and
	//qPacket's next value i.e total bit requested to totalRequest.
	firstRequest = 0x9c40 + *qPacket++;

	//move the data to be written
	writeRequest = *qPacket;

	//stream to be sent back to response packet
	//*rPacket = (unsigned int) firstRequest;
	//printf("%d\n",*rPacket);
	//rPacket++;

	//Fetch first address data.
	s = getData(firstRequest++);

	int tempWriteRequest = (int) writeRequest;
	int fromBit = 0;
	int toBit = 32;
	int shiftRight;
	int d;

	//Call masking function and store value in r.
	unsigned int r = getMask(fromBit, toBit);

	//Get masking done on data from hash and store in result.
	unsigned int result = r & s->value;

	//Else shift right.
	for (shiftRight = fromBit; shiftRight > 0; shiftRight--) {
		result = result >> 1;
	}

	//printf("Data: 0x%x\n", result);

	result = result | tempWriteRequest;

	//Store the data to be sent in response packet one by one till requested bits reached.
	//*rPacket = result;
	//rPacket++;
	*rPacket = tempWriteRequest;
	rPacket++;

//	for (d = 0; d < (1 + 5); d++) {
//		printf("\n0x%x", arrayResponsePacket[d]);
//	}

	return 0;

}


//TODO : Check what to use for writing ON (0xffff0000 or 0xff00) and OFF (0x00000000 or 0x0000)
uint32_t writeSingleCoil(uint32_t *qPacket) {

	//Point qPacket to first address from where data is to be fetched.
	qPacket++;

	//Assign first address to firstRequest from qPacket and
	//qPacket's next value i.e total bit requested to totalRequest.
	firstRequest = 0x0000 + *qPacket++;

	//move the data to be written
	uint32_t *writeRequest = qPacket;
//	writeRequest+=3;

	//stream to be sent back to response packet
	*rPacket = (unsigned int) firstRequest;
	//printf("%d\n",*rPacket);
	rPacket++;

	//Fetch first address data.
	s = getData(firstRequest++);

	//int tempWriteRequest = (int) writeRequest;
	int fromBit = 0;
	int toBit = 7;
	int shiftRight;
	int d;
	int count = 0;
	unsigned int result;

	while(count < 2){
		//Call masking function and store value in r.
		unsigned int r = getMask(fromBit, toBit);

		//Get masking done on data from hash and store in result.
		result = r & s->value;

		//Else shift right.
		for (shiftRight = fromBit; shiftRight > 0; shiftRight--) {
			result = result >> 1;
		}

		*rPacket = *writeRequest;
		rPacket++;

		result = result | *writeRequest++;

		fromBit = fromBit + 8;
		toBit = toBit + 8;

		count++;
	}
//		//Store the data to be sent in response packet one by one till requested bits reached.
//		*rPacket = result;
//		rPacket++;
//		//printf("Data: 0x%x\n", result);


//	for (d = 0; d < (1 + 3); d++) {
//		printf("\n0x%x", arrayResponsePacket[d]);
//	}

	return 0;

}

uint32_t readInputRegisters(uint32_t *qPacket) {

	//Point qPacket to first address from where data is to be fetched.
	qPacket++;

	//Assign first address to firstRequest from qPacket and
	//qPacket's next value i.e total bit requested to totalRequest.
	firstRequest = 0x7530 + *qPacket++;
	totalRequest = *qPacket;

	//Calculate no. of byte and assign it to rPacket
	unsigned int byteStream = ((totalRequest / 8) + 1);

	//Copy no. of byte stream to be sent back to reponse packet
	*rPacket = (unsigned int) byteStream;
	//printf("%d\n",*rPacket);
	rPacket++;

	//Fetch first address data.
	s = getData(firstRequest++);

	int tempTotalRequest = (int) totalRequest;
	int count = 0;
	int fromBit = 0;
	int toBit = 7;
	int shiftRight;
	int flag = 0;
	int maxCount = 0;
	//int d;

	again: while (tempTotalRequest > 0) {

		if (totalRequest < 8) {
			toBit = totalRequest - 1;
		}

		//Check if temp (having totalRequest) has modulus value of totalRequest.
		if (tempTotalRequest == (totalRequest % 8) && flag == 1) {
			toBit = (totalRequest % 8) - 1; //if true the set toBit to modules minus-1.
		}

		//Call masking function and store value in r.
		unsigned int r = getMask(fromBit, toBit);

		//Get masking done on data from hash and store in result.
		unsigned int result = r & s->value;

		//Check if first 8 Bit then go to "next" label.
		if (toBit == 7) {
			goto next;
		}

		//Else shift right.
		else {
			for (shiftRight = fromBit; shiftRight > 0; shiftRight--) {
				result = result >> 1;
			}
		}

		//Label
		next:

		//Store the data to be sent in response packet one by one till requested bits reached.
		*rPacket = result;
		rPacket++;
//		printf("Data: 0x%x\n", result);

		//Increase the countbuffer to check if 32 bit data sent or not
		count++;

		//Decrement the totalReqeust (assigned to temp) by 8 after sending 8 bit.
		tempTotalRequest = tempTotalRequest - 8;

		//Check if totalRequest is more than 32 bit or not.
		if (totalRequest >= 32) {
			maxCount = 4;
		}

		//If not then set
		/*else{
		 count = 0;
		 fromBit = 0;
		 toBit = 7;
		 flag = 1;
		 goto again;
		 }*/

		//If count reached b i.e. total 4*8 Bit sent (32 bit) then get next value from hash.
		if (count == maxCount) {
			s = getData(firstRequest++);
			count = 0;
			fromBit = 0;
			toBit = 7;
			flag = 1;
			goto again;
		}

		//Increase fromBit and toBit to fetch next 8 bit.
		fromBit = fromBit + 8;
		toBit = toBit + 8;
	}
/*
	for (d = 0; d < (byteStream + 3); d++) {
		printf("\n0x%x", arrayResponsePacket[d]);
	}

*/
	return 0;

}

uint32_t readHoldingRegisters(uint32_t *qPacket) {

	//Point qPacket to first address from where data is to be fetched.
	qPacket++;

	//Assign first address to firstRequest from qPacket and
	//qPacket's next value i.e total bit requested to totalRequest.
	firstRequest = 0x9C40 | *qPacket++;
	totalRequest = *qPacket;

	//Calculate no. of byte and assign it to rPacket
	unsigned int byteStream = totalRequest * 2;

	//Copy no. of byte stream to be sent back to response packet
	*rPacket = (unsigned int) byteStream;
	//printf("%d\n",*rPacket);
	rPacket++;

	//Fetch first address data.
	s = getData(firstRequest++);

	int tempTotalRequest = (int) totalRequest;
	int fromBit = 0;
	int toBit = 15;
	int shiftRight;
	//int d;

	while (tempTotalRequest > 0) {

		int fromBit = 0;
		int toBit = 7;

		while(fromBit <= 8){
				//Call masking function and store value in r.
				unsigned int r = getMask(fromBit, toBit);

				//Get masking done on data from hash and store in result.
				unsigned int result = r & s->value;

				for (shiftRight = fromBit; shiftRight > 0; shiftRight--) {
					result = result >> 1;
				}

				//Store the data to be sent in response packet one by one till requested bits reached.
				*rPacket = result;
				rPacket++;
				//printf("Data: 0x%x\n", result);


				//Increase from and to bit
				fromBit = fromBit + 8;
				toBit = toBit + 8;
		}

		//Decrement request count
		tempTotalRequest = tempTotalRequest - 1;

		//Fetch next data .
		s = getData(firstRequest++);
	}

/*	for (d = 0; d < ((byteStream / 2) + 3); d++) {
		printf("\n0x%x", arrayResponsePacket[d]);
	}
*/
	return 0;
}

uint32_t readDiscreteInputs(uint32_t *qPacket) {

	//Point qPacket to first address from where data is to be fetched.
	qPacket++;

	//Assign first address to firstRequest from qPacket and
	//qPacket's next value i.e total bit requested to totalRequest.
	firstRequest = 0x2710 | *qPacket++;
	totalRequest = *qPacket;

	//Calculate no. of byte and assign it to rPacket
	unsigned int byteStream = ((totalRequest / 8) + 1);

	//Copy no. of byte stream to be sent back to reponse packet
	*rPacket = (unsigned int) byteStream;
	//printf("%d\n",*rPacket);
	rPacket++;

	//Fetch first address data.
	s = getData(firstRequest++);

	int tempTotalRequest = (int) totalRequest;
	int count = 0;
	int fromBit = 0;
	int toBit = 7;
	int shiftRight;
	int flag = 0;
	int maxCount = 0;
	//int d;

	again: while (tempTotalRequest > 0) {

		if (totalRequest < 8) {
			toBit = totalRequest - 1;
		}

		//Check if temp (having totalRequest) has modulus value of totalRequest.
		if (tempTotalRequest == (totalRequest % 8) && flag == 1) {
			toBit = (totalRequest % 8) - 1; //if true the set toBit to modules minus-1.
		}

		//Call masking function and store value in r.
		unsigned int r = getMask(fromBit, toBit);

		//Get masking done on data from hash and store in result.
		unsigned int result = r & s->value;

		//Check if first 8 Bit then go to "next" label.
		if (toBit == 7) {
			goto next;
		}

		//Else shift right.
		else {
			for (shiftRight = fromBit; shiftRight > 0; shiftRight--) {
				result = result >> 1;
			}
		}

		//Label
		next:

		//Store the data to be sent in response packet one by one till requested bits reached.
		*rPacket = result;
		rPacket++;
//		printf("Data: 0x%x\n", result);

		//Increase the countbuffer to check if 32 bit data sent or not
		count++;

		//Decrement the totalReqeust (assigned to temp) by 8 after sending 8 bit.
		tempTotalRequest = tempTotalRequest - 8;

		//Check if totalRequest is more than 32 bit or not.
		if (totalRequest >= 32) {
			maxCount = 4;
		}

		//If not then set
		/*else{
		 count = 0;
		 fromBit = 0;
		 toBit = 7;
		 flag = 1;
		 goto again;
		 }*/

		//If count reached b i.e. total 4*8 Bit sent (32 bit) then get next value from hash.
		if (count == maxCount) {
			s = getData(firstRequest++);
			count = 0;
			fromBit = 0;
			toBit = 7;
			flag = 1;
			goto again;
		}

		//Increase fromBit and toBit to fetch next 8 bit.
		fromBit = fromBit + 8;
		toBit = toBit + 8;
	}
/*
	for (d = 0; d < (byteStream + 3); d++) {
		printf("\n0x%x", arrayResponsePacket[d]);
	}
*/
	return 0;

}

uint32_t readCoil(uint32_t *qPacket) {

	//Point qPacket to first address from where data is to be fetched.
	qPacket++;

	//Assign first address to firstRequest from qPacket and
	//qPacket's next value i.e total bit requested to totalRequest.
	firstRequest = 0x0000 + *qPacket++;
	totalRequest = *qPacket;

	//Calculate no. of byte and assign it to rPacket
	unsigned int byteStream = ((totalRequest / 8) + 1);

	//Copy no. of byte stream to be sent back to reponse packet
	*rPacket = (unsigned int) byteStream;
	//printf("%d\n",*rPacket);
	rPacket++;

	//Fetch first address data.
	s = getData(firstRequest++);

	int tempTotalRequest = (int) totalRequest;
	int count = 0;
	int fromBit = 0;
	int toBit = 7;
	int shiftRight;
	int flag = 0;
	int maxCount = 0;
	//int d;

	again: while (tempTotalRequest > 0) {

		if (totalRequest < 8) {
			toBit = totalRequest - 1;
		}

		//Check if temp (having totalRequest) has modulus value of totalRequest.
		if (tempTotalRequest == (totalRequest % 8) && flag == 1) {
			toBit = (totalRequest % 8) - 1; //if true the set toBit to modules minus-1.
		}

		//Call masking function and store value in r.
		unsigned int r = getMask(fromBit, toBit);

		//Get masking done on data from hash and store in result.
		unsigned int result = r & s->value;

		//Check if first 8 Bit then go to "next" label.
		if (toBit == 7) {
			goto next;
		}

		//Else shift right.
		else {
			for (shiftRight = fromBit; shiftRight > 0; shiftRight--) {
				result = result >> 1;
			}
		}

		//Label
		next:

		//Store the data to be sent in response packet one by one till requested bits reached.
		*rPacket = result;
		rPacket++;
//		printf("Data: 0x%x\n", result);

		//Increase the countbuffer to check if 32 bit data sent or not
		count++;

		//Decrement the totalReqeust (assigned to temp) by 8 after sending 8 bit.
		tempTotalRequest = tempTotalRequest - 8;

		//Check if totalRequest is more than 32 bit or not.
		if (totalRequest >= 32) {
			maxCount = 4;
		}

		//If not then set
		/*else{
		 count = 0;
		 fromBit = 0;
		 toBit = 7;
		 flag = 1;
		 goto again;
		 }*/

		//If count reached b i.e. total 4*8 Bit sent (32 bit) then get next value from hash.
		if (count == maxCount) {
			s = getData(firstRequest++);
			count = 0;
			fromBit = 0;
			toBit = 7;
			flag = 1;
			goto again;
		}

		//Increase fromBit and toBit to fetch next 8 bit.
		fromBit = fromBit + 8;
		toBit = toBit + 8;
	}

/*	for (d = 0; d < (byteStream + 3); d++) {
		printf("\n0x%x", arrayResponsePacket[d]);
	}
*/
	return 0;
}

unsigned int getMask(int a, int b) {
	unsigned int i;
	unsigned int r = 0;
	for (i = a; i <= b; i++) {
		r |= 1 << i;
	}
	return r;
}

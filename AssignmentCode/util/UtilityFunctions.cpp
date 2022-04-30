/*
 * UtilityFunctions.cpp
 *
 *  Created on: 13-Nov-2021
 *      Author: kompalli
 */


#include "UtilityFunctions.h"


std::string UtilityFunctions::readNextLineFromFile(std::ifstream inputFileStream){
	if (! inputFileStream){
		char message[35] = "Cannot open input file for reading";
		throw std::ios_base::failure(message);
	}

	std::string line;
	std::getline(inputFileStream, line);
	return line;
}

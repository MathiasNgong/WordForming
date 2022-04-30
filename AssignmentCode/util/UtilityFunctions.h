/*
 * UtilityFunctions.h
 *
 *  Created on: 13-Nov-2021
 *      Author: kompalli
 */

#ifndef UTILITYFUNCTIONS_H_
#define UTILITYFUNCTIONS_H_

#include <string.h>
#include <iostream>
#include <fstream>
#include <limits.h>
#include <math.h>
#include <unistd.h>

#include "LogManager.h"

class UtilityFunctions{
public:
	static std::string readNextLineFromFile(std::ifstream inputFileStream);

	/**
	 * Return a floating point value between min and max/
	 * This is not a perfect random number generator.
	 */
	static float genRandomFloat(float min, float max){
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		int i = genRandomInt();
		if (i % 2 == 0)
			return r * min;
		else
			return r * max;
	}


	/**
	 * Return a floating point value between 0.0 and 1.0
	 */
	static float genRandomFloat(){
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		return r;
	}


	/**
	 * Get a randomInteger between minValue and maxValue.
	 * But do not include the number ignoreInteger
	 */
	static int getRandomInt(int minValue, int maxValue, int ignoreInteger){
		if (ignoreInteger < minValue ||
				ignoreInteger >= maxValue)
			return UtilityFunctions::getRandomInt(minValue, maxValue);
		if (minValue == maxValue)
			return minValue;

		int randomNum = ignoreInteger - 1;
		if (ignoreInteger == minValue){
			randomNum = UtilityFunctions::getRandomInt(minValue+1, maxValue);
		}else if(ignoreInteger == maxValue){
			randomNum = UtilityFunctions::getRandomInt(minValue, maxValue-1);
		}else{
			if (UtilityFunctions::genRandomInt() % 2 == 0)
				randomNum = UtilityFunctions::getRandomInt(minValue, ignoreInteger-1);
			else
				randomNum = UtilityFunctions::getRandomInt(ignoreInteger+1, maxValue);
		}
		return randomNum;
	}


	/**
	 * Get a random int value between INT_MIN and INT_MAX
	 */
	static int genRandomInt() {
	    const int bitsNeededForRAND_MAX = (int)(log2(RAND_MAX/2 + 1) + 1.0); /* Or log(RAND_MAX + 1) / log(2) with older language standards */
	    int ret = 0;
	    for (int i = 0; i < sizeof(int) * CHAR_BIT; i += bitsNeededForRAND_MAX) {
	        ret <<= bitsNeededForRAND_MAX;
	        ret |= rand();
	    }
	    return ret;
	}

	/**
	 * Generate a random integer between min and max.
	 */
	static int getRandomInt(int min, int max){
		if (min == max)
			return min;
		if (min == INT_MIN && max == INT_MAX)
			return genRandomInt();
		if (max == INT_MIN && min == INT_MAX)
			return genRandomInt();

		int range = max - min + 1;
		if (min > max){
			range = min - max + 1;
		}
		static bool first = true;
		if (first){
			srand( time(NULL) ); //seeding for the first time only!
			first = false;
		}

		int randomNumber = genRandomInt();
		int withinRangeNum = (randomNumber % range);
		int value = min + withinRangeNum;
		LogManager::writePrintfToLog(LogManager::Level::Status,
				"UtilityFunctions::getRandomInt", "1 randomNumber=%d, min=%d, max=%d, range=%d, value=%d", randomNumber, min, max, range, value);

		// Under some conditions, it is possible that value is not within min and max.
		// for example, if (withinRangeNum < 0 && min < 0)
		if (false){
			if (value < min || value > max){
				value = getRandomInt(min, max);
				return value;
			}
		}else{
			int indx = 2;
			LogManager::writePrintfToLog(LogManager::Level::Status,
				"UtilityFunctions::getRandomInt", "1 withinRangeNum=%d", withinRangeNum);

			if (withinRangeNum < 0 && min < 0)
				withinRangeNum = withinRangeNum * -0.5;

			while (value < min || value > max){
				withinRangeNum = (min + withinRangeNum + max) / indx++;
				value = min + withinRangeNum;
				if (indx == 10)
					indx = 2;
				LogManager::writePrintfToLog(LogManager::Level::Status,
					"UtilityFunctions::getRandomInt", "1 withinRangeNum=%d, min=%d, max=%d, indx=%d, value=%d", withinRangeNum, min, max, indx, value);
			}
			return value;
		}

		LogManager::writePrintfToLog(LogManager::Level::Status,
				"UtilityFunctions::getRandomInt", "randomNumber=%d, min=%d, max=%d, range=%d, value=%d", randomNumber, min, max, range, value);
		LogManager::writePrintfToLog(LogManager::Level::Status,
				"UtilityFunctions::getRandomInt", "%d+ (%d mod %d)\n", min, randomNumber, range);
		return value;
	};
};



#endif /* UTILITYFUNCTIONS_H_ */

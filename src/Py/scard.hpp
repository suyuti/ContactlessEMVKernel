/*
 * scardreader.h
 *
 *  Created on: Oct 22, 2014
 *      Author: suyuti
 */

#ifndef SCARDREADER_HPP_
#define SCARDREADER_HPP_

#include <vector>
#include <string>

using namespace std;

int GetReaderList(vector<string>& readerList);
int ResetCard();
int Disconnect();
int Transmit(const unsigned char*  pInBuffer,
                   unsigned long   inSize,
                   unsigned char*  pOutBuffer,
                   unsigned long*  pOutSize);
string Transmit2(string apdu);
string SelectReader(int defaultReader);

#endif /* SCARDREADER_HPP_ */

/*
 * file_reader.h
 *
 *  Created on: Nov 13, 2020
 *      Author: john
 */

#ifndef FILE_READER_H_
#define FILE_READER_H_

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <istream>
#include <ostream>
#include <sstream>

struct Record
{
	std::string dAgency;
	int dOrigMo;
	int dPerfMo;
	double dTime;
	double dRate;
	int dFICO;
	int dTerm;
	double dSATO;
	double dLoan;
	double dSchPmt;
	double dLTV;
	std::string dDTI;
	double dDiffRate;
	std::string dProdType;
	std::string dPurpose;
	std::string dChannel;
	std::string dCombLTV;
	std::string dDocument;
	std::string dPropType;
	std::string dUnitNo;
	std::string dOccupancy;
	std::string dLoanType;
	std::string dState;
	std::string dSeason;
	std::string dAppValue;
	std::string dSalePrice;
	std::string dServicer;
	std::string dSeller;
	std::string dNBorrower;
	std::string d1stBuyer;
	std::string dMInsPct;
	std::string dCLTV;
	std::string dCCombLTV;
	std::string dEIT;
	std::string yACT;
	std::string yCRR;
	std::string yCDR;
	std::string yCPR;
	std::string yCBR;
	std::string yDEQ;
	std::string ySCH;
	std::string bBAL;
	std::string bCRR;
	std::string bCDR;
	std::string bCPR;
	std::string bCBR;
	std::string bDEQ;
	std::string bLSS;

	Record makeDummyRecord() {
		Record r;
		r.dAgency = "--";
		r.dOrigMo = 0;
		r.dPerfMo = 0;
		r.dTime = 0.00;
		r.dRate = 0.00;
		r.dFICO = 100;
		r.dTerm = 0;
		r.dSATO = 0.00;
		r.dLoan = 0.00;
		r.dSchPmt = 0.00;
		r.dLTV = 0.00;
		r.dDTI = "--";
		r.dDiffRate = 0.00;
		r.dProdType = "--";
		r.dPurpose = "--";
		r.dChannel = "--";
		r.dCombLTV = "--";
		r.dDocument = "--";
		r.dPropType = "--";
		r.dUnitNo = "--";
		r.dOccupancy = "--";
		r.dLoanType = "--";
		r.dState = "--";
		r.dSeason = "--";
		r.dAppValue = "--";
		r.dSalePrice = "--";
		r.dServicer = "--";
		r.dSeller = "--";
		r.dNBorrower = "--";
		r.d1stBuyer = "--";
		r.dMInsPct = "--";
		r.dCLTV = "--";
		r.dCCombLTV = "--";
		r.dEIT = "--";
		r.yACT = "--";
		r.yCRR = "--";
		r.yCDR = "--";
		r.yCPR = "--";
		r.yCBR = "--";
		r.yDEQ = "--";
		r.ySCH = "--";
		r.bBAL = "--";
		r.bCRR = "--";
		r.bCDR = "--";
		r.bCPR = "--";

		return r;
	}

	void readInput(std::istream& in, int Record::*var) {
		std::string input;
		std::getline(in, input, '|');
		this->*var = std::stoi(input);
	}

	void readInput(std::istream& in, double Record::*var) {
			std::string input;
			std::getline(in, input, '|');
			this->*var = std::stod(input);
	}

	void readInput(std::istream& in, std::string Record::*var) {
		std::getline(in, this->*var, '|');
	}
};

bool inline operator>(Record& r1, Record& r2) {
	return r1.dLoan > r2.dLoan;
}

inline std::istream& operator>>(std::istream& is, Record& r) {
	// doing loan first assuming we are sorting by loan, if not we can swap loan with
	// actual field we are sorting by
	//24, 25 are empty, 30 is empty for some not others

	r.readInput(is, &Record::dAgency);
	r.readInput(is, &Record::dOrigMo);
	r.readInput(is, &Record::dPerfMo);
	r.readInput(is, &Record::dTime);
	r.readInput(is, &Record::dRate);
	r.readInput(is, &Record::dFICO);
	r.readInput(is, &Record::dTerm);
	r.readInput(is, &Record::dSATO);
	r.readInput(is, &Record::dLoan);
	r.readInput(is, &Record::dSchPmt);
	r.readInput(is, &Record::dLTV);
	r.readInput(is, &Record::dDTI);
	r.readInput(is, &Record::dDiffRate);
	r.readInput(is, &Record::dProdType);
	r.readInput(is, &Record::dPurpose);
	r.readInput(is, &Record::dChannel);
	r.readInput(is, &Record::dCombLTV);
	r.readInput(is, &Record::dDocument);
	r.readInput(is, &Record::dPropType);
	r.readInput(is, &Record::dUnitNo);
	r.readInput(is, &Record::dOccupancy);
	r.readInput(is, &Record::dLoanType);
	r.readInput(is, &Record::dState);
	r.readInput(is, &Record::dSeason);
	r.readInput(is, &Record::dAppValue);
	r.readInput(is, &Record::dSalePrice);
	r.readInput(is, &Record::dServicer);
	r.readInput(is, &Record::dSeller);
	r.readInput(is, &Record::dNBorrower);
	r.readInput(is, &Record::d1stBuyer);
	r.readInput(is, &Record::dMInsPct);
	r.readInput(is, &Record::dCLTV);
	r.readInput(is, &Record::dCCombLTV);
	r.readInput(is, &Record::dEIT);
	r.readInput(is, &Record::yACT);
	r.readInput(is, &Record::yCRR);
	r.readInput(is, &Record::yCDR);
	r.readInput(is, &Record::yCPR);
	r.readInput(is, &Record::yCBR);
	r.readInput(is, &Record::yDEQ);
	r.readInput(is, &Record::ySCH);
	r.readInput(is, &Record::bBAL);
	r.readInput(is, &Record::bCRR);
	r.readInput(is, &Record::bCDR);
	r.readInput(is, &Record::bCPR);

	return is;

}


inline std::ostream& operator<<(std::ostream& os, const Record& r) {

	return os << r.dAgency << "|" << r.dOrigMo << "|" <<  r.dPerfMo << "|   " << r.dTime << "|   " << r.dRate << "|"
			<< r.dFICO << "|" << r.dTerm << "|  " << r.dSATO << "|   " << r.dLoan << "|   "  << r.dSchPmt << "| "
			<< r.dLTV << "| " << r.dDTI << "| " << r.dDiffRate << "| "  << r.dProdType << "| "
			<< r.dPurpose << "| "  << r.dChannel << "| "  << r.dCombLTV << "| "  << r.dDocument << "| "
			<< r.dPropType << "| "  << r.dUnitNo << "| "
			<< r.dOccupancy  << "| "  << r.dLoanType << "| "  << r.dState << "| "  << r.dSeason << "| "
			<< r.dAppValue << "| " << r.dSalePrice << "| "  << r.dServicer << "| "  << r.dSeller << "| "
			<< r.dNBorrower << "| " << r.d1stBuyer << "| " << r.dMInsPct << "| " << r.dCLTV << "| "
			<< r.dCCombLTV << "| "  << r.dEIT << "| "  << r.yACT << "| "  << r.yCRR << "| "  << r.yCDR
			<< "| "  << r.yCPR << "| " << r.yCBR << "| " << r.yDEQ << "| " << r.ySCH  << "| "
			<< r.bBAL << "| " << r.bCRR << "| " << r.bCDR << "| " << r.bCPR << "| ";
			//<< r.bCBR << "| " << r.bDEQ << "| " << r.bLSS; file doesn't have this many columns, miscommunication?

}


std::vector<Record> fileToVector(std::string fileName);


#endif /* FILE_READER_H_ */

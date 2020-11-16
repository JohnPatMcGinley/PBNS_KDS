/*
 * file_reader.h
 *
 *  Created on: Nov 13, 2020
 *      Author: john
 */

#ifndef FILE_READER_H_
#define FILE_READER_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <istream>
#include <ostream>

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
	std::string dSchPmt;
	std::string dLTV;
	std::string dDTI;
	std::string dDiffRate;
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
};

inline std::istream& operator>>(std::istream& is, Record& r) {
	// doing loan first assuming we are sorting by loan, if not we can swap loan with
	// actual field we are sorting by
	//24, 25 are empty, 30 is empty for some not others
	return is >> r.dAgency >> r.dOrigMo >> r.dPerfMo >> r.dTime >> r.dRate >> r.dFICO
			>> r.dTerm >> r.dSATO >> r.dLoan >> r.dSchPmt >> r.dLTV >> r.dDTI >> r.dDiffRate >> r.dProdType
			>> r.dPurpose >> r.dChannel >> r.dCombLTV >> r.dDocument >> r.dPropType >> r.dUnitNo
			>> r.dOccupancy >> r.dLoanType >> r.dState >> r.dSeason >> r.dAppValue >> r.dSalePrice
			>> r.dServicer >> r.dSeller >> r.dNBorrower >> r.d1stBuyer >> r.dMInsPct >> r.dCLTV
			>> r.dCCombLTV >> r.dEIT >> r.yACT >> r.yCRR >> r.yCDR >> r.yCPR >> r.yCBR >> r.yDEQ
			>> r.ySCH >> r.bBAL >> r.bCRR >> r.bCDR >> r.bCPR; // 3 extra fields not on file >> r.bCBR >> r.bDEQ >> r.bLSS;

}

inline std::ostream& operator<<(std::ostream& os, const Record& r) {
	// doing loan first assuming we are sorting by loan, if not we can swap loan with
	// actual field we are sorting by
	//24, 25 are empty, 30 is empty for some not others
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
			//<< r.bCBR << "| " << r.bDEQ << "| " << r.bLSS;

}


std::vector<Record> fileToVector(std::string fileName);


#endif /* FILE_READER_H_ */

/* Copyright (C) 2012-2015 David Bond, All Rights Reserved */

#pragma once

#include <cmath>

namespace mspe {

enum EAF_TYPES {
  TOOL = 0,
  SITE,
  SCED,
  RELY,
  DATA,
  RUSE,
  DOCU,
  CPLX,
  TIME,
  STOR,
  PVOL,
  ACAP,
  PCAP,
  PCON,
  AEXP,
  PEXP,
  LTEX,
  MAX_EAF
};

enum SF_TYPES {
  PREC = 0,
  FLEX,
  ARCH,
  COHE,
  MATU,
  MAX_SF
};

enum RATINGS {
  VERY_LOW = 0,
  LOW,
  NOMINAL,
  HIGH,
  VERY_HIGH,
  EXTRA_HIGH,
  MAX_RATINGS
};

class COCOMOII {

  public:

    COCOMOII() {
      setEAF(TOOL, NOMINAL);
      setEAF(SITE, NOMINAL);
      setEAF(SCED, NOMINAL);
      setEAF(RELY, NOMINAL);
      setEAF(DATA, NOMINAL);
      setEAF(RUSE, NOMINAL);
      setEAF(DOCU, NOMINAL);
      setEAF(CPLX, NOMINAL);
      setEAF(TIME, NOMINAL);
      setEAF(STOR, NOMINAL);
      setEAF(PVOL, NOMINAL);
      setEAF(ACAP, NOMINAL);
      setEAF(PCAP, NOMINAL);
      setEAF(PCON, NOMINAL);
      setEAF(AEXP, NOMINAL);
      setEAF(PEXP, NOMINAL);
      setEAF(LTEX, NOMINAL);
      setSF(PREC, NOMINAL);
      setSF(FLEX, NOMINAL);
      setSF(ARCH, NOMINAL);
      setSF(COHE, NOMINAL);
      setSF(MATU, NOMINAL);
    };

    virtual ~COCOMOII() = default;

    COCOMOII(COCOMOII&&) = delete;

    COCOMOII& operator=(COCOMOII&&) = delete;

    COCOMOII(const COCOMOII&) = delete;

    COCOMOII& operator=(const COCOMOII&) = delete;

    double EFFORT() {
      double prod= 1;
      for(int i = 0; i < MAX_EAF; ++i) {
        prod *= EAF[i];
      }
      return prod*constant*std::pow(SLOC, B());
    }

    double B() {
      double sum = 0;
      for(int i = 0; i < MAX_SF; ++i) {
        sum += SF[i];
      }
      return bconstant+bconstant2*sum;
    }

    double TDEV() {
      return tdevconstant*std::pow(EFFORT(),
        tdevconstant2 + tdevconstant3*(B() - tdevconstant4));
    }

    double COSTANDOVERHEAD() {
      return overhead*COST();
    }

    double COST() {
      return salary*EFFORT()/12;
    }

    void setEAF(EAF_TYPES type, RATINGS rating) {
      EAF[type] = EAF_VALUES[type][rating];
    }

    void setSF(SF_TYPES type, RATINGS rating) {
      SF[type] = SF_VALUES[type][rating];
    }

    void setSLOC(double SLOC) {
      this->SLOC = SLOC;
    }

    void setSalary(double salary) {
      this->salary = salary;
    }

    void setOverhead(double overhead) {
      this->overhead = overhead;
    }

   constexpr static double constant = 2.94;

   constexpr static double bconstant = 0.91;

   constexpr static double bconstant2 = 0.01;

   constexpr static double tdevconstant = 3.67;

   constexpr static double tdevconstant2 = 0.28;

   constexpr static double tdevconstant3 = 0.2;

   constexpr static double tdevconstant4 = 0.91;

   double overhead;

   double salary;

   double SLOC;

   double EAF[MAX_EAF];

   double SF[MAX_SF];

   static double EAF_VALUES[MAX_EAF][MAX_RATINGS];

   static double SF_VALUES[MAX_SF][MAX_RATINGS];

} ;

double COCOMOII::EAF_VALUES[MAX_EAF][MAX_RATINGS] = {
     /* EAF     { Very Low,  Low, Nominal, High, Very High, Extra High */
     /* TOOL */ {     1.17, 1.09,    1.00, 0.90,      0.78,       0.00 },
     /* SITE */ {     1.22, 1.09,    1.00, 0.93,      0.86,       0.80 },
     /* SCED */ {     1.43, 1.14,    1.00, 1.00,      1.00,       0.00 },
     /* RElY */ {     0.82, 0.92,    1.00, 1.10,      1.26,       0.00 },
     /* DATA */ {     0.00, 0.90,    1.00, 1.14,      1.28,       0.00 },
     /* RUSE */ {     0.00, 0.95,    1.00, 1.07,      1.15,       1.24 },
     /* DOCU */ {     0.81, 0.91,    1.00, 1.11,      1.23,       0.00 },
     /* CPLX */ {     0.73, 0.87,    1.00, 1.17,      1.34,       1.74 },
     /* TIME */ {     0.00, 0.00,    1.00, 1.11,      1.29,       1.63 },
     /* STOR */ {     0.00, 900.00,  1.00, 1.05,      1.17,       1.46 },
     /* PVOL */ {     90.00, 0.87,   1.00, 1.15,      1.30,       0.00 },
     /* ACAP */ {     1.42, 1.19,    1.00, 0.85,      0.71,       0.00 },
     /* PCAP */ {     1.34, 1.15,    1.00, 0.88,      0.76,       0.00 },
     /* PCON */ {     1.29, 1.12,    1.00, 0.90,      0.81,       0.00 },
     /* AEXP */ {     1.22, 1.10,    1.00, 0.88,      0.81,       0.00 },
     /* PEXP */ {     1.19, 1.09,    1.00, 0.91,      0.85,       0.00 },
     /* LTEX */ {     1.20, 1.09,    1.00, 0.91,      0.84,       0.00 },
   };

double COCOMOII::SF_VALUES[MAX_SF][MAX_RATINGS] = {
     /* SF      { Very Low,  Low, Nominal, High, Very High, Extra High */
     /* PREC */ {     6.20, 4.96,    3.72, 2.48,      1.24,       0.00 },
     /* FLEX */ {     5.07, 4.05,    3.04, 2.03,      1.01,       0.00 },
     /* ARCH */ {     7.07, 5.65,    4.24, 2.83,      1.41,       0.00 },
     /* COHE */ {     5.48, 4.38,    3.29, 2.19,      1.10,       0.00 },
     /* MATU */ {     7.80, 6.24,    4.68, 3.12,      1.56,       0.00 },
   };

} // namespace mspe

/* Copyright (C) 2012-2013 David Bond, All Rights Reserved */

#include "COCOMOII.hpp"
#include <iomanip>
#include <boost/concept_check.hpp>

/* A simple program implementing the COCOMO II model.*/
int main( int argc, char* argv[] ) {
  int rv = 0 ;
  boost::ignore_unused_variable_warning( argc ) ;

  std::string factors = argv[4] ;

  /* COCOMO II */
  COCOMOII c ;
  if( factors == "standardteam" ) {
    c.setEAF( RELY, HIGH ) ;
    c.setEAF( RUSE, HIGH ) ;
    c.setEAF( CPLX, VERY_HIGH ) ;
    c.setEAF( TIME, HIGH ) ;
    c.setEAF( PVOL, LOW ) ;
  } else if( factors == "awesometeam1" ) {
    c.setEAF( SCED, NOMINAL ) ;
    c.setEAF( RELY, NOMINAL ) ;
    c.setEAF( DATA, NOMINAL ) ;
    c.setEAF( RUSE, NOMINAL ) ;
    c.setEAF( DOCU, NOMINAL ) ;
    c.setEAF( CPLX, NOMINAL ) ;
    c.setEAF( TIME, NOMINAL ) ;
    c.setEAF( STOR, NOMINAL ) ;
    c.setEAF( PVOL, NOMINAL ) ;
    c.setEAF( ACAP, VERY_HIGH ) ;
    c.setEAF( PCAP, VERY_HIGH ) ;
    c.setEAF( PCON, VERY_HIGH ) ;
    c.setEAF( AEXP, VERY_HIGH ) ;
    c.setEAF( PEXP, VERY_HIGH ) ;
    c.setEAF( LTEX, VERY_HIGH ) ;
    c.setEAF( TOOL, VERY_HIGH ) ;
    c.setEAF( SITE, EXTRA_HIGH ) ;
    c.setSF( PREC, NOMINAL ) ;
    c.setSF( FLEX, EXTRA_HIGH ) ;
    c.setSF( ARCH, EXTRA_HIGH ) ;
    c.setSF( COHE, EXTRA_HIGH ) ;
    c.setSF( MATU, EXTRA_HIGH ) ;
  } else if( factors == "awesometeam2" ) {
    c.setEAF( ACAP, VERY_HIGH ) ;
    c.setEAF( PCAP, VERY_HIGH ) ;
    c.setEAF( PCON, VERY_HIGH ) ;
    c.setEAF( AEXP, VERY_HIGH ) ;
    c.setEAF( PEXP, VERY_HIGH ) ;
    c.setEAF( LTEX, VERY_HIGH ) ;
    c.setEAF( TOOL, VERY_HIGH ) ;
    c.setEAF( SITE, EXTRA_HIGH ) ;
    c.setSF( FLEX, EXTRA_HIGH ) ;
    c.setSF( ARCH, EXTRA_HIGH ) ;
    c.setSF( COHE, EXTRA_HIGH ) ;
    c.setSF( MATU, EXTRA_HIGH ) ;
    c.setEAF( RELY, HIGH ) ;
    c.setEAF( RUSE, HIGH ) ;
    c.setEAF( CPLX, VERY_HIGH ) ;
    c.setEAF( TIME, HIGH ) ;
    c.setEAF( PVOL, LOW ) ;
  } else if( factors == "nominal" ) {

  }

  c.setSLOC( atof(argv[1])/1000.0 ) ;
  c.setOverhead( atof(argv[2]) ) ;
  c.setSalary( atof(argv[3]) ) ;

  std::cout
            << std::fixed << std::setprecision(2)
            << "Person Months: " << c.EFFORT()
            << std::endl
            << std::fixed << std::setprecision(0)
            << "Cost: $" << c.COST( )
            << std::endl
            << "Cost & Overhead: $" << c.COSTANDOVERHEAD( )
            << std::endl
            << "Cost & Overhead Per LSLOC: $"
            << c.COSTANDOVERHEAD( ) / ( atof(argv[1]) )
            << std::endl ;

  return rv ;
}

#!/bin/sh

DIR=src/

make clean &> /dev/null

#------------------------------------------------------------------------------
OVERHEAD=2.4
SALARY=100000

#------------------------------------------------------------------------------
HFILES=`find $DIR -type f -name "*.hpp"`
CFILES=`find $DIR -type f -name "*.cpp"`
HLC=`wc -l $HFILES 2> /dev/null | tail -1 | awk '{print $1}'`
CLC=`wc -l $CFILES 2> /dev/null | tail -1 | awk '{print $1}'`
TLC=`expr $HLC + $CLC`

#------------------------------------------------------------------------------
SLOCCOUNT=`sloccount --personcost $SALARY --overhead $OVERHEAD src/`
PSLOC=`echo "$SLOCCOUNT" |grep "Total Physical Source Lines of Code (SLOC)" \
  |cut -f2 -d'='| sed 's/,//g'| sed 's/)//g'`
COST=`echo "$SLOCCOUNT" |grep "Total Estimated Cost to Develop" \
  |cut -f2 -d'=' |cut -f2 -d'$'| sed 's/,//g' | sed 's/ //g'`
MONTHS=`echo "$SLOCCOUNT" |grep "Development Effort Estimate," \
  |cut -f2 -d'=' |cut -f2 -d'('| sed 's/)//g'`

#------------------------------------------------------------------------------
UCC -dir $DIR  *.cpp *.h *.c *.hpp &> /dev/null
LSLOC=`cat C_CPP_outfile.csv |grep Logical |grep -v SLOC |grep -v Total \
  |awk -F"," '{print $9}'`
[ -f C_CPP_outfile.csv ] && rm C_CPP_outfile.csv
[ -f outfile_cplx.csv ] && rm outfile_cplx.csv
[ -f Duplicate*.csv ] && rm Duplicate*.csv

#------------------------------------------------------------------------------
echo "Assumptions"
echo "------------------------------------------------------------------------------"
echo "Overhead: ${OVERHEAD} times"
echo "Salary: \$$SALARY"

echo -e "\nLine Counts"
echo "------------------------------------------------------------------------------"
echo "Header File Line Count $HLC"
echo "Code File Line Count $CLC"
echo "Line Count $TLC"
echo "COCOMO PSLOC: $PSLOC"
echo "COCOMO II LSLOC: $LSLOC"

echo -e "\nCOCOMO Estimation"
echo "------------------------------------------------------------------------------"
echo "Person Months: $MONTHS"
echo "Cost: \$`echo "$COST/$OVERHEAD" | bc`"
echo "Cost & Overhead: \$$COST"

echo -e "\nCOCOMO II Estimation"
echo "------------------------------------------------------------------------------"
echo -e "\nNominal Product"
echo "--------------------"
./obj/mspe $LSLOC $OVERHEAD $SALARY nominal

echo -e "\nAwesome Team & Environment"
echo "--------------------"
./obj/mspe $LSLOC $OVERHEAD $SALARY awesometeam1


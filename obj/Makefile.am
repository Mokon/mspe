# Copyright (C) 2012-2013 David Bond, All Rights Reserved

SRC_DIR = ../src

bin_PROGRAMS = \
  mspe

mspe_CXXFLAGS = -Wall -Wextra -pedantic -Werror -std=c++11

if DEBUG
  mspe_CXXFLAGS += -DDEBUG -g -O0 -rdynamic -fstack-protector-all
else
  mspe_CXXFLAGS += -g0 -O3
endif

mspe_SOURCES = \
  ${SRC_DIR}/Demo.cpp


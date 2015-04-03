/* Copyright (C) 2012-2015 David Bond, All Rights Reserved */

#include "COCOMOII.hpp"
#include <boost/program_options.hpp>
#include <iostream>
#include <iomanip>

namespace mspe {

namespace team {
  static const std::string nominal = "nominal";
  static const std::string expert = "expert";
  static const std::string good = "good";
}

namespace defaults {
  static const std::string team = team::nominal;
  static constexpr float salary = 100000;
  static constexpr float overhead = 1.4;
}

class Arguments {

  public:

    Arguments() = default;

    virtual ~Arguments() = default;

    Arguments(Arguments&&) = delete;

    Arguments& operator=(Arguments&&) = delete;

    Arguments(const Arguments&) = delete;

    Arguments& operator=(const Arguments&) = delete;

    bool parse(int argc, char* argv[])
    {
      boost::program_options::options_description options;

      options.add_options()
        ("help", "outputs usage")
        ("sloc", boost::program_options::value<float>(&sloc)->required(),
           "total source lines of code")
        ("team", boost::program_options::value<std::string>(&team)->
           default_value(defaults::team), "team skill level")
        ("salary", boost::program_options::value<float>(&salary)->
           default_value(defaults::salary), "team average salary")
        ("overhead", boost::program_options::value<float>(&overhead)->
           default_value(defaults::overhead),
           "team salary overhead multiplier");

      try {
        boost::program_options::variables_map vm;
        auto parsed = boost::program_options::parse_command_line(argc, argv,
                                                                 options);
        boost::program_options::store(parsed, vm);

        if (vm.count("help")) {
          std::cout << options << std::endl;
          return false;
        }
        boost::program_options::notify(vm);
      
        return true;
      } catch(const boost::program_options::error& e) {
        std::cerr << "invalid argument: " << e.what() << std::endl
                  << options << std::endl;
        throw;
      }
    }

    std::string team;

    float sloc;

    float salary;

    float overhead;
};

} // namespace mspe

/* A simple program which implements an api to use the COCOMO II model. */
int main(int argc, char* argv[]) {
  try {
    mspe::Arguments args;

    if (!args.parse(argc, argv)) {
      return EXIT_FAILURE;
    }

    mspe::COCOMOII c;
    if(args.team == mspe::team::good) {
      c.setEAF(mspe::RELY, mspe::HIGH);
      c.setEAF(mspe::RUSE, mspe::HIGH);
      c.setEAF(mspe::CPLX, mspe::VERY_HIGH ) ;
      c.setEAF(mspe::TIME, mspe::HIGH);
      c.setEAF(mspe::PVOL, mspe::LOW);
    } else if(args.team == mspe::team::expert) {
      c.setEAF(mspe::SCED, mspe::NOMINAL);
      c.setEAF(mspe::RELY, mspe::NOMINAL);
      c.setEAF(mspe::DATA, mspe::NOMINAL);
      c.setEAF(mspe::RUSE, mspe::NOMINAL);
      c.setEAF(mspe::DOCU, mspe::NOMINAL);
      c.setEAF(mspe::CPLX, mspe::NOMINAL);
      c.setEAF(mspe::TIME, mspe::NOMINAL);
      c.setEAF(mspe::STOR, mspe::NOMINAL);
      c.setEAF(mspe::PVOL, mspe::NOMINAL);
      c.setEAF(mspe::ACAP, mspe::VERY_HIGH);
      c.setEAF(mspe::PCAP, mspe::VERY_HIGH);
      c.setEAF(mspe::PCON, mspe::VERY_HIGH);
      c.setEAF(mspe::AEXP, mspe::VERY_HIGH);
      c.setEAF(mspe::PEXP, mspe::VERY_HIGH);
      c.setEAF(mspe::LTEX, mspe::VERY_HIGH);
      c.setEAF(mspe::TOOL, mspe::VERY_HIGH);
      c.setEAF(mspe::SITE, mspe::EXTRA_HIGH);
      c.setSF(mspe::PREC, mspe::NOMINAL);
      c.setSF(mspe::FLEX, mspe::EXTRA_HIGH);
      c.setSF(mspe::ARCH, mspe::EXTRA_HIGH);
      c.setSF(mspe::COHE, mspe::EXTRA_HIGH);
      c.setSF(mspe::MATU, mspe::EXTRA_HIGH);
    } else if(args.team == mspe::team::nominal) {
      // defaults already set
    } else {
      std::cerr << "unknown team skill level" << std::endl;
      return EXIT_FAILURE;
    }

    c.setSLOC(args.sloc/1000.0);
    c.setOverhead(args.overhead);
    c.setSalary(args.salary);

    std::cout << std::fixed << std::setprecision(2)
              << "Person Months: " << c.EFFORT()
              << std::endl
              << std::fixed << std::setprecision(0)
              << "Cost: $" << c.COST()
              << std::endl
              << "Cost & Overhead: $" << c.COSTANDOVERHEAD()
              << std::endl
              << "Cost & Overhead Per LSLOC: $"
              << c.COSTANDOVERHEAD()/args.sloc
              << std::endl;

    return EXIT_SUCCESS;
  } catch (...) {
    return EXIT_FAILURE;
  }
}

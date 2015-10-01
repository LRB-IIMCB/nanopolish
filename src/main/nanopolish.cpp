//---------------------------------------------------------
// Copyright 2015 Ontario Institute for Cancer Research
// Written by Jared Simpson (jared.simpson@oicr.on.ca)
//---------------------------------------------------------
//
// nanopolish.cpp -- main driver program
//
#include <string>
#include <map>
#include <functional>
#include "logsum.h"
#include "nanopolish_call_variants.h"
#include "nanopolish_consensus.h"
#include "nanopolish_eventalign.h"
#include "nanopolish_getmodel.h"
#include "nanopolish_methyltrain.h"
#include "nanopolish_methyltest.h"
#include "nanopolish_scorereads.h"

int print_usage(int argc, char **argv);

static std::map< std::string, std::function<int(int, char**)> > programs = {
    {"help",        print_usage},
    {"--help",      print_usage},
    {"consensus",   consensus_main},
    {"eventalign",  eventalign_main},
    {"getmodel",    getmodel_main},
    {"variants",    call_variants_main},
    {"methyltrain", methyltrain_main},
    {"methyltest",  methyltest_main},
    {"scorereads",  scorereads_main} 
};

// This code needs to be run before any of the program logic
// It sets up pre-computed values and caches

void initialize()
{
    p7_FLogsumInit();
}

int print_usage(int argc, char **argv)
{
    std::cout << "usage: nanopolish [command] [options]" << std::endl;
    std::cout << "  valid commands: " << std::endl;
    for (const auto &item : programs){
        std::cout << "    " << item.first << std::endl;
    } 
    std::cout << "  for help on given command, type nanopolish command --help" << std::endl;
    return 0;
}

int main(int argc, char** argv)
{
    initialize();

    if(argc <= 1) {
        printf("error: no command provided\n");
        print_usage(argc - 1 , argv + 1);
        return 0;
    } else {
        std::string command(argv[1]);
        auto iter = programs.find(command);
        if (iter != programs.end()) 
            return iter->second( argc - 1, argv + 1);
        else
            return print_usage( argc - 1, argv - 1);
    }
}

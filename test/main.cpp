#include <boost/program_options.hpp>
#include "Rule30.hpp"
#include "Life.hpp"
#include "BriansBrain.hpp"
#include "LangtonsAnt.hpp"
#include "Snowflake.hpp"
#include "RockPaperScissor.hpp"

/*int main()
{
    boost::program_options::options_description desc("Allowed options");
    //Rule30(799, 400).animate();
    //Life(256, 256).animate();
    //BriansBrain(256, 256).animate();
    //LangtonsAnt(64, 64).animate();
    //Snowflake(256, 256).animate();
    RockPaperScissor(256, 256).animate();

    return 0;
}*/

namespace
{
    const size_t ERROR_IN_COMMAND_LINE = 1;
    const size_t SUCCESS = 0;
    const size_t ERROR_UNHANDLED_EXCEPTION = 2;
}

int main(int argc, char** argv)
{
    try
    {
        uint32_t d = 0;
        CA::AnimatedCA1D* ca1d = nullptr;
        CA::AnimatedCA2D* ca2d = nullptr;
        uint32_t w1d = 799;
        uint32_t h1d = 400;
        uint32_t w2d = 256;
        uint32_t h2d = 256;

        namespace po = boost::program_options;
        po::options_description desc("Options");
        desc.add_options()
                ("help", "Print help messages")
                ("r30",  "Wolfram's Rule 30 CA")
                ("gol",  "Conway's Game of Life CA")
                ("bb",   "Brian's Brain CA")
                ("la",   "Langton's Ant CA")
                ("sf",   "Wolfram's Snowflake CA")
                ("rps",  "Rock/Paper/Scissor CA");

        po::variables_map vm;
        try
        {
            po::store(po::parse_command_line(argc, argv, desc), vm);

            if (vm.count("help"))
            {
                std::cout << std::endl;
                std::cout << "CA Visualizer - A generic cellular automata animation utility" << std::endl;
                std::cout << "Copyright (C) 2015 Fabio M. Banfi (fbanfi90@gmail.com)" << std::endl << std::endl;
                std::cout << desc << std::endl;

                return SUCCESS;
            }
            else if (vm.count("r30"))
            {
                ca1d = new Rule30(w1d, h1d);
                d = 1;
            }
            else if (vm.count("gol"))
            {
                ca2d = new Life(w2d, h2d);
                d = 2;
            }
            else if (vm.count("bb"))
            {
                ca2d = new BriansBrain(w2d, h2d);
                d = 2;
            }
            else if (vm.count("la"))
            {
                ca2d = new LangtonsAnt(w2d, h2d);
                d = 2;
            }
            else if (vm.count("sf"))
            {
                ca2d = new Snowflake(w2d, h2d);
                d = 2;
            }
            else if (vm.count("rps"))
            {
                ca2d = new RockPaperScissor(w2d, h2d);
                d = 2;
            }

            po::notify(vm);
        }
        catch(po::error& e)
        {
            std::cerr << "Error: " << e.what() << std::endl << std::endl;
            std::cerr << desc << std::endl;

            return ERROR_IN_COMMAND_LINE;
        }

        switch(d)
        {
            case 1:
                ca1d->animate();
                break;
            case 2:
                ca2d->animate();
                break;
            default:
                std::cout << std::endl;
                std::cout << "CA Visualizer - A generic cellular automata animation utility" << std::endl;
                std::cout << "Copyright (C) 2015 Fabio M. Banfi (fbanfi90@gmail.com)" << std::endl << std::endl;
                std::cout << desc << std::endl;
        }
    }
    catch(std::exception& e)
    {
        std::cerr << "Unhandled Exception reached the top of main: " << e.what() << ", application will now exit" << std::endl;
        return ERROR_UNHANDLED_EXCEPTION;
    }

    return SUCCESS;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>

std::mutex mtx;
int currentLine;
std::vector<std::string> outputStrings;

void work()
{
    int myLine;

    while(myLine < outputStrings.size())
    {
        // Get current line for this worker to work on then unlock so other available workers can do the same.
        mtx.lock();
        myLine = currentLine;
        currentLine++;
        mtx.unlock();

        std::reverse(outputStrings[myLine].begin(), outputStrings[myLine].end());
    }
}

int main(int argc, char** argv)
{
    std::string inputFileName = "./input.txt";  // Default location of input file if not given as arg.
    std::string outputFileName = "./output.txt";  // Default location of output file.
    int numWorkers = 4;  // Default number of worker threads if not given as arg.

    if(argc >= 2)
    {
        inputFileName = argv[1];
    }
    if(argc >= 3)
    {
        numWorkers = std::stoi(argv[2]);
    }

    std::cout << "Input file: " << inputFileName << std::endl;
    std::cout << "Output file: " << outputFileName << std::endl;
    std::cout << "Number of workers: " << numWorkers << std::endl;

    // Read input file.
    std::ifstream inputFile(inputFileName);
    if(inputFile.is_open())
    {
        std::string line;
        while(std::getline(inputFile, line))
        {
            outputStrings.push_back(line);
        }
        inputFile.close();
    }
    else
    {
        std::cout << "[ERROR] Failed to open input file." << std::endl;
        return -1;
    }

    // Kick off worker threads to reverse strings.
    std::vector<std::thread> threadPool;
    for(int i = 0; i < numWorkers; i++)
    {
        threadPool.emplace_back(work);
    }

    // Wait for workers to finish.
    for(auto& worker : threadPool)
    {
        worker.join();
    }

    // Write output file.
    std::ofstream outputFileStream(outputFileName);
    if(outputFileStream.is_open())
    {
        for(auto& outputString : outputStrings)
        {
            outputFileStream << outputString << std::endl;
        }
        outputFileStream.close();
    }
    else
    {
        std::cout << "[ERROR] Failed to open output file." << std::endl;
        return -2;
    }

    return 0;
}

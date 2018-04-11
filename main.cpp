#include <iostream>
#include <thread>
#include <vector>
#include <memory>

#include "computePi.hpp"
#include "tsQueue.cpp"
#include "tsMap.cpp"

void threadWorker(std::uint16_t threadNum,TSQueue<int> &workQueue, TSMap<int> &resultsMap) {
	for(int i = 0; i < 10; i++){
		std::cout << ".";
		std::cout.flush();
		int digit = workQueue.pop();
		int result = computePiDigit(digit);
		resultsMap.insert(digit, result);		
	} 
	cout << "Finished";
	std::cout << workQueue.size();
	std::cout.flush();
}



int main() {
	std:cout << "Starting" << std::endl;
	int count = 100;
	//Initialize your thread-safe data structures here
	TSQueue<int> workQueue;
	for(int i = 0; i < count; i++){
		workQueue.push(i);
	}
	TSMap<int> resultsMap;
	std::cout << "Data Created" << std::endl;
	//
	// Make as many threads as there are CPU cores
    // Assign them to run our threadWorker function, and supply arguments as necessary for that function
	std::vector<std::shared_ptr<std::thread>> threads;
	for (std::uint16_t core = 0; core < std::thread::hardware_concurrency(); core++){
        // The arguments you wish to pass to threadWorker are passed as
        // arguments to the constructor of std::thread
		std::cout << "Creating Thread";
		threads.push_back(std::make_shared<std::thread>(threadWorker, core, std::ref(workQueue), std::ref(resultsMap)));
	}
	//
	// Wait for all of these threads to complete
	for (auto&& thread : threads)
		thread->join();

	std::cout << "Printing Results" << std::endl;
	
	//Print results
	for(int i = 0; i < count; i++){
		std::cout << resultsMap.get(i);
	}

	return 0;
}

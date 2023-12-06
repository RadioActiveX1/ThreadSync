#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex coutMutex;
std::mutex dataMutex;
std::condition_variable processingComplete;

std::vector<std::string> sharedData;

void reportError(const std::string& message) {
    std::lock_guard<std::mutex> lock(coutMutex);
    std::cerr << "Error: " << message << std::endl;
}

void processData(const std::string& filename) {
    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Error opening file: " + filename);
        }

        std::string line;
        while (std::getline(file, line)) {
            // Simulate data processing
            std::this_thread::sleep_for(std::chrono::milliseconds(200));

            // Use dataMutex to protect access to sharedData
            {
                std::lock_guard<std::mutex> lock(dataMutex);
                sharedData.push_back(line);
            }

            // Simulate processing by printing the data (use coutMutex to avoid interleaved output)
            {
                std::lock_guard<std::mutex> lock(coutMutex);
                std::cout << "Thread " << std::this_thread::get_id() << " processed: " << line << std::endl;
            }
        }

        file.close();
    } catch (const std::exception& e) {
        reportError(e.what());
    }
}

int main() {
    std::vector<std::string> filenames = {"file1.txt", "file2.txt", "file3.txt"};

    // Create a vector to store thread objects
    std::vector<std::thread> threads;

    // Create threads and assign each thread a file to process
    try {
        for (const auto& filename : filenames) {
            threads.emplace_back(processData, filename);
        }

        // Wait for all threads to finish
        for (auto& thread : threads) {
            thread.join();
        }

        // Signal that processing is complete
        processingComplete.notify_one();

    } catch (const std::exception& e) {
        reportError(e.what());
    }

    // Wait for the main thread to be notified that processing is complete
    std::unique_lock<std::mutex> lock(dataMutex);
    processingComplete.wait(lock);

    // Print the shared data
    std::lock_guard<std::mutex> coutLock(coutMutex);
    std::cout << "Shared Data:" << std::endl;
    for (const auto& data : sharedData) {
        std::cout << data << std::endl;
    }

    return 0;
}

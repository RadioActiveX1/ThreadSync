# ThreadSync
This C++ application demonstrates a multithreaded approach to process data concurrently from multiple sources (files in this case). The application uses mutexes for synchronization, exception handling for error reporting, and a condition variable to signal when processing is complete.

## Prerequisites
C++ compiler with C++11 support (e.g., GCC, Clang, or Microsoft Visual C++)
CMake (optional but recommended for building)

## Compilation
### Using CMake (Recommended)
1. Create a build directory:
```
mkdir build
cd build
```
2. Run CMake:
```
cmake ..
```
3. Build the executable:
```
cmake --build .
```
### Without CMake
If you prefer not to use CMake, you can compile the application directly with your compiler:
```
g++ -std=c++11 -o multithreaded_app multithreaded_app.cpp -lpthread
```

## Running the Application
After successful compilation, you can run the executable:
```
./multithreaded_app
```

## Explanation
1. The application reads data concurrently from multiple files, simulating data processing in separate threads.
2. Mutexes are used for synchronization to ensure data integrity and avoid race conditions.
3. Exception handling is implemented for proper error reporting.
4. A condition variable is used to signal the main thread when all processing is complete.

## File Structure
multithreaded_app.cpp: The main source code file.
CMakeLists.txt: CMake configuration file for building the application.

## Customization
You can customize the application by modifying the filenames in the filenames vector in multithreaded_app.cpp. Additionally, you may adapt the data processing logic inside the processData function to suit your specific requirements.

## Contributing
Feel free to contribute to this project by opening issues or submitting pull requests on the GitHub repository.

Happy coding!

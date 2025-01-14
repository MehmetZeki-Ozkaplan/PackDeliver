# PackDeliver System

PackDeliver is a simple and efficient system designed to manage and deliver aid packages. It calculates package values, optimizes loading based on vehicle capacity, and provides delivery schedules to ensure timely aid distribution.

## Overview
The **PackDeliver System** is a C++ program designed to simulate the process of loading and delivering aid packages. The system reads data from various text files, processes the package information, and outputs the results in terms of the delivery details. The program calculates package values, loads packages into a vehicle based on the available capacity, and provides delivery times and other relevant information.

The system includes the following components:
- **Reading and processing data from external files**: The program reads information about packages, delivery points, and distances from three different files.
- **Package sorting and value calculation**: Packages are sorted based on their value, which is calculated using spoilage score and expected delivery day.
- **Vehicle loading**: Packages are loaded into a vehicle with a limited capacity based on their volume.
- **Delivery time calculation**: The program calculates the delivery time for each package based on distance and delivery order.

## Features
- **File-based data input**: The program reads three text files to fetch package information:
  - **`YardimPaketleri.txt`**: Contains details about each aid package.
  - **`MesafeBilgisi.txt`**: Provides the distance information for delivery points.
  - **`TeslimatNoktasiUzaklikBilgileri.txt`**: Contains the distance details between delivery points and the vehicle's starting location.
- **Package value calculation**: The value of each package is calculated based on spoilage score and expected delivery days.
- **Vehicle loading algorithm**: The program loads packages into a vehicle, ensuring that the total volume does not exceed the vehicle's capacity.
- **Sorting of packages**: Packages are sorted by their value to ensure that the most valuable packages are delivered first.
- **Delivery time calculation**: For each package, the system calculates the time needed for delivery based on distance and order.

## Getting Started

### Prerequisites
To compile and run this project, you need the following:
- A C++ compiler (e.g., **g++** or **Clang**)
- A text editor (optional, for inspecting or modifying the input files)

### Installation

1. Clone the repository to your local machine:
   ```bash
     git clone https://github.com/yourusername/aid-package-delivery.git

2. Navigate to the project directory:

        cd aid-package-delivery

3. Ensure that the following text files are available in the same directory as the main.cpp:

    YardimPaketleri.txt: Contains package details (ID, delivery point, volume, spoilage score, and expected delivery day).
    MesafeBilgisi.txt: Contains distance data for each delivery point.
    TeslimatNoktasiUzaklikBilgileri.txt: Contains distance details between the delivery points and the vehicle's starting location.

# File Format

Each of the input files should follow a specific format:

  # YardimPaketleri.txt:
    YP1,DeliveryPoint1,10,5,2,10
    YP2,DeliveryPoint2,20,3,5,12
    YP3,DeliveryPoint3,15,6,3,9
    ...
Each line represents a package and includes the following data:

  Package ID
  Delivery Point
  Volume
  Spoilage Score
  Expected Delivery Day
  Package Value (Calculated by the program)

  # MesafeBilgisi.txt:
    DeliveryPoint1,10
    DeliveryPoint2,20
    DeliveryPoint3,15
    ...

Each line represents the distance between the vehicle's starting point and the corresponding delivery point.

# TeslimatNoktasiUzaklikBilgileri.txt:
    DeliveryPoint1,10
    DeliveryPoint2,20
    DeliveryPoint3,15
    ...

Each line represents the distance from the vehicle's starting location to the respective delivery point.

# Compilation
To compile the program, use the following command:

    g++ -o aid_package_delivery main.cpp

# Running the Program
Once the program is compiled, you can run it with the following command:

    ./aid_package_delivery
    
The program will read the data from the specified text files, process the information, and print the results to the console.

# Output Example
The output will display the delivery order, package IDs, delivery points, package values, and the estimated delivery time for each package, as shown below:

Aid package deliveries are complete.

    Order    PackageID    Delivery Point    Package Value    Delivery Time
    -------------------------------------------------------------
    1         YP1          DeliveryPoint1    30               40 min
    2         YP3          DeliveryPoint3    28               45 min
    3         YP2          DeliveryPoint2    26               50 min

# Code Structure
main.cpp

  File Reading: Reads data from the three input files.
  Package Value Calculation: Implements the logic for calculating package values based on spoilage score and expected delivery day.
  Vehicle Loading: Implements the logic for loading packages into a vehicle with limited capacity.
  Delivery Time Calculation: Implements the logic for calculating delivery times based on distance and order.
  Sorting: Packages are sorted by value to prioritize high-value packages for delivery.

# Functions

  - dosyaOku: Reads the input files and stores the data.
  - paketDegeriHesapla: Calculates the value of each package.
  - paketYukle: Loads packages into the vehicle based on capacity.
  - compareByDeger: Compares packages by value for sorting.
  - hesaplaTeslimSure: Calculates the delivery time for each package.
  - teslimatSonucunuYazdir: Prints the delivery results to the screen.

# Contributing
If you'd like to contribute to this project, feel free to fork the repository, make changes, and submit a pull request. Contributions are welcome!

# License
This project is licensed under the MIT License - see the LICENSE file for details.

# Acknowledgments

  -This project was developed as part of a simulation exercise to model the delivery process of aid packages.
  -Thanks to all contributors for their continuous support and contributions.

  
### Explanation of the Sections:
1. **Overview**: Provides a high-level description of the project and its functionality.
2. **Features**: Describes the key features of the system and the input/output process.
3. **Getting Started**: Explains how to set up and run the project, including prerequisites and installation steps.
4. **File Format**: Specifies the format of the input files, so users know how to prepare them.
5. **Compilation and Running**: Describes how to compile and execute the program.
6. **Output Example**: Shows what users can expect as output.
7. **Code Structure**: Gives an overview of the code organization and the functions used.
8. **Contributing**: Encourages others to contribute to the project.
9. **License**: Specifies the open-source license for the project.



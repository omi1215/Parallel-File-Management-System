# Parallel File Management System (MPI Project)

## Overview
This project is part of the **CS3006 - Parallel and Distributed Computing** course at the **National University of Computer and Emerging Sciences, Chiniot-Faisalabad Campus**. The goal of the project is to develop a **Parallel Patient Record Management System** using **MPI in C++/C** to efficiently manage patient records across multiple nodes. 

The system handles core functionalities such as:
- Adding, reading, updating, and deleting records
- Distributed record distribution and search
- Data backup, recovery, and load balancing
- Parallel compression and decompression of patient data

## Table of Contents
1. [Project Objectives](#project-objectives)
2. [Features](#features)
3. [Modules Overview](#modules-overview)
4. [Learning Outcomes](#learning-outcomes)
5. [Technologies Used](#technologies-used)
6. [Installation and Setup](#installation-and-setup)
7. [Usage](#usage)
8. [Contributing](#contributing)
9. [License](#license)

---

## Project Objectives
The main objective is to leverage **MPI (Message Passing Interface)** to build a distributed system that ensures efficient management of patient records, while enabling parallel processing and scalability. The system focuses on:
- Efficient data distribution across nodes
- Optimized record processing
- Robust data integrity through backups
- Load balancing for performance efficiency

## Features
- **Initialization & Configuration**: Parses patient configuration files and sets up MPI communication.
- **Patient Record Operations**: Add, update, delete, and read patient records distributed across nodes.
- **Distributed Search**: Enables efficient search functionality across multiple nodes.
- **Backup & Recovery**: Ensures data integrity with scheduled backups and recovery procedures.
- **Load Balancing**: Optimizes resource utilization by dynamically redistributing workloads.
- **Compression & Decompression**: Reduces network load using parallel compression algorithms.
- **Logging & Monitoring**: Logs operations and system performance for debugging and auditing.

## Modules Overview
1. **Initialization and Configuration Module**: Sets up the MPI environment and reads patient data from configuration files.
2. **Patient Distribution Module**: Distributes patient records evenly among nodes.
3. **Implementing Operations Module**: Provides functionalities to add, read, update, and delete records.
4. **Backup and Recovery Module**: Schedules backups and enables recovery in case of data loss.
5. **Distributed Search Module**: Facilitates search across nodes using MPI communication.
6. **Logging Module**: Logs system activities and errors for troubleshooting.
7. **Load Balancing Module**: Dynamically adjusts workload distribution to optimize performance.
8. **Parallel Compression Module**: Compresses and decompresses data in parallel to reduce storage and network usage.

## Learning Outcomes
By completing this project, you will:
- Gain proficiency in **MPI programming** for parallel and distributed systems.
- Understand how to design and implement a **distributed file management system**.
- Develop problem-solving skills related to debugging and optimizing distributed systems.
- Learn to manage **software engineering principles** like modularity and maintainability.
- Build experience in **project management** and collaboration.

## Technologies Used
- **Languages**: C++/C
- **Parallel Computing Framework**: MPI (Message Passing Interface)
- **Development Environment**: Visual Studio 2022

## Installation and Setup
To set up this project on your system, follow these steps:

1. **Clone the repository**:
    ```bash
    git clone https://github.com/your-username/parallel-file-management-system.git
    cd parallel-file-management-system
    ```

2. **Install MPI**:
    - For Windows, install [Microsoft MPI](https://learn.microsoft.com/en-us/message-passing-interface/microsoft-mpi).
    - For Linux, use:
      ```bash
      sudo apt update
      sudo apt install mpich
      ```

3. **Build the Project**:
    Open the solution file (`.sln`) in **Visual Studio** and build the project.

4. **Run the Project**:
    ```bash
    mpiexec -n <number_of_processes> ./MPI_Project.exe
    ```

## Usage
The project provides a **command-line interface** for users to interact with various modules:

- **Add a record**: Allows the user to add patient data.
- **Search records**: Performs a distributed search across all nodes.
- **Backup data**: Manually trigger a backup operation.
- **Load balance**: Redistribute workload dynamically.

## Contributing
We welcome contributions! If you'd like to help out, please:
1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Commit your changes (`git commit -m 'Add new feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Open a Pull Request.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

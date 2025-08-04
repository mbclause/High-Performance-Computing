# ⚙️ High Performance Computing Projects – CPSC 479

This repository contains assignments and projects developed for the High Performance Computing course at California State University, Fullerton. The work demonstrates practical applications of distributed and parallel programming using **MPI**, **CUDA**, and **OpenMP**, alongside algorithmic strategies for parallel computation and inter-process communication.

## 🧰 Technologies Used

- C / C++
- MPI (Message Passing Interface)
- CUDA (NVIDIA GPU Programming)
- OpenMP (Shared Memory Parallelism)
- Linux Shell & Makefiles
- GCC / mpicc / nvcc

---

## 📁 Project Overview

### 🔁 Project 1 – MPI Ring-Based Leader Election  
*Folder: `project-1-leader-election-yes-team-main`*

Implements a **ring-based leader election algorithm** using MPI. Each process in the ring network passes messages to determine the highest-ranked node. Demonstrates concepts of distributed consensus, unidirectional communication, and synchronization in MPI.

---

### 🧮 Project 2 – Shear Sort on GPU using CUDA  
*Folder: `project-2-team_jayson-main`*

Implements **Shear Sort**—a parallel sorting algorithm designed for 2D mesh topologies—using **CUDA** for massively parallel execution on an NVIDIA GPU. Focuses on coalesced memory access, synchronization between CUDA threads, and correctness across multiple phases of row/column sorting.

---

### 🔄 Bidirectional Ring Communication  
*Folder: `bidirectional ring`*

Explores communication models in ring topologies, comparing **unidirectional vs. bidirectional MPI rings**. Measures latency and evaluates message propagation performance.

---

## 🧵 OpenMP Practice  
*Folder: `openMP practice`*

Contains multiple short programs to practice **OpenMP pragmas** including `parallel for`, `critical`, and `reduction`. Benchmarks various scheduling techniques and illustrates the effect of thread count on performance.

---

## 🧠 Homework Assignments

- **HW1–HW6**: Problem sets and code samples covering:
  - Fork-join models
  - Parallel speedup and Amdahl’s Law
  - Load balancing
  - Cache-aware optimization
  - Shared vs distributed memory analysis

---

## 🎓 Education Context

These projects were completed as part of the CSUF Master's in Computer Science program, emphasizing low-level parallelism, distributed algorithms, and performance tuning in modern hardware environments.

---

## ⚠️ Notes

- CUDA projects were developed and tested using `nvcc`.
- MPI programs require `mpicc` and multi-process execution via `mpirun`.
- All code assumes a Linux environment.

---

## 📜 License

MIT License — for academic and educational use.

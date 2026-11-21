# x86-to-C Interface Programming Project: SAXPY Kernel

An x86-to-C interface programming project implementing the single-precision **SAXPY** (`A * X + Y`) vector operation in both **C** and **x86-64 Assembly** using functional scalar SIMD registers and scalar SIMD floating-point instructions, complete with 30-run kernel benchmarking and numerical correctness verification.

---

## Group Members
* **Jensel John Espada**
* **John Benedict Garcia**

---

## Project Overview

The kernel computes the single-precision SAXPY operation across vectors of length `n`:

<p align="center">
  <strong>Z[i] = A &middot; X[i] + Y[i]</strong>
</p>

### Key Specifications
* **Inputs:**
  * `n` (`int`): Length of the vectors.
  * `A` (`float`): Single-precision floating-point scalar multiplier.
  * `X`, `Y` (`float*`): Single-precision floating-point input vectors.
* **Output:**
  * `Z` (`float*`): Single-precision floating-point output vector storing the computed results, with the **first 10 elements** displayed for both the C and x86-64 implementations.
* **x86-64 SIMD Requirement:**
  * Implemented using functional scalar SIMD registers (`XMM0`, `XMM1`, etc.) and scalar SIMD floating-point instructions (`MOVSS`, `MULSS`, `ADDSS`).
* **Benchmarking & Verification:**
  * Only the kernel execution portion is timed across **30 runs** per vector size (n = 2<sup>20</sup>, n = 2<sup>24</sup>, and n = 2<sup>30</sup>, or n = 2<sup>28</sup> / 2<sup>29</sup> depending on system RAM) to compute average execution time.
  * The x86-64 assembly kernel output is validated against the C kernel ("sanity check" reference) to confirm numerical correctness.

---

## Repository Structure

## How to Build and Run

## Comparative Execution Time & Performance Analysis

### Average Execution Time (30 Runs)

*Note: Replace the placeholder values below with your actual recorded benchmark averages.*

| Vector Size (`n`) | C Kernel Avg. Time (ms) | x86-64 Assembly Kernel Avg. Time (ms) | Speedup / Ratio |
| :--- | :---: | :---: | :---: |
| **2<sup>20</sup>** ($1,048,576$) | `[0.0000 ms]` | `[0.0000 ms]` | `[0.00x]` |
| **2<sup>24</sup>** ($16,777,216$) | `[0.0000 ms]` | `[0.0000 ms]` | `[0.00x]` |
| **2<sup>30</sup>** ($1,073,741,824$)* | `[0.0000 ms]` | `[0.0000 ms]` | `[0.00x]` |

*\*If n = 2<sup>30</sup> exceeded system memory limits, update this row to 2<sup>28</sup> or 2<sup>29</sup> accordingly.*

### Performance Analysis

## Program Output & Correctness Check

### 1. C Version Output & Correctness Check

### 2. x86-64 Assembly Version Output & Correctness Check

## Video Walkthrough

Watch the 5–10 minute walkthrough covering our C and x86-64 source code, compilation setup in Visual Studio, and live program execution:

* **[Watch the Demo Video (Google Drive / YouTube Link)](https://your-video-link-here.com)**

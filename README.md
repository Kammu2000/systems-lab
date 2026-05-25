# Systems Lab

A playground for building low-level systems from scratch and understanding how things actually work under the hood.

This repository is focused on implementing core systems concepts in C++ such as concurrency primitives, schedulers, event-driven systems, and performance-oriented infrastructure.

The goal is not just to "use" these concepts, but to deeply understand their architecture, tradeoffs, and real-world design patterns by building them manually.

---

## Why This Repo Exists

As engineers, we often use abstractions like thread pools, schedulers, async runtimes, and event loops without fully understanding what happens underneath.

This repo is my attempt to remove that abstraction layer.

Instead of treating these as black boxes, I want to:

- understand internal architecture
- learn concurrency deeply
- build production-style system components
- improve low-level C++ design thinking
- prepare for high-performance and infrastructure-heavy engineering work

This is especially aligned with my work and learning around WebAssembly, multithreading, runtime systems, and scalable software architecture.

---

## Implementations

### Concurrency

- Thread Pool
- Priority-Based Task Scheduler
- Rate Limiter

### Event-Driven Systems

- Event Loop

### Performance + Infrastructure

- LRU Cache
- Custom Malloc 
- Smart Pointers

---

Copyright (c) 2026 Deepanshu Upadhyay. Licensed under the [MIT License](LICENSE).

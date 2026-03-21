<div align="center">
  
  <h1>⚡ C++ Abstract Data Types (ADT)</h1>
  <p><i>A rigorously tested, interface-driven data structure library for CMSC 123.</i></p>

  [![C++ Standard](https://img.shields.io/badge/C++-11%2F14%2F17-00599C?style=flat-square&logo=c%2B%2B)](https://isocpp.org/)
  [![Architecture](https://img.shields.io/badge/Architecture-Interface--Driven-5a32fa?style=flat-square)](#)
  [![Tests](https://img.shields.io/badge/Tests-Passing-2ea44f?style=flat-square)](#)

</div>

<br>

> [!NOTE]  
> **Project Philosophy** > This project enforces strict Software Engineering principles. Abstract classes (`include/`) act as binding contracts, concrete logic (`src/`) operates independently, and verification is split between logical correctness (`tests/`) and microsecond-level speed scaling (`time_benchmark/`).

---

## 🏗️ System Architecture

Instead of blending our code together, we built a modular pipeline. Here is how our library is structured:

```mermaid
graph LR
    A[include/<br/>Interfaces] -->|Contracts| B(src/<br/>Implementations)
    B --> C{tests/<br/>Correctness}
    B --> D{time_benchmark/<br/>Performance}
    
    style A fill:#f9f9f9,stroke:#333,stroke-width:2px
    style B fill:#e1f5fe,stroke:#0288d1,stroke-width:2px
    style C fill:#e8f5e9,stroke:#388e3c,stroke-width:2px
    style D fill:#fff3e0,stroke:#f57c00,stroke-width:2px

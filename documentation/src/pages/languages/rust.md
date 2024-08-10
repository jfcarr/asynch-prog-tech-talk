# Rust

## Highlights

* Tokio
  * Multiple options for asynchronous handling, but **Tokio** is the most popular.
  * Tokio must be added as a dependency: Not part of the standard library.
  * Uses async/await syntax.
  * Uses `join!` macro to manage task groups.
  * In Rust, promise values are called `futures`.  They are supplied by an external library.

# Go

## Highlights

* Very opinionated language!
* Uses the `go` keyword to make a function call asynchronous.
* Does _not_ understand `await`: Uses `wait groups` to track asynchronous operations.
* **[PATTERN]** Expects shared variables to be protected by a `mutex`.

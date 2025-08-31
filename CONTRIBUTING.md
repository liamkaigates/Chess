# Contributing

Thank you for your interest in improving this Chess project!

## Getting Started
- Install prerequisites listed in `README.md`.
- Build and run tests locally: `make && export XDG_RUNTIME_DIR=/tmp && ./chess_test`.

## Branching & Commits
- Create feature branches from `main`.
- Use imperative commit messages (e.g., "Optimize move generation").
- Keep changes focused; separate refactors from feature work when possible.

## Code Style
- C++20, 4-space indentation, no tabs.
- Match surrounding style and file organization.
- Prefer small, testable units; keep headers lean.

## Tests
- Add/extend tests under `test/` using GoogleTest.
- Ensure tests pass locally and in CI.

## Pull Requests
- Fill out the PR template.
- Include rationale, screenshots/GIFs for UI, and verification steps.
- Link related issues.

## Reporting Issues
- Provide reproduction steps, expected vs. actual behavior, and environment details.


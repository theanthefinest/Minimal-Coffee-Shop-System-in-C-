# Minimal Coffee Shop System in C++

A simple, menu-driven management system for a coffee shop, written in modern C++. This project demonstrates basic file I/O, CSV parsing, terminal UI, and CRUD operations for a drink menu.

## Features

- Display coffee shop menu from CSV
- Add, update, and delete menu items
- Search and sort menu items
- Colorful terminal output
- Data persistence using CSV files

## Project Structure

```
main.cpp                # Main program entry point
utils/
	service.h             # All menu logic and utility functions
database/
	menu.csv              # Menu data in CSV format
README.md               # Project documentation
```

## Getting Started

### Prerequisites

- g++ (C++17 or newer)
- VS Code recommended

### Build

Open a terminal in the project root and run:
```sh
g++ main.cpp -o main
```
Or use the VS Code C++: g++ build active file task.

### Run

```sh
./main
```

### Menu CSV Format

The menu is stored in `database/menu.csv`:
```
ItemID,DrinkName,Size,Price
001,Espresso,Single,2.50
...
```

## Usage

- Follow the on-screen menu to display, add, update, delete, or search menu items.
- All changes are saved to the CSV file.

## Example Output

```
============ MENU ===============================
ID    Drink Name        Size        Price     
------------------------------------------------
001   Espresso         Single      $2.50     
002   Americano        Medium      $3.75     
...
================================================
```

## License

MIT

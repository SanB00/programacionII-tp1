# App for library management

## Introduction

This is a project built on my second programming level using C++ classes and it's run in console and stores data into binary files (.dat extension)

## Functions

- The library has a full CRUD of the Books (Libros), Members (Socios) and Lends (Préstamos) entities. The latter matches the first two of them
- Besides of CRUD we have the searching by ID or by a certain field such as book title.
- The delete of a book or member record, is managed by a feature flag which will allow the recording of a lend
- The lends could not be modified just hard deleted (The record is search on the file and skipped when resaving the binary file)
  - PR #8 (https://github.com/SanB00/programacionII-tp1/pull/8)
- When a lend is being registered, we check the existance of both Libros and Socios
- Dates can be before today's date, but the lend date (fechaPrestamo) can not be greater than the returning date (fechaDevolucion)
- It has reports (Informes) for the sellest book, the member that asked more books historically, the quantity of books a member has and the number of books per month which was lent through a requested year.

## How to run and mantain code

- The project starts with CodeBlocks IDE, opening the `.cbp` file and rebuilding the whole project so it can create the bin and obj folders required for the cpp compiling.
- New files are added manually on Codeblocks for project depedency
- To format and have a better intellisense performance, I´ve used Visual Studio Code and the plugin [C/C++](https://marketplace.visualstudio.com/items/?itemName=ms-vscode.cpptools) setting the format style as "Google".

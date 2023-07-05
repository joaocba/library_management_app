# Library Management App

This is a library management app developed in C as part of the "Programação II" course in the "TeSP Tecnologias e Programação de Sistemas de Informação" program. It allows users to perform various functions related to library management, such as adding books, removing books, registering readers, creating requests, and more.

## Functions

- **Add a book**: Users can add a new book to the library by entering its title and ID.
- **Remove a book**: Users can remove a book from the library by providing its ID.
- **Display books**: Users can view the list of books available in the library.
- **Register a reader**: Users can register a new reader by entering their name and ID.
- **Remove a reader**: Users can remove a reader from the library by providing their ID.
- **Display readers**: Users can view the list of readers registered in the library.
- **Create a book request**: Users can create a request by entering the reader's ID and the book's ID they wish to borrow.
- **Display requests**: Users can view the list of book requests made in the library.
- **Close a request**: Users can close a book request by providing its ID.

## Usage

To use the library management app, follow these steps:

1. Compile the C code.
2. Run the resulting executable.
3. The app will display a menu with various options for managing the library.
4. Choose the desired option by entering the corresponding number.
5. Follow the on-screen instructions to perform the selected operation.

**Note:** The app uses text files ("livros.txt", "leitores.txt", "requisicoes.txt") to store data related to books, readers, and requests, respectively. Make sure these files exist in the same directory as the executable.

For more detailed information about each function and the app's implementation, please refer to the source code.
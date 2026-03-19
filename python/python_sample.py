import threading
import json
import sqlite3
from functools import reduce
from typing import Generator, List


# ---------------------- Database Setup ----------------------
def setup_database():
    conn = sqlite3.connect("library.db")
    cursor = conn.cursor()
    cursor.execute("""
    CREATE TABLE IF NOT EXISTS books (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        title TEXT,
        author TEXT,
        available INTEGER
    )""")
    conn.commit()
    conn.close()


# ---------------------- Context Manager ----------------------
class FileLogger:
    def __init__(self, filename):
        self.file = open(filename, 'a')

    def __enter__(self):
        return self.file

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.file.close()


# ---------------------- Decorator ----------------------
def log_action(func):
    def wrapper(*args, **kwargs):
        result = func(*args, **kwargs)
        with FileLogger('actions.log') as f:
            f.write(f"Action: {func.__name__} called with {args}, {kwargs}\n")
        return result
    return wrapper


# ---------------------- Book Class ----------------------
class Book:
    def __init__(self, title: str, author: str):
        self.title = title
        self.author = author
        self.available = True

    def __str__(self):
        return f"{self.title} by {self.author} - {'Available' if self.available else 'Checked Out'}"


# ---------------------- Library Class ----------------------
class Library:
    book_list: List[Book] = []

    @classmethod
    def load_from_file(cls, filename="books.json"):
        try:
            with open(filename, 'r') as f:
                data = json.load(f)
                cls.book_list = [Book(b["title"], b["author"]) for b in data]
        except FileNotFoundError:
            print("Book file not found. Starting with empty library.")

    @staticmethod
    def search_books(keyword: str):
        return list(filter(lambda book: keyword.lower() in book.title.lower(), Library.book_list))

    @log_action
    def add_book(self, book: Book):
        self.book_list.append(book)
        with sqlite3.connect("library.db") as conn:
            conn.execute("INSERT INTO books (title, author, available) VALUES (?, ?, ?)",
                         (book.title, book.author, int(book.available)))
            conn.commit()

    @log_action
    def list_books(self):
        return [str(book) for book in self.book_list]

    @log_action
    def checkout_book(self, title: str):
        for book in self.book_list:
            if book.title == title and book.available:
                book.available = False
                return f"Book '{title}' checked out!"
        raise Exception("Book not available!")

    @log_action
    def return_book(self, title: str):
        for book in self.book_list:
            if book.title == title and not book.available:
                book.available = True
                return f"Book '{title}' returned!"
        raise Exception("Book not found or already returned!")


# ---------------------- Generator ----------------------
def available_books_gen() -> Generator[str, None, None]:
    for book in Library.book_list:
        if book.available:
            yield book.title


# ---------------------- Multithreading Example ----------------------
def async_add_books(library):
    books = [("1984", "George Orwell"), ("Python 101", "Mike Driscoll")]
    for title, author in books:
        library.add_book(Book(title, author))


# ---------------------- Main Execution ----------------------
def main():
    setup_database()

    library = Library()
    Library.load_from_file()

    # Add books in a separate thread
    t = threading.Thread(target=async_add_books, args=(library,))
    t.start()
    t.join()

    print("All Books:")
    print("\n".join(library.list_books()))

    try:
        print(library.checkout_book("1984"))
    except Exception as e:
        print("Error:", e)

    print("Available Books:")
    for book in available_books_gen():
        print("-", book)

    total_letters = reduce(lambda x, y: x + y, [len(book.title) for book in Library.book_list])
    print(f"\nTotal letters in book titles: {total_letters}")

    # Recursion (simple factorial)
    def factorial(n):
        return 1 if n == 0 else n * factorial(n - 1)

    print("Factorial of 5:", factorial(5))


if __name__ == "__main__":
    main()

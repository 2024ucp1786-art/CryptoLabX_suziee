from collections import Counter

import datetime
import os


def write_log(option):
    os.makedirs("logs", exist_ok=True)

    with open("logs/activity.log", "a") as log:
        now = datetime.datetime.now()
        log.write(
            f"{now.strftime('%Y-%m-%d %H:%M:%S')} - Selected Option: {option}\n"
        )
def analyze_text():
    file_path = "datasets/sample.txt"

    try:
        with open(file_path, "r", encoding="utf-8") as file:
            text = file.read()

        # Number of characters
        characters = len(text)

        # Number of words
        words = len(text.split())

        # Number of lines
        lines = len(text.splitlines())

        # Unique characters
        unique_characters = len(set(text))

        # Letter frequency
        letters = [
            char.lower()
            for char in text
            if char.isalpha()
        ]

        frequency = Counter(letters)

        print("\n====== Text Analysis ======")
        print("Characters:", characters)
        print("Words:", words)
        print("Lines:", lines)
        print("Unique Characters:", unique_characters)

        print("\nLetter Frequency:")
        for letter, count in sorted(frequency.items()):
            print(f"{letter}: {count}")

    except FileNotFoundError:
        print("File not found:", file_path)



def encrypt():
    print("\n[Encrypt] Coming Soon...")


def decrypt():
    print("\n[Decrypt] Coming Soon...")


def attack():
    print("\n[Attack] Coming Soon...")


def analyze():
   analyze_text()


def menu():
    while True:
        print("\n========== CryptoLabX ==========")
        print("1. Encrypt")
        print("2. Decrypt")
        print("3. Attack")
        print("4. Analyze")
        print("5. Exit")
        print("================================")

        choice = input("Enter your choice: ")

        if choice == "1":
            encrypt()

        elif choice == "2":
            decrypt()

        elif choice == "3":
            attack()

        elif choice == "4":
            analyze()

        elif choice == "5":
            print("Exiting CryptoLabX...")
            break

        else:
            print("Invalid choice! Please select 1-5.")


if __name__ == "__main__":
    menu()

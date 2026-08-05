from collections import Counter
import datetime
import os


# ---------------- LOGGING SYSTEM ----------------

def write_log(option):
    os.makedirs("logs", exist_ok=True)

    with open("logs/activity.log", "a", encoding="utf-8") as log:
        now = datetime.datetime.now()
        log.write(f"{now.strftime('%Y-%m-%d %H:%M:%S')} - {option}\n")


# ---------------- FILE ANALYSIS ----------------

def analyze_text():

    filename = input("Enter file name from datasets folder: ")
    file_path = os.path.join("datasets", filename)

    try:
        with open(file_path, "r", encoding="utf-8") as file:
            text = file.read()

        characters = len(text)
        words = len(text.split())
        lines = len(text.splitlines())
        unique_characters = len(set(text))

        letters = [c.lower() for c in text if c.isalpha()]
        frequency = Counter(letters)

        print("\n========== Text Analysis ==========")
        print("File Name:", filename)
        print("Characters:", characters)
        print("Words:", words)
        print("Lines:", lines)
        print("Unique Characters:", unique_characters)

        print("\nLetter Frequency:")
        for letter, count in sorted(frequency.items()):
            print(f"{letter}: {count}")

        print("===================================")

        write_log(f"Analyzed file: {filename}")

    except FileNotFoundError:
        print("File not found inside datasets folder!")
        write_log(f"File not found: {filename}")



# ---------------- FUTURE MODULES ----------------

def encrypt():
    print("\nEncrypt - Coming Soon")


def decrypt():
    print("\nDecrypt - Coming Soon")


def attack():
    print("\nAttack - Coming Soon")


def analyze():
    analyze_text()



# ---------------- COMMAND LINE INTERFACE ----------------

def menu():

    write_log("CryptoLabX Started")

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
            write_log("Selected Encrypt")
            encrypt()


        elif choice == "2":
            write_log("Selected Decrypt")
            decrypt()


        elif choice == "3":
            write_log("Selected Attack")
            attack()


        elif choice == "4":
            write_log("Selected Analyze")
            analyze()


        elif choice == "5":
            write_log("Selected Exit")
            print("\nExiting CryptoLabX...")
            break


        else:
            write_log("Selected Invalid Option")
            print("Invalid choice! Please select 1-5.")



# ---------------- PROGRAM START ----------------

if __name__ == "__main__":
    menu()

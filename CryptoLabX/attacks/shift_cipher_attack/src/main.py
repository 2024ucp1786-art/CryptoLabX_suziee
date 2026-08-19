
from shift_cipher import encrypt, decrypt


def main():
    plaintext = "HELLO WORLD THIS IS CRYPTO LAB ASSIGNMENT 4 "
    key = 3

    ciphertext = encrypt(plaintext, key)
    decrypted = decrypt(ciphertext, key)

    print("Shift Cipher")
    print("============")
    print("Plaintext :", plaintext)
    print("Key       :", key)
    print("Ciphertext:", ciphertext)
    print("Decrypted :", decrypted)


if __name__ == "__main__":
    main()
EOF

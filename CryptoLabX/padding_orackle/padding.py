import os

from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives.padding import PKCS7

BLOCK_SIZE = 16
BACKEND = default_backend()


# --------------------------------------------------
# 1. PKCS#7 PADDING
# --------------------------------------------------

def add_padding(data):
    padder = PKCS7(BLOCK_SIZE * 8).padder()
    return padder.update(data) + padder.finalize()


def remove_padding(data):
    unpadder = PKCS7(BLOCK_SIZE * 8).unpadder()
    return unpadder.update(data) + unpadder.finalize()


# --------------------------------------------------
# 2. AES-CBC ENCRYPTION
# Used only for the demonstration
# --------------------------------------------------

def encrypt(plaintext, key, iv):
    cipher = Cipher(
        algorithms.AES(key),
        modes.CBC(iv),
        backend=BACKEND
    )

    encryptor = cipher.encryptor()
    padded = add_padding(plaintext)

    return encryptor.update(padded) + encryptor.finalize()


# --------------------------------------------------
# 3. PADDING ORACLE
# Returns True for valid padding, False otherwise
# --------------------------------------------------

class PaddingOracle:

    def __init__(self, key):
        self.__key = key
        self.queries = 0

    def check(self, iv, ciphertext):
        self.queries += 1

        cipher = Cipher(
            algorithms.AES(self.__key),
            modes.CBC(iv),
            backend=BACKEND
        )

        decryptor = cipher.decryptor()

        plaintext = (
            decryptor.update(ciphertext)
            + decryptor.finalize()
        )

        try:
            remove_padding(plaintext)
            return True

        except ValueError:
            return False


# --------------------------------------------------
# 4. RECOVER ONE PLAINTEXT BLOCK
# --------------------------------------------------

def attack_block(oracle, previous_block, target_block):

    intermediate = bytearray(BLOCK_SIZE)
    plaintext = bytearray(BLOCK_SIZE)

    # Recover bytes from right to left
    for padding_value in range(1, BLOCK_SIZE + 1):

        position = BLOCK_SIZE - padding_value

        # Create a modified previous block
        modified = bytearray(previous_block)

        # Force recovered bytes to the desired padding
        for j in range(position + 1, BLOCK_SIZE):
            modified[j] = (
                intermediate[j] ^ padding_value
            )

        found = False

        # Try all possible byte values
        for guess in range(256):

            modified[position] = guess

            valid = oracle.check(
                bytes(modified),
                target_block
            )

            if not valid:
                continue

            # Eliminate accidental longer-padding matches
            if padding_value == 1 and position > 0:

                test_block = bytearray(modified)
                test_block[position - 1] ^= 1

                if not oracle.check(
                    bytes(test_block),
                    target_block
                ):
                    continue

            # Recover intermediate byte
            intermediate[position] = (
                guess ^ padding_value
            )

            # Recover original plaintext byte
            plaintext[position] = (
                intermediate[position]
                ^ previous_block[position]
            )

            found = True
            break

        if not found:
            raise RuntimeError(
                "Could not recover byte at position "
                + str(position)
            )

    return bytes(plaintext)


# --------------------------------------------------
# 5. RECOVER COMPLETE PLAINTEXT
# --------------------------------------------------

def padding_oracle_attack(oracle, iv, ciphertext):

    if len(iv) != BLOCK_SIZE:
        raise ValueError("IV must be 16 bytes")

    if not ciphertext or len(ciphertext) % BLOCK_SIZE != 0:
        raise ValueError(
            "Ciphertext must contain complete 16-byte blocks"
        )

    blocks = [
        ciphertext[i:i + BLOCK_SIZE]
        for i in range(0, len(ciphertext), BLOCK_SIZE)
    ]

    recovered = bytearray()

    for i, target_block in enumerate(blocks):

        # The IV precedes the first ciphertext block
        if i == 0:
            previous_block = iv
        else:
            previous_block = blocks[i - 1]

        print(
            "Recovering block "
            + str(i + 1)
            + "/"
            + str(len(blocks))
        )

        recovered_block = attack_block(
            oracle,
            previous_block,
            target_block
        )

        recovered.extend(recovered_block)

    # Remove PKCS#7 padding from the recovered plaintext
    return remove_padding(bytes(recovered))


# --------------------------------------------------
# 6. MAIN PROGRAM
# --------------------------------------------------

def main():

    # Key is used by encryption and the oracle only
    key = os.urandom(32)  # AES-256
    iv = os.urandom(BLOCK_SIZE)

    original_plaintext = (
        b"Padding Oracle Attack: Cryptography Lab!"
    )

    # Prepare demonstration ciphertext
    ciphertext = encrypt(
        original_plaintext,
        key,
        iv
    )

    # Oracle internally holds the key
    oracle = PaddingOracle(key)

    print("=" * 50)
    print("AES-CBC PADDING ORACLE ATTACK")
    print("=" * 50)

    print("\nOriginal plaintext:")
    print(original_plaintext.decode("utf-8"))

    print("\nIV:")
    print(iv.hex())

    print("\nCiphertext:")
    print(ciphertext.hex())

    print("\nStarting attack...\n")

    # The attack receives no key
    recovered_plaintext = padding_oracle_attack(
        oracle,
        iv,
        ciphertext
    )

    print("\n" + "=" * 50)
    print("ATTACK RESULTS")
    print("=" * 50)

    print("\nRecovered plaintext:")
    print(recovered_plaintext.decode("utf-8"))

    print("\nTotal oracle queries:")
    print(oracle.queries)

    print("\nRecovery successful:")
    print(recovered_plaintext == original_plaintext)


if __name__ == "__main__":
    main()

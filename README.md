# SEED

This is an implementation of the SEED algorithm as defined in RFC4269.

## Usage

Initial encryption/decryption calls must be preceded by a call to Initialize(), where the key and initialization vector (IV) are given. Key and IV must be 16 bytes long. Providing an IV is optional; if one is not provided, the IV is set to 0.

The values used here are for this example only, but I _highly_ suggest that you generate your own values.

```c++
unsigned seed_key[] = { 0x32d9d478, 0x333bb2ba, 0x009ba5a1, 0x557e3b45 };
unsigned seed_iv[] = { 0x999f9467, 0x6277ba50, 0xea2fec75, 0x1113fac1 };

char text[] = "This is a test string. There are many like it, but this one, in particular, is mine."
```

### Encryption

```c++
char* encrypted;

SEED seed;
size_t bytesWritten;

// Get size needed to hold the encrypted data.
// You do not need to call Initialize() first to do this.
seed.Encrypt( text, sizeof(text), NULL, 0, &bytesWritten );

// Initialize() must be called before encryption.
seed.Initialize( seed_key, seed_iv );

encrypted = new char[bytesWritten];
if (encrypted) {
      if ( int err = seed.Encrypt( text, sizeof(text), encrypted, bytesWritten, &bytesWritten ) ) {
            printf( "SEED Encrypt error! %d\n", err );
      }
}

// encrypted now contains ciphertext.

```

### Decryption

```c++
// Initialize() must be called before decryption.
seed.Initialize( seed_key, seed_iv );

if ( int err = seed.Decrypt( encrypted, bytesWritten, text, sizeof(text), &bytesWritten ) ) {
     printf( "SEED Decrypt error! %d\n", err );
}

// text now contains plaintext.
```

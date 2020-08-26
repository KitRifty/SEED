#pragma once

// The SEED Algorithm
// https://tools.ietf.org/html/rfc4269

class SEED {

public:
	const enum {
		ERR_OK = 0,
		ERR_BUFFER_TOO_SMALL = -1,
		ERR_NO_MEMORY = -2
	};

	SEED();
	~SEED();

	int Initialize(const void* key, const void* iv=nullptr);

	void EncryptBlock(const void* block, void* outblock);

	/*
		Encrypts data of any length. Writes output to the given output buffer.

		NOTE: The size of the output buffer MUST be 16-byte aligned. If you pass a NULL
		output buffer, the function will pass a 16-byte aligned size in bytesWritten; no
		encryption will occur. You may then call this function again using this given size 
		as the outsize parameter.
	*/
	int Encrypt(const void* in, size_t insize, void* out, size_t outsize, size_t* bytesWritten=nullptr);

	void DecryptBlock(const void* block, void* outblock);

	/*
		Decrypts data that was encrypted with this algorithm. Writes output to the given
		output buffer.

		NOTE: The size of the input buffer does not have to be 16-byte aligned, but if 
		the size is not aligned, the algorithm will not decrypt the last unaligned bytes of
		the input and will not be written to the output buffer.
	*/
	int Decrypt(const void* in, size_t insize, void* out, size_t outsize, size_t* bytesWritten = nullptr);

private:
	int CreateBuffers(size_t insize, size_t outsize);
	void ClearBuffers();

	unsigned init_vector[4];
	unsigned key[4];
	unsigned ksi[16];

	unsigned subkeys[32];

	unsigned char* inBuffer;
	size_t inBufferSize;
	unsigned char* outBuffer;
	size_t outBufferSize;
};
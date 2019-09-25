// MEncrypt.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include <string>
#include <iostream>
#include <conio.h>
#include <time.h>

#include "rsa.h"
#include "randpool.h"
#include "hex.h"
#include "files.h"
#include "gzip.h"

#include "FFileList.h"

using namespace std;
using namespace CryptoPP;

// crypto++ 5.6.2
#pragma comment (lib,"cryptlib.lib")

const char gHeaderChecker[32] = "MAIET Encrypted File System";

union RSAHEADER
{
	byte byteHeader[36];					// 36 byte

	struct
	{
		char szHeaderChecker[32];			// 32 byte
		unsigned long nFileLength;			// 4 byte
	};

	RSAHEADER()					{ memset( byteHeader, 0, sizeof( byteHeader));								}

	void SetHeaderChecker()		{ memcpy( szHeaderChecker, gHeaderChecker, sizeof( gHeaderChecker));		}
	bool IsValidHeader()		{ return (strcmp( szHeaderChecker, gHeaderChecker) == 0) ? true : false;	}
	unsigned long GetLength()	{ return nFileLength;														}
};


RandomNumberGenerator & GlobalRNG()
{
	static RandomPool randomPool;
	return randomPool;
}

void GenerateCPPCode(const char *privFilename)
{
	FILE* outFile = fopen("PrivateKey.h","w+");
	fprintf(outFile,"const unsigned char szPrivateKey[] = {\n");

	FILE* file = fopen(privFilename,"r");
	
	int nCount = 0;
	unsigned char buffer[3] = {0,};

	while( fread(buffer,2,1,file) )
	{
		fprintf(outFile,"0x%s ,",buffer);
		nCount++;
		if(nCount%16 == 0)
			fprintf(outFile,"\n");
	}
	fclose(file);

	fprintf(outFile,"};\n");
	fclose(outFile);
}


void GenerateRSAKey(unsigned int keyLength, const char *privFilename, const char *pubFilename, const char *seed)
{
	RandomPool randPool;
	randPool.IncorporateEntropy((byte*)seed, strlen(seed));

	RSAES_PKCS1v15_Decryptor priv(randPool, keyLength);
	HexEncoder privFile(new FileSink(privFilename));
	priv.DEREncode(privFile);
	privFile.MessageEnd();

	RSAES_PKCS1v15_Encryptor pub(priv);
	HexEncoder pubFile(new FileSink(pubFilename));
	pub.DEREncode(pubFile);
	pubFile.MessageEnd();

	GenerateCPPCode(privFilename);
}


void RSAEncryptFile( const char *pubFilename, const char *szFileName, const char *szOutputFileName, const char *seed)
{
	// Read public key file
	FileSource pubFile( pubFilename, true, new HexDecoder);
	RSAES_PKCS1v15_Encryptor pub( pubFile);

	// Get random seed
	RandomPool randPool;
	randPool.IncorporateEntropy( (byte *)seed, strlen(seed));

	// Get size of 1 block
	size_t nMaxPlainTextLength = pub.FixedMaxPlaintextLength();

	// Zip code
	string strBuff;
	FileSource( szFileName, true, new Gzip( new StringSink( strBuff)));

	// Encrypt
	FileSink* pOutput = new FileSink( szOutputFileName);
	PK_EncryptorFilter *pEncryptFilter = new PK_EncryptorFilter( randPool, pub, pOutput);
	StringSource stringSource( strBuff, false, pEncryptFilter);

	// Write header
	RSAHEADER header;
	header.SetHeaderChecker();
	header.nFileLength = (unsigned long)strBuff.size();
	pOutput->Put( header.byteHeader, sizeof( RSAHEADER));

	// Pump data
	while ( stringSource.Pump( nMaxPlainTextLength))
		pEncryptFilter->MessageEnd();

	pOutput->MessageEnd();

	strBuff.clear();
}

void RSADecryptFile( const char *privFilename, const char *szFileName, const char *szOutputFileName)
{
	// Read private key
	FileSource privFile( privFilename, true, new HexDecoder);
	RSAES_PKCS1v15_Decryptor priv( privFile);

	// Get size of 1 block
	size_t nCipherTextLength = priv.FixedCiphertextLength();

	// Set file source
	FileSource fileSource( szFileName, false);

	// Skip header
	fileSource.Pump( sizeof( RSAHEADER));

	// Decrypt
	string strBuff;
	StringSink* pOutput = new StringSink( strBuff);
	PK_DecryptorFilter *pDecryptFilter = new PK_DecryptorFilter( GlobalRNG(), priv, pOutput);
	fileSource.Attach( pDecryptFilter);

	// Pump data
	lword nPump = 0;
	while ( nPump = fileSource.Pump( nCipherTextLength))
		pDecryptFilter->MessageEnd();

	pOutput->MessageEnd();

	// Unzip code and save to file
	StringSource( strBuff, true, new Gunzip( new FileSink( szOutputFileName)));

	strBuff.clear();
}

RSAHEADER GetHeaderFile( const char* szFileName)
{
	string strBuff;
	StringSink* pOutput = new StringSink( strBuff);
	FileSource fileSource( szFileName, false, pOutput);
	fileSource.Pump( sizeof( RSAHEADER));

	RSAHEADER header;
	memcpy( header.byteHeader, strBuff.c_str(), strBuff.size());

	return header;
}


string RSAEncryptString( const char *pubFilename, const char *data, size_t length, const char *seed)
{
	// Read public key file
	FileSource pubFile( pubFilename, true, new HexDecoder);
	RSAES_PKCS1v15_Encryptor pub( pubFile);

	// Get random seed
	RandomPool randPool;
	randPool.IncorporateEntropy( (byte *)seed, strlen(seed));

	// Get size of 1 block
	size_t nMaxPlainTextLength = pub.FixedMaxPlaintextLength ();

	// Zip code
	string strBuff;
	StringSource( (byte *)data, length, true, new Gzip( new StringSink( strBuff)));

	// Encrypt
	string result;
	StringSink* pOutput = new StringSink( result);
	PK_EncryptorFilter *pEncryptFilter = new PK_EncryptorFilter( randPool, pub, pOutput);
	StringSource stringSource( strBuff, false, pEncryptFilter);

	// Write header
	RSAHEADER header;
	header.SetHeaderChecker();
	header.nFileLength = (unsigned long)strBuff.size();
	pOutput->Put( header.byteHeader, sizeof( RSAHEADER));

	// Pump data
	lword nPump = 0;
	while ( nPump = stringSource.Pump( nMaxPlainTextLength))
		pEncryptFilter->MessageEnd();

	pOutput->MessageEnd();


	return result;
}

string RSADecryptString( const byte *privFilename, size_t keyLength, const char *data, size_t length)
{
	string result;

	try
	{
		// Read private key
		StringSource privFile( privFilename, keyLength, true);
		RSAES_PKCS1v15_Decryptor priv( privFile);

		// Get size of 1 block
		size_t nCipherTextLength = priv.FixedCiphertextLength();

		// Set string source
		StringSource stringSource( (byte *)data, length, false);

		// Skip header
		stringSource.Pump( sizeof( RSAHEADER));

		// Decrypt
		string strBuff;
		StringSink* pOutput = new StringSink( strBuff);
		PK_DecryptorFilter *pDecryptFilter = new PK_DecryptorFilter( GlobalRNG(), priv, pOutput);
		stringSource.Attach( pDecryptFilter);

		// Pump data
		lword nPump = 0;
		while ( nPump = stringSource.Pump( nCipherTextLength))
			pDecryptFilter->MessageEnd();

		pOutput->MessageEnd();

		// Unzip code
		StringSource( strBuff, true, new Gunzip( new StringSink( result)));
	}
	catch ( CryptoPP::Exception &e)
	{
		string str = e.what();
		assert( 0);
	}


	return result;
}

RSAHEADER GetHeaderString( const char* data, size_t length)
{
	string strBuff;
	StringSink* pOutput = new StringSink( strBuff);
	StringSource stringSource( (byte *)data, length, false, pOutput);
	stringSource.Pump( sizeof( RSAHEADER));

	RSAHEADER header;
	memcpy( header.byteHeader, strBuff.c_str(), strBuff.size());

	return header;
}


int main(int argc, char* argv[])
{
	char seed[ 1024] = "blahblah";

	if ( argc > 1  &&  strnicmp( argv[ 1], "-c", 2) == 0)
	{
		unsigned int keyLength	= 2048;
		char privFilename[ 128]	= "privateKey.txt";
		char pubFilename[ 128]	= "publicKey.txt";

		GenerateRSAKey( keyLength, privFilename, pubFilename, seed);
	}

	else if ( argc > 3  &&  strnicmp( argv[ 1], "-e", 2) == 0)
	{ 			
		char* pubFilename		= argv[ 2];
		char* szFileName		= argv[ 3];
		char* szOutputFileName	= argv[ 4];

		RSAEncryptFile( pubFilename, szFileName, szOutputFileName, seed);
	}

	else if ( argc > 3  &&  strnicmp( argv[ 1], "-d", 2) == 0)
	{
		char* privFilename		= argv[ 2];
		char* szFileName		= argv[ 3];
		char* szOutputFileName	= argv[ 4];

		RSADecryptFile( privFilename, szFileName, szOutputFileName);
	}

	else
	{
		cout << "MEncrypt (c) MAIET Entertainment\n"
			"uasge: MEncrypt -c\n"
			"       MEncrypt -d [PrivateKeyFile] [FileToDecrypt] [OutputFileName]\n"
			"       MEncrypt -e [PublicKeyFile] [FileToEncrypt] [OutputFileName]\n"
			"\n"
			" -c : Create public/private key pair. \n"
			" -d : Decrypt a file with Private Key\n"
			" -e : Encrypt a file with Public Key\n";
	}

	return 0;
}

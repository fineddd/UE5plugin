#pragma once
#include "SGTypes.h"
#include "IOBuffer.h"

//THIRD_PARTY_INCLUDES_START
#include "openssl/aes.h"
#include "openssl/blowfish.h"
//THIRD_PARTY_INCLUDES_END
#include <string>

class SGCORE_API SGIEncrypt
{
public:

    virtual std::string Encrypt(std::string& strData) = 0;
    virtual TSharedPtr<IoBuffer> Decrypt(IoBuffer& encryptMsg) = 0;
    virtual EEncryptionType GetEncryptType() = 0;
};

class SGCSimpleEncrypt : public SGIEncrypt
{
public:
	SGCSimpleEncrypt();
	virtual ~SGCSimpleEncrypt()
	{

	}

	bool InitKey(unsigned char* key, int nLen);
	virtual std::string Encrypt(std::string& strData);
	virtual TSharedPtr<IoBuffer> Decrypt(IoBuffer& encryptMsg);
    virtual EEncryptionType GetEncryptType();

private:
	const static int m_KeyLenght = 8;
	unsigned char m_key[m_KeyLenght];//秘钥8个字节
};

class SGCAesCFB8Encrypt : public SGIEncrypt
{
public:
    SGCAesCFB8Encrypt();
    ~SGCAesCFB8Encrypt();

    bool InitAesKey();
    bool InitAesKey(uint8 key[AES_BLOCK_SIZE], uint8 iv[AES_BLOCK_SIZE]);
    virtual std::string Encrypt(std::string& strData);
    virtual TSharedPtr<IoBuffer> Decrypt(IoBuffer& encryptMsg);
    virtual EEncryptionType GetEncryptType();


private:
    AES_KEY m_aesKey;
    uint8 m_key[AES_BLOCK_SIZE];
    uint8 m_iv[AES_BLOCK_SIZE];
};



//
//inline std::string Encode(unsigned char const* bytes_to_encode, unsigned int in_len)
//{
//  std::string ret;
//  int i = 0;
//  int j = 0;
//  unsigned char char_array_3[3];
//  unsigned char char_array_4[4];
//
//  while (in_len--)
//  {
//      char_array_3[i++] = *(bytes_to_encode++);
//      if (i == 3)
//      {
//          char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
//          char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
//          char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
//          char_array_4[3] = char_array_3[2] & 0x3f;
//
//          for (i = 0; i < 4; i++)
//          {
//              ret += cepher[char_array_4[i]];
//          }
//
//          i = 0;
//      }
//  }
//
//  if (i)
//  {
//      for (j = i; j < 3; j++)
//      {
//          char_array_3[j] = '\0';
//      }
//
//      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
//      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
//      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
//      char_array_4[3] = char_array_3[2] & 0x3f;
//
//      for (j = 0; j < i + 1; j++)
//      {
//          ret += cepher[char_array_4[j]];
//      }
//
//      while (i++ < 3)
//      {
//          ret += '=';
//      }
//  }
//
//  return ret;
//}
//
//inline bool IsEncoded(unsigned char c)
//{
//  return isalnum(c) || (c == '+') || (c == '/');
//}
//
//inline std::string Decode(const std::string& encoded_string)
//{
//  int in_len = (int)encoded_string.size();
//  int i = 0;
//  int j = 0;
//  int in_ = 0;
//  unsigned char char_array_4[4], char_array_3[3];
//  std::string ret;
//
//  while (in_len-- && (encoded_string[in_] != '=') && IsEncoded(encoded_string[in_]))
//  {
//      char_array_4[i++] = encoded_string[in_];
//      in_++;
//      if (i == 4)
//      {
//          for (i = 0; i < 4; i++)
//          {
//              char_array_4[i] = cepher.find(char_array_4[i]);
//          }
//
//          char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
//          char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
//          char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
//
//          for (i = 0; i < 3; i++)
//          {
//              ret += char_array_3[i];
//          }
//
//          i = 0;
//      }
//  }
//
//  if (i)
//  {
//      for (j = i; j < 4; j++)
//      {
//          char_array_4[j] = 0;
//      }
//
//      for (j = 0; j < 4; j++)
//      {
//          char_array_4[j] = cepher.find(char_array_4[j]);
//      }
//
//      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
//      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
//      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
//
//      for (j = 0; j < i - 1; j++)
//      {
//          ret += char_array_3[j];
//      }
//  }
//
//  return ret;
//}

class SGCBase64Encrypt : public SGIEncrypt
{
public:
    SGCBase64Encrypt()
    {
    }

    virtual ~SGCBase64Encrypt()
    {

    }

    virtual std::string Encrypt(std::string& strData);
    virtual TSharedPtr<IoBuffer> Decrypt(IoBuffer& encryptMsg);
    virtual EEncryptionType GetEncryptType();

private:
    std::string cepher = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
};

class SGCBlowFish : public SGIEncrypt
{
public:
    SGCBlowFish();
    virtual ~SGCBlowFish()
    {

    }

    bool InitBFKey();
    bool InitBFKey(unsigned char* key, int nLen, unsigned char* iv, int nIvLen);

    virtual std::string Encrypt(std::string& strData);
    virtual TSharedPtr<IoBuffer> Decrypt(IoBuffer& encryptMsg);
    virtual EEncryptionType GetEncryptType();

private:
    BF_KEY  m_bfKey;
    unsigned char m_key[BF_ROUNDS];//秘钥16个字节
    unsigned char m_iv[BF_BLOCK];//加密反馈8个字节，单次加密块8个字节
};

static uint32 GetCrc32(std::string& strMsg);
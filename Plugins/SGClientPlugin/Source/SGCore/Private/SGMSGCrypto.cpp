#include "SGMsgCrypto.h"
#include "boost/crc.hpp"

SGCAesCFB8Encrypt::SGCAesCFB8Encrypt()
{
    FMemory::Memset(m_key, 0, sizeof(m_key));
    FMemory::Memset(m_iv, 0, sizeof(m_iv));
}

SGCAesCFB8Encrypt::~SGCAesCFB8Encrypt()
{
}

bool SGCAesCFB8Encrypt::InitAesKey()
{
    uint8 key[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '1', '2', '3', '4', '5', '6' };
    uint8 iv[AES_BLOCK_SIZE];
    for (int i = 0; i < AES_BLOCK_SIZE; ++i)
    {
        iv[i] = '0';
    }

    return InitAesKey(key, iv);
}

bool SGCAesCFB8Encrypt::InitAesKey(uint8 key[AES_BLOCK_SIZE], uint8 iv[AES_BLOCK_SIZE])
{
    for (int i = 0; i < AES_BLOCK_SIZE; ++i)
    {
        m_key[i] = key[i];
    }

    for (int i = 0; i < AES_BLOCK_SIZE; ++i)
    {
        m_iv[i] = iv[i];
    }

    if (AES_set_encrypt_key(m_key, 128, &m_aesKey) < 0)
    {
        return false;
    }

    return true;
}

std::string SGCAesCFB8Encrypt::Encrypt(std::string& strData)
{
    //if (plainMsg.GetSize() < 16)
    //{
    //    return plainMsg;
    //}

    ///*
    //    由于Unity的AES加密算法，在默认padding方式为None的时候，必须消息长度是128bit的整数倍，也就是16个byte的长度
    //    所以为了配合Unity的特殊性，在解密的时候，只解密16byte的整数个字节，剩下的部分是没有加密的
    //*/
    //size_t nEncryptSize = (plainMsg.size() / 16) * 16;
    //size_t nLeftSize = plainMsg.size() - nEncryptSize;

    //unsigned char* encrypt_string = nullptr;

    //// alloc decrypt_string
    //encrypt_string = new unsigned char[nEncryptSize];
    //if (encrypt_string == nullptr)
    //{
    //    return "";
    //}

    //// 每次解密完之后，iv向量都会变化，所以需要一个临时变量来保存
    //unsigned char iv[AES_BLOCK_SIZE];
    //for (int i = 0; i < AES_BLOCK_SIZE; ++i)
    //{
    //    iv[i] = m_iv[i];
    //}

    //int nNum = 0;
    //AES_cfb128_encrypt((unsigned char*)plainMsg.c_str(), encrypt_string, nEncryptSize, &m_aesKey, iv, &nNum, AES_ENCRYPT);

    //std::string encrypt_msg((char*)encrypt_string, nEncryptSize);
    //if (nLeftSize > 0)
    //{
    //    encrypt_msg += plainMsg.substr(nEncryptSize, nLeftSize);
    //}

    //if (encrypt_string != nullptr)
    //{
    //    delete[] encrypt_string;
    //}
    //return encrypt_msg;
    return strData;
}

TSharedPtr<IoBuffer> SGCAesCFB8Encrypt::Decrypt(IoBuffer& encryptMsg)
{
    //if (encryptMsg.size() < 16)
    //{
    //    return encryptMsg;
    //}

    ///*
    //    由于Unity的AES加密算法，在默认padding方式为None的时候，必须消息长度是128bit的整数倍，也就是16个byte的长度
    //    所以为了配合Unity的特殊性，在解密的时候，只解密16byte的整数个字节，剩下的部分是没有加密的
    //*/
    //size_t nEncryptSize = (encryptMsg.size() / 16) * 16;
    //size_t nLeftSize = encryptMsg.size() - nEncryptSize;

    //unsigned char* decrypt_string = nullptr;

    //// alloc decrypt_string
    //decrypt_string = new unsigned char[nEncryptSize];
    //if (decrypt_string == NULL)
    //{
    //    return "";
    //}

    //// 每次解密完之后，iv向量都会变化，所以需要一个临时变量来保存
    //unsigned char iv[AES_BLOCK_SIZE];
    //for (int i = 0; i < AES_BLOCK_SIZE; ++i)
    //{
    //    iv[i] = m_iv[i];
    //}

    //int nNum = 0;
    ////AES_cfb8_encrypt((unsigned char*)encryptMsg.c_str(), decrypt_string, nEncryptSize, &m_aesKey, iv, &nNum, AES_DECRYPT);
    //AES_cfb128_encrypt((unsigned char*)encryptMsg.c_str(), decrypt_string, nEncryptSize, &m_aesKey, iv, &nNum, AES_DECRYPT);

    //std::string decrypt_msg((char*)decrypt_string, nEncryptSize);
    //if (nLeftSize > 0)
    //{
    //    decrypt_msg += encryptMsg.substr(nEncryptSize, nLeftSize);
    //}

    //if (decrypt_string != nullptr)
    //{
    //    delete[] decrypt_string;
    //}
    //return decrypt_msg;
    return nullptr;
}

EEncryptionType SGCAesCFB8Encrypt::GetEncryptType()
{
    return EEncryptionType::ENCRYPTION_AES;
}

std::string SGCBase64Encrypt::Encrypt(std::string& strData)
{
    return strData;
}
TSharedPtr<IoBuffer> SGCBase64Encrypt::Decrypt(IoBuffer& encryptMsg)
{
    return nullptr;
}
EEncryptionType SGCBase64Encrypt::GetEncryptType()
{
    return EEncryptionType::ENCRYPTION_BASE64;
}


SGCBlowFish::SGCBlowFish()
{
    memset(m_key, 0, sizeof(m_key));
    memset(m_iv, 0, sizeof(m_iv));
}


bool SGCBlowFish::InitBFKey()
{
    unsigned char key[BF_ROUNDS] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '1', '2', '3', '4', '5', '6' };
    unsigned char iv[BF_BLOCK] = { '1', '2', '3', '4', '5', '6', '7', '8'};
    //for (int i = 0; i < BF_BLOCK; ++i)
    //{
    //    iv[i] = '0';
    //}

    return InitBFKey(key, BF_ROUNDS, iv, BF_BLOCK);
}

bool SGCBlowFish::InitBFKey(unsigned char* key, int nKeyLen, unsigned char* iv, int nIvLen)
{
    //密钥长度16个字节
    for (int i = 0; i < BF_ROUNDS; ++i)
    {
        if (i < nKeyLen)
        {
            m_key[i] = key[i];
        }
        else
        {
            m_key[i] = 'c';
        }
    }

    //ivec指向的8字节的内容会影响到加解密的结果.加密反馈
    for (int i = 0; i < BF_BLOCK; ++i)
    {
        if (i < nIvLen)
        {
            m_iv[i] = iv[i];
        }
        else
        {
            m_iv[i] = 'c';
        }
    }

    BF_set_key(&m_bfKey, BF_ROUNDS, m_key);

    return true;
}

std::string SGCBlowFish::Encrypt(std::string& strData)
{
    if (strData.size() < BF_BLOCK)
    {
        return strData;
    }

    size_t nEncryptSize = (strData.size() / BF_BLOCK) * BF_BLOCK;
    size_t nLeftSize = strData.size() - nEncryptSize;

    unsigned char* encrypt_string = nullptr;

    // alloc decrypt_string
    encrypt_string = new unsigned char[nEncryptSize];
    if (encrypt_string == nullptr)
    {
        return "";
    }

    unsigned char iv[BF_BLOCK];
    for (int i = 0; i < BF_BLOCK; ++i)
    {
        iv[i] = m_iv[i];
    }

    int nNum = 0;
    BF_cfb64_encrypt((unsigned char*)strData.c_str(), encrypt_string, nEncryptSize, &m_bfKey, iv, &nNum, BF_ENCRYPT);

    std::string encrypt_msg((char*)encrypt_string, nEncryptSize);
    if (nLeftSize > 0)
    {
        encrypt_msg += strData.substr(nEncryptSize, nLeftSize);
    }

    if (encrypt_string != nullptr)
    {
        delete[] encrypt_string;
        encrypt_string = nullptr;
    }
    return encrypt_msg;
}

TSharedPtr<IoBuffer> SGCBlowFish::Decrypt(IoBuffer& encryptMsg)
{
    //if (encryptMsg.size() < BF_BLOCK)
    //{
    //  return encryptMsg;
    //}

    //size_t nEncryptSize = (encryptMsg.size() / BF_BLOCK) * BF_BLOCK;
    //size_t nLeftSize = encryptMsg.size() - nEncryptSize;

    //unsigned char* encrypt_string = nullptr;

    //// alloc decrypt_string
    //encrypt_string = new unsigned char[nEncryptSize];
    //if (encrypt_string == nullptr)
    //{
    //  return "";
    //}
    //unsigned char iv[BF_BLOCK];
    //for (int i = 0; i < BF_BLOCK; ++i)
    //{
    //  iv[i] = m_iv[i];
    //}


    //int nNum = 0;
    //BF_cfb64_encrypt((unsigned char*)encryptMsg.c_str(), encrypt_string, nEncryptSize, &m_bfKey, iv, &nNum, BF_DECRYPT);

    //std::string encrypt_msg((char*)encrypt_string, nEncryptSize);
    //if (nLeftSize > 0)
    //{
    //  encrypt_msg += encryptMsg.substr(nEncryptSize, nLeftSize);
    //}

    //if (encrypt_string != nullptr)
    //{
    //  delete[] encrypt_string;
    //  encrypt_string = nullptr;
    //}
    //return encrypt_msg;
    return nullptr;
}
EEncryptionType SGCBlowFish::GetEncryptType()
{
    return EEncryptionType::ENCRYPTION_BLOWFISH;
}

static uint32 GetCrc32(std::string& strMsg)
{
	boost::crc_32_type crc;
	crc.process_bytes(strMsg.data(), strMsg.length());
	return crc.checksum();
}

SGCSimpleEncrypt::SGCSimpleEncrypt()
{
	memset(m_key, 0, sizeof(m_key));
}

bool SGCSimpleEncrypt::InitKey(unsigned char* key, int nLen)
{
	//密钥长度16个字节
	for (int i = 0; i < m_KeyLenght; ++i)
	{
		if (i < nLen)
		{
			m_key[i] = key[i];
		}
		else
		{
			m_key[i] = 'c';
		}
	}

	return true;
}

std::string SGCSimpleEncrypt::Encrypt(std::string& strData)
{
	if (strData.size() < m_KeyLenght)
	{
		return strData;
	}

	size_t nEncryptSize = (strData.size() / m_KeyLenght) * m_KeyLenght;
	size_t nLeftSize = strData.size() - nEncryptSize;

	unsigned char* encrypt_string = nullptr;

	// alloc decrypt_string
	encrypt_string = new unsigned char[nEncryptSize];
	if (encrypt_string == nullptr)
	{
		return "";
	}

	for (size_t i = 0; i < nEncryptSize; i += m_KeyLenght)
	{
		for (size_t iKey = 0; iKey < m_KeyLenght && (i + iKey) < nEncryptSize; iKey++)
		{
			encrypt_string[i + iKey] = strData[i + iKey] ^ m_key[iKey];
		}
	}

	std::string encrypt_msg((char*)encrypt_string, nEncryptSize);
	if (nLeftSize > 0)
	{
		encrypt_msg += strData.substr(nEncryptSize, nLeftSize);
	}

	if (encrypt_string != nullptr)
	{
		delete[] encrypt_string;
		encrypt_string = nullptr;
	}

	return encrypt_msg;
}

TSharedPtr<IoBuffer> SGCSimpleEncrypt::Decrypt(IoBuffer& encryptMsg)
{
    return nullptr;
}

EEncryptionType SGCSimpleEncrypt::GetEncryptType()
{
    return EEncryptionType::ENCRYPTION_SIMPLE;
}

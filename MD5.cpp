#include <windows.h>
#include <wincrypt.h>
#include <iostream>
#include <string>

std::string calculateMD5Hash(const std::string& input) {
    HCRYPTPROV hProv;
    HCRYPTHASH hHash;
    BYTE hash[16];
    DWORD cbHash = 16;

    if (CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        if (CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {
            if (CryptHashData(hHash, reinterpret_cast<const BYTE*>(input.c_str()), input.length(), 0)) {
                if (CryptGetHashParam(hHash, HP_HASHVAL, hash, &cbHash, 0)) {
                    std::string result;
                    for (DWORD i = 0; i < cbHash; i++) {
                        result += char(hash[i]);
                    }
                    CryptDestroyHash(hHash);
                    CryptReleaseContext(hProv, 0);
                    return result;
                }
            }
            CryptDestroyHash(hHash);
        }
        CryptReleaseContext(hProv, 0);
    }
    return "";
}

int main() {
    std::string input;
    std::cout << "Enter a string to generate MD5 hash: ";
    std::getline(std::cin, input);

    std::string md5Hash = calculateMD5Hash(input);
    if (!md5Hash.empty()) {
        std::cout << "MD5 Hash: " << md5Hash << std::endl;
    } else {
        std::cout << "Failed to calculate MD5 hash." << std::endl;
    }

    return 0;
}

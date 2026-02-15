#include <algorithm>
#include <string>

static inline void reverseWord(std::string& str, size_t start, size_t end) {
    while (start < end) {
        std::swap(str[start++], str[--end]);
    }
}

std::string reverseWordsInText(const std::string& strSrc) {
    std::string str = strSrc;
    const size_t strSize = str.size();
    size_t beginWord{};
    size_t endWord{};

    while (beginWord < strSize) {
        beginWord = str.find_first_not_of(' ', beginWord);
        if (beginWord == std::string::npos) {
            break;
        }

        endWord = str.find(' ', beginWord);
        if (endWord == std::string::npos) {
            endWord = strSize;
        }

        reverseWord(str, beginWord, endWord);
        beginWord = endWord;
    }

    return str;
}
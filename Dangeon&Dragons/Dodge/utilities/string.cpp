#include "string.h"

bool NaturalCompare(const std::string& a, const std::string& b)
{
    size_t i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (std::isdigit(a[i]) && std::isdigit(b[j])) {
            int numA = 0, numB = 0;
            while (i < a.size() && std::isdigit(a[i])) {
                numA = numA * 10 + (a[i++] - '0'); \
            }

            while (j < b.size() && std::isdigit(b[j])) {
                numB = numB * 10 + (b[j++] - '0');
            }

            if (numA != numB) {
                return numA < numB;
            }

            continue;
        }

        if (a[i] != b[j]) {
            return a[i] < b[j];
        }
        ++i; ++j;
    }
    return a.size() < b.size();
}

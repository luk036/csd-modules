module;
/**
 Canonical Signed Digit Functions

 Handles:
  * Decimals
  *
  *

 eg, +00-00+000.0 or 0.+0000-00+
 Where: '+' is +1
        '-' is -1

 Harnesser
 License: GPL2
*/

import <cmath>;        // for fabs, pow, ceil, log2
import <iosfwd>;       // for string
import <string>;       // for basic_string
import <string_view>;  // for basic_string
import <vector>;

module csd;

using std::ceil;
using std::fabs;
using std::log2;
using std::pow;
using std::string;
using std::string_view;
using std::vector;

namespace csd {

/**
 * @brief Convert to CSD (Canonical Signed Digit) string representation
 *
 * Original author: Harnesser
 * https://sourceforge.net/projects/pycsd/
 * License: GPL2
 *
 * @param num
 * @param places
 * @return string
 */
auto to_csd(double num, const int places) -> string {
    if (num == 0.0) {
        return string("0");
    }
    auto const absnum = fabs(num);
    auto const nn = int(ceil(log2(absnum * 1.5)));
    auto n = absnum < 1.0 ? 0 : nn;
    const auto *const str = absnum < 1.0 ? "0" : "";
    auto csd_str = string(str);
    auto pow2n = pow(2.0, double(n - 1));
    while (n > -places) {
        if (n == 0) {
            csd_str += '.';
        }
        n -= 1;
        auto const d = 1.5 * num;
        if (d > pow2n) {
            csd_str += '+';
            num -= pow2n;
        } else if (d < -pow2n) {
            csd_str += '-';
            num += pow2n;
        } else {
            csd_str += '0';
        }
        pow2n /= 2.0;
    }
    return csd_str;
}

/**
 * @brief Convert the CSD string to a decimal
 *
 * @param csd_str
 * @return double
 */
// auto to_decimal(string_view csd_str) -> double {
//     auto num = 0.0;
//     auto loc = 0U;
//     auto i = 0U;
//     for (; i < csd_str.size(); ++i) {
//         auto c = csd_str[i];
//         if (c == '0') {
//             num *= 2.0;
//         } else if (c == '+') {
//             num = num * 2.0 + 1.0;
//         } else if (c == '-') {
//             num = num * 2.0 - 1.0;
//         } else if (c == '.') {
//             loc = i + 1;
//         } else {
//             // ignore unknown characters such as '
//         }
//     }
//     if (loc != 0) {
//         num /= pow(2.0, double(csd_str.size() - loc));
//     }
//     return num;
// }

/**
 * @brief Convert to CSD (Canonical Signed Digit) string representation
 *
 * @param[in] num
 * @param[in] nnz number of non-zero
 * @return string
 */
auto to_csdfixed(double num, unsigned int nnz) -> string {
    if (num == 0.0) {
        return string("0");
    }
    auto const absnum = fabs(num);
    auto const nn = int(ceil(log2(absnum * 1.5)));
    auto n = absnum < 1.0 ? 0 : nn;
    const auto *const str = absnum < 1.0 ? "0" : "";
    auto csd_str = string(str);
    auto pow2n = pow(2.0, double(n - 1));
    while (n > 0 || (nnz > 0 && fabs(num) > 1e-100)) {
        if (n == 0) {
            csd_str += '.';
        }
        n -= 1;
        auto const d = 1.5 * num;
        if (d > pow2n) {
            csd_str += '+';
            num -= pow2n;
            nnz -= 1;
        } else if (d < -pow2n) {
            csd_str += '-';
            num += pow2n;
            nnz -= 1;
        } else {
            csd_str += '0';
        }
        pow2n /= 2.0;
        if (nnz == 0) {
            num = 0.0;
        }
    }
    return csd_str;
}

// C++ program to find the longest repeated
// non-overlapping substring

// Returns the longest repeating non-overlapping
// substring in sv
auto longest_repeated_substring(string_view sv) -> string {
    const auto n = sv.size();
    auto lcsre = vector(n + 1, vector(n + 1, 0U));

    auto res_length = 0U;  // To store length of result

    // building table in bottom-up manner
    auto index = 0U;
    for (auto i = 1U; i != n + 1; ++i) {
        for (auto j = i + 1; j != n + 1; ++j) {
            // (j-i) > lcsre[i-1][j-1] to remove
            // overlapping
            if (sv[i - 1] == sv[j - 1] && lcsre[i - 1][j - 1] < (j - i)) {
                lcsre[i][j] = lcsre[i - 1][j - 1] + 1;

                // updating maximum length of the
                // substring and updating the finishing
                // index of the suffix
                if (lcsre[i][j] > res_length) {
                    res_length = lcsre[i][j];
                    if (index < i) {
                        index = i;
                    }
                }
            } else {
                lcsre[i][j] = 0U;
            }
        }
    }

    // If we have non-empty result, then insert
    // all characters from first character to
    // last character of string

    auto res = string("");  // To store result
    if (res_length > 0) {
        for (auto i = index - res_length + 1; i != index + 1; ++i) {
            res += sv[i - 1];
        }
    }

    return res;
}
// This code is contributed by ita_c

} // end namespace 


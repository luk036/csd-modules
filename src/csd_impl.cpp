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
import <vector>;       // for vector
import <utility>;      // for pair

module csd;

using std::ceil;
using std::fabs;
using std::log2;
using std::pair;
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
            return "0";
        }
        auto const absnum = fabs(num);
        auto temp = ceil(log2(absnum * 1.5));
        auto [rem, csd] = absnum < 1.0 ? pair{0.0, string{"0"}} : pair{temp, string{""}};

        // int rem; // yes, not yet initialized
        // string csd; // yes, not yet initialzed
        // if (absnum < 1.0) {
        //     rem = 0;
        //     csd = string{"0"};
        // }
        // else {
        //     rem = int(ceil(log2(absnum * 1.5)));
        //     csd = string{""};
        // }
        auto p2n = pow(2.0, rem);
        auto const eps = pow(2.0, double(-places));
        while (p2n > eps) {
            if (p2n == 1.0) {
                csd += '.';
            }
            auto const p2n_half = p2n / 2.0;
            auto const det = 3.0 * num;
            if (det > p2n) {
                csd += '+';
                num -= p2n_half;
            } else {
                if (det < -p2n) {
                    csd += '-';
                    num += p2n_half;
                } else {
                    csd += '0';
                }
            }
            p2n = p2n_half;
        }
        return csd;
    }

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
    auto to_csd_i(int num) -> string {
        if (num == 0) {
            return "0";
        }
        auto const absnum = abs(num);
        auto p2n = int(pow(2.0, ceil(log2(absnum * 1.5))));
        auto csd = string{""};
        while (p2n > 1) {
            auto const p2n_half = p2n / 2;
            auto const det = 3 * num;
            if (det > p2n) {
                csd += '+';
                num -= p2n_half;
            } else if (det < -p2n) {
                csd += '-';
                num += p2n_half;
            } else {
                csd += '0';
            }
            p2n = p2n_half;
        }
        return csd;
    }

    /**
     * @brief Convert the CSD string to a decimal
     *
     * @param csd
     * @return double
     */
    auto to_decimal(string_view csd) -> double {
        auto num = 0.0;
        auto loc = 0U;
        // for (; i < csd.size(); ++i) {
        //     auto digit = csd[i];
        auto pos = 0U;
        for (auto digit : csd) {
            if (digit == '0') {
                num *= 2.0;
            } else if (digit == '+') {
                num = num * 2.0 + 1.0;
            } else if (digit == '-') {
                num = num * 2.0 - 1.0;
            } else if (digit == '.') {
                loc = pos + 1;
            } else {
                // ignore unknown characters such as '
            }
            ++pos;
        }
        if (loc != 0) {
            num /= std::pow(2.0, double(csd.size() - loc));
        }
        return num;
    }

    /**
     * @brief Convert to CSD (Canonical Signed Digit) string representation
     *
     * @param[in] num
     * @param[in] nnz number of non-zero
     * @return string
     */
    auto to_csdfixed(double num, unsigned int nnz) -> string {
        if (num == 0.0) {
            return "0";
        }
        auto const absnum = fabs(num);
        auto temp = ceil(log2(absnum * 1.5));
        auto [rem, csd] = absnum < 1.0 ? pair{0.0, string{"0"}} : pair{temp, string{""}};

        auto p2n = pow(2.0, rem);
        while (p2n > 1.0 || (nnz > 0 && fabs(num) > 1e-100)) {
            if (p2n == 1.0) {
                csd += '.';
            }
            auto const p2n_half = p2n / 2.0;
            auto const det = 3.0 * num;
            if (det > p2n) {
                csd += '+';
                num -= p2n_half;
                nnz -= 1;
            } else {
                if (det < -p2n) {
                    csd += '-';
                    num += p2n_half;
                    nnz -= 1;
                } else {
                    csd += '0';
                }
            }
            p2n = p2n_half;

            if (nnz == 0) {
                num = 0.0;
            }
        }
        return csd;
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

}  // namespace csd

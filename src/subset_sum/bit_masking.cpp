#include "assignment/subset_sum/bit_masking.hpp"

#include <cassert>  // assert

#include "assignment/bits.hpp"  // is_bit_set, mask2indices

namespace assignment {

  std::vector<std::vector<int>> SubsetSumBitMasking::search(const std::vector<int>& set, int target_sum) const {
    assert(target_sum > 0 && set.size() <= 16);

    std::vector<std::vector<int>> indices;

    const auto num_elems = static_cast<int>(set.size());  // N
    const int num_subsets = 1 << num_elems;               // 2^N

    // 1. Внешний цикл: пробегаемся по всем битовым маскам от 0..00 до 1..11
    // 2. Внутренний цикл: проверка разрядов битовой маски и генерация подмножества, ассоциирующегося с этой маской
    // 3. Подсчет суммы текущего подмножества, сохранение индексов подмножества с целевой суммой в результат
    // Tips: можно пропустить итерацию, если сумма текущего подмножества стала больше целевой суммы
    for (int mask = 0; mask < num_subsets; mask++) {
      for (int pos = 0; pos < num_elems; pos++) {
        std::vector<int> subset = mask2indices(set, mask);

        int sum = 0;
        for (int i : subset) {
          sum += set[i];
        }

        if (sum == target_sum) {
          indices.push_back(subset);
        }
        if (sum > target_sum) {
          break;
        }
      }
    }
    return indices;
  }

}  // namespace assignment
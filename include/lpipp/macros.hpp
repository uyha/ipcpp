#pragma once

#define LPIPP_BITOR_OVERRIDE(_1, _2, _3, NAME, ...) NAME

#define LPIPP_BITOR_OP_IMPL(left_type, right_type, return_type)                                                        \
  friend constexpr auto operator|(left_type lhs, right_type rhs) noexcept->return_type {                               \
    return static_cast<return_type>(static_cast<std::underlying_type_t<left_type>>(lhs)                                \
                                    | static_cast<std::underlying_type_t<right_type>>(rhs));                           \
  }

#define LPIPP_SAME_TYPE_BITOR_OP(input_type, return_type) LPIPP_BITOR_OP_IMPL(input_type, input_type, return_type)
#define LPIPP_DIFF_TYPE_BITOR_OP(left_type, right_type, return_type)                                                   \
  LPIPP_BITOR_OP_IMPL(left_type, right_type, return_type)                                                              \
                                                                                                                       \
  friend constexpr auto operator|(right_type lhs, left_type rhs) noexcept->return_type {                               \
    return rhs | lhs;                                                                                                  \
  }

#define LPIPP_BITOR_OP(...)                                                                                            \
  LPIPP_BITOR_OVERRIDE(__VA_ARGS__, LPIPP_DIFF_TYPE_BITOR_OP, LPIPP_SAME_TYPE_BITOR_OP, dummy)(__VA_ARGS__)

#define LPIPP_BITAND_OVERRIDE(_1, _2, NAME, ...) NAME

#define LPIPP_BITAND_OP_IMPL(left_type, right_type)                                                                    \
  friend constexpr auto operator&(left_type lhs, right_type rhs) noexcept->bool {                                      \
    return static_cast<std::underlying_type_t<left_type>>(lhs)                                                         \
           & static_cast<std::underlying_type_t<right_type>>(rhs);                                                    \
  }

#define LPIPP_SAME_TYPE_BITAND_OP(input_type) LPIPP_BITAND_OP_IMPL(input_type, input_type)
#define LPIPP_DIFF_TYPE_BITAND_OP(left_type, right_type)                                                               \
  LPIPP_BITAND_OP_IMPL(left_type, right_type)                                                                           \
                                                                                                                       \
  friend constexpr auto operator&(right_type lhs, left_type rhs) noexcept->bool {                                      \
    return rhs & lhs;                                                                                                  \
  }

#define LPIPP_BITAND_OP(...)                                                                                           \
  LPIPP_BITAND_OVERRIDE(__VA_ARGS__, LPIPP_DIFF_TYPE_BITAND_OP, LPIPP_SAME_TYPE_BITAND_OP, dummy)(__VA_ARGS__)

#pragma once
#include <type_traits>

#define SFINAE_MOVE
//#define COPY_AND_MOVE

// ==============================================================================
// std::enable_if_t<条件, 型> は
// C++14 から導入されたエイリアステンプレートで
// typename std::enable_if<条件, 型>::type の省略形

// std::is_copy_constructible_v<T>
// std::is_move_constructible_v<T> は
// C++17 から導入された変数テンプレートで
// std::is_copy_constructible<T>::value
// std::is_move_constructible_v<T>::value
// の省略形

// 2番目の 'テンプレート' パラメータとして std::enable_if_t を使用
// std::enable_if_t の第二引数に std::nullptr_t を指定し
// デフォルト引数として nullptr を設定
// ==============================================================================
namespace SFINAE {

    template<typename T, std::enable_if_t<std::is_copy_constructible_v<T>, std::nullptr_t> = nullptr>
    void DummyCopy(T& obj) {
        T dummy = obj; // T をコピーして使う
    }

#ifdef SFINAE_MOVE
    // コピーも必要なら && で std::enable_if_t の第一引数をつなげる
    template<typename T, std::enable_if_t<std::is_move_constructible_v<T>, std::nullptr_t> = nullptr>
    void DummyCopy(T&& obj) {
        T dummy = std::move(obj); // T をムーブして使う
    }
#endif

#ifdef COPY_AND_MOVE
    // コピーも条件に増やした記述の方法(&& でつなげる)
    template<typename T, std::enable_if_t<std::is_copy_constructible_v<T> && std::is_move_constructible_v<T>, std::nullptr_t> = nullptr>
    void DummyCopy(T&& obj) {
        T dummy = std::move(obj); // T をムーブして使う
    }
#endif // COPY_AND_MOVE
}

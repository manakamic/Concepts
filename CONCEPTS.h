#pragma once
#include <concepts>

#define CONCEPTS_MOVE

namespace CONCEPTS {

    // ==============================================================================
    // std::copy_constructible
    // std::move_constructible
    // は C++20 の標準ライブラリで定義されているコンセプト
    // よく使用するコンセプトは予め用意されている
    // ==============================================================================

    // コピー構築可能な型に制約
    template<std::copy_constructible T>
    void DummyCopy(T& obj) {
        T dummy = obj; // T をコピーして使う
    }

#ifdef CONCEPTS_MOVE
    // ムーブ構築可能な型に制約(コピーも必要なら requires ... && ... を使う)
    template<std::move_constructible T>
    void DummyCopy(T&& obj) {
        T dummy = std::move(obj); // T をムーブして使う
    }
#endif

    // 2 つ以上のコンセプトが必要な記述の方法
    // requires キーワードを使用して && や || でつなげる
    template<typename T>
    requires std::copy_constructible<T> && std::move_constructible<T>
    void DummyCopy(T&& obj) {
        T dummy = std::move(obj); // T をムーブして使う
    }

    // ==============================================================================
    // 制約式
    // ==============================================================================

    // 制約式
    // requires requires (T x, T y) { { x + y } -> std::same_as<T>; }
    // 最初の requires はキーワード、2番目の requires は式
    // 具体的な制約
    // { x + y } -> std::same_as<T>;
    // 
    // { x + y } の意味
    // x + y という式が有効である事 を意味する
    // 
    // -> std::same_as<T>  の意味
    // その式の評価結果の型が T と同じ型である事 を意味する
    template<typename T>
    T Add2(T a, T b) requires requires(T x, T y) { { x + y } -> std::same_as<T>; } {
        return a + b;
    }

    // ==============================================================================
    // concept を定義して(再)利用
    // 複数のテンプレートで同じ制約を使いたい場合や
    // 制約に分かりやすい名前を付けたい場合
    // ==============================================================================

    // 加算可能な型 Addable を定義
    template<typename T>
    concept Addable = requires(T a, T b)
    {
        { a + b } -> std::same_as<T>;
    };

    // 定義したコンセプトをテンプレート引数に直接適用する
    template<Addable T>
    T Add2Concept(T a, T b) {
        return a + b;
    }
}

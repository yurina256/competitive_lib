#pragma once
#include <string>
#include <cctype>
#include <stdexcept>

/**
 * @brief 再帰下降構文解析 (Recursive Descent Parsing) のテンプレート
 * 
 * 典型的な四則演算の数式を解析・評価するクラスです。
 * 問題の文法定義に合わせて適宜各関数を拡張・変更して使用してください。
 * 
 * デフォルト文法 (EBNF):
 *   expr   = term, { ("+" | "-"), term } ;
 *   term   = factor, { ("*" | "/"), factor } ;
 *   factor = number | "(", expr, ")" ;
 *   number = digit, { digit } ;
 */
struct Parser {
  std::string s;
  int pos;

  Parser(const std::string& s) : s(s), pos(0) {}

  /**
   * @brief 現在の文字を先読みする (ポインタは進めない)
   */
  char peek() const {
    if (pos >= (int)s.size()) return '\0';
    return s[pos];
  }

  /**
   * @brief ポインタを1つ進める
   */
  void next() {
    pos++;
  }

  /**
   * @brief 期待された文字であるか確認し、消費する
   */
  void consume(char expected) {
    if (peek() != expected) {
      throw std::runtime_error("Unexpected character: expected '" + std::string(1, expected) + "', got '" + std::string(1, peek()) + "'");
    }
    next();
  }

  /**
   * @brief 式 (expr) のパース
   */
  long long expr() {
    long long val = term();
    while (true) {
      if (peek() == '+') {
        next();
        val += term();
      } else if (peek() == '-') {
        next();
        val -= term();
      } else {
        break;
      }
    }
    return val;
  }

  /**
   * @brief 項 (term) のパース
   */
  long long term() {
    long long val = factor();
    while (true) {
      if (peek() == '*') {
        next();
        val *= factor();
      } else if (peek() == '/') {
        next();
        long long div = factor();
        if (div == 0) throw std::runtime_error("Division by zero");
        val /= div;
      } else {
        break;
      }
    }
    return val;
  }

  /**
   * @brief 因子 (factor) のパース
   */
  long long factor() {
    if (peek() == '(') {
      next(); // '(' を消費
      long long val = expr();
      consume(')'); // ')' を消費
      return val;
    }
    return number();
  }

  /**
   * @brief 数値 (number) のパース
   */
  long long number() {
    long long val = 0;
    if (!std::isdigit(peek())) {
      throw std::runtime_error("Digit expected");
    }
    while (std::isdigit(peek())) {
      val = val * 10 + (peek() - '0');
      next();
    }
    return val;
  }
};

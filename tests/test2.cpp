#include <Account.h>
#include <Transaction.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

inline bool operator==(Account a, Account b) { return true; }

class MockAccount: public Account{
  public:
  MockAccount(int id, int balance):Account(id, balance){}
  MOCK_METHOD(int, GetBalance, (), (const, override));
  MOCK_METHOD(void, ChangeBalance, (int diff), (override));
  MOCK_METHOD(void, Lock, (), (override));
  MOCK_METHOD(void, Unlock, (), (override));
};

class MockTransaction: public Transaction{
  public:
  MOCK_METHOD(void, SaveToDataBase, (Account& from, Account& to, int sum), (override));
};

//Тестирование класса Transaction

TEST(Transaction, SaveToDataBase) {
  MockTransaction tr;
  MockAccount from(1, 500);
  MockAccount to(2, 400);
  EXPECT_CALL(tr, SaveToDataBase(from, to, 150)).Times(1);
  tr.SaveToDataBase(from, to, 150);
}

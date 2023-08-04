#include <gtest/gtest.h>

#include </usr/local/lib/QtCore.framework/Versions/A/Headers/QChar>
#include </usr/local/lib/QtCore.framework/Versions/A/Headers/QString>

// Пример тестового класса для QString
class QStringTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Инициализация перед каждым тестом
    str = "Hello, World!";
  }

  void TearDown() override {
    // Очистка после каждого теста
  }

  QString str;
};

// Пример теста для проверки длины QString
TEST_F(QStringTest, LengthTest) { EXPECT_EQ(str.length(), 13); }

// Пример теста для проверки содержимого QString
TEST_F(QStringTest, ContentTest) {
  EXPECT_STREQ(str.toStdString().c_str(), "Hello, World!");
}

// Запуск всех тестов
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

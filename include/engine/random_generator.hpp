#include <cstdlib>
#include <ctime>
namespace engine {
class RandomGenerator {
public:
  RandomGenerator() = delete;

  static int getInt(int min, int max) {
    static bool initialized = init();
    (void)initialized;
    return min + std::rand() % (max - min + 1);
  }

private:
  static bool init() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    return true;
  }
};
} // namespace engine

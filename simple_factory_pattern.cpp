#include <iostream>

class Dog {
  public:
    virtual void show_temperament() = 0;
    virtual ~Dog() {};
};

class FrenchBulldog : public Dog {
  public:
    void show_temperament() override {
        std::cout << "Show affectionate..." << std::endl;
    }
};

class LabradorRetriever : public Dog {
  public:
    void show_temperament() override {
        std::cout << "Show friendly..." << std::endl;
    }
};

enum class Type : char {
    kFrenchBulldog,
    kLabradorRetriever
};

class DogFactory {
  public:
    Dog* create_dog(Type type) {
        Dog* dog_ptr = nullptr;

        if (type == Type::kFrenchBulldog) {
            dog_ptr = new FrenchBulldog;
        } else if (type == Type::kLabradorRetriever) {
            dog_ptr = new LabradorRetriever;
        }

        return dog_ptr;
    }
};

int main() {
    DogFactory* dog_factory = new DogFactory;

    Dog* dog = dog_factory->create_dog(Type::kLabradorRetriever);

    dog->show_temperament();

    delete dog_factory;
    delete dog;

    return 0;
}
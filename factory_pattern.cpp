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

class DogFactory {
  public:
    virtual ~DogFactory() {};
    virtual Dog* create_dog() = 0;
};

class FrenchBulldogFactory : public DogFactory {
  public:
    Dog* create_dog() override {
        return new FrenchBulldog;
    }
};

class LabradorRetrieverFactory : public DogFactory {
    public:
      Dog* create_dog() override {
          return new LabradorRetriever;
      }
  };

int main() {
    DogFactory* factory = new LabradorRetrieverFactory;

    Dog* dog = factory->create_dog();

    dog->show_temperament();

    delete factory;
    delete dog;

    return 0;
}
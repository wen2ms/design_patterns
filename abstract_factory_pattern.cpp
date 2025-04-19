#include <iostream>

class ShipBody {
  public:
    virtual ~ShipBody() {}

    virtual std::string get_body() = 0;
};

class WoodBody : public ShipBody {
  public:
    std::string get_body() override {
        return std::string("The ship body is made of <wood>...");
    }
};

class IronBody : public ShipBody {
  public:
    std::string get_body() override {
        return std::string("The ship body is made of <iron>...");
    }
};

class MetalBody : public ShipBody {
  public:
    std::string get_body() override {
        return std::string("The ship body is made of <metal>...");
    }
};

class Engine {
  public:
    virtual ~Engine() {}

    virtual std::string get_engine() = 0;
};

class Human : public Engine {
  public:
    std::string get_engine() override {
        return "The ship engine is <human>...";
    }
};

class Diesel : public Engine {
  public:
    std::string get_engine() override {
        return "The ship engine is <diesel>...";
    }
};

class Nuclear : public Engine {
  public:
    std::string get_engine() override {
        return "The ship engine is <nuclear>...";
    }
};

class Weapon {
  public:
    virtual ~Weapon() {}

    virtual std::string get_weapon() = 0;
};

class Gun : public Weapon {
  public:
    std::string get_weapon() override {
        return std::string("The ship weapon is <gun>...");
    }
};

class Laser : public Weapon {
  public:
    std::string get_weapon() override {
        return std::string("The ship weapon is <laser>...");
    }
};

class Cannon : public Weapon {
  public:
    std::string get_weapon() override {
        return std::string("The ship weapon is <cannon>...");
    }
};

class Ship {
  public:
    Ship(ShipBody* ship_body, Engine* engine, Weapon* weapon) : ship_body_(ship_body), engine_(engine), weapon_(weapon) {};
    ~Ship() {
        delete ship_body_;
        delete engine_;
        delete weapon_;
    }

    std::string get_property() {
        std::string info = ship_body_->get_body() + engine_->get_engine() + weapon_->get_weapon();

        return info;
    }

  private:
    ShipBody* ship_body_;
    Engine* engine_;
    Weapon* weapon_;
};

class AbstractFactory {
  public:
    virtual ~AbstractFactory() {}

    virtual Ship* create_ship() = 0;
};

class BasicFactory : public AbstractFactory {
  public:
    Ship* create_ship() override {
        Ship* ship = new Ship(new WoodBody, new Human, new Gun);
        std::cout << "<Basic> ship has been created..." << std::endl;

        return ship;
    }
};

class StandardFactory : public AbstractFactory {
  public:
    Ship* create_ship() override {
        Ship* ship = new Ship(new IronBody, new Diesel, new Cannon);
        std::cout << "<Standard> ship has been created..." << std::endl;

        return ship;
    }
};

class UltraFactory : public AbstractFactory {
  public:
    Ship* create_ship() override {
        Ship* ship = new Ship(new MetalBody, new Nuclear, new Laser);
        std::cout << "<Ultra> ship has been created..." << std::endl;

        return ship;
    }
};

int main() {
    AbstractFactory* factroy = new UltraFactory;
    Ship* ship = factroy->create_ship();

    std::cout << ship->get_property() << std::endl;

    delete factroy;
    delete ship;

    return 0;
}
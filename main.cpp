#include <iostream>
#include <string>
#include <map>
#include "dict.h"

template<class Key>
class not_found : public not_found_exception<Key>
{
public:
    not_found() = delete;
    not_found(Key in_key) : _key(in_key) { }
    const Key& get_key() const noexcept override
    {
        return _key;
    }
private:
    Key _key;
};

template<class Key, class Value>
class dict : public dictionary<Key, Value>
{
public:
    const Value& get(const Key& key) const override
    {
        if (!is_set(key)) {
            throw not_found<Key>(key);
        }
        return _data.at(key);
    }
    void set(const Key& key, const Value& value) override
    {
        _data[key] = value;
    }
    bool is_set(const Key& key) const override
    {
        return _data.find(key) != _data.end();
    }
private:
    std::map<Key, Value> _data;
};

int main()
{
    dict<int, std::string> Dict;
    Dict.set(0, "Hello");
    Dict.set(1, "World");
    std::cout << Dict.get(0) << " " << Dict.get(1) << std::endl;
    try {
        Dict.get(2);
    }
    catch(not_found<int> e) {
        std::cerr << "Missing key is \"" << e.get_key() << "\"" << std::endl;
        return 1;
    }
    return 0;
}